#include <windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <shellapi.h>
#include <stdio.h>
#include "GuardDB.h"
#include <curl/curl.h>
#include <curl/easy.h>

void SystemProcessesScan() 
{	
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &pe32))
		{
			do
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if(hProcess != NULL)
				{
					if(ScanProcessMemory(hProcess)) 						
					{	
						char Error[300];	// Шлём нахуй
			sprintf(Error,"Hack '%s' detected!\nDont use hacks and cheats.",pe32.szExeFile);
			MessageBoxA(NULL,Error,"Aroth Protect",MB_ICONERROR);	// Показываем, что мы крутые
			ExitProcess(0);
						//char msg[255];
						//sprintf_s(msg,"%s/guard/index.php?c=%s",PageAddr,pe32.szExeFile);
						//ShellExecute(NULL,TEXT("open"), TEXT(msg), TEXT(""),NULL,SW_SHOWNORMAL); 
						//ExitProcess(0);						
					}
				}
			}
			while(Process32Next(hProcessSnap, &pe32));
		}
	}
	CloseHandle(hProcessSnap);
}

bool ScanProcessMemory(HANDLE hProcess) 
{
	for(int i = 0; i < MAX_PROCESS_DUMP; i++)
	{
		char aTmpBuffer[MAX_DUMP_SIZE];
		SIZE_T aBytesRead = 0;
		ReadProcessMemory(hProcess, (LPCVOID)g_ProcessesDumps[i].m_aOffset, (LPVOID)aTmpBuffer, sizeof(aTmpBuffer), &aBytesRead);
		
		if(memcmp(aTmpBuffer, g_ProcessesDumps[i].m_aMemDump, MAX_DUMP_SIZE) == 0)
		{	
			return true;
			break;
		}
	}
	return false;			
}

bool ListProcessModules()
{  
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;  
    MODULEENTRY32 me32;
    hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, 0 );  
    if( hModuleSnap == INVALID_HANDLE_VALUE )
        return( FALSE );
 
    me32.dwSize = sizeof( MODULEENTRY32 );
  
    if( !Module32First( hModuleSnap, &me32 ) )    
        return( FALSE );
  
    do
    { 
		if(strcmp(me32.szModule,"MUEliteClicker.dll")==0 || strcmp(me32.szModule,"Mirror_ws2_32.dll")==0)
        {	
			char msg[255];
			sprintf_s(msg,"%s/guard/index.php?c=MuEliteClicker",PageAddr);
            ShellExecute(NULL,TEXT("open"), TEXT(msg), TEXT(""),NULL,SW_SHOWNORMAL);
            ExitProcess(0);
        }
        if(strcmp(me32.szModule,"inproc.dll")==0)
        {	
			char msg[255];
			sprintf_s(msg,"%s/guard/index.php?c=SpeedGear",PageAddr);
            ShellExecute(NULL,TEXT("open"), TEXT(msg), TEXT(""),NULL,SW_SHOWNORMAL);
            ExitProcess(0); 
        }
		if(strcmp(me32.szModule,"rpe.dll")==0)
        {	
			char msg[255];
			sprintf_s(msg,"%s/guard/index.php?c=RPE",PageAddr);
            ShellExecute(NULL,TEXT("open"), TEXT(msg), TEXT(""),NULL,SW_SHOWNORMAL);
            ExitProcess(0); 
        }
		if(strcmp(me32.szModule,"gearntke.dll")==0)
		{	
			char msg[255];
			sprintf_s(msg,"%s/guard/index.php?c=SpeedGear",PageAddr);
			ShellExecute(NULL,TEXT("open"), TEXT(msg), TEXT(""),NULL,SW_SHOWNORMAL);
            ExitProcess(0); 
		}
    } 
    while( Module32Next( hModuleSnap, &me32 ) );
 
  CloseHandle( hModuleSnap );
  return( TRUE );
}

int debug1()
{ 
	_asm{
	mov eax,fs:[0x018];
	mov eax,[eax+0x30]
	movzx eax,byte ptr [eax+0x02]
	}
}

void FindHacks()
{
looper:
	if(debug1())
		::ExitProcess(0);

	SystemProcessesScan();
	ListProcessModules();
	RegisterHotKey(NULL, 1,MOD_ALT, VK_F4);
    Sleep(2000);
    goto looper;
}

void Setup()
{	
	SystemProcessesScan();	
	ListProcessModules();
	RegisterHotKey(NULL, 1,MOD_ALT, VK_F4);
	DWORD MyId;
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)FindHacks,NULL,0,&MyId);
}