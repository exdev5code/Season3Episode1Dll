#include "Protocol.h"
#include "USER.h"
#include <time.h>
#include "Defines.h"
#include "Jewels.h"
#include "AddFunctions.h"
#include "Message.h"


//==================================================================================================
// Set Default Item Options
//==================================================================================================
void ItemClear(int aIndex,int pos)	
{	
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	memset(gObj->pInventory[pos].m_Special, 0, sizeof(gObj->pInventory[pos].m_Special));
	memset(gObj->pInventory[pos].m_SpecialValue, 0, sizeof(gObj->pInventory[pos].m_SpecialValue));
	memset(gObj->pInventory[pos].m_Resistance, 0, sizeof(gObj->pInventory[pos].m_Resistance));

	gObj->pInventory[pos].m_Type =-1;
	gObj->pInventory[pos].m_Level =0;
	gObj->pInventory[pos].m_Part=0;
	gObj->pInventory[pos].m_Class=0;
	gObj->pInventory[pos].m_TwoHand=0;
	gObj->pInventory[pos].m_AttackSpeed=0;
	gObj->pInventory[pos].m_DamageMin=0;
	gObj->pInventory[pos].m_DamageMax=0;
	gObj->pInventory[pos].m_SuccessfulBlocking=0;
	gObj->pInventory[pos].m_Defense=0;
	gObj->pInventory[pos].m_MagicDefense =0;
	gObj->pInventory[pos].m_Durability=0;
	gObj->pInventory[pos].m_SpecialNum=0;
	gObj->pInventory[pos].m_Value=0;
	gObj->pInventory[pos].m_SetiSkill =0;      
	gObj->pInventory[pos].m_SetiLuck =0;  
	gObj->pInventory[pos].m_SetiOption =0;   
	gObj->pInventory[pos].m_SetiExcellent =0;
	gObj->pInventory[pos].m_Number =0;
	gObj->pInventory[pos].m_DurabilitySmall =0;
	gObj->pInventory[pos].m_iPShopValue=-1;
	gObj->pInventory[pos].m_bItemExist=true;
	gObj->pInventory[pos].m_CurrentDurabilityState=-1;
	gObj->pInventory[pos].m_SetOption=0;
	gObj->pInventory[pos].m_QuestItem=false;
	gObj->pInventory[pos].m_IsLoadPetItemInfo=0;
	gObj->pInventory[pos].m_PetItem_Level =1;
	gObj->pInventory[pos].m_PetItem_Exp =0;
	gObj->pInventory[pos].m_Leadership=0;
	gObj->pInventory[pos].m_JewelOfHarmonyOption = 0;
	gObj->pInventory[pos].m_ItemOptionEx = 0;
}

//==================================================================================================
// Jewels Adder
//==================================================================================================
void CGUseItemRecv(PMSG_USEITEM* lpMsg, int aIndex)
{	
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
//--------------------------------------------------------------------------------------------------
// [14:101] Jewel Of Luck [Luck in weapons]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,101))
	{	
		int WindJewelRate = GetPrivateProfileInt("Jewels","JewelOfLuckRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand (time(NULL));

		if(gObj->pInventory[lpMsg->invenrotyTarget].m_SetiLuck != 1)
		{
			if((rand()%100) <= WindJewelRate)
			{

				gObj->pInventory[lpMsg->invenrotyTarget].m_SetiLuck = 1;
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else 
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
		}
		else
		{
				MsgNormal(aIndex,"[Jewel] This Jewel not used to this item");
				return;
		}
	}
//--------------------------------------------------------------------------------------------------
// [14:102] Jewel Of Skill [Skill in weapons]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,102))
	{	
		int FireJewelRate = GetPrivateProfileInt("Jewels","JewelOfSkillRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );

		if((gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,3) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,4)  || 
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,5) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,6)  || 
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,7) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,8)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,9) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,10) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,11)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,12) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,13)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,14) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,15)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,16) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,17)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,18) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,19)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,20) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,21)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,22) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,23)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,24) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,25)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(0,31) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,0) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,1)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,2) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,3)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,4) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,5)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,6) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,8)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,9) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,10) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,11)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,12) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,13)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,14) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,16)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,17) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,18)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,19) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,20)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,21) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(4,22)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,4)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,6) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,7)  ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,13)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,12) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,11)|| gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,10) ||
			gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,9) || gObj->pInventory[lpMsg->invenrotyTarget].m_Type == ITEMGET(6,8)) &&
			(gObj->pInventory[lpMsg->invenrotyTarget].m_SetiSkill < 1))
		{
			if((rand()%100) < FireJewelRate)
			{	

				gObj->pInventory[lpMsg->invenrotyTarget].m_SetiSkill = 1;
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This Jewel not used to this item");
			return;
		}
	}
//--------------------------------------------------------------------------------------------------
// [14:103] Jewel Of Everest [Make excellent from normal]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,103))
	{	
		int ElemJewelRate = GetPrivateProfileInt("Jewels","JewelOfEverestRate",100,"..\\Settings\\Jewels.ini");
		int ExcellentOpt[5] = { 1, 4, 8, 16, 32 };
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );

		if((gObj->pInventory[lpMsg->invenrotyTarget].m_Type < ITEMGET(12,0)) && (gObj->pInventory[lpMsg->invenrotyTarget].m_SetiExcellent == 0))
		{	
			if((rand()%100) < ElemJewelRate)
			{

				gObj->pInventory[lpMsg->invenrotyTarget].m_SetiExcellent = ExcellentOpt[rand()% 4];
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This Jewel not used to this item");
			return;
		}
	}
//--------------------------------------------------------------------------------------------------
// [14:104] Jewel Of Level [Item level++ 9-13]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,104))
	{	
		int LightJewelRate = GetPrivateProfileInt("Jewels","JewelOfLevelRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );

		if((gObj->pInventory[lpMsg->invenrotyTarget].m_Level < 13) && (gObj->pInventory[lpMsg->invenrotyTarget].m_Level > 8))
		{	
			if((rand()%100) < LightJewelRate)
			{

				gObj->pInventory[lpMsg->invenrotyTarget].m_Level++;
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
			}
			else
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This Jewel not use to this item");
			return;
		}
	}
//--------------------------------------------------------------------------------------------------
// [14:105] Jewel Of Added [Add 28 options]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,105))
	{	
		int DarkJewelRate = GetPrivateProfileInt("Jewels","JewelOfAddedRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );

		if(gObj->pInventory[lpMsg->invenrotyTarget].m_SetiOption < 7)
		{	
			if((rand()%100) < DarkJewelRate)
			{

				gObj->pInventory[lpMsg->invenrotyTarget].m_SetiOption = 7;
				//gObj->pInventory[lpMsg->invenrotyTarget].m_SetOption = 5; // Ancente options add
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This Jewel not use to this item");
			return;
		}
	} 

//--------------------------------------------------------------------------------------------------
// [14:99] Jewel Of Ancent [Add Ancent Options options]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,98))
	{	
		int AnceJewelRate = GetPrivateProfileInt("Jewels","JewelOfAncentRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );

		if(gObj->pInventory[lpMsg->invenrotyTarget].m_SetOption != 5)
		{	
			if((rand()%100) < AnceJewelRate)
			{

				gObj->pInventory[lpMsg->invenrotyTarget].m_SetOption = 5; // Ancente options add
				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
			else
			{

				gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
				ItemClear(aIndex,lpMsg->inventoryPos);
				GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
				GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This Jewel not use to this item");
			return;
		}
	} 
//--------------------------------------------------------------------------------------------------
// [14:97] Jewel of Justice [Add Max Harmony Options]
//--------------------------------------------------------------------------------------------------
	if (gObj->pInventory[lpMsg->inventoryPos].m_Type == ITEMGET(14,97))
	{	
		int JusticeJewelRate = GetPrivateProfileInt("Jewels","JewelofJusticeRate",100,"..\\Settings\\Jewels.ini");
		//int iRate = rand()%100+1;
		//srand ( time(NULL) );
		if(gObj->pInventory[lpMsg->invenrotyTarget].m_Level == 13)
		{
			//Проверка на запрещенные вещи
			bool NextStage = true;
			if(TypeItemInt(gObj->pInventory[lpMsg->invenrotyTarget].m_Type)==12||TypeItemInt(gObj->pInventory[lpMsg->invenrotyTarget].m_Type)==13||
				TypeItemInt(gObj->pInventory[lpMsg->invenrotyTarget].m_Type)==14||TypeItemInt(gObj->pInventory[lpMsg->invenrotyTarget].m_Type)==15)
			{
				NextStage = false;
			}
			if(NextStage == true)
			{
				//Проверка стоит в шмотке уже хармони опция
				if(gObj->pInventory[lpMsg->invenrotyTarget].m_JewelOfHarmonyOption == 0)
				{	
					if((rand()%100) < JusticeJewelRate)
					{
						int TypeItemSwitch = TypeItemInt(gObj->pInventory[lpMsg->invenrotyTarget].m_Type);
						if(TypeItemSwitch>=0 && TypeItemSwitch <= 4)
						{
							int maxHarmonyOpt = 10; int HarmonyOpt[10] = { 29, 45, 61, 77, 93, 109, 125, 141, 157, 173};
							gObj->pInventory[lpMsg->invenrotyTarget].m_JewelOfHarmonyOption = HarmonyOpt[rand()% maxHarmonyOpt];
						}
						else
						{
							int maxHarmonyOpt = 8; int HarmonyOpt[8] = { 29, 45, 61, 77, 93, 109, 125, 141};
							gObj->pInventory[lpMsg->invenrotyTarget].m_JewelOfHarmonyOption = HarmonyOpt[rand()% maxHarmonyOpt];
						}

						gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
						ItemClear(aIndex,lpMsg->inventoryPos);
						GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
						GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);
					}
					else
					{

						gObjInventoryItemSet(aIndex,lpMsg->inventoryPos, -1);
						ItemClear(aIndex,lpMsg->inventoryPos);
						GCInventoryItemOneSend(aIndex, lpMsg->invenrotyTarget);
						GCInventoryItemDeleteSend(aIndex, lpMsg->inventoryPos, 1);	
					}
				}
				else
				{
					MsgNormal(aIndex,"[Jewel] This Jewel not use to this item");
					return;
				}
			}
			else
			{
				MsgNormal(aIndex,"[Jewel] This Jewel not use to this item");
				return;
			}
		}
		else
		{
			MsgNormal(aIndex,"[Jewel] This jewel is used in 13 level items");
			return;
		}
	} 
} 