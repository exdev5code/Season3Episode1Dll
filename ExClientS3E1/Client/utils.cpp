#include "stdafx.h"
#include "utils.h"

#include <stdio.h>
#include <stdarg.h>

//void MsgBox(char *szlog, ...)
//{
//	char szBuffer[512]="";
//	va_list pArguments;
//	va_start(pArguments, szlog);
//	vsprintf(szBuffer, szlog, pArguments);
//	va_end(pArguments);
//	MessageBoxA(NULL, szBuffer, "error", MB_OK|MB_APPLMODAL);
//}



DWORD UnProtect(DWORD dwAddr, DWORD size)
{
	DWORD old = 0;
	VirtualProtect((LPVOID)dwAddr, size, PAGE_EXECUTE_READWRITE, &old);
//		MsgBox("Unable to remove page protection. ERROR: %08X.", GetLastError());
	return old;
}

void Protect(DWORD dwAddr, DWORD size, DWORD dwProtection)
{
	DWORD old = 0;
	VirtualProtect((LPVOID)dwAddr, size, dwProtection, &old);
}

DWORD HookThis2(DWORD dwMyFuncOffset, DWORD dwJmpOffset)
{
	DWORD old = 0;
	__try
	{
		DWORD dwP = UnProtect(dwJmpOffset, 10);

		old = *(DWORD*)(dwJmpOffset+1) + dwJmpOffset + 5;
		*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset - (dwJmpOffset+5);

		Protect(dwJmpOffset, 10, dwP);
	}
	__finally{}

	return old;
}

void WriteJmp(DWORD dwWriteOffset, DWORD dwDstJmp)
{
	if(dwWriteOffset)
	{
		__try
		{
			DWORD dwP = UnProtect(dwWriteOffset, 10);
	
			SetByte(dwWriteOffset, 0xE9);
			HookThis(dwDstJmp, dwWriteOffset);
	
			Protect(dwWriteOffset, 10, dwP);
		}
		__finally{}
	}

}

void WriteCall(DWORD dwWriteOffset, DWORD dwDstJmp)
{
	__try
	{
		DWORD dwP = UnProtect(dwWriteOffset, 10);

		SetByte(dwWriteOffset, 0xE8);
		HookThis(dwDstJmp, dwWriteOffset);

		Protect(dwWriteOffset, 10, dwP);
	}
	__finally{}

}

void SetRangeNop(DWORD dwStart, DWORD dwEnd)
{
	__try
	{
		DWORD dwP = UnProtect(dwStart, dwEnd - dwStart);

		for(int n=dwStart; n < dwEnd; n++)
		{
			*(BYTE*)(n) = 0x90;
		}

		Protect(dwStart, dwEnd - dwStart, dwP);
	}
	__finally{}
}



void SetRetn(DWORD dwOffset)
{
	__try
	{
		DWORD dwP = UnProtect(dwOffset, 1);

		*(BYTE*)(dwOffset)=0xC3;

		Protect(dwOffset, 1, dwP);
	}
	__finally{}
}

void SetByte(DWORD dwOffset, BYTE btValue)
{
	__try
	{
		DWORD dwP = UnProtect(dwOffset, 1);

		*(BYTE*)(dwOffset)=btValue;

		Protect(dwOffset, 1, dwP);
	}
	__finally{}
}


BYTE GetByte(DWORD dwOffset)
{
	BYTE byVal = 0;
	__try
	{
		DWORD dwP = UnProtect(dwOffset, 1);

		byVal = *(BYTE*)(dwOffset);

		Protect(dwOffset, 1, dwP);
	}
	__finally{}

	return byVal;
}



void SetDword(DWORD dwOffset, DWORD dwValue)
{	
	__try
	{
		DWORD dwP = UnProtect(dwOffset, 4);

		*(DWORD*)(dwOffset)=dwValue;

		Protect(dwOffset, 4, dwP);
	}
	__finally{}
}


DWORD GetDword(DWORD dwOffset)
{
	DWORD dwVal = 0;
	__try
	{
		DWORD dwP = UnProtect(dwOffset, 4);

		dwVal = *(DWORD*)(dwOffset);

		Protect(dwOffset, 4, dwP);
	}
	__finally{}

	return dwVal;
}

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

void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset-(dwJmpOffset+5);
}