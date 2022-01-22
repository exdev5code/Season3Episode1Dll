#include "Protocol.h"
#include "Item.h"
#include "USER.h"
#include "Defines.h"
#include "Message.h"

//==================================================================================================
// Jewels Pack System
//==================================================================================================
int repeat2;
int PackPrice = GetPrivateProfileInt("Common","PackPrice",1000000,"..\\Settings\\PackSystem.ini");
int UnPackPrice = GetPrivateProfileInt("Common","UnPackPrice",1000000,"..\\Settings\\PackSystem.ini");

int LifeCount = GetPrivateProfileInt("LifePack","GemCount",10,"..\\Settings\\PackSystem.ini");
unsigned int LifePack = GetPrivateProfileInt("LifePack","PackItem",7275,"..\\Settings\\PackSystem.ini");

int ChaosCount = GetPrivateProfileInt("ChaosPack","GemCount",10,"..\\Settings\\PackSystem.ini");
unsigned int ChaosPack = GetPrivateProfileInt("ChaosPack","PackItem",7274,"..\\Settings\\PackSystem.ini");

int CreationCount = GetPrivateProfileInt("CreationPack","GemCount",10,"..\\Settings\\PackSystem.ini");
unsigned int CreationPack = GetPrivateProfileInt("CreationPack","PackItem",7276,"..\\Settings\\PackSystem.ini");

int GuardionCount = GetPrivateProfileInt("GuardionPack","GemCount",10,"..\\Settings\\PackSystem.ini");
unsigned int GuardionPack = GetPrivateProfileInt("GuardionPack","PackItem",7277,"..\\Settings\\PackSystem.ini");

int HarmonyCount = GetPrivateProfileInt("HarmonyPack","GemCount",10,"..\\Settings\\PackSystem.ini");
unsigned int HarmonyPack = GetPrivateProfileInt("HarmonyPack","PackItem",7278,"..\\Settings\\PackSystem.ini");

//==========================
// Jewel Of Life
//==========================
 void PackLife (DWORD gObjId)
{
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
 if(gObj->Money >= PackPrice)
 {
	 if((gObjGetItemCountInInventory(gObjId,0x1C10,0) < LifeCount))
	{
	 MsgNormal(gObjId,"[Pack] You dont have jewels to pack");
	 return;
	 }
	 gObjDeleteItemsCount(gObjId,0x1C10,0,LifeCount);
 
	 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;

	 DWORD Item = ItemType*512+ItemNr;

	 ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,LifePack,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
	 (gObj->Money -= PackPrice);
	 GCMoneySend(gObj->m_Index, gObj->Money);
	 MsgNormal(gObjId,"[Pack] Jewels packed");
	 return;
 }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",PackPrice);
 }
} 
//==========================
// UnPack
//==========================
void UnPackLife (DWORD gObjId)
{ 
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
 if(gObj->Money >= UnPackPrice)
 {
	if((gObjGetItemCountInInventory(gObjId,LifePack,0) < 1))
	{
	MsgNormal(gObjId,"[Pack] You dont have jewels to unpack");
	 return;
	 }
	int iEmptyCount = 0;

	 for ( int x=0;x<64;x++)
	 {
	 if ( gObj->pInventoryMap[x] == 0xFF )
	 {
	  iEmptyCount++;
	 }
	 }

	if ( iEmptyCount < LifeCount )
	{
	 MsgNormal(gObjId,"[Pack] You dont have inventory space");
	 }
	 else 
	 {
	 gObjDeleteItemsCount(gObjId,LifePack,0,1);
	 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
	 DWORD Item = ItemType*512+ItemNr;
	do
	{
	ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,0x1C10,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
	repeat2++;
	} while (repeat2 < LifeCount);
	(gObj->Money -= UnPackPrice);
	GCMoneySend(gObj->m_Index, gObj->Money);
	MsgNormal(gObjId,"[Pack] Jewels unpacked");
	 repeat2=0;
	 return;
	 }
 }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",UnPackPrice);
 }
}

//==========================
// Jewel Of Chaos
//==========================
 void PackChaos (DWORD gObjId)
{
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
  if(gObj->Money >= PackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,0x180F,0) < ChaosCount))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to pack");
 return;
 }
 gObjDeleteItemsCount(gObjId,0x180F,0,ChaosCount);
 
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;

 DWORD Item = ItemType*512+ItemNr;

 ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,ChaosPack,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
 (gObj->Money -= PackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);
 MsgNormal(gObjId,"[Pack] Jewels packed");
 return;
  }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",PackPrice);
 }

 }
//==========================
// UnPack
//==========================
void UnPackChaos (DWORD gObjId)
{ 
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
  if(gObj->Money >= UnPackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,ChaosPack,0) < 1))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to unpack");
 return;
 }
 int iEmptyCount = 0;

 for ( int x=0;x<64;x++)
 {
  if ( gObj->pInventoryMap[x] == 0xFF )
  {
   iEmptyCount++;
  }
 }

 if ( iEmptyCount < ChaosCount )
 {
  MsgNormal(gObjId,"[Pack] You dont have inventory space");
 }
 else 
 {
 gObjDeleteItemsCount(gObjId,ChaosPack,0,1);
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
 DWORD Item = ItemType*512+ItemNr;
do
{
ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,0x180F,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
repeat2++;
} while (repeat2 < ChaosCount);
 (gObj->Money -= UnPackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);

 MsgNormal(gObjId,"[Pack] Jewels unpacked"); 
 repeat2=0;
 return;
 }
  }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",UnPackPrice);
 }
}
//==================================================================================================
//NEW
//==================================================================================================
//==========================
// Jewel Of Creation
//==========================
 void PackCreation (DWORD gObjId)
{
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
   if(gObj->Money >= PackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,0x1C16,0) < CreationCount))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to pack");
 return;
 }
 gObjDeleteItemsCount(gObjId,0x1C16,0,CreationCount);
 
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;

 DWORD Item = ItemType*512+ItemNr;

 ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,CreationPack,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
 (gObj->Money -= PackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);
 MsgNormal(gObjId,"Jewels packed");
 return;
   }
  else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",PackPrice);
 }
 }
//==========================
// UnPack
//==========================
void UnPackCreation (DWORD gObjId)
{ 
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
   if(gObj->Money >= UnPackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,CreationPack,0) < 1))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to unpack");
 return;
 }
 int iEmptyCount = 0;

 for ( int x=0;x<64;x++)
 {
  if ( gObj->pInventoryMap[x] == 0xFF )
  {
   iEmptyCount++;
  }
 }

 if ( iEmptyCount < CreationCount )
 {
  MsgNormal(gObjId,"[Pack] You dont have inventory space");
 }
 else 
 {
 gObjDeleteItemsCount(gObjId,CreationPack,0,1);
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
 DWORD Item = ItemType*512+ItemNr;
do
{
ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,0x1C16,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
repeat2++;
} while (repeat2 < CreationCount);
 (gObj->Money -= UnPackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);

 MsgNormal(gObjId,"[Pack] Jewels unpacked"); 
 repeat2=0;
 return;
 }
   }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",UnPackPrice);
 }
}

//==========================
// Jewel Of Guardion
//==========================
 void PackGuardion (DWORD gObjId)
{
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
    if(gObj->Money >= PackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,0x1C1F,0) < GuardionCount))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to pack");
 return;
 }
 gObjDeleteItemsCount(gObjId,0x1C1F,0,GuardionCount);
 
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;

 DWORD Item = ItemType*512+ItemNr;

 ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,GuardionPack,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
 (gObj->Money -= PackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);
 MsgNormal(gObjId,"[Pack] Jewels packed");
 return;
    }
  else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",PackPrice);
 }
 }
//==========================
// UnPack
//==========================
void UnPackGuardion (DWORD gObjId)
{ 
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
    if(gObj->Money >= UnPackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,GuardionPack,0) < 1))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to unpack");
 return;
 }
 int iEmptyCount = 0;

 for ( int x=0;x<64;x++)
 {
  if ( gObj->pInventoryMap[x] == 0xFF )
  {
   iEmptyCount++;
  }
 }

 if ( iEmptyCount < GuardionCount )
 {
  MsgNormal(gObjId,"[Pack] You dont have inventory space");
 }
 else 
 {
 gObjDeleteItemsCount(gObjId,GuardionPack,0,1);
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
 DWORD Item = ItemType*512+ItemNr;
do
{
ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,0x1C1F,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
repeat2++;
} while (repeat2 < GuardionCount);
 (gObj->Money -= UnPackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);

 MsgNormal(gObjId,"[Pack] Jewels unpacked"); 
 repeat2=0;
 return;
 }
    }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",UnPackPrice);
 }
}
//==========================
// Jewel Of Harmony
//==========================
 void PackHarmony (DWORD gObjId)
{
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
    if(gObj->Money >= PackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,0x1C2A,0) < HarmonyCount))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to pack");
 return;
 }
 gObjDeleteItemsCount(gObjId,0x1C2A,0,HarmonyCount);
 
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;

 DWORD Item = ItemType*512+ItemNr;

 ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,HarmonyPack,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
 (gObj->Money -= PackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);
 MsgNormal(gObjId,"[Pack] Jewels packed");
 return;
     }
  else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",PackPrice);
 }
 }
//==========================
// UnPack
//==========================
void UnPackHarmony (DWORD gObjId)
{ 
 OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
     if(gObj->Money >= UnPackPrice)
 {
 if((gObjGetItemCountInInventory(gObjId,HarmonyPack,0) < 1))
 {
 MsgNormal(gObjId,"[Pack] You dont have jewels to unpack");
 return;
 }
 int iEmptyCount = 0;

 for ( int x=0;x<64;x++)
 {
  if ( gObj->pInventoryMap[x] == 0xFF )
  {
   iEmptyCount++;
  }
 }

 if ( iEmptyCount < HarmonyCount )
 {
  MsgNormal(gObjId,"[Pack] You dont have inventory space");
 }
 else 
 {
 gObjDeleteItemsCount(gObjId,HarmonyPack,0,1);
 int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
 DWORD Item = ItemType*512+ItemNr;
do
{
ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,0x1C2A,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
repeat2++;
} while (repeat2 < HarmonyCount);
 (gObj->Money -= UnPackPrice);
 GCMoneySend(gObj->m_Index, gObj->Money);

 MsgNormal(gObjId,"[Pack] Jewels unpacked"); 
 repeat2=0;
 return;
 }
     }
 else
 {
	 MsgNormal(gObjId,"[Pack] You need above %d Zen to Pack",UnPackPrice);
 }
}