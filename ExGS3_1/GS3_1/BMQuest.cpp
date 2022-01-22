#include "StdAfx.h"
#include "BMQuest.h"
#include "Message.h"
#include "USER.h"
#include "Utilits.h"
#include "CQuery.h"
#include "AddFunctions.h"


cBMQuest BMQuest;


void cBMQuest::StartConfig()
{
	Enable = GetPrivateProfileInt("Common","Enable",0,_DIR_BMQUEST);
	NPC = GetPrivateProfileInt("Common","NPC",0,_DIR_BMQUEST);
	NPC_Map = GetPrivateProfileInt("Common","NPC_Map",0,_DIR_BMQUEST);
	NPC_X = GetPrivateProfileInt("Common","NPC_X",0,_DIR_BMQUEST);
	NPC_Y = GetPrivateProfileInt("Common","NPC_Y",0,_DIR_BMQUEST);

	Reset = GetPrivateProfileInt("Common","Reset",0,_DIR_BMQUEST);

	for (int i(0);i<_MAX_CLASS_BMQUEST;i++)
	{
		for(int j(0);j<_MAX_BMQUEST;j++)
		{
			Quest[i][j].Mob = 0;
			Quest[i][j].Coun = 0;
			Quest[i][j].proc = 0;
			Quest[i][j].rew = 0;
			Quest[i][j].gift = 0;
			Quest[i][j].msg[0] = NULL;
			Quest[i][j].msg2[0] = NULL;
		}
	}
}

void cBMQuest::StartUP()
{
	StartConfig();
	if(!Enable)
	{
		return;
	}

	FILE *file;
	file = fopen(_DIR_BMQUEST,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\BMQuest.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}
	char Buff[256];
	int Flag = 0;
	Count[1] = 0;
	Count[2] = 0;
	Count[3] = 0;
	Count[4] = 0;
	Count[5] = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[1][Count[1]].Mob  = n[0];
			Quest[1][Count[1]].Coun = n[1];
			Quest[1][Count[1]].proc = n[2];
			Quest[1][Count[1]].rew  = n[3];
			Quest[1][Count[1]].gift = n[4];
			sprintf(Quest[1][Count[1]].msg,"%s",mes);
			sprintf(Quest[1][Count[1]].msg2,"%s",mes2);
			Count[1]++;
		}
		if(Flag == 2)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[2][Count[2]].Mob  = n[0];
			Quest[2][Count[2]].Coun = n[1];
			Quest[2][Count[2]].proc = n[2];
			Quest[2][Count[2]].rew  = n[3];
			Quest[2][Count[2]].gift = n[4];
			sprintf(Quest[2][Count[2]].msg,"%s",mes);
			sprintf(Quest[2][Count[2]].msg2,"%s",mes2);
			Count[2]++;
		}
		if(Flag == 3)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[3][Count[3]].Mob  = n[0];
			Quest[3][Count[3]].Coun = n[1];
			Quest[3][Count[3]].proc = n[2];
			Quest[3][Count[3]].rew  = n[3];
			Quest[3][Count[3]].gift = n[4];
			sprintf(Quest[3][Count[3]].msg,"%s",mes);
			sprintf(Quest[3][Count[3]].msg2,"%s",mes2);
			Count[3]++;
		}
		if(Flag == 4)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[4][Count[4]].Mob  = n[0];
			Quest[4][Count[4]].Coun = n[1];
			Quest[4][Count[4]].proc = n[2];
			Quest[4][Count[4]].rew  = n[3];
			Quest[4][Count[4]].gift = n[4];
			sprintf(Quest[4][Count[4]].msg,"%s",mes);
			sprintf(Quest[4][Count[4]].msg2,"%s",mes2);
			Count[4]++;
		}
		if(Flag == 5)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[5][Count[5]].Mob  = n[0];
			Quest[5][Count[5]].Coun = n[1];
			Quest[5][Count[5]].proc = n[2];
			Quest[5][Count[5]].rew  = n[3];
			Quest[5][Count[5]].gift = n[4];
			sprintf(Quest[5][Count[5]].msg,"%s",mes);
			sprintf(Quest[5][Count[5]].msg2,"%s",mes2);
			Count[5]++;
		}
	}
	fclose(file);
}

void cBMQuest::StartStruct(int aIndex)
{
	if(!Enable)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);								 //  int Q_PGW_num;
	
	//BMQuest_num
	Char[aIndex].BMQuest_num = exQueryReturnInt("SELECT BMQuest_num FROM Character WHERE Name='%s'", gObj->Name);// MySQL.GetInt();

	//BMQuest_kill
	Char[aIndex].BMQuest_kill = 0;

	//BMQuest_start
	Char[aIndex].BMQuest_start = exQueryReturnInt("SELECT BMQuest_start FROM Character WHERE Name='%s'", gObj->Name);

	//BMDamageReflect
	Char[aIndex].BMDamageReflect = exQueryReturnInt("SELECT BMDamageReflect FROM Character WHERE Name='%s'", gObj->Name);

	//BMDamage
	Char[aIndex].BMDamage = exQueryReturnInt("SELECT BMDamage FROM Character WHERE Name='%s'", gObj->Name);

	//BMDefense
	Char[aIndex].BMDefense = exQueryReturnInt("SELECT BMDefense FROM Character WHERE Name='%s'", gObj->Name);

	//BMCriticalDamage
	Char[aIndex].BMCriticalDamage = exQueryReturnInt("SELECT BMCriticalDamage FROM Character WHERE Name='%s'", gObj->Name);

	//BMExcelentDamage
	Char[aIndex].BMExcelentDamage = exQueryReturnInt("SELECT BMExcelentDamage FROM Character WHERE Name='%s'", gObj->Name);

	//BMLife
	Char[aIndex].BMLife = exQueryReturnInt("SELECT BMLife FROM Character WHERE Name='%s'", gObj->Name);

	gObj->MaxLife += Char[aIndex].BMLife;

	j_gObjCalCharacter(aIndex);

	AddedCharacter(aIndex);

	//LevelUpEffect (aIndex,1);
	//LifeReFill (aIndex,(gObj->MaxLife+gObj->AddLife),0,0, 0);
	//gObj->DamageReflect += Char[aIndex].BMDamageReflect;

	//gObj->m_AttackDamageMaxLeft += Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMinLeft += Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMaxRight += Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMinRight += Char[aIndex].BMDamage;
	//gObj->m_MagicDamageMin += Char[aIndex].BMDamage;
	//gObj->m_MagicDamageMax += Char[aIndex].BMDamage;

	//gObj->m_Defense += Char[aIndex].BMDefense;
	//gObj->m_MagicDefense += Char[aIndex].BMDefense;

	//gObj->m_CriticalDamage += Char[aIndex].BMCriticalDamage;
	//gObj->m_ExcelentDamage += Char[aIndex].BMExcelentDamage;

	//gObj->MaxLife += Char[aIndex].BMLife;
}

void cBMQuest::AddedCharacter(int aIndex)
{
	if(!Enable)
		return;	
	
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	gObj->DamageReflect += Char[aIndex].BMDamageReflect;

	gObj->m_AttackDamageMaxLeft += Char[aIndex].BMDamage;
	gObj->m_AttackDamageMinLeft += Char[aIndex].BMDamage;
	gObj->m_AttackDamageMaxRight += Char[aIndex].BMDamage;
	gObj->m_AttackDamageMinRight += Char[aIndex].BMDamage;

	gObj->m_MagicDamageMin += Char[aIndex].BMDamage;
	gObj->m_MagicDamageMax += Char[aIndex].BMDamage;

	gObj->m_Defense += Char[aIndex].BMDefense;
	gObj->m_MagicDefense += Char[aIndex].BMDefense;

	gObj->m_CriticalDamage += Char[aIndex].BMCriticalDamage;
	gObj->m_ExcelentDamage += Char[aIndex].BMExcelentDamage;
}

void cBMQuest::CharacterInformation(int aIndex)
{
	if(!Enable)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	
	MessageChat(aIndex,"@[BMInfo] +%d Reflect",Char[aIndex].BMDamageReflect);
	MessageChat(aIndex,"@[BMInfo] +%d Damage",Char[aIndex].BMDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Defense",Char[aIndex].BMDefense);
	MessageChat(aIndex,"@[BMInfo] +%d CritDamage",Char[aIndex].BMCriticalDamage);
	MessageChat(aIndex,"@[BMInfo] +%d ExcDamage",Char[aIndex].BMExcelentDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Life",Char[aIndex].BMLife);
}

void cBMQuest::NPCClick(int aIndex,int aNPC)
{
	if(!Enable)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);
	if ((gObjNPC->Class == NPC) && (gObjNPC->MapNumber == NPC_Map) && (gObjNPC->X == NPC_X) && (gObjNPC->Y == NPC_Y))
	{
		
		NPCdialogue(aIndex,aNPC);
	}
}

void cBMQuest::NPCdialogue(int aIndex,int aNPC)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);

	if(ExUser[aIndex].Resets < Reset)
	{
		char Buffs[100];
		sprintf(Buffs,"Mission is available with %d reset",Reset);
		ChatTargetSendNogs(gObjNPC,Buffs,aIndex);
		return;
	}

	int QClass = gObj->Class+1;
	//Проверяем не закончен ли квест
	if(Char[aIndex].BMQuest_num < Count[QClass])
	{
		//Проверяем начат ли уже квест
		if(Char[aIndex].BMQuest_start == 0)
		{
			ChatTargetSendNogs(gObjNPC,"Good luck!",aIndex);
			Char[aIndex].BMQuest_start = 1;
			exQueryUpdate("UPDATE Character SET BMQuest_start = 1 WHERE Name='%s'", gObj->Name);
			MessageChat(aIndex,"@[BMQuest] Mission: %d",Char[aIndex].BMQuest_num+1);
			MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][Char[aIndex].BMQuest_num].msg);
			MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
				Quest[QClass][Char[aIndex].BMQuest_num].msg2,
				Char[aIndex].BMQuest_kill,
				Quest[QClass][Char[aIndex].BMQuest_num].Coun);
		}
		//Если квест уже взят
		else if(Char[aIndex].BMQuest_start == 1)
		{
			//Если квест выполнен
			if(Char[aIndex].BMQuest_kill >= Quest[QClass][Char[aIndex].BMQuest_num].Coun)
			{
				Presents(aIndex,
					Quest[QClass][Char[aIndex].BMQuest_num].rew,
					Quest[QClass][Char[aIndex].BMQuest_num].gift); //Функция вознаграждения

				Char[aIndex].BMQuest_start = 0;
				Char[aIndex].BMQuest_num++;
				Char[aIndex].BMQuest_kill = 0;
				ChatTargetSendNogs(gObjNPC,"You completed the mission!",aIndex);
				exQueryUpdate("UPDATE Character SET BMQuest_start = 0 WHERE Name='%s'", gObj->Name);
				exQueryUpdate("UPDATE Character SET BMQuest_num = BMQuest_num + 1 WHERE Name='%s'", gObj->Name);
				//MySQL.Execute("UPDATE Character SET BMQuest_kill = 0 WHERE Name='%s'",gObj->Name);
				if(Char[aIndex].BMQuest_num == Count[QClass])
				{
					MessageChat(aIndex,"@[BMQuest] Finish");
				}
			}
			//Если квест не выполнен
			else
			{
				ChatTargetSendNogs(gObjNPC,"Your Mission is not finished!",aIndex);
				MessageChat(aIndex,"@[BMQuest] Mission: %d",Char[aIndex].BMQuest_num+1);
				MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][Char[aIndex].BMQuest_num].msg);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][Char[aIndex].BMQuest_num].msg2,
					Char[aIndex].BMQuest_kill,
					Quest[QClass][Char[aIndex].BMQuest_num].Coun);
			}
		}
	}
	else
	{
		ChatTargetSendNogs(gObjNPC,"You have completed all the Mission!",aIndex);
		MessageChat(aIndex,"@[BMQuest] Finish");
	}
}

void cBMQuest::MonsterKill(int aIndex, int mIndex)
{
	if(!Enable)
		return;
	
	OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	int QClass = gObj->Class+1;

	if(Char[aIndex].BMQuest_start == 1 && mObj->Class == Quest[QClass][Char[aIndex].BMQuest_num].Mob)
	{
		int iRate = rand()%100+1;

		if(Quest[QClass][Char[aIndex].BMQuest_num].proc >= iRate)
		{			

			if(Char[aIndex].BMQuest_kill < Quest[QClass][Char[aIndex].BMQuest_num].Coun)
			{
				
				Char[aIndex].BMQuest_kill++;
				//MySQL.Execute("UPDATE Character SET BMQuest_kill = BMQuest_kill + 1 WHERE Name='%s'",gObj->Name);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][Char[aIndex].BMQuest_num].msg2,
					Char[aIndex].BMQuest_kill,
					Quest[QClass][Char[aIndex].BMQuest_num].Coun);
			
				if(Char[aIndex].BMQuest_kill == Quest[QClass][Char[aIndex].BMQuest_num].Coun)
				{
					MessageChat(aIndex,"@[BMQuest] Mission accomplished!");
				}
			}
		}
	}
}

void cBMQuest::Presents(int aIndex, int Present, int Gifts)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	
	/*
		1 - BMDamageReflect;
		2 - BMDamage;
		3 - BMDefense;
		4 - BMCriticalDamage;
		5 - BMExcelentDamage;
		6 - BMLife;
	*/
	if(Present == 1)		//BMDamageReflect
	{
		Char[aIndex].BMDamageReflect += Gifts;
		exQueryUpdate("UPDATE Character SET BMDamageReflect = BMDamageReflect + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] DamageReflect: +%d",Gifts);
	}
	else if(Present == 2)	//BMDamage
	{
		Char[aIndex].BMDamage += Gifts;
		exQueryUpdate("UPDATE Character SET BMDamage = BMDamage + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Damage: +%d",Gifts);
	}
	else if(Present == 3)	//BMDefense
	{
		Char[aIndex].BMDefense += Gifts;
		exQueryUpdate("UPDATE Character SET BMDefense = BMDefense + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Defense: +%d",Gifts);
	}
	else if(Present == 4)	//BMCriticalDamage
	{
		Char[aIndex].BMCriticalDamage += Gifts;
		exQueryUpdate("UPDATE Character SET BMCriticalDamage = BMCriticalDamage + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] CriticalDamage: +%d",Gifts);
	}
	else if(Present == 5)	//BMExcelentDamage
	{
		Char[aIndex].BMExcelentDamage += Gifts;
		exQueryUpdate("UPDATE Character SET BMExcelentDamage = BMExcelentDamage + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] ExcelentDamage: +%d",Gifts);
	}
	else if(Present == 6)	//BMLife
	{
		Char[aIndex].BMLife += Gifts;
		exQueryUpdate("UPDATE Character SET BMLife = BMLife + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Life: +%d",Gifts);
	}
	//LevelUpEffect (aIndex,1);
	FireCracker(aIndex, gObj->X, gObj->Y);
}