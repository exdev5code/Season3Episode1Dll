#pragma once
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "md5.h"
#include <winbase.h>
#include <process.h>   
#include <tlhelp32.h>
#include <stdio.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#include <WinSock.h>
#pragma comment (lib,"ws2_32.lib") 
#include "TMemory.h"
// ----------------------------------------------------------------------------------------------
void Init();
// ----------------------------------------------------------------------------------------------
#define REF_08(x) (*(unsigned char *)(x));
#define REF_16(x) (*(unsigned short *)(x));
#define REF_32(x) (*(unsigned int *)(x));
// ----------------------------------------------------------------------------------------------
#define ITEM(type, index)	(type*512 + index)
#define ITEM2(type, index)	(type*512 + index + 635)
// ----------------------------------------------------------------------------------------------
#define FuckAdder 635
#define ITEM_IN_MAIN(x,y) ((x)*512+(y)+FuckAdder)
#define VirtualAddressOffset 0x07EECFFE
// ----------------------------------------------------------------------------------------------
#define ScreenFolder		(0x007E88D4)
#define WindowName			(0x007D36AC)
#define LogFolder		    (0x007D059C)
#define DumpFolder		    (0x007D3910)
#define ConnectIP			(0x007D2888)
#define ExeSerial			(0x007D3B5C)
// ----------------------------------------------------------------------------------------------
#define LoadModel_Offset	 0x006A0714
#define BMDModelLoad	     0x0069BBF3
#define ReturnOffset	     0x006A072B
#define PatchJewelsOffset	 0x0059ABE8
#define OpenTexture		     0x0069B777
// ----------------------------------------------------------------------------------------------
struct DataJMP
{
	BYTE Command;
	DWORD PointerToFunc;
};

// ----------------------------------------------------------------------------------------------
#define ANTI_CHEAT_PLUS			0
// ----------------------------------------------------------------------------------------------
