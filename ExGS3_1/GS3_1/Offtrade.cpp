//==================================================================================================
//=====================================AROTH GAMESERVER PROJECT=====================================
//==================================================================================================
// File:          Offtrade.cpp
// Description:   Offline Trade System
// Last Edit:     02.10.2011
//==================================================================================================
// Code: SmallHabit, Imposible, Crazzy
//==================================================================================================
#include "OffTrade.h"
#include "Protocol.h"
#include <WinSock2.h>
#include "USER.h"
#include "Defines.h"
#include "Message.h"

#include "SystemBrother.h"
//==================================================================================================
// Offline Trade System
//==================================================================================================
CRITICAL_SECTION criti;
COFFTrade OFFTrade;
OFFLINETRADE OfflineShop[OBJECT_MAX];
int OffPrice = GetPrivateProfileInt("Common","CreateCost",250000,"..\\Settings\\OffTrade.ini");
int MapAllow = GetPrivateProfileInt("MapSystem","Enable",1,"..\\Settings\\OffTrade.ini");
int MessageAll = GetPrivateProfileInt("Common","MessageAllEnable",0,"..\\Settings\\OffTrade.ini");
int Map1 = GetPrivateProfileInt("MapSystem","Map1",0,"..\\Settings\\OffTrade.ini");
int Map2 = GetPrivateProfileInt("MapSystem","Map2",3,"..\\Settings\\OffTrade.ini");
int Map3 = GetPrivateProfileInt("MapSystem","Map3",2,"..\\Settings\\OffTrade.ini");

//==========================
// Functions Hook
//==========================
void COFFTrade::Init()
{
	 HookThis((DWORD)&CloseClient2Hook,0x00405CA4);//finished
	 HookThis((DWORD)&CGPShopAnsCloseHook,0x00404552);//finished
	 HookThis((DWORD)&ResponErrorCloseClientHook,0x0040422D);
	 HookThis((DWORD)&CloseClientHook,0x00407E82);//finished
}

//==========================
// OffTrade Create
//==========================
void COFFTrade::CreateOfflineTrade(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->m_bPShopOpen == false)
	{
		MsgNormal(aIndex,"[OffTrade] You need create Personal Store to use this command");
		return;
	}
	else 
	{
		if(MapAllow == 1)
		{
			if(gObj->MapNumber == Map1 || gObj->MapNumber == Map2 || gObj->MapNumber == Map3)
			{
				if(MessageAll)
				{
					if(gObj->MapNumber==0)
						MessaageAllGlobal("[OffTrade][%s] Lorencia %d %d",gObj->Name,gObj->X,gObj->Y);
					else if(gObj->MapNumber==2)
						MessaageAllGlobal("[OffTrade][%s] Devias %d %d",gObj->Name,gObj->X,gObj->Y);
					else if(gObj->MapNumber==3)
						MessaageAllGlobal("[OffTrade][%s] Noria %d %d",gObj->Name,gObj->X,gObj->Y);
				}
				(gObj->Money -= OffPrice);
				GCMoneySend(gObj->m_Index, gObj->Money);
				OfflineShop[aIndex].IsOffTrade=1;
				//SQL.OffTradeOn(aIndex);
				CloseClient(aIndex);
				return;
			}
		MsgNormal(aIndex,"[OffTrade] OffTrade work only special maps");
		return;
		}
	}
	if(MapAllow == 0)
	{
		if(MessageAll)
		{
			if(gObj->MapNumber==0)
				MessaageAllGlobal("[OffTrade][%s] Lorencia %d %d",gObj->Name,gObj->X,gObj->Y);
			else if(gObj->MapNumber==2)
				MessaageAllGlobal("[OffTrade][%s] Devias %d %d",gObj->Name,gObj->X,gObj->Y);
			else if(gObj->MapNumber==3)
				MessaageAllGlobal("[OffTrade][%s] Noria %d %d",gObj->Name,gObj->X,gObj->Y);
		}
		//Log.GameLogs("[OffTrade][Open] Name: %s",gObj->Name);
		(gObj->Money -= OffPrice);
	    GCMoneySend(gObj->m_Index, gObj->Money);
		OfflineShop[aIndex].IsOffTrade=1;
		//SQL.OffTradeOn(aIndex);
		CloseClient(aIndex);
		//int TimeDelayCorrect = ( 60 - t.GetSecond() ) * 1000;
		//Sleep(TimeDelayCorrect);	
		return;
	}
}

//==========================
// Shop Close
//==========================
void CGPShopAnsCloseHook(int aIndex, BYTE btResult)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//Log.GameLogs("[OffTrade][Close] Name: %s",gObj->Name);
    if(OfflineShop[aIndex].IsOffTrade)
		gObjDel(aIndex);

	OfflineShop[aIndex].IsOffTrade = 0;
	//SQL.OffTradeOff(aIndex);
	CGPShopAnsClose(aIndex,btResult);
}

//==========================
// Client Close
//==========================
void CloseClientHook(int aIndex)
{	
	if ( aIndex < 0 || aIndex > OBJECT_MAX-1 )
	{
		return;
	}

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//Log.GameLogs("[OffTrade][Close] Name: %s",gObj->Name);
	if ( gObj->Connected == PLAYER_EMPTY )
	{	
		return;
	}

	if(OfflineShop[aIndex].IsOffTrade != 0)
	{	
		gObj->CheckTick = GetTickCount();
		return; 
	}

	if(ExUser[aIndex].OffAfk)
	{
		gObj->CheckTick = GetTickCount();
		return; 
	}

	//#############################################
	if(SystemBrother.User[aIndex].Off != 0)
	{	
		gObj->CheckTick = GetTickCount();
		return; 
	}
	//#############################################

	if(gObj->m_socket != INVALID_SOCKET)
	{
		closesocket(gObj->m_socket );
		gObj->m_socket = INVALID_SOCKET;
		//SQL.OffTradeOff(aIndex);
	}
}

//==========================
// Error Checker
//==========================
void ResponErrorCloseClientHook(int aIndex)
{	
	if ( aIndex < 0 || aIndex > OBJECT_MAX-1 )
	{	
		//g_Console.ConsoleOutput(1,"error-L1 : CloseClient index error");
		//return;
	}
	
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//Log.GameLogs("[OffTrade][Close] Name: %s",gObj->Name);
	if ( gObj->Connected == PLAYER_EMPTY )
	{
		return;
	}

	if(ExUser[aIndex].OffAfk)
	{
		gObj->CheckTick = GetTickCount();
		return; 
	}

	if(OfflineShop[aIndex].IsOffTrade != 0)
	{	
		gObj->CheckTick = GetTickCount();
		return; 
	}

	//#############################################
	if(SystemBrother.User[aIndex].Off != 0)
	{	
		gObj->CheckTick = GetTickCount();
		return; 
	}
	//#############################################

	closesocket(gObj->m_socket);
	gObj->m_socket = INVALID_SOCKET;

	if ( gObj->m_socket == INVALID_SOCKET )
	{
	}
	
	if(gObj->m_socket != INVALID_SOCKET)
		//SQL.OffTradeOff(aIndex);
		gObjDel(aIndex);
}

//==========================
// Client Close 2
//==========================
void CloseClient2Hook(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result)
{
    int index = -1;
    index = lpPerSocketContext->nIndex ;    

	if ( index >= OBJECT_MIN && index < OBJECT_MAX )
	{	
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER(index);
		//Log.GameLogs("[OffTrade][Close] Name: %s",gObj->Name);
		if(OfflineShop[index].IsOffTrade != 0)
        {	
			gObj->CheckTick = GetTickCount();
			return; 
		}

		if(ExUser[index].OffAfk)
		{
			gObj->CheckTick = GetTickCount();
			return; 
		}

		//#############################################
		if(SystemBrother.User[index].Off != 0)
		{	
			gObj->CheckTick = GetTickCount();
			return; 
		}
		//#############################################

		if ( gObj->m_socket != INVALID_SOCKET )
		{
			if (closesocket(gObj->m_socket) == -1 )
			{
				if (WSAGetLastError() != WSAENOTSOCK)
				{
					return;
				}
			}

			gObj->m_socket = INVALID_SOCKET;
		}
		//SQL.OffTradeOff(index);
		gObjDel(index);
	}
}