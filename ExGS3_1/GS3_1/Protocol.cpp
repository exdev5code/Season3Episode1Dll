#include "USER.h"
#include "Defines.h"
#include <time.h>
#include "StdAfx.h"
#include "Commands.h"
#include "Jewels.h"
#include "Offtrade.h"
#include "Buffer.h"
#include "AddFunctions.h"
#include "NPCTeleport.h"
#include "AddFunctions.h"
#include "CQuery.h"
#include "ChaosMix.h"
#include "ExCore.h"
#include "Message.h"
#include "Protocol.h"
#include "AntiCheatPlus.h"

int AccMode = GetPrivateProfileInt("Connect","AccMode",1,"..\\Settings\\Connect.ini");
//==================================================================================================
// Protocol Core
//==================================================================================================
bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	switch(BYTE(protoNum))
	{
//==========================
// Chat Data Send
//==========================
	case 0x00: 
		ChatDataSend(aIndex,aRecv);
		break;
//==========================
// Connect Data
//==========================
	case 0x03: 
		ConnectStart(aIndex);
		break;
//==========================
// Item Recv Data
//==========================
	case 0x26: 
		CGUseItemRecv((PMSG_USEITEM *)aRecv, aIndex);
		break;
//==========================
// NPC Click Send&Recv
//==========================
	case 0x30: 
		ExClickNPC (aIndex,(aRecv[4] + aRecv[3] * 256));
		//NewNPC(aIndex,(aRecv[4] + aRecv[3] * 256));
		//NPCTeleportStart(aIndex,(aRecv[4] + aRecv[3] * 256));
		//NewResNPC(aIndex,(aRecv[4] + aRecv[3] * 256));
	//	g_Console.ConsoleOutput(4,"[DEBUG] [%s][%s] NPC Data Send",gObj->AccountID,gObj->Name);
		break;
//==========================
// ChaosBox Hook
//==========================
	case 0x86://Chaos Machine
		ChaosBoxHook(aIndex,aRecv[3]);
		break;
//==========================
// Login Data
//==========================
	case 0xF1:
		{
			int TradeMode = GetPrivateProfileInt("Common","TradeMode",1,"..\\Settings\\OffTrade.ini");
			if(TradeMode == 1 || AccMode == 1)
				OffTradeLogin(aIndex,aRecv);
		}
		break;
//==========================
// ExTeam Protocol
//==========================
	case 0xFB:
		{
			PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)aRecv;

			switch ( lpDef->subcode )
			{
				#if(ANTI_CHEAT_PLUS==TRUE)
				case 0xFE:
					g_AntiCheatPlus.CG_HddSend((CG_PMSG_HDDKEY*) aRecv, aIndex);
					break;
				case 0xFF:
					g_AntiCheatPlus.CG_Cheater((PMST_CheaterUser*) aRecv, aIndex);
					break;
				#endif
			}
			return true;
		}
		break;
	}

	DataRecv(protoNum,aRecv,aLen,aIndex,Encrypt,Serial);
	return true;
}

static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};
struct PMSG_IDPASS
{
	PBMSG_HEADIT h;
	BYTE subcode;	
	char Id[10];	
	char Pass[10];	
	DWORD TickCount;	
	BYTE CliVersion[5];	
	BYTE CliSerial[16];	 
};

void BuxConvert(char* buf, int size)
{
	for (int n=0;n<size;n++)
		buf[n]^=bBuxCode[n%3];
}

void OffTradeLogin(int aIndex,LPBYTE aRecv)
{
	PMSG_IDPASS *lpMsg = (PMSG_IDPASS*)aRecv;

	char AccountID[11];
	AccountID[10] = 0;
	char Password[11];
	Password[10] = 0;

	memcpy(AccountID,lpMsg->Id,sizeof(lpMsg->Id));
	memcpy(Password,lpMsg->Pass,sizeof(lpMsg->Pass));
	BuxConvert(AccountID,10);
	BuxConvert(Password,10);

	for(int i = OBJECT_MIN; i<OBJECT_MAX;i++)
	{
		OBJECTSTRUCT *lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(lpObj->Connected == 3)
		{
			if(!strcmp(AccountID,lpObj->AccountID))
			{
				if(OfflineShop[i].IsOffTrade == 1)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(i);
					OfflineShop[i].IsOffTrade = 0;
				}
				else if(ExUser[i].OffAfk == 1)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(i);
					ExUser[i].OffAfk = 0;
				}
				else if(AccMode == 1)
				{
					int AccModeOn = exQueryReturnInt("SELECT AccMode FROM MEMB_INFO WHERE memb___id='%s'", lpObj->AccountID);
					if(AccModeOn == 1)
					{
						CloseClient(lpObj->m_Index);
						GJPUserClose(lpObj->AccountID);
						gObjDel(i);
					}
				}	
				break;
			}
		}
	}
}

