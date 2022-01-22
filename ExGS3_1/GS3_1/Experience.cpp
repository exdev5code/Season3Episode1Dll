#include "StdAfx.h"
#include "Experience.h"
#include "USER.h"
#include "Message.h"
#include "Defines.h"
#include "VipSystem.h"
#include "HappyHour.h"


Experience cExperience;

bool Experience::IsBadFileLine(char *FileLine, int &Flag)
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
void Experience::ExpConfig()
{
	for(int i(0);i<255;i++)
	{
		Number[i].Res = 0;
		Number[i].Exp = 0;
	}
}
void Experience::ExpLoad ()
{
	ExpConfig();
	Enable = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\Experience.ini");
	FILE *file;
	file = fopen("..\\Settings\\Experience.ini","r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\Experience.ini Load Error","CRITICAL ERROR",0);
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
			int n[5];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			Number[Count].Res = n[0];
			Number[Count].Exp = n[1];
			if(-100 >= n[1] || n[1] >= 1000)
			{
				MessageBoxA(0,"Min -99 and Max 999","Critical Error",0);
				ExitProcess(1);
				return;
			}
			Count++;
		}
	}
	fclose(file);
}

void iExpAdder (int aIndex, int TargetIndex, int Exp, int AttackDamage, BOOL MSBFlag)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	unsigned int pNewExperience = Exp;
	if(cExperience.Enable)
	{
		int pBonusExp = 0;
		int CharReset = ExUser[aIndex].Resets;
		
		for (int i=0; i < cExperience.Count; i++)
		{
			if(pNewExperience < 100)
				break;

			if(CharReset < cExperience.Number[i].Res)
				break;

			if(cExperience.Number[i].Res == CharReset)
			{
				pBonusExp = (( pNewExperience / 100 ) * cExperience.Number[i].Exp);
				pNewExperience += pBonusExp;
				gObj->Experience += pBonusExp;
				//MsgNormal(aIndex,"%d / %d / %d / %d / %d / %d",Exp,pNewExperience,pBonusExp,
				//	cExperience.Number[i].Exp,
				//	cExperience.Number[i].Res);
				break;
			}
		}
	}
	
	//VipSystem
	if(Vip.EnableVipSystem != 0 && ExUser[aIndex].VipStatus == 1)
	{
		int ExVipBonus = (pNewExperience / 100) * Vip.PlusExp;
		pNewExperience += ExVipBonus;
		gObj->Experience += ExVipBonus;
	}
	//HappyHour
	if(HappyHour.Enable != 0 && HappyHour.StartHappyHour == true)
	{
		int HappyHourBonus = (pNewExperience / 100) * HappyHour.PlusExp;
		pNewExperience += HappyHourBonus;
		gObj->Experience += HappyHourBonus;
	}
	//MsgNormal(aIndex,"Obtained %d Exp",pNewExperience);
	GCKillPlayerExpSend(aIndex,TargetIndex,pNewExperience,AttackDamage,MSBFlag);
}
