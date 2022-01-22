//=========================================================================
// LCTeam Presents - GameServer/GameServer-CS Season II & III (EP1 & EP2)
// Project started at 25.02.2009
// Main coder - SmallHabit
// Items.h
//=========================================================================

#include <windows.h>

#ifndef ITEMS_H
	#define ITEMS_H

#define SLOT_EMPTY -1

#define MAKEITEMID(group, index) (group * 512 + index)

enum PLAYER_WARDROBE 
{
	WEAPON_01	= 0,	
	WEAPON_02	= 1,	
	HELMET		= 2,	
	ARMOR		= 3,	
	PANTS		= 4,	
	GLOVES		= 5,	
	BOOTS		= 6,	
	WINGS		= 7,	
	GUARDIAN	= 8,	
	PENDANT		= 9,	
	RING_01		= 10,	
	RING_02		= 11,	
};

enum ITEMCREATE_PLACE 
{
	INVENTORY	= 0xeb,
	CHAOSBOX	= 0xff,
};

enum VIEWPORT_WINGS03 
{
	WINGS_OF_STORM		= 0x07,
	WINGS_OF_VORTEX		= 0x08,
	WINGS_OF_ILLUSION		= 0x0c,
	WINGS_OF_HURRICANE	= 0x10,
	MANTLE_OF_MONARCH		= 0x14,
	MISERY_WINGS            = 0x18,
	DESPAIR_WINGS           = 0x1c,
	DIMENSION_WINGS         = 0x1b,
};

enum VIEWPORT_FENRIR 
{
	FENRIR_TYPE		    	= 0x1a25,
	FENRIR_EMPTY	    	= 0x00,
	FENRIR_GOLD	        	= 0x03,
};

enum VIEWPORT_QUEST03_ITEMS 
{
	FLAME_OF_DEATH		= 0x1c41,
	HELL_MAINE_HORN	    	= 0x1c42,
	PHOENIX_FEATHER     	= 0x1c43,
};

struct ITEMSTRUCT 
{
	/*0x0>	|0x4|*/ unsigned long m_Number;
	/*0x4>	|0x1|*/ char m_serial;
	/*0x6>	|0x2|*/ short m_Type;
	/*0x8>	|0x2|*/ short m_Level;
	/*0xa>	|0x1|*/ unsigned char m_Part;
	/*0xb>	|0x1|*/ unsigned char m_Class;
	/*0xc>	|0x1|*/ unsigned char m_TwoHand;
	/*0xd>	|0x1|*/ unsigned char m_AttackSpeed;
	/*0xe>	|0x1|*/ unsigned char m_WalkSpeed;
	/*0x10>	|0x2|*/ unsigned short m_DamageMin;
	/*0x12>	|0x2|*/ unsigned short m_DamageMax;
	/*0x14>	|0x1|*/ unsigned char m_SuccessfulBlocking;
	/*0x16>	|0x2|*/ unsigned short m_Defense;
	/*0x18>	|0x2|*/ unsigned short m_MagicDefense;
	/*0x1a>	|0x1|*/ unsigned char m_Speed;
	/*0x1c>	|0x2|*/ unsigned short m_DamageMinOrigin;
	/*0x1e>	|0x2|*/ unsigned short m_DefenseOrigin;
	/*0x20>	|0x2|*/ unsigned short m_Magic;
	/*0x24>	|0x4|*/ float m_Durability;
	/*0x28>	|0x2|*/ unsigned short m_DurabilitySmall;
	/*0x2c>	|0x4|*/ float m_BaseDurability;
	/*0x30>	|0x1|*/ unsigned char m_SpecialNum;
	/*0x31>	|0x8|*/ unsigned char m_Special[8];
	/*0x39>	|0x8|*/ unsigned char m_SpecialValue[8];
	/*0x42>	|0x2|*/ unsigned short m_RequireStrength;
	/*0x44>	|0x2|*/ unsigned short m_RequireDexterity;
	/*0x46>	|0x2|*/ unsigned short m_RequireEnergy;
	/*0x48>	|0x2|*/ unsigned short m_RequireLevel;
	/*0x4a>	|0x2|*/ unsigned short m_RequireVitality;
	/*0x4c>	|0x2|*/ unsigned short m_RequireLeaderShip;
	/*0x4e>	|0x2|*/ unsigned short m_Leadership;
	/*0x50>	|0x5|*/ unsigned char m_RequireClass[5];
	/*0x55>	|0x7|*/ unsigned char m_Resistance[7];
	/*0x5c>	|0x4|*/ int m_Value;
	/*0x60>	|0x4|*/ unsigned long m_SellMoney;
	/*0x64>	|0x4|*/ unsigned long m_BuyMoney;
	/*0x68>	|0x4|*/ int m_iPShopValue;
	/*0x6c>	|0x1|*/ unsigned char m_bItemExist;
	/*0x70>	|0x4|*/ int m_OldSellMoney;
	/*0x74>	|0x4|*/ int m_OldBuyMoney;
	/*0x78>	|0x1|*/ unsigned char m_SetiSkill;
	/*0x79>	|0x1|*/ unsigned char m_SetiLuck;
	/*0x7a>	|0x1|*/ unsigned char m_SetiOption;
	/*0x7b>	|0x1|*/ unsigned char m_SetiExcellent;
	/*0x7c>	|0x10|*/float m_DurabilityState[4];
	/*0x8c>	|0x4|*/ float m_CurrentDurabilityState;
	/*0x90>	|0x1|*/ unsigned char m_SkillChange;
	/*0x91>	|0x1|*/ unsigned char m_QuestItem;
	/*0x92>	|0x1|*/ unsigned char m_SetOption;
	/*0x93>	|0x1|*/ unsigned char m_SetAddStat;
	/*0x94>	|0x1|*/ unsigned char m_IsValidItem;
	/*0x95>	|0x7|*/ unsigned char m_SkillResistance[7];
	/*0x9c>	|0x4|*/ int m_IsLoadPetItemInfo;
	/*0xa0>	|0x4|*/ int m_PetItem_Level;
	/*0xa4>	|0x4|*/ int m_PetItem_Exp;
	/*0xa8>	|0x1|*/ unsigned char m_JewelOfHarmonyOption;
	/*0xaa>	|0x2|*/ unsigned short m_HJOpStrength;
	/*0xac>	|0x2|*/ unsigned short m_HJOpDexterity;
	/*0xae>	|0x1|*/ unsigned char m_ItemOptionEx;
};

int DelPlayerEspecificItem(DWORD PlayerID,DWORD itemId,BYTE Location);
int gObjDeleteItemsCount(int aIndex, short Type, short Level, int Count);
int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel);
int gObjGetItemCountInChaosbox(int aIndex, short type);


#endif //~ITEMS_H