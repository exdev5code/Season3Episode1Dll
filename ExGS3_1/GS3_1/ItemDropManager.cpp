#include "StdAfx.h"
#include "Defines.h"
#include "USER.h"
#include "ItemDropManager.h"
#include "Utilits.h"
#include "Message.h"


cItemDropManager ItemDropManager;

void cItemDropManager::LoadFiles()
{
	FILE *file;
	file = fopen(_ITEM_DROP_MANAGER_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\ItemDropManager.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;
	CountMob = 0;
	CountMap = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;

		if(Flag == 1)
		{
			int n[15];
			sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],&n[10],&n[11],&n[12],&n[13]);

			ItemMob[CountMob].Mob			= 0;
			ItemMob[CountMob].Type			= 0;
			ItemMob[CountMob].Index			= 0;
			ItemMob[CountMob].Level			= 0;
			ItemMob[CountMob].Options		= 0;
			ItemMob[CountMob].Luck			= 0;
			ItemMob[CountMob].LuckDropRate	= 0;
			ItemMob[CountMob].Skill			= 0;
			ItemMob[CountMob].SkillDropRate = 0;
			ItemMob[CountMob].Exe			= 0;
			ItemMob[CountMob].ExeDropRate	= 0;
			ItemMob[CountMob].Anc			= 0;
			ItemMob[CountMob].AncDropRate	= 0;
			ItemMob[CountMob].ItemDropRate  = 0;
			//запись
			ItemMob[CountMob].Mob			= n[0];
			ItemMob[CountMob].Type			= n[1];
			ItemMob[CountMob].Index			= n[2];
			ItemMob[CountMob].Level			= n[3];
			ItemMob[CountMob].Options		= n[4];
			ItemMob[CountMob].Luck			= n[5];
			ItemMob[CountMob].LuckDropRate	= n[6];
			ItemMob[CountMob].Skill			= n[7];
			ItemMob[CountMob].SkillDropRate = n[8];
			ItemMob[CountMob].Exe			= n[9];
			ItemMob[CountMob].ExeDropRate	= n[10];
			ItemMob[CountMob].Anc			= n[11];
			ItemMob[CountMob].AncDropRate	= n[12];
			ItemMob[CountMob].ItemDropRate  = n[13];
			CountMob++;
		}

		if(Flag == 2)
		{
			int n[17];
			sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],&n[10],&n[11],&n[12],&n[13],&n[14],&n[15]);

			ItemMap[CountMap].Map			= 0;
			ItemMap[CountMap].Type			= 0;
			ItemMap[CountMap].Index			= 0;
			ItemMap[CountMap].Level			= 0;
			ItemMap[CountMap].Options		= 0;
			ItemMap[CountMap].Luck			= 0;
			ItemMap[CountMap].LuckDropRate	= 0;
			ItemMap[CountMap].Skill			= 0;
			ItemMap[CountMap].SkillDropRate = 0;
			ItemMap[CountMap].Exe			= 0;
			ItemMap[CountMap].ExeDropRate	= 0;
			ItemMap[CountMap].Anc			= 0;
			ItemMap[CountMap].AncDropRate	= 0;
			ItemMap[CountMap].MobMinLvl		= 0;
			ItemMap[CountMap].MobMaxLvl		= 0;
			ItemMap[CountMap].ItemDropRate  = 0;

			ItemMap[CountMap].Map			= n[0];
			ItemMap[CountMap].Type			= n[1];
			ItemMap[CountMap].Index			= n[2];
			ItemMap[CountMap].Level			= n[3];
			ItemMap[CountMap].Options		= n[4];
			ItemMap[CountMap].Luck			= n[5];
			ItemMap[CountMap].LuckDropRate	= n[6];
			ItemMap[CountMap].Skill			= n[7];
			ItemMap[CountMap].SkillDropRate = n[8];
			ItemMap[CountMap].Exe			= n[9];
			ItemMap[CountMap].ExeDropRate	= n[10];
			ItemMap[CountMap].Anc			= n[11];
			ItemMap[CountMap].AncDropRate	= n[12];
			ItemMap[CountMap].MobMinLvl		= n[13];
			ItemMap[CountMap].MobMaxLvl		= n[14];
			ItemMap[CountMap].ItemDropRate  = n[15];
			//MessageBoxA(0,(LPCSTR)ItemMap[CountMap].Anc,"CRITICAL ERROR",0);
			CountMap++;

		}
	}
	fclose(file);
}

void cItemDropManager::Process(int aIndex, int mIndex)
{
	ClassProcessMob(aIndex, mIndex);
	ClassProcessMap(aIndex, mIndex);
}
void cItemDropManager::ClassProcessMob(int aIndex, int mIndex)
{
	OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	for(int i=0;i<CountMob;i++)
	{
		if(mObj->Class == ItemMob[i].Mob)
		{
			if ( (rand()%10000) < ItemMob[i].ItemDropRate )
			{
				int iLuck	= 0;
				int iSkill	= 0;
				int iExe	= 0;
				int iAnc	= 0;

				int Type = ITEMGET(ItemMob[i].Type,ItemMob[i].Index);
						
				if(ItemMob[i].Luck)
				{
					if(ItemMob[i].LuckDropRate > (rand()%100))
					{
						iLuck = 1;
					}
				}

				if(ItemMob[i].Skill)
				{
					if(ItemMob[i].SkillDropRate > (rand()%100))
					{
						iSkill = 1;
					}
				}

				if(ItemMob[i].Exe)
				{
					if(ItemMob[i].ExeDropRate > (rand()%100))
					{
						iExe = GenExcOpt(ItemMob[i].Exe);
					}
				}

				if(ItemMob[i].Anc == 5 || ItemMob[i].Anc == 10)
				{
					if(ItemMob[i].AncDropRate > (rand()%100))
					{
						iAnc = ItemMob[i].Anc;
					}
				}

				ItemSerialCreateSend(mIndex,mObj->MapNumber,mObj->X,mObj->Y,Type,ItemMob[i].Level,0,iSkill,iLuck,ItemMob[i].Options,aIndex,iExe,iAnc);
				return;
			}
		}
	}
}

void cItemDropManager::ClassProcessMap(int aIndex, int mIndex)
{
	OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	for(int i=0;i<CountMap;i++)
	{
		if ( mObj->MapNumber == ItemMap[i].Map || ItemMap[i].Map == -1 )
		{
			if ( mObj->Level >= ItemMap[i].MobMinLvl && mObj->Level <= ItemMap[i].MobMaxLvl )
			{
				if ( (rand()%10000) < ItemMap[i].ItemDropRate )
				{
					int iLuck	= 0;
					int iSkill	= 0;
					int iExe	= 0;
					int iAnc	= 0;

					int Type = ITEMGET(ItemMap[i].Type,ItemMap[i].Index);
						
					if(ItemMap[i].Luck)
					{
						if(ItemMap[i].LuckDropRate > (rand()%100))
						{
							iLuck = 1;
						}
					}

					if(ItemMap[i].Skill)
					{
						if(ItemMap[i].SkillDropRate > (rand()%100))
						{
							iSkill = 1;
						}
					}

					if(ItemMap[i].Exe)
					{
						if(ItemMap[i].ExeDropRate > (rand()%100))
						{
							iExe = GenExcOpt(ItemMap[i].Exe);
						}
					}

					if(ItemMap[i].Anc == 5 || ItemMap[i].Anc == 10)
					{
						if(ItemMap[i].AncDropRate > (rand()%100))
						{
							iAnc = ItemMap[i].Anc;
						}
					}
					ItemSerialCreateSend(mIndex,mObj->MapNumber,mObj->X,mObj->Y,Type,ItemMap[i].Level,0,iSkill,iLuck,ItemMap[i].Options,aIndex,iExe,iAnc);
					return;
				}
			}
		}
	}
}

