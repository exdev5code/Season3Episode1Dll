#include "Quest_PGW.h"
#include "StdAfx.h"
//#include "Experience.h"
#include "USER.h"
#include "Message.h"
#include "Defines.h"
#include "CQuery.h"
#include "AddFunctions.h"
#include "ExCore.h"


Q_PGW Qest_PGW;


int EnableExQuest = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\ExQuest.ini");

bool Q_PGW::IsBadFileLine(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)
	{
		Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}
//====================================================
void Q_PGW::Q_Num()
{
	for(int i(0);i<1000;i++)
	{
		Number[i].Mob = 0;
		Number[i].Coun = 0;
		Number[i].proc = 0;
		Number[i].rew = 0;
		Number[i].gift = 0;
		Number[i].msg[0] = NULL;
		Number[i].msg2[0] = NULL;
	}
}
void Q_PGW::Q_Load()
{
	if(!EnableExQuest)
		return;
	Q_Num();
	FILE *file;
	file = fopen("..\\Settings\\ExQuest.ini","r");
	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\ExQuest.ini Load Error","CRITICAL ERROR",0);
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
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Number[Count].Mob  = n[0];
			Number[Count].Coun = n[1];
			Number[Count].proc = n[2];
			Number[Count].rew  = n[3];
			Number[Count].gift = n[4];
			sprintf(Number[Count].msg,"%s",mes);
			sprintf(Number[Count].msg2,"%s",mes2);
			Count++;
		}
	}
	fclose(file);
}
void Q_PGW::Q_CreateStruct(int aIndex)
{
	if(!EnableExQuest)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);								 //  int Q_PGW_num;
	   /*	Путь великого воина #end	*/// int Ex_FreePoints;
	   /*	Путь великого воина #kill	*/// int Q_PGW_kill;
	   /*	Путь великого воина #start	*/// int Q_PGW_start;

	ExUser[aIndex].ExQuest_num = exQueryReturnInt("SELECT ExQuest_num FROM Character WHERE Name='%s'", gObj->Name);
	//-------------------------------------------------------------------------
	ExUser[aIndex].ExQuest_kill = 0;
	//-------------------------------------------------------------------------
	ExUser[aIndex].ExQuest_start = exQueryReturnInt("SELECT ExQuest_start FROM Character WHERE Name='%s'", gObj->Name);
	//-------------------------------------------------------------------------
	ExUser[aIndex].Ex_FreePoints = exQueryReturnInt("SELECT Ex_FreePoints FROM Character WHERE Name='%s'", gObj->Name);
	//-------------------------------------------------------------------------
}
void Q_PGW::Q_NPC (int aIndex,int aNPC)
{
	if(!EnableExQuest)
		return;
	int ExQNPC = GetPrivateProfileInt("Common","NPC",0,"..\\Settings\\ExQuest.ini");
	int ExQNPCM = GetPrivateProfileInt("Common","NPC_Map",0,"..\\Settings\\ExQuest.ini");
	int ExQNPCX = GetPrivateProfileInt("Common","NPC_X",0,"..\\Settings\\ExQuest.ini");
	int ExQNPCY = GetPrivateProfileInt("Common","NPC_Y",0,"..\\Settings\\ExQuest.ini");
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);
	//371 120 141
	if ((gObjNPC->Class == ExQNPC) && (gObjNPC->MapNumber == ExQNPCM) && (gObjNPC->X == ExQNPCX) && (gObjNPC->Y == ExQNPCY)) 
	{
		//MySQL.Execute("SELECT ExQuest_num FROM Character WHERE Name='%s'",gObj->Name);
		//int ExQuest_num = MySQL.GetInt();
		//Проверяем не закончен ли квест
		if(ExUser[aIndex].ExQuest_num < Count)
		{
			//MySQL.Execute("SELECT ExQuest_start FROM Character WHERE Name='%s'",gObj->Name);
			//int ExQuest_start = MySQL.GetInt();
			//MySQL.Execute("SELECT ExQuest_kill FROM Character WHERE Name='%s'",gObj->Name);
			//int ExQuest_kill = MySQL.GetInt();
			//Проверяем начат ли уже квест
			if(ExUser[aIndex].ExQuest_start == 0)
			{

				ChatTargetSendNogs(gObjNPC,"Удачной охоты!",aIndex);
				ExUser[aIndex].ExQuest_start = 1;
				exQueryUpdate("UPDATE Character SET ExQuest_start = 1 WHERE Name='%s'", gObj->Name);
				MessageChat(aIndex,"@[ExQuest] Задание №%d",ExUser[aIndex].ExQuest_num+1);
				MessageChat(aIndex,"@[ExQuest] %s",Number[ExUser[aIndex].ExQuest_num].msg);
				MessageChat(aIndex,"@[ExQuest] %s [%d/%d]",Number[ExUser[aIndex].ExQuest_num].msg2,ExUser[aIndex].ExQuest_kill,Number[ExUser[aIndex].ExQuest_num].Coun);
			}
			//Если квест уже взят
			else if (ExUser[aIndex].ExQuest_start == 1)
			{

				//Если квест выполнен
				if(ExUser[aIndex].ExQuest_kill == Number[ExUser[aIndex].ExQuest_num].Coun)
				{
					int ExQuest_gift = Presents(aIndex,Number[ExUser[aIndex].ExQuest_num].rew,Number[ExUser[aIndex].ExQuest_num].gift); //Функция вознаграждения
					if(ExQuest_gift == false)
					{
						ChatTargetSendNogs(gObjNPC,"Освободите место и вернитесь за подарком!",aIndex);
						return;
					}
					ExUser[aIndex].ExQuest_start = 0;
					ExUser[aIndex].ExQuest_num++;
					ExUser[aIndex].ExQuest_kill = 0;
					ChatTargetSendNogs(gObjNPC,"Поздравляю вы выполнили задание!",aIndex);
					exQueryUpdate("UPDATE Character SET ExQuest_start = 0 WHERE Name='%s'", gObj->Name);
					exQueryUpdate("UPDATE Character SET ExQuest_num = ExQuest_num + 1 WHERE Name='%s'", gObj->Name);
					//MySQL.Execute("UPDATE Character SET ExQuest_kill = 0 WHERE Name='%s'",gObj->Name);
					if(ExUser[aIndex].ExQuest_num == Count)
						MessageChat(aIndex,"@[ExQuest] Finish");
				}
				//Если квест не выполнен
				else
				{
					ChatTargetSendNogs(gObjNPC,"Ваше задание не закончено!",aIndex);
					MessageChat(aIndex,"@[ExQuest] %s",Number[ExUser[aIndex].ExQuest_num].msg);
					MessageChat(aIndex,"@[ExQuest] %s [%d/%d]",Number[ExUser[aIndex].ExQuest_num].msg2,ExUser[aIndex].ExQuest_kill,Number[ExUser[aIndex].ExQuest_num].Coun);
				}
			}
		}
		else
		{

			ChatTargetSendNogs(gObjNPC,"Вы выполнили все задания!",aIndex);
			MessageChat(aIndex,"@[ExQuest] Finish");
		}
	}
}
void Q_PGW::KilledMob(int aIndex)
{
	if(!EnableExQuest)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	int iRate = rand()%100+1;
	//MySQL.Execute("SELECT ExQuest_num FROM Character WHERE Name='%s'",gObj->Name);
	//int ExQuest_num = MySQL.GetInt();
	if(Number[ExUser[aIndex].ExQuest_num].proc >= iRate)
	{			
		//MySQL.Execute("SELECT ExQuest_kill FROM Character WHERE Name='%s'",gObj->Name);
		//int ExQuest_kill = MySQL.GetInt();
		if(ExUser[aIndex].ExQuest_kill < Number[ExUser[aIndex].ExQuest_num].Coun)
		{

			ExUser[aIndex].ExQuest_kill++;
			//MySQL.Execute("UPDATE Character SET ExQuest_kill = ExQuest_kill + 1 WHERE Name='%s'",gObj->Name);
			MessageChat(aIndex,"@[ExQuest] %s [%d/%d]",Number[ExUser[aIndex].ExQuest_num].msg2,ExUser[aIndex].ExQuest_kill,Number[ExUser[aIndex].ExQuest_num].Coun);
			if(ExUser[aIndex].ExQuest_kill == Number[ExUser[aIndex].ExQuest_num].Coun)
				MessageChat(aIndex,"@[ExQuest] Задание выполнено!");
		}
	}
}
bool Q_PGW::Presents(int aIndex, int Present, int Gifts)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//1- Зен, 2 - Gem, 3 - FreePoints, 4 - Items

	if(Present == 1)
	{
		if((gObj->Money + Gifts) <= 2000000000)
		{
			gObj->Money += Gifts;
			MessageChat(aIndex,"@[ExQuest] Вознаграждение Zen: %d",Gifts);
			GCMoneySend(gObj->m_Index, gObj->Money);
		}
		else
		{
			MessageChat(aIndex,"@[ExQuest] Не достаточно места под зен");
			return false;
		}
	}
	else if(Present == 2)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", Gifts, gObj->AccountID);
		MessageChat(aIndex,"@[ExQuest] Вознаграждение Gem: %d",Gifts);
	}
	else if(Present == 3)
	{
		ExUser[aIndex].Ex_FreePoints += Gifts;
		gObj->LevelUpPoint += Gifts;
		exQueryUpdate("UPDATE Character SET Ex_FreePoints = Ex_FreePoints + %d WHERE Name='%s'", Gifts, gObj->Name);
		MessageChat(aIndex,"@[ExQuest] Вознаграждение Points: %d",Gifts);
		LevelUpEffect (aIndex,1);
	}
	else if(Present == 4)
	{
		ItemSerialCreateSend(aIndex,gObj->MapNumber,gObj->X,gObj->Y,Gifts,0,0,0,0,0,aIndex,0,0);
		MessageChat(aIndex,"@[ExQuest] Вознаграждение Items");
	}
	FireCracker(aIndex, gObj->X, gObj->Y);
	return true;
}