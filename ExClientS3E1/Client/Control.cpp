#include "stdafx.h"
#include "Control.h"
#include "Config.h"
#include "Security.h"

BOOL KeyboardSetHook(BOOL set_or_remove)
{
	if(set_or_remove == TRUE) 
	{
		if(KeyboardHook == NULL) 
		{
			KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hInstance, GetCurrentThreadId());
			
			if(!KeyboardHook) { return FALSE; }
		}
	} 
	else
	{
		KeyboardHook = NULL;
		return UnhookWindowsHookEx(KeyboardHook);
	}
	return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{	
	if (((lParam >> 31) & 1) && (nCode == HC_ACTION)) 
	{
		//====================
		if(wParam == VK_NUMPAD9)
		{
			//Emulator Battle Mode
			if(Config.Ctrl == true) 
			{
				Config.Ctrl = false;
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // вот тут какой-то флаг
			}
			else 
			{
				Config.Ctrl = true;
			}
		}
	}	
	return CallNextHookEx(KeyboardHook, nCode, wParam, lParam);
}


