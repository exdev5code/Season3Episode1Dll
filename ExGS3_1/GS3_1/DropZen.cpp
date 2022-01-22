#include "StdAfx.h"
#include "USER.h"
#include "DropZen.h"
#include "Quest_PGW.h"
#include "VipSystem.h"
#include "HappyHour.h"
#include "BMQuest.h"	//BMQuest
#include "ItemDropManager.h"	//ItemDropManager

int EnableMap = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\CustomZen.ini");
int DropZen(BYTE *b_MonsterDataAddr,BYTE *a_gObjAddr)
{
	int Default = gEventMonsterItemDrop(b_MonsterDataAddr, a_gObjAddr);
	if(!EnableMap)
		return Default;
	//Map Конфигурации
	int map00 = GetPrivateProfileInt("Map","Map00",100,"..\\Settings\\CustomZen.ini");
	int map01 = GetPrivateProfileInt("Map","Map01",100,"..\\Settings\\CustomZen.ini");
	int map02 = GetPrivateProfileInt("Map","Map02",100,"..\\Settings\\CustomZen.ini");
	int map03 = GetPrivateProfileInt("Map","Map03",100,"..\\Settings\\CustomZen.ini");
	int map04 = GetPrivateProfileInt("Map","Map04",100,"..\\Settings\\CustomZen.ini");
	int map05 = GetPrivateProfileInt("Map","Map05",100,"..\\Settings\\CustomZen.ini");
	int map06 = GetPrivateProfileInt("Map","Map06",100,"..\\Settings\\CustomZen.ini");
	int map07 = GetPrivateProfileInt("Map","Map07",100,"..\\Settings\\CustomZen.ini");
	int map08 = GetPrivateProfileInt("Map","Map08",100,"..\\Settings\\CustomZen.ini");
	int map09 = GetPrivateProfileInt("Map","Map09",100,"..\\Settings\\CustomZen.ini");
	int map10 = GetPrivateProfileInt("Map","Map10",100,"..\\Settings\\CustomZen.ini");
	int map11 = GetPrivateProfileInt("Map","Map11",100,"..\\Settings\\CustomZen.ini");
	int map12 = GetPrivateProfileInt("Map","Map12",100,"..\\Settings\\CustomZen.ini");
	int map13 = GetPrivateProfileInt("Map","Map13",100,"..\\Settings\\CustomZen.ini");
	int map14 = GetPrivateProfileInt("Map","Map14",100,"..\\Settings\\CustomZen.ini");
	int map15 = GetPrivateProfileInt("Map","Map15",100,"..\\Settings\\CustomZen.ini");
	int map16 = GetPrivateProfileInt("Map","Map16",100,"..\\Settings\\CustomZen.ini");
	int map17 = GetPrivateProfileInt("Map","Map17",100,"..\\Settings\\CustomZen.ini");
	int map18 = GetPrivateProfileInt("Map","Map18",100,"..\\Settings\\CustomZen.ini");
	int map19 = GetPrivateProfileInt("Map","Map19",100,"..\\Settings\\CustomZen.ini");
	int map20 = GetPrivateProfileInt("Map","Map20",100,"..\\Settings\\CustomZen.ini");
	int map21 = GetPrivateProfileInt("Map","Map21",100,"..\\Settings\\CustomZen.ini");
	int map22 = GetPrivateProfileInt("Map","Map22",100,"..\\Settings\\CustomZen.ini");
	int map23 = GetPrivateProfileInt("Map","Map23",100,"..\\Settings\\CustomZen.ini");
	int map24 = GetPrivateProfileInt("Map","Map24",100,"..\\Settings\\CustomZen.ini");
	int map25 = GetPrivateProfileInt("Map","Map25",100,"..\\Settings\\CustomZen.ini");
	int map26 = GetPrivateProfileInt("Map","Map26",100,"..\\Settings\\CustomZen.ini");
	int map27 = GetPrivateProfileInt("Map","Map27",100,"..\\Settings\\CustomZen.ini");
	int map28 = GetPrivateProfileInt("Map","Map28",100,"..\\Settings\\CustomZen.ini");
	int map29 = GetPrivateProfileInt("Map","Map29",100,"..\\Settings\\CustomZen.ini");
	int map30 = GetPrivateProfileInt("Map","Map30",100,"..\\Settings\\CustomZen.ini");
	int map31 = GetPrivateProfileInt("Map","Map31",100,"..\\Settings\\CustomZen.ini");
	int map32 = GetPrivateProfileInt("Map","Map32",100,"..\\Settings\\CustomZen.ini");
	int map33 = GetPrivateProfileInt("Map","Map33",100,"..\\Settings\\CustomZen.ini");
	int map34 = GetPrivateProfileInt("Map","Map34",100,"..\\Settings\\CustomZen.ini");
	int map35 = GetPrivateProfileInt("Map","Map35",100,"..\\Settings\\CustomZen.ini");
	int map36 = GetPrivateProfileInt("Map","Map36",100,"..\\Settings\\CustomZen.ini");
	int map37 = GetPrivateProfileInt("Map","Map37",100,"..\\Settings\\CustomZen.ini");
	int map38 = GetPrivateProfileInt("Map","Map38",100,"..\\Settings\\CustomZen.ini");
	int map39 = GetPrivateProfileInt("Map","Map39",100,"..\\Settings\\CustomZen.ini");
	int map40 = GetPrivateProfileInt("Map","Map40",100,"..\\Settings\\CustomZen.ini");
	int map41 = GetPrivateProfileInt("Map","Map41",100,"..\\Settings\\CustomZen.ini");
	int map42 = GetPrivateProfileInt("Map","Map42",100,"..\\Settings\\CustomZen.ini");
	int map43 = GetPrivateProfileInt("Map","Map43",100,"..\\Settings\\CustomZen.ini");
	int map44 = GetPrivateProfileInt("Map","Map44",100,"..\\Settings\\CustomZen.ini");
	int map45 = GetPrivateProfileInt("Map","Map45",100,"..\\Settings\\CustomZen.ini");
	int map46 = GetPrivateProfileInt("Map","Map46",100,"..\\Settings\\CustomZen.ini");
	int map47 = GetPrivateProfileInt("Map","Map47",100,"..\\Settings\\CustomZen.ini");
	int map48 = GetPrivateProfileInt("Map","Map48",100,"..\\Settings\\CustomZen.ini");
	int map49 = GetPrivateProfileInt("Map","Map49",100,"..\\Settings\\CustomZen.ini");
	int map50 = GetPrivateProfileInt("Map","Map50",100,"..\\Settings\\CustomZen.ini");

	PBYTE a_aIndex = 0;
	PBYTE b_mIndex = 0;

	a_aIndex = (PBYTE)a_gObjAddr;
	b_mIndex = (PBYTE)b_MonsterDataAddr;

	WORD mIndex = 0;
	WORD aIndex = 0;

	memcpy(&mIndex, b_mIndex+0x00,sizeof(WORD));
	memcpy(&aIndex, a_aIndex+0x00,sizeof(WORD));

	OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	
	switch(pObj->MapNumber)
	{
		case 0: mObj->Money = (mObj->Money/100)*map00;break;
		case 1: mObj->Money = (mObj->Money/100)*map01;break;
		case 2: mObj->Money = (mObj->Money/100)*map02;break;
		case 3: mObj->Money = (mObj->Money/100)*map03;break;
		case 4: mObj->Money = (mObj->Money/100)*map04;break;
		case 5: mObj->Money = (mObj->Money/100)*map05;break;
		case 6: mObj->Money = (mObj->Money/100)*map06;break;
		case 7: mObj->Money = (mObj->Money/100)*map07;break;
		case 8: mObj->Money = (mObj->Money/100)*map08;break;
		case 9: mObj->Money = (mObj->Money/100)*map09;break;
		case 10: mObj->Money = (mObj->Money/100)*map10;break;
		case 11: mObj->Money = (mObj->Money/100)*map11;break;
		case 12: mObj->Money = (mObj->Money/100)*map12;break;
		case 13: mObj->Money = (mObj->Money/100)*map13;break;
		case 14: mObj->Money = (mObj->Money/100)*map14;break;
		case 15: mObj->Money = (mObj->Money/100)*map15;break;
		case 16: mObj->Money = (mObj->Money/100)*map16;break;
		case 17: mObj->Money = (mObj->Money/100)*map17;break;
		case 18: mObj->Money = (mObj->Money/100)*map18;break;
		case 19: mObj->Money = (mObj->Money/100)*map19;break;
		case 20: mObj->Money = (mObj->Money/100)*map20;break;
		case 21: mObj->Money = (mObj->Money/100)*map21;break;
		case 22: mObj->Money = (mObj->Money/100)*map22;break;
		case 23: mObj->Money = (mObj->Money/100)*map23;break;
		case 24: mObj->Money = (mObj->Money/100)*map24;break;
		case 25: mObj->Money = (mObj->Money/100)*map25;break;
		case 26: mObj->Money = (mObj->Money/100)*map26;break;
		case 27: mObj->Money = (mObj->Money/100)*map27;break;
		case 28: mObj->Money = (mObj->Money/100)*map28;break;
		case 29: mObj->Money = (mObj->Money/100)*map29;break;
		case 30: mObj->Money = (mObj->Money/100)*map30;break;
		case 31: mObj->Money = (mObj->Money/100)*map31;break;
		case 32: mObj->Money = (mObj->Money/100)*map32;break;
		case 33: mObj->Money = (mObj->Money/100)*map33;break;
		case 34: mObj->Money = (mObj->Money/100)*map34;break;
		case 35: mObj->Money = (mObj->Money/100)*map35;break;
		case 36: mObj->Money = (mObj->Money/100)*map36;break;
		case 37: mObj->Money = (mObj->Money/100)*map37;break;
		case 38: mObj->Money = (mObj->Money/100)*map38;break;
		case 39: mObj->Money = (mObj->Money/100)*map39;break;
		case 40: mObj->Money = (mObj->Money/100)*map40;break;
		case 41: mObj->Money = (mObj->Money/100)*map41;break;
		case 42: mObj->Money = (mObj->Money/100)*map42;break;
		case 43: mObj->Money = (mObj->Money/100)*map43;break;
		case 44: mObj->Money = (mObj->Money/100)*map44;break;
		case 45: mObj->Money = (mObj->Money/100)*map45;break;
		case 46: mObj->Money = (mObj->Money/100)*map46;break;
		case 47: mObj->Money = (mObj->Money/100)*map47;break;
		case 48: mObj->Money = (mObj->Money/100)*map48;break;
		case 49: mObj->Money = (mObj->Money/100)*map49;break;
		case 50: mObj->Money = (mObj->Money/100)*map50;break;
	}

	//ExQuest
	if(ExUser[aIndex].ExQuest_start == 1 && mObj->Class == Qest_PGW.Number[ExUser[aIndex].ExQuest_num].Mob)
		Qest_PGW.KilledMob(aIndex);

	//VipSystem
	if(Vip.EnableVipSystem != 0 && ExUser[aIndex].VipStatus == 1)
		mObj->Money += (mObj->Money/100)*Vip.PlusDrop;
	
	//HappyHour
	if(HappyHour.Enable != 0 && HappyHour.StartHappyHour == true)
		mObj->Money += (mObj->Money/100)*HappyHour.PlusDrop;

	BMQuest.MonsterKill(aIndex,mIndex);	//BMQuest

	ItemDropManager.Process(aIndex,mIndex);	//ItemDropManager
	
	return Default;
}