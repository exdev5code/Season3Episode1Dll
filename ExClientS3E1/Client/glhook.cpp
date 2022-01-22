#include <windows.h>
#include <cmath>
#include <GL/gl.h>
#include "glaux.h"
#include <gl/glu.h>
#include "detours.h"
#include "glhook.h"
#include "tga.h"
#include <iostream>
#include <fstream>
#include "Config.h"
#include "ArothGuard.h"

enum MAINSTATE {
	SELECT_SERVER    = 2,
	SELECT_CHARACTER = 4,
	SELECT_GAME      = 5,
};

int *MAIN_STATE_ADDR  = (int*)0x007E8088; 

hookglobal GLOBAL;
MapFogStruct FogConfig[100];
FogDrawStruct FDRAW;

GLint g_nMaxAnisotropy = Config.MaxAnisotropy;

//OGL Function Prototypes
typedef void (APIENTRY *FUNC_GLENABLE)			(GLenum mode);
FUNC_GLENABLE glEnable_o = NULL;

//WinExec Function
typedef HWND (APIENTRY *FUNC_WINEXEC)			(LPCTSTR lpClassName,LPCTSTR lpWindowName);
FUNC_WINEXEC WinExec_o = NULL;

//WinExec Function
typedef void (APIENTRY *FUNC_GLBIND)			(GLenum target,GLuint texture);
FUNC_GLBIND glBindTex_o = NULL;

void APIENTRY glEnable_h(GLenum mode)
{	
	if(Config.InGameEffects != 0)
	{
		if(*MAIN_STATE_ADDR == SELECT_GAME)
		{
			if(Config.Anisotropy != 0)
			{
				glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
				glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
			}
			if(Config.Linear != 0)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
		}
	}
	else
	{
		if(Config.Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
		}
		if(Config.Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	//Вызов оригинальной функции
	glEnable_o(mode);
}

void InitOGLHook()
{	
	glEnable_o		= (FUNC_GLENABLE) DetourFunction((PBYTE)DetourFindFunction("OpenGL32.dll", "glBegin"),(PBYTE)glEnable_h);
}