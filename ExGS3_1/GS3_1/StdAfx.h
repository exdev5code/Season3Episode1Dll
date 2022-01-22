#ifndef G_STDAFX_H
#define G_STDAFX_H
//-----------------------------------------------------------------------------
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Process.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <rpc.h>
#include <rpcdce.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#include <algorithm>

//-----------------------------------------------------------------------------
using namespace std;
#pragma comment(lib, "ws2_32.lib")
//-----------------------------------------------------------------------------
static HMENU MyMenu;
static DWORD OldProtect;
static UINT_PTR MyMenuTimerID;
static UINT_PTR cPluginsTimer;
//-----------------------------------------------------------------------------
static HWND cWND;
static HINSTANCE hInst;
//-----------------------------------------------------------------------------

//#define DEBUG_CRASH	1

#pragma warning(disable : 4010 4244 4309 4995 4172 4715)
#pragma warning(disable : 4101)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4482)
#pragma warning(disable : 4700)
#pragma warning(disable : 4996)
#pragma warning(disable : 4018)
//-----------------------------------------------------------------------------
typedef BYTE OBJECTWARNING;
//-----------------------------------------------------------------------------
typedef enum
{
	Preto = 1,
	Vermelho = 2,
	Verde = 3,
	Azul = 4,
	Vermelho2 = 5,
	Azul2 = 6,
	Rosa = 7
} LogColors;
//-----------------------------------------------------------------------------
#define DEV_OFFEXP				1
#define ANTI_CHEAT_PLUS			0
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------