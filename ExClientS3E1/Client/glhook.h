#pragma once
#include <windows.h>
#include <GL\gl.h>
#include <gl\glu.h>
#include "glaux.h"
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"GLu32.lib")
#pragma comment(lib,"GLaux.lib")
#pragma comment(lib,"ADVAPI32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"User32.lib")
#include <Windows.h>
#include <iostream>


void InitOGLHook();
void DeleteOGLHook();

struct hookglobal{
	bool isAnizot;
	bool isFog;
	int iMaxClipXY;

	char cAnizot[50];
	char cFog[50];
	char cMaxClipXY[50];
	char cIsCamera[50];

	char cAddress[30];
	char cVersion[10];
	char cSerial[20];
	char cPort[10];
	char cFontSize[10];
	DWORD dwTickCount;

	char cR[50];
	char cG[50];
	char cB[50];
};

struct MapFogStruct{
	int r;
	int g;
	int b;
};

struct FogDrawStruct{
	int sDist;
	int eDist;
	int sZoom;
	int eZoom;
};

extern hookglobal GLOBAL;
extern MapFogStruct FogConfig[100];
extern FogDrawStruct FDRAW;