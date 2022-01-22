#include "Models.h"
#include "stdafx.h"
#include "utils.h"
#include "Config.h"
//=======================================================================================================================
// Model Loader
//=======================================================================================================================
char* WaytoCustomz = "Data\\Custom\\Item\\";
char* CustomzFolder = "Custom\\Item\\";
//=======================================================================================================================
int Flag = 2;

void LoadThisFuckingModelByITEMID(int ItemID,char* ModelName,char* FolderFrom,char* WayFrom)
{
	_asm
	{
		PUSH -1
		PUSH ModelName                   	
		PUSH WayFrom
		PUSH ItemID
		mov eax,BMDModelLoad 
		CALL eax  

		PUSH 1
		PUSH 0x2600
		PUSH 0x2901
		PUSH FolderFrom                  		 	; |Arg2 = 0090175C ASCII "Item\"
		PUSH ItemID                                 ; |Arg1 = 00001FF1
		mov eax,OpenTexture
		CALL eax
	}
}

__declspec(naked) void PatchMainForLoadModels()
{

/*
14:89     "Bronze Coin"
14:90     "Silver Coin"
14:91     "Golden Coin"		
14:92     "Platina Coin"
14:102    "Artifact Of Knight"		
14:103    "Artifact Of Mage"	
14:104    "Artifact Of Elf"		
14:105    "Artifact Of Gladiator"	
14:106    "Artifact Of Lord"		
*/
//=======================================================================================================================
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,31),"JewelOfGuardion",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,89),"BronzeCoin",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,90),"SilverCoin",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,91),"GoldenCoin",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,92),"PlatinaCoin",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,101),"JewelOfFire2",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,102),"JewelOfFire",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,103),"JewelOfLight",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,104),"JewelOfWind",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,105),"JewelOfNew",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,106),"ChaosPack",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,107),"LifePack",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,108),"CreationPack",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,109),"GuardianPack",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,110),"HarmonyPack",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,98),"JewelOfAncent",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,97),"JewelofJustice",CustomzFolder,WaytoCustomz);
	LoadThisFuckingModelByITEMID(ITEM_IN_MAIN(14,96),"GEM",CustomzFolder,WaytoCustomz);
//=======================================================================================================================
	_asm
	{
		PUSH -1								; /Arg4 = FFFFFFFF
		PUSH 0x0093693C						; |Arg3 = 00900014 ASCII "suho"
		PUSH 0x00936944						; |Arg2 = 0090001C ASCII "Data\Item\"
		PUSH 0x1F96							; |Arg1 = 00001F84
		mov eax,BMDModelLoad 
		CALL eax                   			; \Main.005F1BC3
		ADD ESP,0x10
		mov eax,ReturnOffset
		JMP eax
	}
}


__inline __declspec(naked) void ModelsFloat()
{
 _asm
    {
CMP ESI,0x1EB6
JE Float
CMP ESI,ITEM2(14,89)
JE Float
CMP ESI,ITEM2(14,90)
JE Float
CMP ESI,ITEM2(14,91)
JE Float
CMP ESI,ITEM2(14,92)
JE Float
CMP ESI,ITEM2(14,96)
JE Float

mov eax,0x00650966
JMP eax

Float:
mov eax,0x00650BA9
JMP eax
	 }
} 

void ModelsLoad()
{
	DataJMP ModelJMP;
	SetNop(LoadModel_Offset,25);
	ModelJMP.Command=0xE9;
	ModelJMP.PointerToFunc=(DWORD)&PatchMainForLoadModels;
	memcpy((int*)LoadModel_Offset,&ModelJMP,sizeof(ModelJMP));
	HookThis((DWORD)&PatchMainForLoadModels,LoadModel_Offset);

	SetNop(0x0065095A,12);
	HookOffset((DWORD)&ModelsFloat, 0x0065095A, 0xE9); 
}