//==================================================================================================
//===================================== EX-GAMES GAMESERVER PROJECT ================================
//==================================================================================================
// File:          NPCTeleport.cpp
// Description:   Teleport System
// Last Edit:     20.02.2013
//==================================================================================================
// Code: DangeR Skype: muonline.bk
//==================================================================================================
#include "StdAfx.h"
#include "USER.h"
#include "Defines.h"
#include "Message.h"
#include "CQuery.h"


//=========================
//		Конфигурации
//=========================
int NPCTeleportEnable = GetPrivateProfileInt("Common","NPCTeleportEnable",0,"..\\Settings\\NPCTeleport.ini");
int NPCTNumber = GetPrivateProfileInt("Common","NPCNumber",371,"..\\Settings\\NPCTeleport.ini");
int NPCTMap = GetPrivateProfileInt("Common","NPCMap",0,"..\\Settings\\NPCTeleport.ini");
int NPCTX = GetPrivateProfileInt("Common","NPC_X",140,"..\\Settings\\NPCTeleport.ini");
int NPCTY = GetPrivateProfileInt("Common","NPC_Y",140,"..\\Settings\\NPCTeleport.ini");
int NPCTRusMSG = GetPrivateProfileInt("Common","RussianMsg",1,"..\\Settings\\NPCTeleport.ini");

int NPCTCheckLvl = GetPrivateProfileInt("Check","CheckLevel",1,"..\\Settings\\NPCTeleport.ini");
int NPCTCheckRes = GetPrivateProfileInt("Check","CheckReset",1,"..\\Settings\\NPCTeleport.ini");
int NPCTCheckGR = GetPrivateProfileInt("Check","CheckGrandReset",1,"..\\Settings\\NPCTeleport.ini");
int NPCTCheckZen = GetPrivateProfileInt("Check","CheckZen",1,"..\\Settings\\NPCTeleport.ini");
int NPCTCheckGem = GetPrivateProfileInt("Check","CheckGem",1,"..\\Settings\\NPCTeleport.ini");

int NPCTMinLevel = GetPrivateProfileInt("Config","MinLevel",1,"..\\Settings\\NPCTeleport.ini");
int NPCTMaxLevel = GetPrivateProfileInt("Config","MaxLevel",400,"..\\Settings\\NPCTeleport.ini");
int NPCTMinReset = GetPrivateProfileInt("Config","MinReset",0,"..\\Settings\\NPCTeleport.ini");
int NPCTMaxReset = GetPrivateProfileInt("Config","MaxReset",100,"..\\Settings\\NPCTeleport.ini");
int NPCTMinGReset = GetPrivateProfileInt("Config","MinGReset",0,"..\\Settings\\NPCTeleport.ini");
int NPCTMaxGReset = GetPrivateProfileInt("Config","MaxGReset",100,"..\\Settings\\NPCTeleport.ini");
int NPCTZenPrice = GetPrivateProfileInt("Config","ZenPrice",0,"..\\Settings\\NPCTeleport.ini");
int NPCTGemPrice = GetPrivateProfileInt("Config","GemPrice",0,"..\\Settings\\NPCTeleport.ini");

int NPCTeleport_Map = GetPrivateProfileInt("Teleport","Teleport_Map",0,"..\\Settings\\NPCTeleport.ini");
int NPCTeleport_X = GetPrivateProfileInt("Teleport","Teleport_X",123,"..\\Settings\\NPCTeleport.ini");
int NPCTeleport_Y = GetPrivateProfileInt("Teleport","Teleport_Y",123,"..\\Settings\\NPCTeleport.ini");

void NPCTeleportStart (int aIndex,int aNPC)
{
	if(!NPCTeleportEnable)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);
	if ((gObjNPC->Class == NPCTNumber) && (gObjNPC->MapNumber == NPCTMap) && (gObjNPC->X == NPCTX) && (gObjNPC->Y == NPCTY)) 
	{

		//Проверка на Grand Reset
		if(NPCTCheckGR==1)
		{
			int EnableRangSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\GrandReset.ini");
			if(EnableRangSys==1)
			{
				//MySQL.Execute("SELECT gr_res FROM Character WHERE Name='%s'",gObj->Name);
				//int UserRang = MySQL.GetInt();
				//ExUser[aIndex].GResets
				if(NPCTMinGReset > ExUser[aIndex].GResets)
				{
					char MinGR_MSG[70];
					if(!NPCTRusMSG)
						sprintf(MinGR_MSG, "Sorry, teleport needs %d Grand Reset",NPCTMinGReset);
					else
						sprintf(MinGR_MSG, "Извините, для телепорта необходим %d Гранд ресет",NPCTMinGReset);
					ChatTargetSendNogs(gObjNPC,MinGR_MSG,aIndex);
					return;
				}
				if(ExUser[aIndex].GResets > NPCTMaxGReset)
				{
					char MaxGR_MSG[70];
					if(NPCTRusMSG)
						sprintf(MaxGR_MSG, "Извините, я телепортирую персонажей до %d Гранд ресета",NPCTMaxGReset);
					else
						sprintf(MaxGR_MSG, "Sorry, I teleport characters to %d Grand Reset",NPCTMaxGReset);
					ChatTargetSendNogs(gObjNPC,MaxGR_MSG,aIndex);
					return;
				}
			}
		}
		//Проверка на ресет
		if(NPCTCheckRes==1)
		{
			int EnableResSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\Reset.ini");
			if(EnableResSys==1)
			{
				//MySQL.Execute("SELECT Resets FROM Character WHERE Name='%s'",gObj->Name);
				//int UserReset = MySQL.GetInt();
				
				if(NPCTMinReset > ExUser[aIndex].Resets)
				{
					char MinR_MSG[70];
					if(!NPCTRusMSG)
						sprintf(MinR_MSG, "Sorry, teleport needs %d Reset",NPCTMinReset);
					else
						sprintf(MinR_MSG, "Извините, для телепорта необходим %d Ресета",NPCTMinReset);
					ChatTargetSendNogs(gObjNPC,MinR_MSG,aIndex);
					return;
				}
				if(ExUser[aIndex].Resets > NPCTMaxReset)
				{
					char MaxR_MSG[70];
					if(NPCTRusMSG)
						sprintf(MaxR_MSG, "Извините, я телепортирую персонажей до %d Ресета",NPCTMaxReset);
					else
						sprintf(MaxR_MSG, "Sorry, I teleport characters to %d Resets",NPCTMaxReset);
					ChatTargetSendNogs(gObjNPC,MaxR_MSG,aIndex);
					return;
				}
			}
		}
		//Проверка на уровень
		if(NPCTCheckLvl==1)
		{
			if(NPCTMinLevel > gObj->Level)
			{
				char MinL_MSG[70];
				if(NPCTRusMSG)
					sprintf(MinL_MSG, "Извините, для телепорта необходим %d Уровень",NPCTMinLevel);
				else
					sprintf(MinL_MSG, "Sorry, I teleport characters to %d Level",NPCTMinLevel);
				ChatTargetSendNogs(gObjNPC,MinL_MSG,aIndex);
				return;
			}
			if(gObj->Level > NPCTMaxLevel)
			{
				char MaxL_MSG[70];
				if(NPCTRusMSG)
					sprintf(MaxL_MSG, "Извините, я телепортирую персонажей до %d Уровня",NPCTMaxLevel);
				else
					sprintf(MaxL_MSG, "Sorry, I teleport characters to %d Level",NPCTMaxLevel);
				ChatTargetSendNogs(gObjNPC,MaxL_MSG,aIndex);
				return;
			}
		}
		//Проверка на Gem
		if(NPCTCheckGem==1)
		{
			int MyGem = exQueryReturnInt("SELECT CashPoint FROM MEMB_INFO WHERE memb___id='%s'", gObj->AccountID);
			if(NPCTGemPrice > MyGem)
			{
				char GEM_MSG[70];
				if(NPCTRusMSG)
					sprintf(GEM_MSG, "Извините, для телепорта нужно иметь %d Gem",NPCTGemPrice);
				else
					sprintf(GEM_MSG, "Sorry, you need to have to teleport %d Gem",NPCTGemPrice);
				ChatTargetSendNogs(gObjNPC,GEM_MSG,aIndex);
				return;
			}
		}
		//Проверка на Зен
		if(NPCTCheckZen==1)
		{
			if(NPCTZenPrice > gObj->Money)
			{
				char ZEN_MSG[70];
				if(NPCTRusMSG)
					sprintf(ZEN_MSG, "Извините, для телепорта нужно иметь %d Zen",NPCTZenPrice);
				else
					sprintf(ZEN_MSG, "Sorry, you need to have to teleport %d Zen",NPCTZenPrice);
				ChatTargetSendNogs(gObjNPC,ZEN_MSG,aIndex);
				return;
			}
		}
		//////////////////
		//	Выполнение	// 
		//////////////////
		if(NPCTCheckGem==1)
		{
			exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint - %d WHERE memb___id='%s'", NPCTGemPrice, gObj->AccountID);
			MsgNormal(aIndex,"[Teleport]Price: %d GEM",NPCTGemPrice);
		}
		if(NPCTCheckZen==1)
		{
			gObj->Money = gObj->Money - NPCTZenPrice;
			GCMoneySend(gObj->m_Index, gObj->Money);
			MsgNormal(aIndex,"[Teleport]Price: %d Zen",NPCTZenPrice);
		}
		gObjTeleport(aIndex, NPCTeleport_Map, NPCTeleport_X, NPCTeleport_Y);
	}	
}










