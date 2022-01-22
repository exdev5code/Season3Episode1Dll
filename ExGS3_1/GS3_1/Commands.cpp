//==================================================================================================
//===================================== EX-GAMES GAMESERVER PROJECT ================================
//==================================================================================================
// File:          Commands.cpp
// Description:   Commands
// Last Edit:     2.04.2013
//==================================================================================================
// Code: DangeR Skype: muonline.bk
//==================================================================================================
#include "USER.h"
#include "Defines.h"
#include "StdAfx.h"
#include "CQuery.h"
#include "Protocol.h"
#include "Reset.h"
#include "PackSystem.h"
#include "OffTrade.h"
#include "CoinZen.h"
#include "AddFunctions.h"
#include "Rang.h"
#include "GMSystem.h"
#include "VipSystem.h"
#include "BMQuest.h"	//BMQuest

#include "SystemBrother.h"

#include "OffExp.h"

//Функция ввода команды в чат
//===========================
void ChatDataSend(DWORD gObjId,LPBYTE Protocol)
{	
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (gObjId);
	#if(DEV_OFFEXP)
	char CommandOffExp[]	= "/offafk";
	if(!memcmp(&Protocol[13],CommandOffExp,strlen(CommandOffExp))) OffExp.OffExpStart(gObjId);
	#endif
	//if(!memcmp(&Protocol[13],CommandEliteGt,strlen(CommandEliteGt)))//LogChat System
	//{
	//	EliteClickerCick(gObjId);
	//}
	

	int OnPackSystem	=	GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\PackSystem.ini");
	int OnCoinsSystem	=	GetPrivateProfileInt("Common","Enable",0,"..\\Settings\\Coins.ini");
	//Ресет команда
	char ResetCommand[] = "/reset";
	//AddCom команда
	char CmDCommand[] = "/cmd";
	//Пак команды
	char PackLifeCMD[300];
	GetPrivateProfileString("LifePack", "PackCMD","/pack life",PackLifeCMD,300,"..\\Settings\\PackSystem.ini");
	char UnPackLifeCMD[300];
	GetPrivateProfileString("LifePack", "UnPackCMD","/unpack life",UnPackLifeCMD,300,"..\\Settings\\PackSystem.ini");
	char PackChaosCMD[300];
	GetPrivateProfileString("ChaosPack", "PackCMD","/pack chaos",PackChaosCMD,300,"..\\Settings\\PackSystem.ini");
	char UnPackChaosCMD[300];
	GetPrivateProfileString("ChaosPack", "UnPackCMD","/unpack chaos",UnPackChaosCMD,300,"..\\Settings\\PackSystem.ini");
	char PackCreationCMD[300];
	GetPrivateProfileString("CreationPack", "PackCMD","/pack creation",PackCreationCMD,300,"..\\Settings\\PackSystem.ini");
	char UnPackCreationCMD[300];
	GetPrivateProfileString("CreationPack", "UnPackCMD","/unpack creation",UnPackCreationCMD,300,"..\\Settings\\PackSystem.ini");
	char PackGuardionCMD[300];
	GetPrivateProfileString("GuardionPack", "PackCMD","/pack guardian",PackGuardionCMD,300,"..\\Settings\\PackSystem.ini");
	char UnPackGuardionCMD[300];
	GetPrivateProfileString("GuardionPack", "UnPackCMD","/unpack guardian",UnPackGuardionCMD,300,"..\\Settings\\PackSystem.ini");
	char PackHarmonyCMD[300];
	GetPrivateProfileString("HarmonyPack", "PackCMD","/pack harmony",PackHarmonyCMD,300,"..\\Settings\\PackSystem.ini");
	char UnPackHarmonyCMD[300];
	GetPrivateProfileString("HarmonyPack", "UnPackCMD","/unpack harmony",UnPackHarmonyCMD,300,"..\\Settings\\PackSystem.ini");
	//ОффТрейд
	char OffTrade[300];
    GetPrivateProfileString("Common", "CmdName","/offtrade",OffTrade,300,"..\\Settings\\OffTrade.ini");
	//Coins
	char SellBronzeCoinCMD[300];
    GetPrivateProfileString("Coins", "SellBronzeCoin","/sell bronzecoin",SellBronzeCoinCMD,300,"..\\Settings\\Coins.ini");
	char BuyBronzeCoinCMD[300];
    GetPrivateProfileString("Coins", "BuyBronzeCoin","/buy bronzecoin",BuyBronzeCoinCMD,300,"..\\Settings\\Coins.ini");

	char SellSilverCoinCMD[300];
    GetPrivateProfileString("Coins", "SellSilverCoin","/sell silvercoin",SellSilverCoinCMD,300,"..\\Settings\\Coins.ini");
	char BuySilverCoinCMD[300];
    GetPrivateProfileString("Coins", "BuySilverCoin","/buy silvercoin",BuySilverCoinCMD,300,"..\\Settings\\Coins.ini");

	char SellGoldenCoinCMD[300];
    GetPrivateProfileString("Coins", "SellGoldenCoin","/sell goldencoin",SellGoldenCoinCMD,300,"..\\Settings\\Coins.ini");
	char BuyGoldenCoinCMD[300];
    GetPrivateProfileString("Coins", "BuyGoldenCoin","/buy goldencoin",BuyGoldenCoinCMD,300,"..\\Settings\\Coins.ini");

	char SellPlatinaCoinCMD[300];
    GetPrivateProfileString("Coins", "SellPlatinaCoin","/sell platinacoin",SellPlatinaCoinCMD,300,"..\\Settings\\Coins.ini");
	char BuyPlatinaCoinCMD[300];
    GetPrivateProfileString("Coins", "BuyPlatinaCoin","/buy platinacoin",BuyPlatinaCoinCMD,300,"..\\Settings\\Coins.ini");

	//Гранд ресет команда
	char GResetCommand[] = "/greset";

	//Покупка Гем
	char BuyGemCMD[300];
    GetPrivateProfileString("Common", "CmdName","/buygem",BuyGemCMD,300,"..\\Settings\\BuyGem.ini");

	//Credits Server
	char InfoCommand[] = "/info";
	//Trace
	char CommandTrace[] = "/trace";
	//PkSet
	char CommandPkSet[] = "/pkset";
	//Move
	char CommandMove[] = "/teleport";
	//Move
	char CommandInfoChar[] = "/char";
	//Move
	char CommandAccMode[] = "/accmode";
	//BuyVip
	char CommandBuyVip[] = "/buyvip";
	//SellVip
	char CommandSellVip[] = "/sellvip";

	//bminfo
	char Commandbminfo[] = "/bminfo";	//BMQuest

	//pkclear
	char Commandpkclear[] = "/pkclear";	//pkclear

	//EliteCick Security
	char CommandElitePick[] = "//pick";
	char CommandEliteGt[] = "//gt";

	//char CommandBan[] = "/ban";	//ban

	char CommandMinusGem[] = "/minusgem";

	char CommandStats[] = "/stats";
//--------------------------------------------------------------------------------------------------
//Stats Reset
if(!memcmp(&Protocol[13],CommandStats,strlen(CommandStats)))
{
	RestartStats(gObjId);
}
//#####################################################################################################
	char CommandBrother[] = "/brother";	//Проверка есть бонус от братства
	char CommandBrothTeleportCMD[] = "/brteleport";	//телепорт брата на спот
	char CommandBrothOffChar[] = "/broffexp";	//Оставить чара в офф, доверить клану
	char CommandBrotherInfo[] = "/brinfo";	//информация о братстве

	//--------------------------------------------------------------------------------------------------
	//Information Brotherd
	if(!memcmp(&Protocol[13],CommandBrotherInfo,strlen(CommandBrotherInfo)))
	{
		SystemBrother.BrotherInformation(gObjId);
	}
	//--------------------------------------------------------------------------------------------------
	//Off Char
	if(!memcmp(&Protocol[13],CommandBrothOffChar,strlen(CommandBrothOffChar)))
	{
		SystemBrother.BrothOffCharCMD(gObjId);
	}	
	//--------------------------------------------------------------------------------------------------
	//BrothTeleportCMD
	if(!memcmp(&Protocol[13],CommandBrothTeleportCMD,strlen(CommandBrothTeleportCMD)))
	{
		SystemBrother.BrothTeleportCMD(gObjId,(char*)Protocol+13+strlen(CommandBrothTeleportCMD));
	}	
	//--------------------------------------------------------------------------------------------------
	//Brother
	if(!memcmp(&Protocol[13],CommandBrother,strlen(CommandBrother)))
	{
		SystemBrother.BrothCMD(gObjId);
	}	
//#####################################################################################################
//--------------------------------------------------------------------------------------------------
// CommandMinusGem
	if(!memcmp(&Protocol[13],CommandMinusGem,strlen(CommandMinusGem)))
	{
		MinusGemForADM(gObjId,(char*)Protocol+13+strlen(CommandMinusGem));
	}	
//--------------------------------------------------------------------------------------------------
//// CharacterBan
//	if(!memcmp(&Protocol[13],CommandBan,strlen(CommandBan)))
//	{
//		CharacterBan(gObjId,(char*)Protocol+13+strlen(CommandBan));
//	}	
//--------------------------------------------------------------------------------------------------
//gt
	if(!memcmp(&Protocol[13],CommandEliteGt,strlen(CommandEliteGt)))//Gt
	{
		EliteClickerCick(gObjId);
	}
//--------------------------------------------------------------------------------------------------
//pick
	if(!memcmp(&Protocol[13],CommandElitePick,strlen(CommandElitePick)))//Pick
	{
		EliteClickerCick(gObjId);
	}
//--------------------------------------------------------------------------------------------------
//pkclear
	if(!memcmp(&Protocol[13],Commandpkclear,strlen(Commandpkclear)))//BMQuest
	{
		Ex_PkClear(gObjId);
	}	
//--------------------------------------------------------------------------------------------------
// Commandbminfo
	if(!memcmp(&Protocol[13],Commandbminfo,strlen(Commandbminfo)))//BMQuest
	{
		BMQuest.CharacterInformation(gObjId);
	}	
//--------------------------------------------------------------------------------------------------
// CommandSellVip
	if(!memcmp(&Protocol[13],CommandSellVip,strlen(CommandSellVip)))
	{
		Vip.SellVipPoint(gObjId,(char*)Protocol+13+strlen(CommandSellVip));
	}	
//--------------------------------------------------------------------------------------------------
// BuyVip
	if(!memcmp(&Protocol[13],CommandBuyVip,strlen(CommandBuyVip)))
	{
		Vip.BuyVip(gObjId,(char*)Protocol+13+strlen(CommandBuyVip));
	}	
//--------------------------------------------------------------------------------------------------
// ChatInfoChar
	if(!memcmp(&Protocol[13],CommandAccMode,strlen(CommandAccMode)))
	{
		ChatAccMode(gObjId,(char*)Protocol+13+strlen(CommandAccMode));
	}	
//--------------------------------------------------------------------------------------------------
// ChatInfoChar
	if(!memcmp(&Protocol[13],CommandInfoChar,strlen(CommandInfoChar)))
	{
		ChatInfoChar(gObjId,(char*)Protocol+13+strlen(CommandInfoChar));
	}
//--------------------------------------------------------------------------------------------------
// Move
	if(!memcmp(&Protocol[13],CommandMove,strlen(CommandMove)))
	{
		ChatMove(gObjId,(char*)Protocol+13+strlen(CommandMove));
	}
//--------------------------------------------------------------------------------------------------
// PkSet
	if(!memcmp(&Protocol[13],CommandPkSet,strlen(CommandPkSet)))
	{
		ChatPkSet(gObjId,(char*)Protocol+13+strlen(CommandPkSet));
	}
//--------------------------------------------------------------------------------------------------
// Trace
	if(!memcmp(&Protocol[13],CommandTrace,strlen(CommandTrace)))
	{
		ChatTrace(gObjId,(char*)Protocol+13+strlen(CommandTrace));
	}
//--------------------------------------------------------------------------------------------------
// Credits Server
    if(!memcmp(&Protocol[13],InfoCommand,strlen(InfoCommand)))
	{
		Credits(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Покупка ГЕМ
    if(!memcmp(&Protocol[13],BuyGemCMD,strlen(BuyGemCMD)))
	{
		BuyGemFun(gObjId,(char*)Protocol+13+strlen(BuyGemCMD));
	}
//--------------------------------------------------------------------------------------------------
// Add Commands
    if(!memcmp(&Protocol[13],CmDCommand,strlen(CmDCommand)))
	{
		AddCommandsDarkLodr(gObjId,(char*)Protocol+13+strlen(CmDCommand));
	}
//--------------------------------------------------------------------------------------------------
// Гранд ресет
    if(!memcmp(&Protocol[13],GResetCommand,strlen(GResetCommand)))
	{
		GrandResetSystem(gObjId);
	}
if(OnCoinsSystem)
{
//--------------------------------------------------------------------------------------------------
// Sell PlatinaCoin
    if(!memcmp(&Protocol[13],SellPlatinaCoinCMD,strlen(SellPlatinaCoinCMD)))
	{
		SellPlatinaCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Buy PlatinaCoin
    if(!memcmp(&Protocol[13],BuyPlatinaCoinCMD,strlen(BuyPlatinaCoinCMD)))
	{
		BuyPlatinaCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Sell GoldenCoin
    if(!memcmp(&Protocol[13],SellGoldenCoinCMD,strlen(SellGoldenCoinCMD)))
	{
		SellGoldenCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Buy GoldenCoin
    if(!memcmp(&Protocol[13],BuyGoldenCoinCMD,strlen(BuyGoldenCoinCMD)))
	{
		BuyGoldenCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Sell SilverCoin
    if(!memcmp(&Protocol[13],SellSilverCoinCMD,strlen(SellSilverCoinCMD)))
	{
		SellSilverCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Buy SilverCoin
    if(!memcmp(&Protocol[13],BuySilverCoinCMD,strlen(BuySilverCoinCMD)))
	{
		BuySilverCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Sell BronzeCoin
    if(!memcmp(&Protocol[13],SellBronzeCoinCMD,strlen(SellBronzeCoinCMD)))
	{
		SellBronzeCoin(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Buy BronzeCoin
    if(!memcmp(&Protocol[13],BuyBronzeCoinCMD,strlen(BuyBronzeCoinCMD)))
	{
		BuyBronzeCoin(gObjId);
	}
}
//--------------------------------------------------------------------------------------------------
// Reset System
    if(!memcmp(&Protocol[13],ResetCommand,strlen(ResetCommand)))
	{
		CheckReset(gObjId);
	}
if(OnPackSystem)
{
//--------------------------------------------------------------------------------------------------
// Life Pack & UnPack
	if(!memcmp(&Protocol[13],PackLifeCMD,strlen(PackLifeCMD)))
	{
		PackLife(gObjId);
	}
	if(!memcmp(&Protocol[13],UnPackLifeCMD,strlen(UnPackLifeCMD)))
	{
		UnPackLife(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Chaos Pack & UnPack
	if(!memcmp(&Protocol[13],PackChaosCMD,strlen(PackChaosCMD)))
	{
		PackChaos(gObjId);
	}
	if(!memcmp(&Protocol[13],UnPackChaosCMD,strlen(UnPackChaosCMD)))
	{
		UnPackChaos(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Creation Pack & UnPack
	if(!memcmp(&Protocol[13],PackCreationCMD,strlen(PackCreationCMD)))
	{
		PackCreation(gObjId);
	}
	if(!memcmp(&Protocol[13],UnPackCreationCMD,strlen(UnPackCreationCMD)))
	{
		UnPackCreation(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Guardion Pack & UnPack
	if(!memcmp(&Protocol[13],PackGuardionCMD,strlen(PackGuardionCMD)))
	{
		PackGuardion(gObjId);
	}
	if(!memcmp(&Protocol[13],UnPackGuardionCMD,strlen(UnPackGuardionCMD)))
	{
		UnPackGuardion(gObjId);
	}
//--------------------------------------------------------------------------------------------------
// Harmony Pack & UnPack
	if(!memcmp(&Protocol[13],PackHarmonyCMD,strlen(PackHarmonyCMD)))
	{
		PackHarmony(gObjId);
	}
	if(!memcmp(&Protocol[13],UnPackHarmonyCMD,strlen(UnPackHarmonyCMD)))
	{
		UnPackHarmony(gObjId);
	}
}
//--------------------------------------------------------------------------------------------------
// Оффтрейд
	if(!memcmp(&Protocol[13],OffTrade,strlen(OffTrade)))
	{
     OFFTrade.CreateOfflineTrade(gObjId);
	} 
}