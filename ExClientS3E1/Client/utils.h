#pragma once

#include <windows.h>

DWORD HookThis2(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset);
void HookOffset(DWORD my, DWORD tohook, BYTE type);
void WriteJmp(DWORD dwWriteOffset, DWORD dwDstJmp);
void WriteCall(DWORD dwWriteOffset, DWORD dwDstJmp);

void SetNop(DWORD dwOffset,int Size);
void SetRangeNop(DWORD dwStart, DWORD dwEnd);
void SetRetn(DWORD dwOffset);
void SetByte(DWORD dwOffset, BYTE btValue);
void SetDword(DWORD dwOffset, DWORD dwValue);
DWORD GetDword(DWORD dwOffset);

DWORD UnProtect(DWORD dwAddr, DWORD size);
void Protect(DWORD dwAddr, DWORD size, DWORD dwProtection);
BYTE GetByte(DWORD dwOffset);


