#include "StdAfx.h"
#include "USER.h"
#include "Message.h"
#include "Quest_PGW.h"
#include "Buffer.h"
#include "NPCTeleport.h"
#include "AddFunctions.h"

#include "CQuery.h"
//=================
//Выводим тупе вещи
//=================
int TypeItemInt (int ItemCode)
{
	int TypeNum = ItemCode/512;
	return TypeNum;
}
//===========================
//Информация при входе игрока
//===========================
void PlayerConnect(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	ExUser[aIndex].Resets = exQueryReturnInt("SELECT Resets FROM Character WHERE Name = '%s'", gObj->Name);
	ExUser[aIndex].GResets = exQueryReturnInt("SELECT gr_res FROM Character WHERE Name = '%s'", gObj->Name); //m_DBQuery.GetInt("gr_res");

	int EnableRangSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\GrandReset.ini");
	int UserGReset = 0;
	if(EnableRangSys)
	{

	}

	int EnablePlayerConnect = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\PlayerConnect.ini");
	if(!EnablePlayerConnect)
		return;
	
	//Оповешение всем о входе в игру
	int EnableAllMassage = GetPrivateProfileInt("Common","EnableAllMassage",0,"..\\Settings\\PlayerConnect.ini");
	if(EnableAllMassage)
		MessageAllChat(aIndex,"~[%s]: Online",gObj->Name);
	//Показать количество Гем
	int ShowGem = GetPrivateProfileInt("Common","ShowGem",0,"..\\Settings\\PlayerConnect.ini");
	if(ShowGem)
	{

		int MyGem = exQueryReturnInt("SELECT CashPoint FROM MEMB_INFO WHERE memb___id = '%s'", gObj->AccountID);
		
		MsgNormal(aIndex,"[GEM]: %d",MyGem);
	}
	//Показать количество ресетов
	int ShowReset = GetPrivateProfileInt("Common","ShowReset",0,"..\\Settings\\PlayerConnect.ini");
	if(ShowReset)
	{
		MsgNormal(aIndex, "[Reset]: %d", ExUser[aIndex].Resets);
	}
	//показать количество Гресетов
	int ShowGReset = GetPrivateProfileInt("Common","ShowGReset",1,"..\\Settings\\PlayerConnect.ini");
	if(ShowGReset)
	{

		MsgNormal(aIndex, "[GReset]: %d", ExUser[aIndex].GResets);
	}
}
//==========================
//Функция добовления Command
//==========================
void AddCommandsDarkLodr (DWORD gObjId,char* msg)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);

	if(gObj->Class == 4)
	{
		if(gObj->LevelUpPoint == 0)
			return;
	
		unsigned int AddPoints = 0;
		sscanf_s(msg,"%d",&AddPoints);
		if(AddPoints)
		{
			if(gObj->LevelUpPoint >= AddPoints)
			{
				if((gObj->Leadership + AddPoints)>32767)
					return;
				gObj->LevelUpPoint = gObj->LevelUpPoint - AddPoints;
				gObj->Leadership = gObj->Leadership + AddPoints;
				MsgNormal(gObjId,"Need to re-login");
				return;
			}
			else
				return;
		}
		else
			return;
	}
	else
		return;
}
//==========================
// Функция Обмена Зен на Gem
//==========================
void BuyGemFun (DWORD gObjId,char* msg)
{
	int EnableBuyGem = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\BuyGem.ini");
	if(!EnableBuyGem)
		return;
	int Price1Gem = GetPrivateProfileInt("Common","Price",0,"..\\Settings\\BuyGem.ini");
	int MaxBuyPrice = GetPrivateProfileInt("Common","MaxBuy",1000,"..\\Settings\\BuyGem.ini");
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);

	unsigned int BGemPoints = 0;
	sscanf_s(msg,"%d",&BGemPoints);
	if(BGemPoints >= 1 && BGemPoints <= MaxBuyPrice)
	{
		unsigned int SumPriceGem = Price1Gem*BGemPoints;
		if(gObj->Money>=SumPriceGem)
		{
			gObj->Money -= SumPriceGem;

			exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", BGemPoints, gObj->AccountID);

			GCMoneySend(gObj->m_Index, gObj->Money);
			MsgNormal(gObjId,"[BuyGem] Buy: %d Gem, Sell: %d Zen",BGemPoints,SumPriceGem);
			return;
		}
		else
		{
			MsgNormal(gObjId,"[BuyGem] You need above %d Zen",SumPriceGem);
			return;
		}
	}
}
//==================================================================================================
// FireCracker
//==================================================================================================
void FireCracker(int aIndex, BYTE X, BYTE Y)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	BYTE Packet[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y};
	DataSend(aIndex,Packet,Packet[1]);
	BYTE Packet2[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X+1, Y};
	DataSend(aIndex,Packet2,Packet2[1]);
	BYTE Packet3[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y+1};
	DataSend(aIndex,Packet3,Packet3[1]);
	BYTE Packet4[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y-1};
	DataSend(aIndex,Packet4,Packet4[1]);
	BYTE Packet5[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X-1, Y};
	DataSend(aIndex,Packet5,Packet5[1]);
}
//==================================================================================================
// Credits
//==================================================================================================
void Credits(DWORD gObjId)
{
	MsgNormal(gObjId,"Server: Ex-Team");
	MsgNormal(gObjId,"Developer: DangeR");
	MsgNormal(gObjId,"Skype: muonline.bk");
	MsgNormal(gObjId,"Version: 6.0");
	MsgNormal(gObjId,"Project: Ex-Game");
}
//==================================================================================================
// Информация о персонаже
//==================================================================================================
void ChatInfoChar(int aIndex,char* msg)
{	
	int InfoCharCMD = GetPrivateProfileInt("Command","char",0,"..\\Settings\\Command.ini");
	if(!InfoCharCMD)
		return;

	if (strlen(msg) > 10) return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		int isFind = 0;
		char Name[100];
		sscanf(msg,"%s",&Name);
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(strcmp(Name,sObj->Name) == 0)
			{
				int UserReset = ExUser[i].Resets;
				int UserGReset = ExUser[i].GResets;
				MsgNormal(aIndex,"[Name]:%s [Reset]:%d [GRes]:%d",msg,UserReset,UserGReset);
				MsgNormal(aIndex,"[Strength]:%d",sObj->Strength);
				MsgNormal(aIndex,"[Dexterity]:%d",sObj->Dexterity);
				MsgNormal(aIndex,"[Vitality]:%d",sObj->Vitality);
				MsgNormal(aIndex,"[Energy]:%d",sObj->Energy);
				if(sObj->Class == 4)
					MsgNormal(aIndex,"[Command]:%d",sObj->Leadership);
				isFind = 1;
				break;
			}
		}
		if(!isFind)
			MsgNormal(aIndex,"[CharInfo] Player '%s' not found.",msg);
}
//==================================================================================================
// Accaunt Mode
//==================================================================================================
void ChatAccMode(int aIndex,char* msg)
{
	int AccMode = GetPrivateProfileInt("Connect","AccMode",1,"..\\Settings\\Connect.ini");
	if(!AccMode)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	//if (strlen(msg) > 5) return;

	char AccModeMSG[100];
	sscanf(msg,"%s",&AccModeMSG);
	char AccModeOn[5] = "on";
	char AccModeOff[5] = "off";
	//AccMode = 0[On] AccMode = 1[Off]
	if(!strcmp(AccModeOn,AccModeMSG))
	{
		exQueryUpdate("UPDATE MEMB_INFO SET AccMode = 1 WHERE memb___id='%s'", gObj->AccountID);
		MsgNormal(aIndex,"[AccMode] On");
	}
	else if (!strcmp(AccModeOff,AccModeMSG))
	{
		exQueryUpdate("UPDATE MEMB_INFO SET AccMode = 0 WHERE memb___id='%s'", gObj->AccountID);
		MsgNormal(aIndex,"[AccMode] Off");
	}
}
//==================================================================================================
// Points For Online
//==================================================================================================
void ExPointsForOnline(int aIndex)
{
	int Enable = GetPrivateProfileInt("Common","Enable",1,"..\\Settings\\PointsOnline.ini");
	if(!Enable)
		return;
	if(OfflineShop[aIndex].IsOffTrade == 1)
		return;

	int TimeTick = GetPrivateProfileInt("Common","TimeTick",1,"..\\Settings\\PointsOnline.ini");

	ExUser[aIndex].ExTimeTick++;
	if(ExUser[aIndex].ExTimeTick == TimeTick)
	{
		ExUser[aIndex].ExTimeTick = 0;
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	

		int BonusGem = GetPrivateProfileInt("Common","BonusGem",1,"..\\Settings\\PointsOnline.ini");

		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", BonusGem, gObj->AccountID);
		MsgNormal(aIndex,"[Time] Bonus: %d Gem",BonusGem);
	}
}
//==================================================================================================
// Command PK Clear	//PkClear
//==================================================================================================
void Ex_PkClear(int aIndex)
{
	int Ex_PkClear_Enabled = GetPrivateProfileInt("PkClear","Enabled",1,"..\\Settings\\Command.ini");
	if(!Ex_PkClear_Enabled)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	int Ex_PkClearLevel = GetPrivateProfileInt("PkClear","PkClearLevel",0,"..\\Settings\\Command.ini");
	if(Ex_PkClearLevel > gObj->Level)
	{
		MsgNormal(aIndex,"[PkClear] Need %d Level",Ex_PkClearLevel);
		return;
	}
	int Ex_PkClearMoney = GetPrivateProfileInt("PkClear","PkClearMoney",0,"..\\Settings\\Command.ini");
	int Ex_PKClearType = GetPrivateProfileInt("PkClear","PKClearType",0,"..\\Settings\\Command.ini");
	if(gObj->m_PK_Level <= 3)
		return;
	if(Ex_PKClearType == 1)
	{
			int PkLevel = gObj->m_PK_Level - 3;
			if(PkLevel == 0)
				return;
			int PkMoney = PkLevel * Ex_PkClearMoney;
			if(PkMoney > gObj->Money)
			{
				MsgNormal(aIndex,"[PkClear] Need %d Zen",PkMoney);
				return;
			}
			gObj->Money -= PkMoney;
			gObj->m_PK_Level = 3;
			gObj->m_PK_Count = 0;
			GCMoneySend(aIndex,gObj->Money);
			GCPkLevelSend(aIndex,gObj->m_PK_Level);
	}
	else if(Ex_PKClearType == 2)
	{
			if(Ex_PkClearMoney > gObj->Money)
			{
				MsgNormal(aIndex,"[PkClear] Need %d Zen",Ex_PkClearMoney);
				return;
			}
			gObj->Money -= Ex_PkClearMoney;
			gObj->m_PK_Level = 3;
			gObj->m_PK_Count = 0;
			GCMoneySend(aIndex,gObj->Money);
			GCPkLevelSend(aIndex,gObj->m_PK_Level);
	}
	else
	{
			gObj->m_PK_Level = 3;
			gObj->m_PK_Count = 0;
			GCPkLevelSend(aIndex,gObj->m_PK_Level);
	}
}

void ErrorConnectDataBase(int aIndex)
{
	//OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	//MsgNormal(aIndex,"[Connect]: Error");
	//MySQL.Disconnect();
	//MySQL.Connect();
}

void EliteClickerCick(int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	CloseClient(aIndex);
	GJPUserClose(gObj->AccountID);
	gObjDel(aIndex);
}

void CriticalExError(int aIndex)
{
	//OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	//Log.GameLogs("[Error] Kick Name: %s",gObj->Name);
	//MsgNormal(aIndex,"[Connect]: Error");
	//gObjCloseSet(aIndex, 1);
	//CloseClient(aIndex);
	//GJPUserClose(gObj->AccountID);
	//gObjDel(aIndex);
}
//==================================================================================================
// Command Restart Stats
//==================================================================================================
void RestartStats (int aIndex)
{
	int Enable = GetPrivateProfileInt("Stats","Enabled",0,"..\\Settings\\Command.ini");
	if(!Enable)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if( gObj->pInventory[WEAPON_01].m_Type == -1&&gObj->pInventory[WEAPON_02].m_Type == -1&&gObj->pInventory[HELMET].m_Type == -1&&
		gObj->pInventory[ARMOR].m_Type == -1&&gObj->pInventory[PANTS].m_Type == -1&&gObj->pInventory[GLOVES].m_Type == -1&&
		gObj->pInventory[BOOTS].m_Type == -1&&gObj->pInventory[WINGS].m_Type == -1&&gObj->pInventory[GUARDIAN].m_Type == -1&&
		gObj->pInventory[PENDANT].m_Type == -1&&gObj->pInventory[RING_01].m_Type == -1&&gObj->pInventory[RING_02].m_Type == -1 )
	{

		int LevelPoint = 0;

		if(gObj->Class == 0 || gObj->Class == 1 || gObj->Class == 2)
			LevelPoint = gObj->Level * 5;
		else
			LevelPoint = gObj->Level * 7;

		int Dkpoints = GetPrivateProfileInt("Common","Dk.points",600,"..\\Settings\\Reset.ini");
		int Dwpoints = GetPrivateProfileInt("Common","Dw.points",600,"..\\Settings\\Reset.ini");
		int Elfpoints = GetPrivateProfileInt("Common","Elf.points",600,"..\\Settings\\Reset.ini");
		int Mgpoints = GetPrivateProfileInt("Common","Mg.points",700,"..\\Settings\\Reset.ini");
		int Dlpoints = GetPrivateProfileInt("Common","Dl.points",700,"..\\Settings\\Reset.ini");

		int NumRes;

		switch(gObj->Class)
		{
			case 0: NumRes = ExUser[aIndex].Resets*Dwpoints; break;
			case 1: NumRes = ExUser[aIndex].Resets*Dkpoints; break;
			case 2: NumRes = ExUser[aIndex].Resets*Elfpoints;break;
			case 3: NumRes = ExUser[aIndex].Resets*Mgpoints; break;
			case 4: NumRes = ExUser[aIndex].Resets*Dlpoints; break;
		}
		int UserRangs = ExUser[aIndex].GResets;
		int EnableRangSys = GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\GrandReset.ini");
		if(EnableRangSys == 1 && UserRangs > 0)
		{
			//GRand Reset Configs
			int GDkpoints = GetPrivateProfileInt("Common","Dk.points",600,"..\\Settings\\GrandReset.ini");
			int GDwpoints = GetPrivateProfileInt("Common","Dw.points",600,"..\\Settings\\GrandReset.ini");
			int GElfpoints = GetPrivateProfileInt("Common","Elf.points",600,"..\\Settings\\GrandReset.ini");
			int GMgpoints = GetPrivateProfileInt("Common","Mg.points",700,"..\\Settings\\GrandReset.ini");
			int GDlpoints = GetPrivateProfileInt("Common","Dl.points",700,"..\\Settings\\GrandReset.ini");
			int GNumRes(0);
			switch(gObj->Class)
			{
				case 0: GNumRes = UserRangs*GDwpoints;break;
				case 1: GNumRes = UserRangs*GDkpoints;break;
				case 2: GNumRes = UserRangs*GElfpoints;break;
				case 3: GNumRes = UserRangs*GMgpoints;break;
				case 4: GNumRes = UserRangs*GDlpoints;break;
			}
			gObj->LevelUpPoint = ( GNumRes + NumRes + ExUser[aIndex].Ex_FreePoints + LevelPoint );
		}
		else
		{
			gObj->LevelUpPoint = ( NumRes + ExUser[aIndex].Ex_FreePoints + LevelPoint );
		}
			gObj->Strength = 25;
			gObj->Dexterity = 25;
			gObj->Vitality = 25;
			gObj->Energy = 25;
			if(gObj->Class == 4)
				gObj->Leadership = 25;
			MsgNormal(aIndex,"Stats reset");
			gObjCloseSet(aIndex, 1);
	}
	else
	{
		MsgNormal(aIndex,"Free inventory to be empty");
	}
}

int  gObjCalDistance(OBJECTSTRUCT * lpObj1, OBJECTSTRUCT * lpObj2)
{
	if ( lpObj1->X == lpObj2->X && lpObj1->Y == lpObj2->Y )
	{
		return 0;
	}

	float tx = (float)(lpObj1->X - lpObj2->X);
	float ty = (float)(lpObj1->Y - lpObj2->Y);

	return (int)(sqrt( (tx*tx)+(ty*ty) ));
}