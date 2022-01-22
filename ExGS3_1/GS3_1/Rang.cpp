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


//Функция Гранд Ресета
void GrandResetSystem (int aIndex)
{
	int EnableRangSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\GrandReset.ini");
	if(!EnableRangSys)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//Необходимый ресет
	int ResetTo = GetPrivateProfileInt("Common","Reset",100,"..\\Settings\\GrandReset.ini");
	//MySQL.Execute("SELECT Resets FROM Character WHERE Name='%s'",gObj->Name);
	//int UseRes = MySQL.GetInt();
	int UseRes = ExUser[aIndex].Resets;
	if(ResetTo>UseRes)
	{
		MsgNormal(aIndex,"[GReset] You need above %d Reset to GReset",ResetTo);
		return;
	}//Необходимый уровень
	int LevelTo = GetPrivateProfileInt("Common","Level",400,"..\\Settings\\GrandReset.ini");
	if(LevelTo>gObj->Level)
	{
		MsgNormal(aIndex,"[GReset] You need above %d Level to GReset",LevelTo);
		return;
	}//Необходимость рездеть чара
	if(gObj->pInventory[WEAPON_01].m_Type != -1&&gObj->pInventory[WEAPON_02].m_Type != -1&&gObj->pInventory[HELMET].m_Type != -1&&
	   gObj->pInventory[ARMOR].m_Type != -1&&gObj->pInventory[PANTS].m_Type != -1&&gObj->pInventory[GLOVES].m_Type != -1&&
	   gObj->pInventory[BOOTS].m_Type != -1&&gObj->pInventory[WINGS].m_Type != -1&&gObj->pInventory[GUARDIAN].m_Type != -1&&
	   gObj->pInventory[PENDANT].m_Type != -1&&gObj->pInventory[RING_01].m_Type != -1&&gObj->pInventory[RING_02].m_Type != -1)
	{
		MsgNormal(aIndex,"[GReset] Чар должен быть раздет");
		return;
	}//Максимальный Гранд ресет
	int MaxGR = GetPrivateProfileInt("Common","MaxGR",10,"..\\Settings\\GrandReset.ini");
	//MySQL.Execute("SELECT gr_res FROM Character WHERE Name='%s'",gObj->Name);
	//int UserRang = MySQL.GetInt();
	int UserRang = ExUser[aIndex].GResets;
	if(UserRang>=MaxGR)
	{
		MsgNormal(aIndex,"[Reset] Max GReset %d",MaxGR);
		return;
	}//Зен на Гранд ресет
	int multzen = GetPrivateProfileInt("Common","multzen",1,"..\\Settings\\GrandReset.ini");
	int Zen = GetPrivateProfileInt("Common","Zen",1,"..\\Settings\\GrandReset.ini");
	int newZen;
	if(multzen)
	{
		newZen = (UserRang+1)*Zen;
	}
	else
		newZen = Zen;
	if(gObj->Money < newZen)
	{
		MsgNormal(aIndex,"[Reset] You need above %d Zen to Reset",newZen);
		return;
	}//Выполнение Гра
	int Dkpoints = GetPrivateProfileInt("Common","Dk.points",600,"..\\Settings\\GrandReset.ini");
	int Dwpoints = GetPrivateProfileInt("Common","Dw.points",600,"..\\Settings\\GrandReset.ini");
	int Elfpoints = GetPrivateProfileInt("Common","Elf.points",600,"..\\Settings\\GrandReset.ini");
	int Mgpoints = GetPrivateProfileInt("Common","Mg.points",700,"..\\Settings\\GrandReset.ini");
	int Dlpoints = GetPrivateProfileInt("Common","Dl.points",700,"..\\Settings\\GrandReset.ini");
	MsgNormal(aIndex,"[GReset] Start Grand Reset");
	FireCracker(aIndex, gObj->X, gObj->Y);
	gObjCloseSet(aIndex, 1);

	exQueryUpdate("UPDATE Character SET gr_res = gr_res +1 WHERE Name='%s'", gObj->Name);

	exQueryUpdate("UPDATE Character SET Resets = 0 WHERE Name='%s'", gObj->Name);


	//MySQL.Execute("SELECT gr_res FROM Character WHERE Name='%s'",gObj->Name);
	//int NEWUserRang = MySQL.GetInt();
	int NEWUserRang = (UserRang + 1);
	int  NumRes;
	switch(gObj->Class)
	{
		case 0: NumRes = NEWUserRang*Dwpoints;break;
		case 1: NumRes = NEWUserRang*Dkpoints;break;
		case 2: NumRes = NEWUserRang*Elfpoints;break;
		case 3: NumRes = NEWUserRang*Mgpoints;break;
		case 4: NumRes = NEWUserRang*Dlpoints;break;
	}
	gObj->LevelUpPoint = ( NumRes + ExUser[aIndex].Ex_FreePoints );
	gObj->Money -= newZen;
	gObj->Level = 1;
	gObj->Experience = 0;
	gObj->Strength = 25;
	gObj->Dexterity = 25;
	gObj->Vitality = 25;
	gObj->Energy = 25;
	if(gObj->Class == 4)
		gObj->Leadership = 25;

	int AddGemOn = GetPrivateProfileInt("Common","AddGemOn",0,"..\\Settings\\GrandReset.ini");
	int AddGem = GetPrivateProfileInt("Common","AddGem",0,"..\\Settings\\GrandReset.ini");

	if(AddGemOn)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", AddGem, gObj->AccountID);
	}
}