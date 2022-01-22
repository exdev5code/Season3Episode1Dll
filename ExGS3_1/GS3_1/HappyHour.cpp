#include "StdAfx.h"
#include "USER.h"
#include "HappyHour.h"
#include "Utilits.h"
#include "Message.h"



cHappyHour HappyHour;

void cHappyHour::LoadConfig()
{
	Enable = GetPrivateProfileInt("Common","Enable",1,HH_DIR);
	PlusExp = GetPrivateProfileInt("Common","PlusExp",10,HH_DIR);
	PlusDrop = GetPrivateProfileInt("Common","PlusDrop",10,HH_DIR);
	StartHappyHour = false;

}

void cHappyHour::LoadFile()
{
	FILE *file;
	file = fopen("..\\Settings\\HappyHour.ini","r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\HappyHour.ini Load Error","CRITICAL ERROR",0);
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
			HappyStruct[Count].Hour		= 0;
			HappyStruct[Count].Min		= 0;
			HappyStruct[Count].EndHour	= 0;
			HappyStruct[Count].EndMin	= 0;

			int n[5];
			sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
			HappyStruct[Count].Hour		= n[0];
			HappyStruct[Count].Min		= n[1];
			HappyStruct[Count].EndHour	= n[2];
			HappyStruct[Count].EndMin	= n[3];
			Count++;
		}
	}
	fclose(file);
}

void cHappyHour::Timetick()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	if(time.wSecond == 00)
	{
		for(int i = 0; i < Count; i++)
		{
			if(HappyStruct[i].Hour == time.wHour && HappyStruct[i].Min == time.wMinute)
			{

				StartHappyHour = true;
				MessaageAllGlobal("[Happy Hour] Event Started!");
				MessaageAllGlobal("[Happy Hour] Exp: +%d Drop: +%d",PlusExp,PlusDrop);
				break;
			}
			if(HappyStruct[i].EndHour == time.wHour && HappyStruct[i].EndMin == time.wMinute)
			{

				MessaageAllGlobal("[Happy Hour] Event Close!");
				StartHappyHour = false;
				break;
			}
		}
	}
}