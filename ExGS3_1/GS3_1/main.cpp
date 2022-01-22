#include "USER.h"
#include "Protocol.h"
#include "CQuery.h"
#include "Fix.h"
#include "Offtrade.h"
#include "DropZen.h"
#include "Character.h"
#include "PvPSystem.h"
#include "Quest_PGW.h"
#include "Experience.h"
#include "ExCore.h"
#include "HappyHour.h"
#include "CQuery.h"

__declspec (dllexport) DWORD ProtocolClient(DWORD Type)
{
	if(Type == 0x1D)return 0x1D;
	if(Type == 0xD6)return 0xD6;
	if(Type == 0xDC)return 0xDC;
	return Type;
}

__declspec (dllexport) DWORD ProtocolServer(DWORD Type)
{
	if(Type == 0x1D)return 0x1D;
	if(Type == 0xD6)return 0xD6;
	if(Type == 0xDC)return 0xDC;
	return Type;
}

void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset-(dwJmpOffset+5);
}

DWORD WINAPI EventTimer(LPVOID lpParam)
{
	Sleep(5000);
	ExEventTimeTick();
	return 1;
} 

DWORD WINAPI PlayerTimer(LPVOID lpParam)
{
	Sleep(1000);
	ExPlayerTimeTick();
	return 1;
} 

extern "C" _declspec(dllexport) void Load()
{	
	DWORD dProtect;
	if(VirtualProtect (LPVOID (0x401000) , 0x00746FFF, PAGE_EXECUTE_READWRITE , &dProtect))
	{
		//if(!ExCoreSecurity()) 
		//	ExitProcess(0);	 	 //ExCoreSecurity

		//ExCoreConfigs();
		_asm
		{
			MOV DWORD PTR DS:[00700000H],Offset ProtocolServer
			MOV DWORD PTR DS:[00700004H],Offset ProtocolClient
		}

		CloseHandle(CreateThread(NULL,0,EventTimer,NULL,0,NULL));
		CloseHandle(CreateThread(NULL,0,PlayerTimer,NULL,0,NULL));

		//HookThis((DWORD)&gObjLevelUpPointAddEx,0x004052C7);
	    HookThis((DWORD)&DropZen, 0x00405402); 
		HookThis((DWORD)&iExpAdder, GCKill);
		HookThis((DWORD)&MyCharacter,gObjCalCharacter_CALL);
		HookThis((DWORD)&ProtocolCore,0x00403BA7);

		*(DWORD*)((0x0040308F+1)) = (DWORD)&gObjPlayerKillerEx - (0x0040308F+5);
		*(DWORD*)((0x00406587+1)) = (DWORD)&PkCheckEx - (0x00406587+5);
		//MySQL.Load();
		char szServer[50];
		char szUser[50];
		char szPassword[50];
		char szDatabase[50];

		GetPrivateProfileStringA("Connect", "Server", "127.0.0.1", szServer, sizeof(szServer), "..\\Settings\\Connect.ini");
		GetPrivateProfileStringA("Connect", "Account", "sa", szUser, sizeof(szUser), "..\\Settings\\Connect.ini");
		GetPrivateProfileStringA("Connect", "Password", "123456", szPassword, sizeof(szPassword), "..\\Settings\\Connect.ini");
		GetPrivateProfileStringA("Connect", "Database", "MuOnline", szDatabase, sizeof(szDatabase), "..\\Settings\\Connect.ini");

		if (m_DBQuery.Connect(3, szDatabase, szUser, szPassword) == FALSE)
		{
			MessageBox(NULL, "SQL Connect Error", "Error", ERROR);
			
			#if(!DEV_OFFEXP)
			ExitProcess(0);
			#endif
		}

		g_Fix.Load();
		OFFTrade.Init();
		Qest_PGW.Q_Load();
		cExperience.ExpLoad();
		ExCoreLoader();
	}
	else
	{
		MessageBoxA(NULL, "DLL Lybrary not Loaded", "Error", MB_OK);
		ExitProcess(0);
	}
}

