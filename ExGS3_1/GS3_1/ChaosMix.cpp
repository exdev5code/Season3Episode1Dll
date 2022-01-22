#include "USER.h"
#include "Protocol.h"
#include "Defines.h"
#include "ChaosMix.h"
#include "Item.h"
#include "Functions.h"
#include "MixList.h"


int ItemRange (DWORD gObjId, WORD ItemIDStart, WORD ItemIDEnd)
{
	DWORD * inv = (DWORD*) (OBJECT_BASE + (OBJECT_SIZE * gObjId) + gObj_CBOX);

	for (BYTE i = 0 ; i < 32 ; i ++)
	{
		WORD * pitemId = (WORD*) ((i * GS_ITEMSIZE) + *inv + 6);
		if ((*pitemId >= ItemIDStart) && (*pitemId <= ItemIDEnd)) 
		{
			return 1;
		}
	}
	return 0;
}

bool gObjGetItemInChaosbox(int aIndex, short type) {
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	int count = 0;

	for(unsigned i = 0; i < 32; i++)
	{
		if(gObj->pChaosBox[i].m_Type == type)
			return true;
	}
	return false;
}

int gObjGetItemLevelInChaosbox(int aIndex, short type) 
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	int count = 0;

	for(unsigned i = 0; i < 32; i++)
	{
		if(gObj->pChaosBox[i].m_Type == type)
			return gObj->pChaosBox[i].m_Level;
	}
	return 1;
}

void __declspec(naked) ChaosBoxItemsRegardingEx() 
{
	_asm 
	{
		/*
		CPU Disasm
Address   Hex dump          Command                                  Comments
005C47C7   .  8B4D 88       MOV ECX,DWORD PTR SS:[EBP-78]
005C47CA   .  0FBF51 06     MOVSX EDX,WORD PTR DS:[ECX+6]
005C47CE   .  81FA 0D1C0000 CMP EDX,1C0D
005C47D4   .  74 2C         JE SHORT 005C4802
*/
		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(12,15)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,13)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,106)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,107)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,108)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,109)
		je ItemAllowed

		mov ecx, dword ptr ss:[ebp-0x78]
		movsx edx, word ptr ds:[ecx+0x6]
		cmp edx, ITEMGET(14,110)
		je ItemAllowed
		/*
		cmp eax, ITEM(12,15)
			je ItemAllowed

			cmp eax, ITEM(14,16)
			je ItemAllowed

			cmp eax, ITEM(14,31)
			je ItemAllowed

			cmp eax, ITEM(14,22)
			je ItemAllowed

			cmp eax, ITEM(14,42)
			je ItemAllowed

			cmp eax, ITEM(14,106)
			je ItemAllowed

			cmp eax, ITEM(14,107)
			je ItemAllowed

			cmp eax, ITEM(14,108)
			je ItemAllowed

			cmp eax, ITEM(14,109)
			je ItemAllowed

			cmp eax, ITEM(14,110)
			je ItemAllowed

			cmp eax, ITEM(14,13)
			je ItemAllowed

			cmp eax, ITEM(14,14)
			je ItemAllowed
			*/
			mov edi, 0x005C47D6
			jmp edi;

ItemAllowed:
		mov edi, 0x005C4802
			jmp edi;
	}
}

void ChaosMixSendFail(int gObjID) 
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	ChaosBoxInit(gObj);
	GCUserChaosBoxSend(gObj, 0);
	PMSG_CHAOSBOX_RESULT Msg = {0xC1, 0x0A, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	DataSend(gObjID, (unsigned char*)&Msg, 10);
}

void ChaosMixSendSuccess(ITEMSTRUCT *ChaosItem, int aIndex) 
{	
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	ChaosBoxInit(gObj);
	ItemSerialCreateSend(aIndex, 255, 0, 0, ChaosItem->m_Type, ChaosItem->m_Level, (int)ChaosItem->m_Durability, ChaosItem->m_SetiSkill, ChaosItem->m_SetiLuck, ChaosItem->m_SetiOption, -1, ChaosItem->m_SetiExcellent, 0);
}

void ChaosBoxHook(DWORD gObjID , DWORD MixID) 
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjID);
	
	switch (MixID)
	{
	case 100:
		ChaosPack(gObjID);
		break;

	case 101:
		LifePack(gObjID);
		break;

	case 102:
		CreationPack(gObjID);
		break;

	case 103:
		GuardionPack(gObjID);
		break;

	case 104:
		HarmonyPack(gObjID);
		break;

	case 105:
		ChaosUnPack(gObjID);
		break;

	case 106:
		LifeUnPack(gObjID);
		break;

	case 107:
		CreationUnPack(gObjID);
		break;

	case 108:
		GuardionUnPack(gObjID);
		break;

	case 109:
		HarmonyUnPack(gObjID);
		break;

	default: break;
	}
}