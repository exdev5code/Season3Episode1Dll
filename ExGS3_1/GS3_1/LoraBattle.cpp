#include "StdAfx.h"
#include "LoraBattle.h"
#include "USER.h"
#include "Utilits.h"
#include "Message.h"
#include "AddFunctions.h"
#include "CQuery.h"


cLoraBattle LoraBattle;

void cLoraBattle::LoadConfigs()
{

	Enable = GetPrivateProfileInt("Common","Enable",1,LORABATTLE_DIR);
	

	if(!Enable)
		return;
	//Configs
	GetPrivateProfileStringA("Common", "MGS","[Lora Battle] Start after 1 minute",MSG,sizeof(MSG),LORABATTLE_DIR);
	RewardGem = GetPrivateProfileInt("Reward","RewardGem",1,LORABATTLE_DIR);
	RewardItem = GetPrivateProfileInt("Reward","RewardItem",1,LORABATTLE_DIR);

	GEM = GetPrivateProfileInt("Reward","GEM",1,LORABATTLE_DIR);
	ITEM = GetPrivateProfileInt("Reward","ITEM",1,LORABATTLE_DIR);
	ITEM_LEVEL = GetPrivateProfileInt("Reward","ITEM_LEVEL",1,LORABATTLE_DIR);

	Fallen_DROP = GetPrivateProfileInt("Fallen","Fallen_DROP",1,LORABATTLE_DIR);
	Fallen_ITEM = GetPrivateProfileInt("Fallen","Fallen_ITEM",1,LORABATTLE_DIR);
	Fallen_ITEM_LEVEL = GetPrivateProfileInt("Fallen","Fallen_ITEM_LEVEL",1,LORABATTLE_DIR);

	for(int i=OBJECT_MIN; i<=OBJECT_MAX; i++)
	{
		KillSocer[i] = 0;
		m_PK_Level[i] = 0;
	}

	MaxSocer	 = 0;

	Start = false;

	FILE *file = fopen(LORABATTLE_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\LoraBattleEvent.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			Time[Count].StrHour	= 0;
			Time[Count].StrMin	= 0;
			Time[Count].Hour	= 0;
			Time[Count].Min		= 0;
			Time[Count].EndHour	= 0;
			Time[Count].EndMin	= 0;

			int n[7];
			sscanf(Buff, "%d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
			Time[Count].StrHour	= n[0];
			Time[Count].StrMin	= n[1];
			Time[Count].Hour	= n[2];
			Time[Count].Min		= n[3];;
			Time[Count].EndHour	= n[4];
			Time[Count].EndMin	= n[5];
			Count++;
		}
	}
	fclose(file);
}
void cLoraBattle::Start1min()
{
	MessaageAllGlobal("%s",MSG);
}

void cLoraBattle::StartEvent()
{
	for(int j=OBJECT_MIN; j<=OBJECT_MAX; j++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(j);
		m_PK_Level[j] = gObj->m_PK_Level;
	}

	Start = true;
	MessaageAllGlobal("[Lora Battle] Event Started!");
}

void cLoraBattle::EndEvent()
{
	Start = false;
	for(int j=OBJECT_MIN; j<=OBJECT_MAX; j++)
	{
		//MaxSocer = KillSocer[j];
		if(KillSocer[j] > MaxSocer)
		{
			MaxSocer = KillSocer[j];
			MaxIndex = j;
		}
	}
	for(int l=OBJECT_MIN; l<=OBJECT_MAX; l++)
	{
		if(KillSocer[l] == 0)
			continue;

		if(MaxSocer == KillSocer[l])
		{
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(l);
			if(gObj->Connected == PLAYER_PLAYING)
			{
				MessaageAllGlobal("[Lora Battle] Win %s !",gObj->Name);
				Reward(l);
			}
		}
	}
	
	MessaageAllGlobal("[Lora Battle] Event End!");

	for(int i=OBJECT_MIN; i<=OBJECT_MAX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		KillSocer[i] = 0;
		gObj->m_PK_Level = m_PK_Level[i];
		GCPkLevelSend(i, gObj->m_PK_Level);
	}

	MaxSocer	 = 0;
}

void cLoraBattle::TickTime()
{
	if(!Enable)
		return;
	SYSTEMTIME time;
	GetLocalTime(&time);

	if(time.wSecond == 00)
	{
		for(int i = 0; i < Count; i++)
		{
			if(Time[i].StrHour == time.wHour && Time[i].StrMin == time.wMinute)
			{

				Start1min();
			}

			else if(Time[i].Hour == time.wHour && Time[i].Min == time.wMinute)
			{

				StartEvent();
			}
			else if(Time[i].EndHour == time.wHour && Time[i].EndMin == time.wMinute)
			{

				EndEvent();
			}
		}
	}
}

void cLoraBattle::Process(int aIndex)
{
	if(!Enable)
		return;
	if(!Start)
		return;

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	//Лора Ринг ПвП
	if(gObj->MapNumber==0 && gObj->X >= 137 && gObj->X <= 144 && gObj->Y >= 124 && gObj->Y <= 131)
	{
		if(BattleRing[aIndex] == true)
			return;
		gObj->m_PK_Level = 6;
		GCPkLevelSend(aIndex, gObj->m_PK_Level);
		
		BattleRing[aIndex] = true;
	}
	else 
	{
		if(BattleRing[aIndex] == false)
			return;

		gObj->m_PK_Level = m_PK_Level[aIndex];
		GCPkLevelSend(aIndex, gObj->m_PK_Level);
		
		BattleRing[aIndex] = false;
	}
}

void cLoraBattle::BattleKillSocer(int aIndex,int aIndex2)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	OBJECTSTRUCT *lpTargetObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex2);	
	if(gObj->MapNumber == 0 && gObj->X >= 137 && gObj->X <= 144 && gObj->Y >= 124 && gObj->Y <= 131)
	{
		KillSocer[aIndex]++;
		MsgNormal(aIndex,"[LoraBattle] Killed: %d",KillSocer[aIndex]);
		if(Fallen_DROP)
			ItemSerialCreateSend(aIndex2,lpTargetObj->MapNumber,lpTargetObj->X,lpTargetObj->Y,Fallen_ITEM,Fallen_ITEM_LEVEL,0,0,0,0,aIndex,0,0);
		//OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	}
}

void cLoraBattle::Reward(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	if(RewardGem)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", GEM, gObj->AccountID);
		MsgNormal(aIndex,"[LoraBattle] Reward Gem: +%d",GEM);
	}

	if(RewardItem)
	{
		ItemSerialCreateSend(aIndex,gObj->MapNumber,gObj->X,gObj->Y,ITEM,ITEM_LEVEL,0,0,0,0,aIndex,0,0);
	}

	
	FireCracker(aIndex,gObj->X,gObj->Y);
}