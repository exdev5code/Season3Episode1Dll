#include "stdafx.h"
#include "utils.h"
#include "WeaponView.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#pragma comment (lib, "kernel32")

DWORD SecondWeaponFixVal = 1;
DWORD IsShield = 0;

__declspec(naked) void WeaponViewCheck()
{
	__asm
	{

#ifndef OLD_MAIN
		MOV BYTE PTR SS:[EBP+WeaponViewFlagFixup], 0

		CMP DWORD PTR SS:[EBP+SafeZoneFlagFixup], 0
		JE WEAPON_CHECK
		MOV BYTE PTR SS:[EBP+WeaponViewFlagFixup], 1	

WEAPON_CHECK:

		MOV EAX, DWORD PTR SS:[EBP+8]
		CMP DWORD PTR SS:[EBP+HandFlagFixup], 0
		JNZ LEFT_HAND
	

		MOVSX ECX, WORD PTR DS:[EAX+RightHandFixup]

		CMP ECX, MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE NO_DISPLAY

		CMP ECX, MAKE_ITEM(4, 15) + OBJ_OFFS
		JE DISPLAY_WEAPON
		JMP END_CHECK

LEFT_HAND:
		MOVSX ECX, WORD PTR DS:[EAX+LeftHandFixup]

		CMP ECX, MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE NO_DISPLAY

		CMP ECX, MAKE_ITEM(4, 7) + OBJ_OFFS
		JE DISPLAY_WEAPON
		JMP END_CHECK


DISPLAY_WEAPON:
		MOV BYTE PTR SS:[EBP+WeaponViewFlagFixup], 1
		JMP END_CHECK

NO_DISPLAY:
		MOV BYTE PTR SS:[EBP+WeaponViewFlagFixup], 0

#elif defined OLD_MAIN


		MOV BYTE PTR SS:[STACK_PTR+WeaponViewFlagFixup], 0

		CMP DWORD PTR SS:[STACK_PTR+SafeZoneFlagFixup], 0
		JE WEAPON_CHECK
		MOV BYTE PTR SS:[STACK_PTR+WeaponViewFlagFixup], 1	

WEAPON_CHECK:

		CMP EAX, 0
		JNZ LEFT_HAND
	

		CMP WORD PTR DS:[CHAR_REG+RightHandFixup], MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE NO_DISPLAY

		CMP WORD PTR DS:[CHAR_REG+RightHandFixup], MAKE_ITEM(4, 15) + OBJ_OFFS
		JE DISPLAY_WEAPON
		JMP END_CHECK

LEFT_HAND:


		CMP WORD PTR DS:[CHAR_REG+LeftHandFixup], MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE NO_DISPLAY

		CMP WORD PTR DS:[CHAR_REG+LeftHandFixup], MAKE_ITEM(4, 7) + OBJ_OFFS
		JE DISPLAY_WEAPON
		JMP END_CHECK


DISPLAY_WEAPON:
		MOV BYTE PTR SS:[STACK_PTR+WeaponViewFlagFixup], 1
		JMP END_CHECK

NO_DISPLAY:
		MOV BYTE PTR SS:[EBP+WeaponViewFlagFixup], 0


#else 

		//check for correct preprocessor definitions :D
		throw

#endif

END_CHECK:
		
		jmp WeaponViewCheck_Ret
	}
}

__declspec(naked) void SecondWeaponViewCheck()
{
	__asm
	{
#ifndef OLD_MAIN

		CMP DWORD PTR SS:[EBP+HandFlagFixup], 0
		JNZ END_CHECK

		MOV DWORD PTR SS:[EBP+HandFlagFixup], 1
		MOV SecondWeaponFixVal, 1

#elif defined OLD_MAIN

		CMP SecondWeaponFixVal, 1
		JNZ END_CHECK

		MOV EAX, 1
		MOV SecondWeaponFixVal, 1

#else

		//check for correct preprocessor definitions :D
		throw

#endif


		JMP WeaponViewCheck

END_CHECK:
		MOV SecondWeaponFixVal, 1
		jmp SecondWeaponViewCheck_Ret
	}
}

__declspec(naked) void SecondWeaponViewCheckReplacedCode()
{
	__asm
	{
#ifndef OLD_MAIN

		MOV EDX, DWORD PTR SS:[EBP+SomeVal1Fixup]
		MOV EAX, DWORD PTR SS:[EBP+SomeVal2Fixup]
		MOV DWORD PTR DS:[EDX+SomeVal3Fixup], EAX

#elif defined OLD_MAIN
		MOV EDX, 0x3E800000
#else
		throw
#endif
		JMP SecondWeaponViewCheck
	}
}

DWORD s_eax, s_ecx, s_edx;

__declspec(naked) void SecondWeaponViewFix()
{
	__asm
	{

#ifdef OLD_MAIN
		MOV s_eax, EAX
		MOV s_ecx, ECX
		MOV s_edx, EDX
#endif

		MOV EAX, SecondWeaponFixVal
		XOR DWORD PTR SS:[EBP+RotFixup], EAX
		XOR DWORD PTR SS:[EBP+TransFixup], EAX
		MOV IsShield, 0

		// check for shield
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 0) + OBJ_OFFS
		JL FLIP_CHECK
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(7, 0) + OBJ_OFFS
		JGE FLIP_CHECK

		MOV IsShield, 1
		
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 16) + OBJ_OFFS
		JNZ CHECK_SHIELD_14_15


		MOV DWORD PTR SS:[STACK_PTR+RotFixup], 0x41F00000
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+4], 0
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+8], 0x42B40000
		LEA EDX, DWORD PTR SS:[STACK_PTR+TransFixup]
		LEA EAX, DWORD PTR SS:[STACK_PTR+RotFixup]
		PUSH EDX
		PUSH EAX
		CALL RotateFunc
		ADD ESP, 8
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x0C], 0xC1A00000
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x1C], 0
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x2C], 0xC1A00000

		JMP FLIP_CHECK


CHECK_SHIELD_14_15:

		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 15) + OBJ_OFFS
		JE SHIELD_14_15
		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 14) + OBJ_OFFS
		JNZ CHECK_SHIELD_6

SHIELD_14_15:

		MOV DWORD PTR SS:[STACK_PTR+RotFixup], 0x42480000
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+4], 0
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+8], 0x42B40000
		LEA EDX, DWORD PTR SS:[STACK_PTR+TransFixup]
		LEA EAX, DWORD PTR SS:[STACK_PTR+RotFixup]
		PUSH EDX
		PUSH EAX
		CALL RotateFunc
		ADD ESP, 8
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x0C], 0xC1E00000
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x1C], 0
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x2C], 0xC1C80000

		JMP FLIP_CHECK


CHECK_SHIELD_6:

		CMP WEAPON_ID_CONTAINER, MAKE_ITEM(6, 6) + OBJ_OFFS
		JNZ SET_SHIELD

		MOV DWORD PTR SS:[STACK_PTR+RotFixup], 0x41F00000
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+4], 0
		MOV DWORD PTR SS:[STACK_PTR+RotFixup+8], 0x42B40000
		LEA EDX, DWORD PTR SS:[STACK_PTR+TransFixup]
		LEA EAX, DWORD PTR SS:[STACK_PTR+RotFixup]
		PUSH EDX
		PUSH EAX
		CALL RotateFunc
		ADD ESP, 8
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x0C], 0xC1700000
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x1C], 0
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x2C], 0xC1C80000

		JMP FLIP_CHECK


SET_SHIELD:


		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x0C], 0xC1200000
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x1C], 0
		MOV DWORD PTR SS:[STACK_PTR+TransFixup+0x2C], 0


FLIP_CHECK:
		
		CMP IsShield, 1
		JE EXIT
	
		CMP SecondWeaponFixVal, 1
		JE EXIT

		SUB ESP, 0x3C
#if STACK_PTR == ESP
	#define fixup	0x3C
#else
	#define fixup	0
#endif
		MOV DWORD PTR SS:[ESP+0x30], 0x43110000
		MOV DWORD PTR SS:[ESP+0x34], 0
		MOV DWORD PTR SS:[ESP+0x38], 0x43898000
		LEA EAX, DWORD PTR SS:[ESP]
		LEA ECX, DWORD PTR SS:[ESP+0x30]
		PUSH EAX
		PUSH ECX
		CALL RotateFunc
		ADD ESP, 8

		MOV DWORD PTR SS:[ESP+0x0C], 0
		MOV DWORD PTR SS:[ESP+0x1C], 0x41200000
		MOV DWORD PTR SS:[ESP+0x2C], 0xC1F00000
		LEA EDX, DWORD PTR SS:[STACK_PTR+TransFixup+fixup]
		LEA EAX, DWORD PTR SS:[ESP]
		LEA ECX, DWORD PTR SS:[STACK_PTR+TransFixup+fixup]
		PUSH EDX
		PUSH EAX
		PUSH ECX
		CALL TransFunc

		ADD ESP, 0x48

EXIT:

#ifdef OLD_MAIN
		MOV EAX, s_eax
		MOV ECX, s_ecx
		MOV EDX, s_edx
#endif

		PUSH SomeVal4
		JMP SecondWeaponViewFix_Ret
	}
}

//DWORD SecondWeaponViewRotFix_Old;
//DWORD SecondWeaponViewTransFix_Old;
//
//__declspec(naked) void SecondWeaponViewRotFix()
//{
//	__asm
//	{
//		MOV EAX, DWORD PTR SS:[ESP+4]
//		MOV ECX, SecondWeaponFixVal
//		XOR DWORD PTR DS:[EAX+8], ECX
//		JMP SecondWeaponViewRotFix_Old
//	}
//}
//
//__declspec(naked) void SecondWeaponViewTransFix()
//{
//	__asm
//	{
//		MOV EAX, DWORD PTR SS:[ESP+8]
//		MOV ECX, SecondWeaponFixVal
//		XOR DWORD PTR DS:[EAX+0x0C], ECX
//		JMP SecondWeaponViewTransFix_Old		
//	}
//}

void WeaponViewLoad()
{
	WriteJmp(WeaponViewCheck_Hook, (DWORD)WeaponViewCheck);
	WriteJmp(SecondWeaponViewCheckReplacedCode_Hook, (DWORD)SecondWeaponViewCheckReplacedCode);
	
	HookThis((DWORD)SecondWeaponViewCheck, SecondWeaponViewCheck_Hook1);
	HookThis((DWORD)SecondWeaponViewCheck, SecondWeaponViewCheck_Hook2);

	WriteJmp(SecondWeaponViewFix_Hook, (DWORD)SecondWeaponViewFix);
} 
#ifdef _MANAGED
#pragma managed(pop)
#endif
