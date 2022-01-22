//------------------------------------------------------------------------------
// Items
//------------------------------------------------------------------------------
#define ItemSerialCreateSend ((int(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD)) 0x004999B0)
#define MAX_SUBTYPE_ITEMS 512
#define ITEMGET(x,y) ( (x)*MAX_SUBTYPE_ITEMS + (y))
#define gObjInventoryDeleteItem ((void(*)(int,int)) 0x005BFE40)
#define gObjInventoryItemSet ((void(*) (int,int,BYTE)) 0x005BF880)
#define GCInventoryItemOneSend ((void(*) (int, int)) 0x005513F0) 
#define GCInventoryItemDeleteSend ((void(*)(int,int,unsigned char)) 0x0056E560)
#define GCMoneySend ((void(*) (DWORD,int)) 0x00551D00)
#define GCUseEffectItem ((void(*) (LPOBJ lpObj, int iEffectUseOption, int iOptionType, int iEffectType, int iLeftTime)) 0x004023C9);
#define GCKillPlayerExpSend	((int(*) (DWORD, int, int, int,int))0x005676C0)
#define GCKill 0x004072DE

//------------------------------------------------------------------------------
// Objects
//------------------------------------------------------------------------------
#define gObjViewportListProtocolCreate ((void(*)(OBJECTSTRUCT*)) 0x005D20F0)
#define gObj_X											0x108
#define gObj_Y											0x10A
#define gObj_MAP										0x10D
#define OBJECT_BASE	0x0B692D60
#define OBJECT_SIZE	0x19A0
#define OBJECT_MIN	0x20D0
#define OBJECT_MAX	0x24B8
#define OBJECT_POINTER(aIndex) ((aIndex * OBJECT_SIZE) + OBJECT_BASE)
#define OBJECT_TABINDEX(lpObj) ((lpObj - OBJECT_BASE) / OBJECT_SIZE)
#define GCStateInfoSend					((int(*) (int, int, int)) 0x00568490 )
#define	j_gObjCalCharacter							((int(*) (int)) 0x0053B410 )
#define gObjCalCharacter_CALL						0x004033C3
#define gObj_INV										0xCAC

//------------------------------------------------------------------------------
// Data
//------------------------------------------------------------------------------
#define DataSend ((void(*)(DWORD PlayerID,PBYTE Packet,DWORD Size)) 0x004CAB40)
#define DataSendB ((void(*)(DWORD,LPSTR,DWORD)) 0x004CAB40)
#define DataRecv ((void(*)(BYTE,PBYTE,DWORD,DWORD,...)) 0x0054C430)

//------------------------------------------------------------------------------
// Chat
//------------------------------------------------------------------------------
#define ChatTargetSendNogs ((void(*)(OBJECTSTRUCT*,char* Text,DWORD PlayerID)) 0x0054E510)
#define GCServerMsgStringSend ((void(*) (char* Text, DWORD PlayerID, int Type)) 0x00406C67)

//------------------------------------------------------------------------------
// Offtrade
//------------------------------------------------------------------------------
#define gObjDel	((void(*) (int)) 0x00403E09 ) 
#define CloseClient ((void(*) (int)) 0x004CB7B0)
#define CGPShopAnsClose ((void(*) (int,BYTE)) 0x0055DF50)    
#define GJPUserClose ((void(*) (LPSTR)) 0x0058E880)

//------------------------------------------------------------------------------
// Other
//------------------------------------------------------------------------------
#define gObjSetItemPlusSpecial ((void(*) (LPOBJ lpObj, int option, int ivalue)) 0x004C6E20)
#define LifeReFill ((void(*)(int aIndex, WORD Life, BYTE Ipos, unsigned char flag,  WORD wShield)) 0x0056E3C0)
#define GCMagicAttackNumberSend ((void(*) (LPOBJ lpObj, BYTE MagicNumber, int usernumber, unsigned char skillsuccess)) 0x00568060)
#define LevelUpEffect ((void(*)(int, unsigned char)) 0x00551040)
#define gObjTeleport ((void(*) (int,int,int,int)) 0x005D8A00)
#define gObjCloseSet ((void(*) (int,int)) 0x005AA5E0)
#define ReloadMonsterSetBase ((void(*)()) 0x00407B9E)
#define Reload ((void(*)()) 0x00425280)
#define Reload2 ((void(*)()) 0x004B97DE)
#define gObjMonsterDieGiveItem ((int(*) (OBJECTSTRUCT* lpObj, OBJECTSTRUCT* lpTargetObj)) 0x004010CD)
#define gObjLevelUpPointAdd ((bool(*)(BYTE type, OBJECTSTRUCT* lpObj)) 0x005B69B0) 
#define gEventMonsterItemDrop ((int(*) (BYTE*,BYTE*)) 0x004DC900)

#define MAIN_INVENTORY_SIZE 76

//------------------------------------------------------------------------------
// Calculator
//------------------------------------------------------------------------------
#define AttackDamageMin_Bow_StrDexDiv_Elf1				(0x0053B9A0+1) 
#define AttackDamageMin_Bow_StrDexDiv_Elf2				(0x0053B9CF+1) 
#define AttackDamageMax_Bow_StrDexDiv_Elf1				(0x0053B9B7+2)
#define AttackDamageMax_Bow_StrDexDiv_Elf2				(0x0053B9E6+2) 
#define AttackDamageMin_NoBow_DexDiv_Elf1				(0x0053BA00+1) 
#define AttackDamageMin_NoBow_DexDiv_Elf2				(0x0053BA48+1) 
#define AttackDamageMin_NoBow_StrDiv_Elf1				(0x0053BA0D+1) 
#define AttackDamageMin_NoBow_StrDiv_Elf2				(0x0053BA55+1) 
#define AttackDamageMax_NoBow_Elf1						(0x0053BA23+2) 
#define AttackDamageMax_NoBow_Elf2						(0x0053BA6B+2) 
#define AttackDamageMin_DexStrDiv_Elf1					(0x0053BA95+1) 
#define AttackDamageMin_DexStrDiv_Elf2					(0x0053BAC4+1) 
#define AttackDamageMax_DexStrDiv_Elf1					(0x0053BADB+2) 
#define AttackDamageMax_DexStrDiv_Elf2					(0x0053BAAC+2) 
// Dark Knight
#define AttackDamageMin_StrDiv_DK1						(0x0053BB06+1) 
#define AttackDamageMin_StrDiv_DK2						(0x0053BB2F+1) 
#define AttackDamageMax_StrDiv_DK1						(0x0053BB1A+2)
#define AttackDamageMax_StrDiv_DK2						(0x0053BB43+2) 
// Magic Gladiator
#define AttackDamageMin_StrDiv_MG1						(0x0053BB72+1) 
#define AttackDamageMin_StrDiv_MG2						(0x0053BBBA+1)
#define AttackDamageMin_EneDiv_MG1						(0x0053BB7F+1) 
#define AttackDamageMin_EneDiv_MG2						(0x0053BBC7+1) 
#define AttackDamageMax_StrDiv_MG1						(0x0053BB95+2) 
#define AttackDamageMax_StrDiv_MG2						(0x0053BBDD+2) 
// Dark Lord
#define AttackDamageMin_StrDiv_DL1						(0x0053BC62+1) 
#define AttackDamageMin_StrDiv_DL2						(0x0053BC1C+1) 
#define AttackDamageMin_EneDiv_DL1						(0x0053BC29+1) 
#define AttackDamageMin_EneDiv_DL2						(0x0053BC6F+1) 
#define AttackDamageMax_StrDiv_DL1						(0x0053BC3F+1) 
#define AttackDamageMax_StrDiv_DL2						(0x0053BC85+1) 
#define AttackDamageMax_EneDiv_DL1						(0x0053BC4C+1) 
#define AttackDamageMax_EneDiv_DL2						(0x0053BC92+1) 
// Dark Wizard
#define AttackDamageMin_StrDiv_DW1						(0x0053BCAA+2) 
#define AttackDamageMin_StrDiv_DW2						(0x0053BCD4+2) 
#define AttackDamageMax_StrDiv_DW1						(0x0053BCBF+2) 
#define AttackDamageMax_StrDiv_DW2						(0x0053BCE9+2) 
#define AttackDamageMin_EneDiv_DW1						(0x0053BCAF+2) 
#define AttackDamageMax_EneDiv_DW2						(0x0053BCD9+2) 
// Attack Speed Calculator
#define AttackSpeed_Elf1				                (0x0053C203+1) 
#define AttackSpeed_Elf2				                (0x0053C217+1) 
#define AttackSpeed_DK_MG1				                (0x0053C252+1) 
#define AttackSpeed_DK_MG2				                (0x0053C266+1) 
#define AttackSpeed_DL1					                (0x0053C28D+1)  
#define AttackSpeed_DL2					                (0x0053C2A1+1)  
#define AttackSpeed_DW1					                (0x0053C2B7+1) 
#define AttackSpeed_DW2					                (0x0053C2CB+1)  
// Succesful Blocking Calculator
#define SuccessfulBlocking_Elf		                    (0x0053C961+2)
#define SuccessfulBlocking_DW_DK_MG	                    (0x0053C989+1)
#define SuccessfulBlocking_DL		                    (0x0053C99F+1) 
// Defense Calculator
#define Defense_Elf					                    (0x0053CDBA+1)
#define Defense_DK					                    (0x0053CDE1+1) 
#define Defense_DL					                    (0x0053CE08+1) 
#define Defense_DW_MG				                    (0x0053CE1E+2) 

//------------------------------------------------------------------------------
// Folders
//------------------------------------------------------------------------------
#define FolderChatLog                                   (0x0075BE00)
#define FolderCastleSiege   	                        (0x0074D964)
#define FolderKanturu        	                        (0x007606C0)
#define FolderKundunGM       	                        (0x0075B76C)
#define FolderKundunEvent    	                        (0x0075C228)
#define FolderServerConnect  	                        (0x0076C73C)
#define FolderLogs           	                        (0x007625B0)
#define FileServerInfo       	                        (0x0075799C)

//------------------------------------------------------------------------------
// GameServer Functions
//------------------------------------------------------------------------------
#define GameServerTitle      	                        (0x0076C708)
#define WindowGSTitle       	                        (0x00757B25) 
#define LogAddText     ((void(*) (int Type,char * Text, ...)) 0x00407969)
//----------------
// Color Table
//----------------
// Black     = 1
// Red       = 2
// Green     = 3
// Blue      = 4
// Dark Red  = 5
// Dark Blue = 6
// Violet    = 7
//------------------------------------------------------------------------------
// Chaos Machine
//------------------------------------------------------------------------------
//#define ChaosBoxInit	((void(*) ( DWORD ))0x4044E4)
#define ChaosBoxSend	((void(*) ( DWORD , DWORD ))0x4050AB)
#define CHAOS_ADR_RETURN		0x005C47C7
#define CHAOS_ADR_ITEM_ALLOW	0x005C4802
#define gObjOffset 0x660F078
#define gObjSize 0x1968
#define INVALID_MIX	-1
#define GS_ITEMSIZE				0xB0
#define gObj_CBOX			    0xCFC

//==============
//	Цель
//==============
#define OBJ_EMPTY -1
#define OBJ_MONSTER 2
#define OBJ_USER 1
#define OBJ_NPC 3
#define NO_SPC_MAP -1
//Обновление PKstatus
#define GCPkLevelSend ((void(*)(DWORD aIndex,BYTE PkLevel)) 0x005514C0)




