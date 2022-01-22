#include "StdAfx.h"
#include "Defines.h"
#include "USER.h"
#include "Message.h"
#include "Map.h"
#include "LoraBattle.h"
#include "AddFunctions.h"

//Common Конфигурации
int EnablePvP = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\PvPSystem.ini");
int PlayerShowHp = GetPrivateProfileInt("Common","PlayerShowHp",0,"..\\Settings\\PvPSystem.ini");
int BossShowHp = GetPrivateProfileInt("Common","BossShowHp",0,"..\\Settings\\PvPSystem.ini");
int LoraRingPvP = GetPrivateProfileInt("Common","LoraRingPvP",0,"..\\Settings\\PvPSystem.ini");

//Map Конфигурации
int map00 = GetPrivateProfileInt("Map","Map00",0,"..\\Settings\\PvPSystem.ini");
int map01 = GetPrivateProfileInt("Map","Map01",0,"..\\Settings\\PvPSystem.ini");
int map02 = GetPrivateProfileInt("Map","Map02",0,"..\\Settings\\PvPSystem.ini");
int map03 = GetPrivateProfileInt("Map","Map03",0,"..\\Settings\\PvPSystem.ini");
int map04 = GetPrivateProfileInt("Map","Map04",0,"..\\Settings\\PvPSystem.ini");
int map05 = GetPrivateProfileInt("Map","Map05",0,"..\\Settings\\PvPSystem.ini");
int map06 = GetPrivateProfileInt("Map","Map06",0,"..\\Settings\\PvPSystem.ini");
int map07 = GetPrivateProfileInt("Map","Map07",0,"..\\Settings\\PvPSystem.ini");
int map08 = GetPrivateProfileInt("Map","Map08",0,"..\\Settings\\PvPSystem.ini");
int map09 = GetPrivateProfileInt("Map","Map09",0,"..\\Settings\\PvPSystem.ini");
int map10 = GetPrivateProfileInt("Map","Map10",0,"..\\Settings\\PvPSystem.ini");
int map11 = GetPrivateProfileInt("Map","Map11",0,"..\\Settings\\PvPSystem.ini");
int map12 = GetPrivateProfileInt("Map","Map12",0,"..\\Settings\\PvPSystem.ini");
int map13 = GetPrivateProfileInt("Map","Map13",0,"..\\Settings\\PvPSystem.ini");
int map14 = GetPrivateProfileInt("Map","Map14",0,"..\\Settings\\PvPSystem.ini");
int map15 = GetPrivateProfileInt("Map","Map15",0,"..\\Settings\\PvPSystem.ini");
int map16 = GetPrivateProfileInt("Map","Map16",0,"..\\Settings\\PvPSystem.ini");
int map17 = GetPrivateProfileInt("Map","Map17",0,"..\\Settings\\PvPSystem.ini");
int map18 = GetPrivateProfileInt("Map","Map18",0,"..\\Settings\\PvPSystem.ini");
int map19 = GetPrivateProfileInt("Map","Map19",0,"..\\Settings\\PvPSystem.ini");
int map20 = GetPrivateProfileInt("Map","Map20",0,"..\\Settings\\PvPSystem.ini");
int map21 = GetPrivateProfileInt("Map","Map21",0,"..\\Settings\\PvPSystem.ini");
int map22 = GetPrivateProfileInt("Map","Map22",0,"..\\Settings\\PvPSystem.ini");
int map23 = GetPrivateProfileInt("Map","Map23",0,"..\\Settings\\PvPSystem.ini");
int map24 = GetPrivateProfileInt("Map","Map24",0,"..\\Settings\\PvPSystem.ini");
int map25 = GetPrivateProfileInt("Map","Map25",0,"..\\Settings\\PvPSystem.ini");
int map26 = GetPrivateProfileInt("Map","Map26",0,"..\\Settings\\PvPSystem.ini");
int map27 = GetPrivateProfileInt("Map","Map27",0,"..\\Settings\\PvPSystem.ini");
int map28 = GetPrivateProfileInt("Map","Map28",0,"..\\Settings\\PvPSystem.ini");
int map29 = GetPrivateProfileInt("Map","Map29",0,"..\\Settings\\PvPSystem.ini");
int map30 = GetPrivateProfileInt("Map","Map30",0,"..\\Settings\\PvPSystem.ini");
int map31 = GetPrivateProfileInt("Map","Map31",0,"..\\Settings\\PvPSystem.ini");
int map32 = GetPrivateProfileInt("Map","Map32",0,"..\\Settings\\PvPSystem.ini");
int map33 = GetPrivateProfileInt("Map","Map33",0,"..\\Settings\\PvPSystem.ini");
int map34 = GetPrivateProfileInt("Map","Map34",0,"..\\Settings\\PvPSystem.ini");
int map35 = GetPrivateProfileInt("Map","Map35",0,"..\\Settings\\PvPSystem.ini");
int map36 = GetPrivateProfileInt("Map","Map36",0,"..\\Settings\\PvPSystem.ini");
int map37 = GetPrivateProfileInt("Map","Map37",0,"..\\Settings\\PvPSystem.ini");
int map38 = GetPrivateProfileInt("Map","Map38",0,"..\\Settings\\PvPSystem.ini");
int map39 = GetPrivateProfileInt("Map","Map39",0,"..\\Settings\\PvPSystem.ini");
int map40 = GetPrivateProfileInt("Map","Map40",0,"..\\Settings\\PvPSystem.ini");
int map41 = GetPrivateProfileInt("Map","Map41",0,"..\\Settings\\PvPSystem.ini");
int map42 = GetPrivateProfileInt("Map","Map42",0,"..\\Settings\\PvPSystem.ini");
int map43 = GetPrivateProfileInt("Map","Map43",0,"..\\Settings\\PvPSystem.ini");
int map44 = GetPrivateProfileInt("Map","Map44",0,"..\\Settings\\PvPSystem.ini");
int map45 = GetPrivateProfileInt("Map","Map45",0,"..\\Settings\\PvPSystem.ini");
int map46 = GetPrivateProfileInt("Map","Map46",0,"..\\Settings\\PvPSystem.ini");
int map47 = GetPrivateProfileInt("Map","Map47",0,"..\\Settings\\PvPSystem.ini");
int map48 = GetPrivateProfileInt("Map","Map48",0,"..\\Settings\\PvPSystem.ini");
int map49 = GetPrivateProfileInt("Map","Map49",0,"..\\Settings\\PvPSystem.ini");
int map50 = GetPrivateProfileInt("Map","Map50",0,"..\\Settings\\PvPSystem.ini");
//0 - Нормально, 1 - можно убивать и не фонишся, 2 - нельзя атаковать цель
//Во время атаки противника
bool PkCheckEx(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj)
{
	if(!EnablePvP)
		return true;
	//Настройки запрета на атаку
	if(lpTargetObj->Type == OBJ_USER && lpObj->Type != OBJ_MONSTER)
	{
		switch(lpObj->MapNumber)
		{
			case 0: if(map00==2) return false; break;
			case 1: if(map01==2) return false; break;
			case 2: if(map02==2) return false; break;
			case 3: if(map03==2) return false; break;
			case 4: if(map04==2) return false; break;
			case 5: if(map05==2) return false; break;
			case 6: if(map06==2) return false; break;
			case 7: if(map07==2) return false; break;
			case 8: if(map08==2) return false; break;
			case 9: if(map09==2) return false; break;
			case 10:if(map10==2) return false; break;
			case 11:if(map11==2) return false; break;
			case 12:if(map12==2) return false; break;
			case 13:if(map13==2) return false; break;
			case 14:if(map14==2) return false; break;
			case 15:if(map15==2) return false; break;
			case 16:if(map16==2) return false; break;
			case 17:if(map17==2) return false; break;
			case 18:if(map18==2) return false; break;
			case 19:if(map19==2) return false; break;
			case 20:if(map20==2) return false; break;
			case 21:if(map21==2) return false; break;
			case 22:if(map22==2) return false; break;
			case 23:if(map23==2) return false; break;
			case 24:if(map24==2) return false; break;
			case 25:if(map25==2) return false; break;
			case 26:if(map26==2) return false; break;
			case 27:if(map27==2) return false; break;
			case 28:if(map28==2) return false; break;
			case 29:if(map29==2) return false; break;
			case 30:if(map30==2) return false; break;
			case 31:if(map31==2) return false; break;
			case 32:if(map32==2) return false; break;
			case 33:if(map33==2) return false; break;
			case 34:if(map34==2) return false; break;
			case 35:if(map35==2) return false; break;
			case 36:if(map36==2) return false; break;
			case 37:if(map37==2) return false; break;
			case 38:if(map38==2) return false; break;
			case 39:if(map39==2) return false; break;
			case 40:if(map40==2) return false; break;
			case 41:if(map41==2) return false; break;
			case 42:if(map42==2) return false; break;
			case 43:if(map43==2) return false; break;
			case 44:if(map44==2) return false; break;
			case 45:if(map45==2) return false; break;
			case 46:if(map46==2) return false; break;
			case 47:if(map47==2) return false; break;
			case 48:if(map48==2) return false; break;
			case 49:if(map49==2) return false; break;
			case 50:if(map50==2) return false; break;
		}
	}

	//HP Player
	if(PlayerShowHp == 1 && lpTargetObj->Type == OBJ_USER)
	{
		int Distance = gObjCalDistance(lpObj, lpTargetObj);
		MsgNormal(lpObj->m_Index,"[%s][HP] %d [Distance] %d",lpTargetObj->Name,(int)lpTargetObj->Life,Distance); 
	}
			
	//HP Boss
	if(BossShowHp == 1 && lpTargetObj->Type == OBJ_MONSTER)
	{
		if(lpTargetObj->Class == 481 || lpTargetObj->Class == 275 || lpTargetObj->Class == 295 || lpTargetObj->Class == 44 ||
		   lpTargetObj->Class == 43  || lpTargetObj->Class == 55  || lpTargetObj->Class == 56  || lpTargetObj->Class == 78 ||
		   lpTargetObj->Class == 53  || lpTargetObj->Class == 54  || lpTargetObj->Class == 79  || lpTargetObj->Class == 80 ||
		   lpTargetObj->Class == 81  || lpTargetObj->Class == 82  || lpTargetObj->Class == 83  || lpTargetObj->Class == 151||
		   lpTargetObj->Class == 135 || lpTargetObj->Class == 349 || lpTargetObj->Class == 361 || lpTargetObj->Class == 362||
		   lpTargetObj->Class == 363 || lpTargetObj->Class == 412 || lpTargetObj->Class == 499)
			MsgNormal(lpObj->m_Index,"[HP][%s] %d",lpTargetObj->Name,(int)lpTargetObj->Life); 
	}
	return true;	
}

//После смерти противника
void gObjPlayerKillerEx (OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj)
{
	if(LoraBattle.Start)	//LoraBattle
		LoraBattle.BattleKillSocer(lpObj->m_Index,lpTargetObj->m_Index);
	//Лора Ринг ПвП
	if(LoraRingPvP==1 && lpObj->MapNumber==0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131)
		return;
	//Убиваешь и не фонишся
	if(lpTargetObj->Type == OBJ_USER)
	{
		switch(lpObj->MapNumber)
		{
			case 0: if(map00==1) return ; break;
			case 1: if(map01==1) return	; break;
			case 2: if(map02==1) return ; break;
			case 3: if(map03==1) return ; break;
			case 4: if(map04==1) return ; break;
			case 5: if(map05==1) return ; break;
			case 6: if(map06==1) return ; break;
			case 7: if(map07==1) return ; break;
			case 8: if(map08==1) return ; break;
			case 9: if(map09==1) return ; break;
			case 10:if(map10==1) return ; break;
			case 11:if(map11==1) return ; break;
			case 12:if(map12==1) return ; break;
			case 13:if(map13==1) return ; break;
			case 14:if(map14==1) return ; break;
			case 15:if(map15==1) return ; break;
			case 16:if(map16==1) return ; break;
			case 17:if(map17==1) return ; break;
			case 18:if(map18==1) return ; break;
			case 19:if(map19==1) return ; break;
			case 20:if(map20==1) return ; break;
			case 21:if(map21==1) return ; break;
			case 22:if(map22==1) return ; break;
			case 23:if(map23==1) return ; break;
			case 24:if(map24==1) return ; break;
			case 25:if(map25==1) return ; break;
			case 26:if(map26==1) return ; break;
			case 27:if(map27==1) return ; break;
			case 28:if(map28==1) return ; break;
			case 29:if(map29==1) return ; break;
			case 30:if(map30==1) return ; break;
			case 31:if(map31==1) return ; break;
			case 32:if(map32==1) return ; break;
			case 33:if(map33==1) return ; break;
			case 34:if(map34==1) return ; break;
			case 35:if(map35==1) return ; break;
			case 36:if(map36==1) return ; break;
			case 37:if(map37==1) return ; break;
			case 38:if(map38==1) return ; break;
			case 39:if(map39==1) return ; break;
			case 40:if(map40==1) return ; break;
			case 41:if(map41==1) return ; break;
			case 42:if(map42==1) return ; break;
			case 43:if(map43==1) return ; break;
			case 44:if(map44==1) return ; break;
			case 45:if(map45==1) return ; break;
			case 46:if(map46==1) return ; break;
			case 47:if(map47==1) return ; break;
			case 48:if(map48==1) return ; break;
			case 49:if(map49==1) return ; break;
			case 50:if(map50==1) return ; break;
		}
	}
	//Если убиваешь фономана тогда не фонишься
	if(lpObj->Type == OBJ_USER && lpTargetObj->m_PK_Level <= 4)
	{
		if(lpObj->m_PK_Level < 3)
			lpObj->m_PK_Level = 4;
		else
			lpObj->m_PK_Level += 1;
		GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);
	}
	else if(lpObj->Type == OBJ_USER && lpTargetObj->m_PK_Level >5)
	{
		if(lpObj->m_PK_Level > 1)
			lpObj->m_PK_Level -= 1;
		GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);
	}
}

