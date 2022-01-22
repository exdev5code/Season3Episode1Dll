#pragma once

#define OBJ_OFFS				(0x27B)

const int WeaponViewCheck_Hook = 0x538EC9;
const int WeaponViewCheck_Ret = 0x539020;

#define fixup	0x3C
#define MAX_ITEM				(512)
#define STACK_PTR				EBP
#define WEAPON_ID_CONTAINER		DWORD PTR SS:[EBP+0x1C]

#define RightHandFixup 0x2F8
#define LeftHandFixup 0x318

#define WeaponViewFlagFixup -0x1A8
#define HandFlagFixup -0x1B0
#define SafeZoneFlagFixup -0x5C

#define SomeVal1Fixup -0x1BC
#define SomeVal2Fixup -0x1C0
#define SomeVal3Fixup 8

const int SecondWeaponViewCheckReplacedCode_Hook = 0x539249;

const int SecondWeaponViewCheck_Hook1 = 0x5390D9+1;
const int SecondWeaponViewCheck_Hook2 = 0x5390E6+1;
const int SecondWeaponViewCheck_Ret = 0x539258;

const int SecondWeaponViewFix_Hook = 0x530A5B;
const int SecondWeaponViewFix_Ret = 0x530A60;
#define SomeVal4 0x69D9554

const int RotateFunc = 0x679035;
const int TransFunc = 0x6792D1;

#define RotFixup	(-0x2B8)
#define TransFixup	(-0x2AC)
#define MAKE_ITEM(type, index)	(type*MAX_ITEM + index)

void WeaponViewLoad();