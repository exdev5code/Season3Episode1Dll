#include "Protocol.h"
#include "Item.h"
#include "USER.h"
#include "Defines.h"
#include "Message.h"
//==================================================================================================
// CoinZen �������������
//==================================================================================================

unsigned int BronzeCoin = 7257;
unsigned int SilverCoin = 7258;
unsigned int GoldenCoin = 7259;
unsigned int PlatinaCoin = 7260;
//============================
//	������ ����
//============================
//������� ������� ������ �����
void SellBronzeCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObjGetItemCountInInventory(gObjId,0x1C59,0) >= 1)	//Bronze Coin
	{
		int CountZen = gObj->Money + 100000000;
		if(CountZen<=2000000000)
		{
			gObjDeleteItemsCount(gObjId,0x1C59,0,1);	//Bronze Coin
			gObj->Money += 100000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] Max 2 000 000 000 Zen");
		}
	}
	else
	{
		 MsgNormal(gObjId,"[Coin] No Items");
	}
}
//������� ������� ������ �����
void BuyBronzeCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObj->Money>=100000000)
	{
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( gObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if(iEmptyCount >= 1)
		{
			int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
			ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,BronzeCoin,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
			gObj->Money -= 100000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] You dont have inventory space");
		}
	}
	else
	{
		MsgNormal(gObjId,"[Coin] No Money");
	}
}
//============================
// ������� ����
//============================
//������� ������� ������� �����
void SellSilverCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObjGetItemCountInInventory(gObjId,0x1C5A,0) >= 1)	//Item Hex Code
	{
		int CountZen = gObj->Money + 250000000;
		if(CountZen<=2000000000)
		{
			gObjDeleteItemsCount(gObjId,0x1C5A,0,1);	//Item Hex Code
			gObj->Money += 250000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] Max 2 000 000 000 Zen");
		}
	}
	else
	{
		 MsgNormal(gObjId,"[Coin] No Items");
	}
}
//������� ������� ������� �����
void BuySilverCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObj->Money>=250000000)
	{
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( gObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if(iEmptyCount >= 1)
		{
			int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
			ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,SilverCoin,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
			gObj->Money -= 250000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] You dont have inventory space");
		}
	}
	else
	{
		MsgNormal(gObjId,"[Coin] No Money");
	}
}
//============================
// ������ ����
//============================
//������� ������� ������� �����
void SellGoldenCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObjGetItemCountInInventory(gObjId,0x1C5B,0) >= 1)	//Item Hex Code
	{
		int CountZen = gObj->Money + 500000000;
		if(CountZen<=2000000000)
		{
			gObjDeleteItemsCount(gObjId,0x1C5B,0,1);	//Item Hex Code
			gObj->Money += 500000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] Max 2 000 000 000 Zen");
		}
	}
	else
	{
		 MsgNormal(gObjId,"[Coin] No Items");
	}
}
//������� ������� ������� �����
void BuyGoldenCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObj->Money>=500000000)
	{
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( gObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if(iEmptyCount >= 1)
		{
			int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
			ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,GoldenCoin,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
			gObj->Money -= 500000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] You dont have inventory space");
		}
	}
	else
	{
		MsgNormal(gObjId,"[Coin] No Money");
	}
}
//============================
// ��������
//============================
//������� ������� ������� �����
void SellPlatinaCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObjGetItemCountInInventory(gObjId,0x1C5C,0) >= 1)	//Item Hex Code
	{
		int CountZen = gObj->Money + 1000000000;
		if(CountZen<=2000000000)
		{
			gObjDeleteItemsCount(gObjId,0x1C5C,0,1);	//Item Hex Code
			gObj->Money += 1000000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] Max 2 000 000 000 Zen");
		}
	}
	else
	{
		 MsgNormal(gObjId,"[Coin] No Items");
	}
}
//������� ������� ������� �����
void BuyPlatinaCoin(DWORD gObjId)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
	if(gObj->Money>=1000000000)
	{
		int iEmptyCount = 0;
		for ( int x=0;x<64;x++)
		{
			if ( gObj->pInventoryMap[x] == 0xFF )
			{
				iEmptyCount++;
			}
		}
		if(iEmptyCount >= 1)
		{
			int ItemType=0,ItemNr=0,ItemLevel=0,ItemSkill=0,ItemLuck=0,ItemOpt=0,ItemExc=0,ItemDur=0;
			ItemSerialCreateSend(gObjId,235,gObj->X,gObj->Y,PlatinaCoin,ItemLevel,ItemDur,ItemSkill,ItemLuck,ItemOpt,gObjId,ItemExc,0);
			gObj->Money -= 1000000000;
			GCMoneySend(gObj->m_Index, gObj->Money);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[Coin] You dont have inventory space");
		}
	}
	else
	{
		MsgNormal(gObjId,"[Coin] No Money");
	}
}