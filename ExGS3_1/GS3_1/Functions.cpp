//==================================================================================================
//=====================================AROTH GAMESERVER PROJECT=====================================
//==================================================================================================
// File:          Functions.cpp
// Description:   Additional functions
// Last Edit:     20.10.2011
//==================================================================================================
// Code: SmallHabit
//==================================================================================================
#include "Functions.h"
#include "windows.h"
#include "Defines.h"
// ---------------------------------------------------------------------------
Funtions g_Funtions;
// ---------------------------------------------------------------------------

Funtions::Funtions(void)
{
	// ----
}
// ---------------------------------------------------------------------------

Funtions::~Funtions(void)
{
	// -----
}
// ---------------------------------------------------------------------------

void __cdecl Funtions::SetJmp(DWORD Offset)
{
	*(BYTE*)(Offset) = 0xEB;
}

void __cdecl Funtions::SetNop(DWORD dwOffset,int Size)
{
	for(int n=0;n < Size;n++)
	{
		*(BYTE*)(dwOffset+n)=0x90;
	}
}
// ---------------------------------------------------------------------------