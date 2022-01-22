#include "User.h"
#include "Protocol.h"
#include "Item.h"
#include "USER.h"
#include "Defines.h"
#include "CQuery.h"
#include "Offtrade.h"
#include "Defines.h"
#include "Message.h"

//==========================
// NPC Buffer
//==========================
int NPCNumber = GetPrivateProfileInt("Common","NPCNumber",371,"..\\Settings\\Buffer.ini");
int NPCMap    = GetPrivateProfileInt("Common","NPCMap",0,"..\\Settings\\Buffer.ini");
int NPCX      = GetPrivateProfileInt("Common","NPCX",122,"..\\Settings\\Buffer.ini");
int NPCY      = GetPrivateProfileInt("Common","NPCY",114,"..\\Settings\\Buffer.ini");

int MinLevel        = GetPrivateProfileInt("BuffPrice","MinLevel",1,"..\\Settings\\Buffer.ini");
int MaxLevel        = GetPrivateProfileInt("BuffPrice","MaxLevel",20,"..\\Settings\\Buffer.ini");
int NeedItem        = GetPrivateProfileInt("BuffPrice","NeedItem",1,"..\\Settings\\Buffer.ini");
unsigned int ItemID = GetPrivateProfileInt("BuffPrice","ItemID",6159,"..\\Settings\\Buffer.ini");
int ItemCount       = GetPrivateProfileInt("BuffPrice","ItemCount",1,"..\\Settings\\Buffer.ini");
int ItemLevel       = GetPrivateProfileInt("BuffPrice","ItemLevel",0,"..\\Settings\\Buffer.ini");
int ZenPrice        = GetPrivateProfileInt("BuffPrice","ZenPrice",0,"..\\Settings\\Buffer.ini");

int MSBuffEnable    = GetPrivateProfileInt("ManaShield","BuffWork",1,"..\\Settings\\Buffer.ini");
int MSBuffTime      = GetPrivateProfileInt("ManaShield","BuffTime",60,"..\\Settings\\Buffer.ini");
int MSEnergy        = GetPrivateProfileInt("ManaShield","Energy",32000,"..\\Settings\\Buffer.ini");

int MLBuffEnable    = GetPrivateProfileInt("MaxLifeBuff","BuffWork",1,"..\\Settings\\Buffer.ini");
int MLBuffTime      = GetPrivateProfileInt("MaxLifeBuff","BuffTime",32000,"..\\Settings\\Buffer.ini");
int MLEnergy        = GetPrivateProfileInt("MaxLifeBuff","Energy",32000,"..\\Settings\\Buffer.ini");
int MLVitality      = GetPrivateProfileInt("MaxLifeBuff","Vitality",32000,"..\\Settings\\Buffer.ini");

//==========================
// Buffs
//==========================
void BuffsInit (int aIndex, int aNPC) 
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);

	if(MSBuffEnable == 1)
	{
		gObj->m_WizardSkillDefenseTime = MSBuffTime;
		gObj->m_WizardSkillDefense = (MSEnergy) / 40 + 60;
		gObj->m_ViewSkillState |= 0x1u;
		GCStateInfoSend((DWORD)gObj,1,256);
	}
	if(MLBuffEnable == 1)
	{
		gObj->AddLife -= gObj->m_SkillAddLife;
		gObj->AddLife += (gObj->MaxLife) * ((MLEnergy) / 20 + (MLVitality) / 100 + 13) / 100;
		LifeReFill(gObj->m_Index,WORD(gObj->MaxLife + gObj->AddLife),0xFE,0,gObj->iMaxShield + gObj->iAddShield);
		gObj->m_SkillAddLife = (gObj->MaxLife) * ((MLEnergy) / 20 + (MLVitality) / 100 + 13) / 100;
		gObj->m_SkillAddLifeTime = MLBuffTime;
		gObj->m_ViewSkillState |= 0x10u;
		GCStateInfoSend((DWORD)gObj,1,16);
	}
}
//==========================
// Buffer Init
//==========================
void NPCBuffer (int aIndex, int aNPC)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);

	if ((gObjNPC->Class == NPCNumber) && (gObjNPC->MapNumber == NPCMap) && (gObjNPC->X == NPCX) && (gObjNPC->Y == NPCY)) 
	{
		if((gObj->Level >= MinLevel) && (gObj->Level <= MaxLevel))
		{
			
			if(NeedItem == 1)
			{
				if((gObjGetItemCountInInventory(aIndex,ItemID,ItemLevel) >= ItemCount) && (gObj->Money >= ZenPrice))
				{
					BuffsInit (aIndex,aNPC);

					gObjDeleteItemsCount(aIndex,ItemID,0,ItemCount);
					(gObj->Money -= ZenPrice);
					GCMoneySend(gObj->m_Index, gObj->Money);

					ChatTargetSendNogs(gObjNPC,"Buff succefull added",aIndex);
				}
				else
				{       	
					char Text[70];
					sprintf(Text, "You need %d cnt of special item & %d Zen to buff",ItemCount, ZenPrice);
					ChatTargetSendNogs(gObjNPC,Text,aIndex);
				}
			}
			else
			{
				if(gObj->Money >= ZenPrice)
				{
					BuffsInit (aIndex,aNPC);

					(gObj->Money -= ZenPrice);
					GCMoneySend(gObj->m_Index, gObj->Money);

					ChatTargetSendNogs(gObjNPC,"Buff succefull added",aIndex);
				}
				else
				{
					char Text3[70];
					sprintf(Text3, "You need above %d Zen to buff",ZenPrice);
					ChatTargetSendNogs(gObjNPC,Text3,aIndex);
				}
			}
		}
		else
		{
			char Text2[70];
			sprintf(Text2, "Sorry, i dont add buff to you, you level above %d",MaxLevel);
			ChatTargetSendNogs(gObjNPC,Text2,aIndex);
		}
	}
}

//==================================================================================================
// New NPC Adder
//==================================================================================================
void NewNPC(int aIndex, int aNPC)
{
	int NPCBufferOn = GetPrivateProfileInt("Common","NPCWork",1,"..\\Settings\\Buffer.ini");

	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	if(NPCBufferOn == 1)
	{
		NPCBuffer(aIndex,aNPC);
	}
}
