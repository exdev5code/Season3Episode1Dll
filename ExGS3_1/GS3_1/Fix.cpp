#include "Fix.h"
#include "Defines.h"
#include "USER.h"
#include "Protocol.h"
#include "Functions.h"
#include "ChaosMix.h"
#include "StdAfx.h"

void HookOffset(DWORD my, DWORD tohook, BYTE type)
{
 *(BYTE*)tohook = type;
 *(DWORD*)(tohook+1) = my - (tohook+5);
}

void SetNop(DWORD dwOffset,int Size)
{
	for(int n=0;n<Size;n++)
		*(BYTE*)(dwOffset+n) = 0x90;
}

Fix g_Fix;

Fix::Fix(void)
{

}
Fix::~Fix(void)
{

}
	
int BronzeCoin			= GetPrivateProfileInt("Coins","BronzeCoin",100000000,"..\\Settings\\Price.ini");
int SilverCoin			= GetPrivateProfileInt("Coins","SilverCoin",250000000,"..\\Settings\\Price.ini");
int GoldenCoin			= GetPrivateProfileInt("Coins","GoldenCoin",500000000,"..\\Settings\\Price.ini");
int PlatinumCoin		= GetPrivateProfileInt("Coins","PlatinumCoin",1000000000,"..\\Settings\\Price.ini");

int JewelofJusticu		= GetPrivateProfileInt("Jewels","JewelofJusticu",2000000,"..\\Settings\\Price.ini");
int JewelofAncent		= GetPrivateProfileInt("Jewels","JewelofAncent",2000000,"..\\Settings\\Price.ini");
int JewelofMystical		= GetPrivateProfileInt("Jewels","JewelofMystical",2000000,"..\\Settings\\Price.ini");
int JewelofExelent		= GetPrivateProfileInt("Jewels","JewelofExelent",2000000,"..\\Settings\\Price.ini");
int JewelofLuck			= GetPrivateProfileInt("Jewels","JewelofLuck",2000000,"..\\Settings\\Price.ini");
int JewelofSkill		= GetPrivateProfileInt("Jewels","JewelofSkill",2000000,"..\\Settings\\Price.ini");
int JewelOfElement		= GetPrivateProfileInt("Jewels","JewelOfElement",2000000,"..\\Settings\\Price.ini");
int JewelOflevel		= GetPrivateProfileInt("Jewels","JewelOflevel",2000000,"..\\Settings\\Price.ini");
int JewelOfAdded		= GetPrivateProfileInt("Jewels","JewelOfAdded",2000000,"..\\Settings\\Price.ini");

int BounchOfChaos		= GetPrivateProfileInt("Packs","BounchOfChaos",2000000,"..\\Settings\\Price.ini");
int BounchOfLife		= GetPrivateProfileInt("Packs","BounchOfLife",2000000,"..\\Settings\\Price.ini");
int BounchOfCreation	= GetPrivateProfileInt("Packs","BounchOfCreation",2000000,"..\\Settings\\Price.ini");
int BounchOfGuardian	= GetPrivateProfileInt("Packs","BounchOfGuardian",2000000,"..\\Settings\\Price.ini");
int BounchOfHarmony		= GetPrivateProfileInt("Packs","BounchOfHarmony",2000000,"..\\Settings\\Price.ini");

__inline __declspec(naked) void Price()
{   
    _asm
    {	// Jewel Of chaos
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x180F
        JNZ Item1
		MOV DWORD PTR SS:[EBP-0x14], 0x3D090
		MOV DWORD PTR SS:[EBP-0x10], 0x00
	    JMP Exit 
//==========================================//
//					Coins					//
//==========================================//
Item1:  // Bronze Coin
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,89) 
        JNZ Item2
		MOV ECX, BronzeCoin
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
Item2:	// SilverCoin
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,90) 
        JNZ Item3
		MOV ECX, SilverCoin
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
Item3:	// GoldenCoin
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,91) 
        JNZ Item4
		MOV ECX, GoldenCoin
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
Item4:	// PlatinumCoin
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,92) 
        JNZ Item5
		MOV ECX, PlatinumCoin
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
//==========================================//
//					Jewels					//
//==========================================//
Item5:	// JewelofJusticu
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,97) 
        JNZ Item6
		MOV ECX, JewelofJusticu
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
Item6:	// JewelofAncent
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,98) 
        JNZ Item7
		MOV ECX, JewelofAncent
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item7:	// JewelofMystical
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,99) 
        JNZ Item8
		MOV ECX, JewelofMystical
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item8:	// JewelofExelent
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,100) 
        JNZ Item9
		MOV ECX, JewelofExelent	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item9:	// JewelofLuck
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,101) 
        JNZ Item10
		MOV ECX, JewelofLuck	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item10:	// JewelofSkill
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,102) 
        JNZ Item11
		MOV ECX, JewelofSkill	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item11:	// JewelOfElement
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,103) 
        JNZ Item12
		MOV ECX, JewelOfElement	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item12:	// JewelOflevel
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,104) 
        JNZ Item13
		MOV ECX, JewelOflevel	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item13:	// JewelOfAdded		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,105) 
        JNZ Item14
		MOV ECX, JewelOfAdded	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
//==========================================//
//					Packs					//
//==========================================//
Item14:	// BounchOfChaos		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,106) 
        JNZ Item15
		MOV ECX, BounchOfChaos	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item15:	// BounchOfLife		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,107) 
        JNZ Item16
		MOV ECX, BounchOfLife	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item16:	// BounchOfCreation		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,108) 
        JNZ Item17
		MOV ECX, BounchOfCreation	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item17:	// BounchOfGuardian		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,109) 
        JNZ Item18
		MOV ECX, BounchOfGuardian	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item18:	// BounchOfHarmony		
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,ITEMGET(14,110) 
        JNZ Continue
		MOV ECX, BounchOfHarmony	//Price
        MOV DWORD PTR SS:[EBP-0x14], ECX 
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Exit:
        mov esi,0x005F3B7F
        jmp esi
Continue:
		mov esi,0x005F2AD3
		jmp esi
    }
} 
//==============================================================================
// Item Price [005F36DE = 3]
//==============================================================================
/*
__inline __declspec(naked) void Price()
{   
    _asm
    {

        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x180F //[14:15] Jewel Of Chaos
        JNZ Item1
		MOV DWORD PTR SS:[EBP-0x14], 0xB71B0 // [750 000]
		MOV DWORD PTR SS:[EBP-0x10], 0x00
	    JMP Exit 
Item1: 
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C63 // [14:99]
        JNZ Item2
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit 
Item2:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C64 // [14:100]
        JNZ Item3
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item3:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C65 // [14:101]
        JNZ Item4
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item4:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C66 // [14:102]
        JNZ Item5
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item5:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C67 // [14:103]
        JNZ Item6
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item6:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C68 // [14:104]
        JNZ Item7
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item7:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C69 // [14:105]
        JNZ Item8
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item8:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C1F // [14:31] guardian
        JNZ Item9
        MOV DWORD PTR SS:[EBP-0x14], 0x3938700 // [60 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item9:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C62 // [14:98] Jewel Of Ancent
        JNZ Item10
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Item10:
        MOV EDX,DWORD PTR SS:[EBP-0x04]
        MOVSX EAX,WORD PTR DS:[EDX+0x06]
        CMP EAX,0x1C61 // [14:97] Jewel Of Justicu
        JNZ Continue
        MOV DWORD PTR SS:[EBP-0x14], 0x5F5E100 // [100 000 000]
        MOV DWORD PTR SS:[EBP-0x10], 0x00
        JMP Exit
Exit:
        mov esi,0x005F3B7F
        jmp esi
Continue:
		mov esi,0x005F2AD3
		jmp esi
    }
} 
*/
//==============================================================================
// Loader
//==============================================================================
void Fix::Load()
{
// Ancient+Excellent Options Fix
//==============================================================================
	g_Funtions.SetJmp(0x005F00C8);

//==============================================================================
// Item Price
//==============================================================================

	//*(unsigned int*)(0x005F4602+3) = GetPrivateProfileInt("Jewels","JewelOfBless",500000,"..\\Settings\\Price.ini");
	//*(unsigned int*)(0x005F461A+3) = GetPrivateProfileInt("Jewels","JewelOfSoul",500000,"..\\Settings\\Price.ini");
	//*(unsigned int*)(0x005F4632+3) = GetPrivateProfileInt("Jewels","JewelOfChaos",500000,"..\\Settings\\Price.ini");
	//*(unsigned int*)(0x005F4661+3) = GetPrivateProfileInt("Jewels","JewelOfLife",500000,"..\\Settings\\Price.ini");
	//*(unsigned int*)(0x005F4649+3) = GetPrivateProfileInt("Jewels","JewelOfCreation",500000,"..\\Settings\\Price.ini");
	//*(unsigned int*)(0x005F2C21+3) = GetPrivateProfileInt("Jewels","JewelOfGuardion",500000,"..\\Settings\\Price.ini");

	SetNop(0x005F2AB3,31);
	HookOffset((DWORD)&Price, 0x005F2AB3, 0xE9);

	SetNop(0x005C47C7,15);
	HookOffset((DWORD)&Price, 0x005C47C7, 0xE9);

	*(BYTE*)(0x005F00C8) = 0xEB;

	*(BYTE*)(0x005F3BEF+1) = 0x01; // Change % For Sell

//==============================================================================
// Chaos Mix
//==============================================================================
	BYTE ChaosBox[] = { 0xFF, 0x25, 0x00, 0xB6, 0x71, 0x00, 0x90, 0x90 };
	memcpy((int*)0x005C47C0,ChaosBox,sizeof(ChaosBox));
	*(unsigned int*)0x0071B600 = (unsigned int)ChaosBoxItemsRegardingEx; 

//==============================================================================
// GameServer Window 
//==============================================================================
	char cTemp[30] = "[-  ExTeam Game Server  -]";
    DWORD *offsetGSTitle = (DWORD*)(GameServerTitle);
    memset(&offsetGSTitle[0],0,30);
    memcpy(&offsetGSTitle[0],cTemp,strlen(cTemp));
	
	char cTemp1[31] = "[Dev]Skype: muonline.bk";
    DWORD *offsetWindowTitle = (DWORD*)(WindowGSTitle);
    memset(&offsetWindowTitle[0],0,31);
    memcpy(&offsetWindowTitle[0],cTemp1,strlen(cTemp1));
//==============================================================================
// Folders Changer
//==============================================================================
	char cTemp2[30];
    DWORD *offsetChatFolder = (DWORD*)(FolderChatLog);
    GetPrivateProfileStringA("Folders","LogChat","Logs\\Chat",cTemp2,30,"..\\Settings\\GameServer.ini");
    memset(&offsetChatFolder[0],0,30);
    memcpy(&offsetChatFolder[0],cTemp2,strlen(cTemp2));

	char cTemp3[30];
    DWORD *offsetCSFolder = (DWORD*)(FolderCastleSiege);
    GetPrivateProfileStringA("Folders","LogCastleSiege","Logs\\CastleSiege",cTemp3,30,"..\\Settings\\GameServer.ini");
    memset(&offsetCSFolder[0],0,30);
    memcpy(&offsetCSFolder[0],cTemp3,strlen(cTemp3));

	char cTemp4[30];
    DWORD *offsetKanturuFolder = (DWORD*)(FolderKanturu);
    GetPrivateProfileStringA("Folders","LogKanturu","Logs\\Kanturu",cTemp4,30,"..\\Settings\\GameServer.ini");
    memset(&offsetKanturuFolder[0],0,30);
    memcpy(&offsetKanturuFolder[0],cTemp4,strlen(cTemp4));

	char cTemp5[30];
    DWORD *offsetKundunFolder = (DWORD*)(FolderKundunGM);
    GetPrivateProfileStringA("Folders","LogKundun","Logs\\Kundun",cTemp5,30,"..\\Settings\\GameServer.ini");
    memset(&offsetKundunFolder[0],0,30);
    memcpy(&offsetKundunFolder[0],cTemp5,strlen(cTemp5));

	char cTemp6[30];
    DWORD *offsetKundun2Folder = (DWORD*)(FolderKundunEvent);
    GetPrivateProfileStringA("Folders","LogKundun","Logs\\Kundun",cTemp6,30,"..\\Settings\\GameServer.ini");
    memset(&offsetKundun2Folder[0],0,30);
    memcpy(&offsetKundun2Folder[0],cTemp6,strlen(cTemp6));

	char cTemp7[30];
    DWORD *offsetConnectFolder = (DWORD*)(FolderServerConnect);
    GetPrivateProfileStringA("Folders","LogConnect","Logs\\Connect",cTemp7,30,"..\\Settings\\GameServer.ini");
    memset(&offsetConnectFolder[0],0,30);
    memcpy(&offsetConnectFolder[0],cTemp7,strlen(cTemp7)); 

	char cTemp8[27];
    DWORD *offsetLogFolder = (DWORD*)(FolderLogs);
    GetPrivateProfileStringA("Folders","LogFile",".\\Logs\\%02d%02d%02d_%s.log",cTemp8,27,"..\\Settings\\GameServer.ini");
    memset(&offsetLogFolder[0],0,27);
    memcpy(&offsetLogFolder[0],cTemp8,strlen(cTemp8)); 

	char cTemp9[25];
    DWORD *offsetFileInfo = (DWORD*)(FileServerInfo);
    GetPrivateProfileStringA("Folders","ServerInfo","Data\\Server.dat",cTemp9,25,"..\\Settings\\GameServer.ini");
    memset(&offsetFileInfo[0],0,25);
    memcpy(&offsetFileInfo[0],cTemp9,strlen(cTemp9));
//==============================================================================
// Calculator
//==============================================================================
	int EnableCalcSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\Calculator.ini");
	if(EnableCalcSys==1)
	{
		//Elf
		*(unsigned int *) AttackDamageMin_Bow_StrDexDiv_Elf1	 = GetPrivateProfileInt("Elf", "AttackDamageMin_Bow_StrDexDiv_Elf1",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_Bow_StrDexDiv_Elf2	 = GetPrivateProfileInt("Elf", "AttackDamageMin_Bow_StrDexDiv_Elf2",7,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_Bow_StrDexDiv_Elf1	 = GetPrivateProfileInt("Elf", "AttackDamageMax_Bow_StrDexDiv_Elf1",4,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_Bow_StrDexDiv_Elf2	 = GetPrivateProfileInt("Elf", "AttackDamageMax_Bow_StrDexDiv_Elf2",4,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_NoBow_DexDiv_Elf1		 = GetPrivateProfileInt("Elf", "AttackDamageMin_NoBow_DexDiv_Elf1",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_NoBow_DexDiv_Elf2		 = GetPrivateProfileInt("Elf", "AttackDamageMin_NoBow_DexDiv_Elf2",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_NoBow_StrDiv_Elf1		 = GetPrivateProfileInt("Elf", "AttackDamageMin_NoBow_StrDiv_Elf1",14,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_NoBow_StrDiv_Elf2		 = GetPrivateProfileInt("Elf", "AttackDamageMin_NoBow_StrDiv_Elf2",14,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_NoBow_Elf1			 = GetPrivateProfileInt("Elf", "AttackDamageMax_NoBow_Elf1",3,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_NoBow_Elf2			 = GetPrivateProfileInt("Elf", "AttackDamageMax_NoBow_Elf2",3,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_DexStrDiv_Elf1		 = GetPrivateProfileInt("Elf", "AttackDamageMin_DexStrDiv_Elf1",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_DexStrDiv_Elf2		 = GetPrivateProfileInt("Elf", "AttackDamageMin_DexStrDiv_Elf2",7,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_DexStrDiv_Elf1		 = GetPrivateProfileInt("Elf", "AttackDamageMax_DexStrDiv_Elf1",4,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_DexStrDiv_Elf2		 = GetPrivateProfileInt("Elf", "AttackDamageMax_DexStrDiv_Elf2",4,"..\\Settings\\Calculator.ini");

		*(unsigned int *) Defense_Elf							 = GetPrivateProfileInt("Elf", "Defense_Elf",10,"..\\Settings\\Calculator.ini");
		*(unsigned char *) SuccessfulBlocking_Elf				 = GetPrivateProfileInt("Elf", "SuccessfulBlocking_Elf",3,"..\\Settings\\Calculator.ini");
		//Dark Knight
		*(unsigned int *) AttackDamageMin_StrDiv_DK1			 = GetPrivateProfileInt("DarkKnight", "AttackDamageMin_StrDiv_DK1",6,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_StrDiv_DK2			 = GetPrivateProfileInt("DarkKnight", "AttackDamageMin_StrDiv_DK2",6,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_StrDiv_DK1			 = GetPrivateProfileInt("DarkKnight", "AttackDamageMax_StrDiv_DK1",4,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_StrDiv_DK2			 = GetPrivateProfileInt("DarkKnight", "AttackDamageMax_StrDiv_DK2",4,"..\\Settings\\Calculator.ini");

		*(unsigned int *) Defense_DK							 = GetPrivateProfileInt("DarkKnight", "Defense_DK",3,"..\\Settings\\Calculator.ini");
		//Magic Gladiator
		*(unsigned int *) AttackDamageMin_StrDiv_MG1			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMin_StrDiv_MG1",6,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_StrDiv_MG2			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMin_StrDiv_MG2",6,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_EneDiv_MG1			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMin_EneDiv_MG1",12,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_EneDiv_MG2			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMin_EneDiv_MG2",12,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_StrDiv_MG1			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMax_StrDiv_MG1",4,"..\\Settings\\Calculator.ini");
		*(unsigned char *) AttackDamageMax_StrDiv_MG2			 = GetPrivateProfileInt("MagicGladiator", "AttackDamageMax_StrDiv_MG2",4,"..\\Settings\\Calculator.ini");
		//Dark Lord
		*(unsigned int *) AttackDamageMin_StrDiv_DL1			 = GetPrivateProfileInt("DarkLord", "AttackDamageMin_StrDiv_DL1",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_StrDiv_DL2			 = GetPrivateProfileInt("DarkLord", "AttackDamageMin_StrDiv_DL2",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_EneDiv_DL1			 = GetPrivateProfileInt("DarkLord", "AttackDamageMin_EneDiv_DL1",14,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMin_EneDiv_DL2			 = GetPrivateProfileInt("DarkLord", "AttackDamageMin_EneDiv_DL2",14,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMax_StrDiv_DL1			 = GetPrivateProfileInt("DarkLord", "AttackDamageMax_StrDiv_DL1",5,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMax_StrDiv_DL2			 = GetPrivateProfileInt("DarkLord", "AttackDamageMax_StrDiv_DL2",5,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMax_EneDiv_DL1			 = GetPrivateProfileInt("DarkLord", "AttackDamageMax_EneDiv_DL1",10,"..\\Settings\\Calculator.ini");
		*(unsigned int *) AttackDamageMax_EneDiv_DL2			 = GetPrivateProfileInt("DarkLord", "AttackDamageMax_EneDiv_DL2",10,"..\\Settings\\Calculator.ini");

		*(unsigned int *) Defense_DL							 = GetPrivateProfileInt("DarkLord", "Defense_DL",7,"..\\Settings\\Calculator.ini");
		*(unsigned int *) SuccessfulBlocking_DL					 = GetPrivateProfileInt("DarkLord", "SuccessfulBlocking_DL",3,"..\\Settings\\Calculator.ini");
		//Other
		*(unsigned int *) SuccessfulBlocking_DW_DK_MG			 = GetPrivateProfileInt("Other", "SuccessfulBlocking_DW_DK_MG",7,"..\\Settings\\Calculator.ini");
		*(unsigned char *) Defense_DW_MG						 = GetPrivateProfileInt("Other", "Defense_DW_MG",4,"..\\Settings\\Calculator.ini");
	}

	#if(ENABLE_SKILL_SUMMON)

	//HookThis((DWORD)&SkillRecallParty,0x0054268E);

	BYTE btPachDL[] = { 0x81, 0xFA, 0xFA, 0x00, 0x00, 0x00};

	memcpy((int*)0x00546D63,btPachDL,sizeof(btPachDL));

	#endif
}

#if(ENABLE_SKILL_SUMMON)

//int *__thiscall sub_546AD0(void *this, int a2, int a3)

#define pSkillRecallParty ((int*(__thiscall*)(void *This, int a2, int a3)) 0x546AD0)

int * Fix::SkillRecallParty(void *This, int a2, int a3)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(a2);

	for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
	{
		OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);

		if(gObj->PartyNumber == sObj->PartyNumber)
		{
			if(sObj->Level < 300)
			{
				return 0;
			}
		}
	}


	return pSkillRecallParty(This, a2, a3);
}

#endif
