//==================================================================================================
//===================================== EX-GAMES GAMESERVER PROJECT ================================
//==================================================================================================
// File:          Reset.cpp
// Description:   Reset System
// Last Edit:     2.04.2013
//==================================================================================================
// Code: DangeR Skype: muonline.bk
//==================================================================================================
#include "USER.h"
#include "Defines.h"
#include "StdAfx.h"
#include "CQuery.h"
#include "Protocol.h"
#include "Message.h"
#include "AddFunctions.h"
#include "Quest_PGW.h"


//	Конфигурации
//==============
int EnableResSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\Reset.ini");
int multEn = GetPrivateProfileInt("Common","multEn",0,"..\\Settings\\Reset.ini");

int MaxRes = GetPrivateProfileInt("Common","Max.res",100,"..\\Settings\\Reset.ini");
int Needlvl = GetPrivateProfileInt("Common","Need.lvl",400,"..\\Settings\\Reset.ini");
int Needzen = GetPrivateProfileInt("Common","Need.zen",10000000,"..\\Settings\\Reset.ini");
int Dkpoints = GetPrivateProfileInt("Common","Dk.points",600,"..\\Settings\\Reset.ini");
int Dwpoints = GetPrivateProfileInt("Common","Dw.points",600,"..\\Settings\\Reset.ini");
int Elfpoints = GetPrivateProfileInt("Common","Elf.points",600,"..\\Settings\\Reset.ini");
int Mgpoints = GetPrivateProfileInt("Common","Mg.points",700,"..\\Settings\\Reset.ini");
int Dlpoints = GetPrivateProfileInt("Common","Dl.points",700,"..\\Settings\\Reset.ini");

int AddGemOn = GetPrivateProfileInt("Common","AddGemOn",0,"..\\Settings\\Reset.ini");
int AddGem = GetPrivateProfileInt("Common","AddGem",0,"..\\Settings\\Reset.ini");
// Функция выполнения
//===================
void FunctionReset (DWORD gObjId,char UserName[11]) 
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	
	exQueryUpdate("UPDATE Character SET Resets = Resets + 1 WHERE Name='%s'", UserName);

	if(AddGemOn)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'",AddGem,gObj->AccountID);
	}

	//MySQL.Execute("SELECT Resets FROM Character WHERE Name='%s'",UserName);
	//int UserRes = MySQL.GetInt();
	int UserRes = ( ExUser[gObjId].Resets + 1 );
	int NumRes = 0;

	switch(gObj->Class)
	{
		case 0: NumRes = UserRes*Dwpoints; break;
		case 1: NumRes = UserRes*Dkpoints; break;
		case 2: NumRes = UserRes*Elfpoints;break;
		case 3: NumRes = UserRes*Mgpoints; break;
		case 4: NumRes = UserRes*Dlpoints; break;
	}
	int NewNeedZen(0);
	if(multEn)
	{
		NewNeedZen = UserRes * Needzen;
		gObj->Money = gObj->Money - NewNeedZen;
	}
	else
		gObj->Money = gObj->Money - Needzen;

	gObj->Level = 1;
	gObj->Experience = 0;
	gObj->Strength = 25;
	gObj->Dexterity = 25;
	gObj->Vitality = 25;
	gObj->Energy = 25;
	if(gObj->Class == 4)
		gObj->Leadership = 25;
	//MySQL.Execute("SELECT gr_res FROM Character WHERE Name='%s'",UserName);
	//int UserRangs = MySQL.GetInt();
	int UserRangs = ExUser[gObjId].GResets;
	int EnableRangSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\GrandReset.ini");
	if(EnableRangSys == 1 && UserRangs > 0)
	{
		//GRand Reset Configs
		int GDkpoints = GetPrivateProfileInt("Common","Dk.points",600,"..\\Settings\\GrandReset.ini");
		int GDwpoints = GetPrivateProfileInt("Common","Dw.points",600,"..\\Settings\\GrandReset.ini");
		int GElfpoints = GetPrivateProfileInt("Common","Elf.points",600,"..\\Settings\\GrandReset.ini");
		int GMgpoints = GetPrivateProfileInt("Common","Mg.points",700,"..\\Settings\\GrandReset.ini");
		int GDlpoints = GetPrivateProfileInt("Common","Dl.points",700,"..\\Settings\\GrandReset.ini");
		int GNumRes(0);
		switch(gObj->Class)
		{
			case 0: GNumRes = UserRangs*GDwpoints;break;
			case 1: GNumRes = UserRangs*GDkpoints;break;
			case 2: GNumRes = UserRangs*GElfpoints;break;
			case 3: GNumRes = UserRangs*GMgpoints;break;
			case 4: GNumRes = UserRangs*GDlpoints;break;
		}
		gObj->LevelUpPoint = GNumRes + NumRes + ExUser[gObjId].Ex_FreePoints;
	}
	else
	{
		gObj->LevelUpPoint = NumRes + ExUser[gObjId].Ex_FreePoints;
	}


}
// Функция проверки
//=================
void CheckReset (int aIndex)
{
	if(!EnableResSys)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//MySQL.Execute("SELECT Resets FROM Character WHERE Name='%s'",gObj->Name);
	//int UserReset = MySQL.GetInt();
	int UserReset = ExUser[aIndex].Resets;
	int ifNeedzen(0);
	if(multEn)
		ifNeedzen = (UserReset+1)*Needzen;
	else
		ifNeedzen = Needzen;

	if(gObj->pInventory[WEAPON_01].m_Type == -1&&gObj->pInventory[WEAPON_02].m_Type == -1&&gObj->pInventory[HELMET].m_Type == -1&&
	   gObj->pInventory[ARMOR].m_Type == -1&&gObj->pInventory[PANTS].m_Type == -1&&gObj->pInventory[GLOVES].m_Type == -1&&
	   gObj->pInventory[BOOTS].m_Type == -1&&gObj->pInventory[WINGS].m_Type == -1&&gObj->pInventory[GUARDIAN].m_Type == -1&&
	   gObj->pInventory[PENDANT].m_Type == -1&&gObj->pInventory[RING_01].m_Type == -1&&gObj->pInventory[RING_02].m_Type == -1)
	{
		if(UserReset<MaxRes)
		{
			if(gObj->Level >= Needlvl)
			{
				if(gObj->Money >= ifNeedzen)
				{
					MsgNormal(aIndex,"[Reset] Start Reset");

					FireCracker(aIndex, gObj->X, gObj->Y);
					gObjCloseSet(aIndex, 1);
					FunctionReset (aIndex,gObj->Name);
					GCMoneySend(gObj->m_Index, gObj->Money);	
				}
				else
				{
					MsgNormal(aIndex,"[Reset] You need above %d Zen to Reset",ifNeedzen);
				}
			}
			else
			{	
				MsgNormal(aIndex,"[Reset] You need above %d lvl to Reset",Needlvl);
			}
		}
		else
		{
			MsgNormal(aIndex,"[Reset] Max Reset %d",UserReset);
		}
	}
	else
	{
		MsgNormal(aIndex,"[Reset] Чар должен быть раздет");
	}
	
}