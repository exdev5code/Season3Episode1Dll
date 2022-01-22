#include "Protocol.h"
#include "MixList.h"
#include "Item.h"
#include "USER.h"
#include "Defines.h"
#include "ChaosMix.h"
#include "Functions.h"

void ChaosPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(12,15));
	int CombinationCheckSum = Item1 * 15;
	int Percent				= 100;
	int Zen					= 250000;

	if (CombinationCheckSum >= 15)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,106);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	} 
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void LifePack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,16));
	int CombinationCheckSum = Item1 * 15;
	int Percent				= 100;
	int Zen					= 250000;

	if (CombinationCheckSum >= 15)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,107);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	} 
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void CreationPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,22));
	int CombinationCheckSum = Item1 * 15;
	int Percent				= 100;
	int Zen					= 250000;

	if (CombinationCheckSum >= 15)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,108);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	} 
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void GuardionPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,31));
	int CombinationCheckSum = Item1 * 15;
	int Percent				= 100;
	int Zen					= 250000;

	if (CombinationCheckSum >= 15)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,109);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	} 
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void HarmonyPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,42));
	int CombinationCheckSum = Item1 * 15;
	int Percent				= 100;
	int Zen					= 250000;

	if (CombinationCheckSum >= 15)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,110);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	} 
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void ChaosUnPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,106));
	int CombinationCheckSum = Item1;
	int Percent				= 100;
	int Zen					= 250000;
	int iEmptyCount			= 0;
	int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	DWORD Item				= ItemType*512+ItemNr;
	int Repeat				= 0;

	if (CombinationCheckSum >= 1)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(12,15);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);


			do
			{
				ItemSerialCreateSend(gObjID,235,gObj->X,gObj->Y,ITEMGET(12,15),ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjID,ItemExc,0);
				Repeat++;
			} while (Repeat < 14);
			Repeat=0;
			return;
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	}
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void LifeUnPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,107));
	int CombinationCheckSum = Item1;
	int Percent				= 100;
	int Zen					= 250000;
	int iEmptyCount			= 0;
	int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	DWORD Item				= ItemType*512+ItemNr;
	int Repeat				= 0;

	if (CombinationCheckSum >= 1)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,16);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);

			do
			{
				ItemSerialCreateSend(gObjID,235,gObj->X,gObj->Y,ITEMGET(14,16),ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjID,ItemExc,0);
				Repeat++;
			} while (Repeat < 14);
			Repeat=0;
			return;
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	}
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void CreationUnPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,108));
	int CombinationCheckSum = Item1;
	int Percent				= 100;
	int Zen					= 250000;
	int iEmptyCount			= 0;
	int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	DWORD Item				= ItemType*512+ItemNr;
	int Repeat				= 0;

	if (CombinationCheckSum >= 1)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,22);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);

			do
			{
				ItemSerialCreateSend(gObjID,235,gObj->X,gObj->Y,ITEMGET(14,22),ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjID,ItemExc,0);
				Repeat++;
			} while (Repeat < 14);
			Repeat=0;
			return;
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	}
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void GuardionUnPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,109));
	int CombinationCheckSum = Item1;
	int Percent				= 100;
	int Zen					= 250000;
	int iEmptyCount			= 0;
	int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	DWORD Item				= ItemType*512+ItemNr;
	int Repeat				= 0;

	if (CombinationCheckSum >= 1)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,31);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);

			do
			{
				ItemSerialCreateSend(gObjID,235,gObj->X,gObj->Y,ITEMGET(14,31),ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjID,ItemExc,0);
				Repeat++;
			} while (Repeat < 14);
			Repeat=0;
			return;
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	}
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 

void HarmonyUnPack(DWORD gObjID)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ITEMSTRUCT ChaosItem;

	int Item1				= gObjGetItemInChaosbox(gObjID,ITEMGET(14,110));
	int CombinationCheckSum = Item1;
	int Percent				= 100;
	int Zen					= 250000;
	int iEmptyCount			= 0;
	int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	DWORD Item				= ItemType*512+ItemNr;
	int Repeat				= 0;

	if (CombinationCheckSum >= 1)
	{
		//srand(time(NULL));
		//DWORD dwRand = rand();
		//if(dwRand % Percent >= (100-Percent))
		if(Percent >= (rand()%100))
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);

			ChaosItem.m_Type			= ITEMGET(14,42);
			ChaosItem.m_Level			= 0;
			ChaosItem.m_Durability		= 0;
			ChaosItem.m_SetiLuck		= 0;
			ChaosItem.m_SetiOption		= 0;
			ChaosItem.m_SetiSkill		= 0;
			ChaosItem.m_SetiExcellent	= 0;

			ChaosMixSendSuccess(&ChaosItem, gObjID);

			do
			{
				ItemSerialCreateSend(gObjID,235,gObj->X,gObj->Y,ITEMGET(14,42),ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjID,ItemExc,0);
				Repeat++;
			} while (Repeat < 14);
			Repeat=0;
			return;
		}
		else
		{
			gObj->Money-=(Zen);
			GCMoneySend(gObjID, gObj->Money);
			ChaosMixSendFail(gObjID);
		}
	}
	else 
	{
		ChaosMixSendFail(gObjID);
	}
} 