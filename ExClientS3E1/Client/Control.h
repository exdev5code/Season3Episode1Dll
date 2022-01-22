#include "stdafx.h"

static HINSTANCE hInstance;

#pragma data_seg(".SHAREDDATA")
static HHOOK MouseHook = NULL; 
static HHOOK KeyboardHook = NULL;
#pragma data_seg()

#pragma comment(linker, "/SECTION:.SHAREDDATA,RWS")


BOOL KeyboardSetHook(BOOL set_or_remove);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) ;