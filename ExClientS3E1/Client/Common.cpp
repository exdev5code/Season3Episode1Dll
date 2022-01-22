// Aroth Mu Online Main Addon
// Project owner: DarkSim
// Code: tag-egor, SmallHabit
// Special Thanks for help 8BitCore
//=======================================================================================================================
#include "stdafx.h"
#include "Jewels.h"
#include "Price.h"
//#include "WeaponView.h"
#include "utils.h"
#include "Models.h"
#include "glhook.h"
#include "Config.h"
#include "base64.h"
#include "md5.h"
#include <Windows.h>
#include <stdio.h>
#include "ArothGuard.h"
#include "Guard.h"
#include "Control.h"
#include "Security.h"
#include <string.h>
#include <stdio.h>                       /* для printf() */
#include <cstring>
#include "Protocol.h"
#include "AntiCheatPlus.h"

//DWORD WINAPI Timer(LPVOID lpParam)
//{
//	Sleep(5000);
//	while(true)
//	{
//		if(Config.Ctrl == true)
//			keybd_event(VK_CONTROL, 0, 0, 0); // вот тут какой-то флаг
//		Sleep(1000);
//	}
//	return 1;
//}

void Init()
{
	Security.ConfigStart();
//Лимит на передачу зена
	/*
*(BYTE*)(0x006CA535 + 1)    = 9;
*(BYTE*)(0x006BEF2E)        = 0xEB;
*/
	
//------------------------------------------------------------------------
// FIX ANSI
//------------------------------------------------------------------------
  	BYTE Font[3] = { 0x01, 0x00, 0x00 }; 
	memcpy((int*)0x007D2790, Font, sizeof(Font));


//------------------------------------------------------------------------
// FIX Carnage Ticket  
//------------------------------------------------------------------------
  *(BYTE*)(0x006475AD+2) = 0x3D; 
 
//------------------------------------------------------------------------
// Change Price % 
//------------------------------------------------------------------------
  *(BYTE*)(0x0059A561+1) = 0x01;

  /*
*(BYTE*)(0x004DD61B+1) = 0x01;
*(BYTE*)(0x004DD65B+1) = 0x01;
*(BYTE*)(0x004DD69B+1) = 0x01;
*(BYTE*)(0x004DD6F4+1) = 0x01;
*(BYTE*)(0x006DA9D5+1) = 0x01; 
  
*(BYTE*)(0x004DD61D+1) = 0xCC;
*(BYTE*)(0x004DD61D+2) = 0x00;
*(BYTE*)(0x004DD6F6+1) = 0xCC;
*(BYTE*)(0x004DD6F6+2) = 0x00;

*(BYTE*)(0x007D2790) = 0x04;
*/
*(BYTE*)(0x007D2790+2) = 0x01;
//------------------------------------------------------------------------
// Decrypt Logs
//------------------------------------------------------------------------

if(Config.DecryptLogs != 0)
{
	BYTE DecriptLog[5] = {0x90, 0x90, 0x90, 0x90, 0x90};
	memcpy((int*)0x0042176D, DecriptLog, sizeof(DecriptLog));
	memcpy((int*)0x00421980, DecriptLog, sizeof(DecriptLog));
}
//------------------------------------------------------------------------
// Change Folder
//------------------------------------------------------------------------    
char cTempLog[20] = "Data/Logs/Error.log";
DWORD *offsetLog = (DWORD*)(LogFolder);
memset(&offsetLog[0],0,20);
memcpy(&offsetLog[0],cTempLog,strlen(cTempLog));


char cTempDump[22] = "Data/Logs/Error.dmp";
DWORD *offsetDump = (DWORD*)(DumpFolder);
memset(&offsetDump[0],0,22);
memcpy(&offsetDump[0],cTempDump,strlen(cTempDump));

//=======================================================================================================================
// Item Price Changer
//=======================================================================================================================
 *(unsigned int*) (0x0059951B+3) = Config.SoulPrice;  
 *(unsigned int*) (0x0059953B+3) = Config.ChaosPrice; 
 *(unsigned int*) (0x0059955C+3) = Config.LifePrice;  
 *(unsigned int*) (0x0059957D+3) = Config.CreationPrice; 
 *(unsigned int*) (0x00599ADF+3) = Config.GuardianPrice;  

//=======================================================================================================================
// Screenshot Folder
//=======================================================================================================================
    DWORD *ScreenFolder2 = (DWORD*)(ScreenFolder);
    memset(&ScreenFolder2[0],0,45);
	memcpy(&ScreenFolder2[0],Config.ImagesFolder,strlen(Config.ImagesFolder));
//=======================================================================================================================
// Window Name
//=======================================================================================================================
    DWORD *WindowName2 = (DWORD*)(WindowName);
    memset(&WindowName2[0],0,18);
	memcpy(&WindowName2[0],Config.MainName,strlen(Config.MainName));
//=======================================================================================================================
// Connect
//=======================================================================================================================
   /*
	DWORD *ConnectIP2 = (DWORD*)(ConnectIP);
    memset(&ConnectIP2[0],0,16);
	//char eXIP[] =	"178.124.144.169";
	char eXIP[] =	"192.168.0.103";
	memcpy(&ConnectIP2[0], eXIP, sizeof(eXIP));
	*/
	char cAdress[20];
	sprintf(cAdress, "176.31.57.127", ConnectIP);
	WriteMemory( (PVOID) ConnectIP, cAdress, sizeof( cAdress ) );

	//memcpy(&ConnectIP2[0],Security.RealIP,strlen(Security.RealIP));

	//91.211.117.81
	//char NewSerial[20] = "st1Hpk6be03jdt7z";

    DWORD *ExeSerial2 = (DWORD*)(ExeSerial);
    memset(&ExeSerial2[0],0,17);
	char eXSerial[] = "Td4e8UtYvLo90zZd";	//1qve7Lcvdhk3Rysq
	memcpy(&ExeSerial2[0], eXSerial, sizeof(eXSerial));


	/*char rVersion[] = "22656";
	int *Version = (int*)(0x007D3B54);
	memset(&Version[0], 0x00, sizeof(rVersion));
	memcpy(&Version[0], rVersion, sizeof(rVersion)); */
//=======================================================================================================================
// Item Text
//=======================================================================================================================
	memcpy((char*)0x00907000,Config.iText,50);
	memcpy((char*)0x00907050,Config.iText2,50);
	memcpy((char*)0x00907100,Config.iText3,50);
	memcpy((char*)0x00907150,Config.iText4,50);
	memcpy((char*)0x00907200,Config.iText5,50);
	memcpy((char*)0x00907250,Config.iText6,50);
	memcpy((char*)0x00907300,Config.iText7,50);
	memcpy((char*)0x00907350,Config.iText8,50);
	memcpy((char*)0x00907400,Config.iText9,50);
	memcpy((char*)0x00907450,Config.iText10,50);
	memcpy((char*)0x00907500,Config.iText11,50);
	memcpy((char*)0x00907550,Config.iText12,50);
	memcpy((char*)0x00907600,Config.iText13,50);
	memcpy((char*)0x00907650,Config.iText14,50);
	memcpy((char*)0x00907700,Config.iText15,50);
	memcpy((char*)0x00907750,Config.iText16,50);
	memcpy((char*)0x00907800,Config.iText17,50);
	memcpy((char*)0x00907850,Config.iText18,50);
	memcpy((char*)0x00907900,Config.Options1,50);
//=======================================================================================================================
// Load
//=======================================================================================================================

	//*(BYTE*)(0x00221009+1) = 0x23;

	//00221009 - 3d camera f7	//MaEx.dll

	BYTE bCharSet[] = {0x01, 0x00, 0x00, 0x00, 0x01, 0x00};
	memcpy((int*)0x007D2790, bCharSet, sizeof(bCharSet));

	DWORD OldProtect;

	if(VirtualProtect(LPVOID(0x401000),VirtualAddressOffset,PAGE_EXECUTE_READWRITE,&OldProtect)) 
	{	
#if(ANTI_CHEAT_PLUS==TRUE)
		g_AntiCheatPlus.Load();
#endif
		//MessageBoxA(0,"Click","OK",0);
		KeyboardSetHook(true); //MouseSetHook(true);
		//Guard.Load();
		ModelsLoad();
		//PriceLoad();
		JewelsLoad();
		if(Config.ShieldView != 0)
		{
		//WeaponViewLoad();
		}
		//CloseHandle(CreateThread(NULL,0,Timer,NULL,0,NULL));
		//LoadLibraryA("NSTech.dll");

		g_Protocol.Load();

	} 
	else
	{
		MessageBoxA(NULL,"Unable to load  \n Submit about this error to support.","ExTeam Mu Online",MB_OK);
		ExitProcess(0);
	}
}


 BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				//MessageBoxA(0,"Click","OK",0);
			hInstance = hModule;
			ConfigLoad();
			Init();
			//LoadLibrary("Name.dll");
			}
		break;
		case DLL_PROCESS_DETACH:
			{
				//keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // вот тут какой-то флаг
				KeyboardSetHook(false);// MouseSetHook(false);
			}
			break;
	}
	return TRUE;
} 