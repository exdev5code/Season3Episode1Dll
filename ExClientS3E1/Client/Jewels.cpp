#include "stdafx.h"
#include "utils.h"
#include "Jewels.h"
//=======================================================================================================================
// Item Title Color
//=======================================================================================================================
 void __declspec(naked) ItemTextColor()
{
_asm
{
cmp ax, 0x180F; 
je Gold;

cmp ax, ITEM(14,89); 
je Gold;

cmp ax, ITEM(14,90); 
je Gold;

cmp ax, ITEM(14,91); 
je Gold;

cmp ax, ITEM(14,92); 
je Gold;

cmp ax, ITEM(14,97); 
je Gold;

cmp ax, ITEM(14,98); 
je Gold;

cmp ax, ITEM(14,101); 
je Gold;

cmp ax, ITEM(14,102); 
je Gold;

cmp ax, ITEM(14,103); 
je Gold;

cmp ax, ITEM(14,104); 
je Gold;

cmp ax, ITEM(14,105); 
je Gold;

cmp ax, ITEM(14,106); 
je Gold;

cmp ax, ITEM(14,107); 
je Blue;

mov edx, 0x0061534F;
jmp edx;
//------------------------------------------------------------------------
// Colors
//------------------------------------------------------------------------
Blue:
MOV DWORD PTR SS:[ESP+0x1C],0x1
je Exit;

Red:
MOV DWORD PTR SS:[ESP+0x1C],0x2
je Exit;

Gold: 
MOV DWORD PTR SS:[ESP+0x1C],0x3
je Exit;

Excellent:
MOV DWORD PTR SS:[ESP+0x1C],0x4
je Exit;

Warning:
MOV DWORD PTR SS:[ESP+0x1C],0x5
je Exit;

Divine:
MOV DWORD PTR SS:[ESP+0x1C],0x6
je Exit;

WhiteBlue:
MOV DWORD PTR SS:[ESP+0x1C],0x7
je Exit;

WhiteYellow:
MOV DWORD PTR SS:[ESP+0x1C],0x8
je Exit;

Ancient:
MOV DWORD PTR SS:[ESP+0x1C],0x9
je Exit;

Exit:
mov edx, 0x00615446;
jmp edx;
}
}
//=======================================================================================================================
// Jewels Upgrade Allow
//=======================================================================================================================
__inline __declspec(naked) void JewelUpAllow()
{   
    _asm
    {
CMP SI,0x1C0E
JE Exit

CMP SI,0x1C10
JE Exit

CMP SI,0x1C2A
JE Exit

CMP SI,0x1C61 // Jewel Of justice
JE Exit

CMP SI,0x1C62 // Jewel Of Ancent
JE Exit

CMP SI,0x1C63 // Jewel Of Water
JE Exit

CMP SI,0x1C64 // Jewel Of Earth
JE Exit

CMP SI,0x1C65 // Jewel Of Wind
JE Exit

CMP SI,0x1C66 // Jewel Of Fire
JE Exit

CMP SI,0x1C67 // Jewel Of Elements
JE Exit

CMP SI,0x1C68 // Jewel Of Wind
JE Exit

CMP SI,0x1C69 // Jewel Of Fire
JE Exit

CMP SI,0x1C2B // Lower Refining Stone
JE Exit

CMP SI,0x1C2C // Higher Refining Stone
JE Exit


mov esi,0x006331B9
jmp esi

Exit:
mov esi,0x006331F3
jmp esi
 }
}
//=======================================================================================================================
// Jewels Insert Allow = Возможность добавлять в вещи опцию
//=======================================================================================================================
__inline __declspec(naked) void JewelInsertAllow()
{   
    _asm
    {
CMP DI,0x1C0D
JE Exit

CMP DI,0x1C2A
JE Exit

CMP DI,0x1C10
JE Exit

CMP DI,0x1C67 // Jewel Of Water
JE Exit

CMP DI,0x1C61 // Jewel Of justice
JE Exit

CMP DI,0x1C62 // Jewel Of Ancent
JE Exit

CMP DI,0x1C63 // Jewel Of Water
JE Exit

CMP DI,0x1C65 // Jewel Of Water
JE Exit

CMP DI,0x1C64 // Jewel Of Water
JE Exit

CMP DI,0x1C68 // Jewel Of Water
JE Exit

CMP DI,0x1C69 // Jewel Of Water
JE Exit

CMP DI,0x1C66 // Jewel Of Water
JE Exit

CMP DI,0x1C6B // Jewel Of Water
JE Exit

CMP DI,0x1C2B // Lower Refining Stone
JE Exit

CMP DI,0x1C2C // Higher Refining Stone
JE Exit

Exit:
mov esi,0x0064687A
jmp esi

mov esi,0x00646853
jmp esi
 }
}
//=======================================================================================================================
// Item Shine Adder
//=======================================================================================================================
__inline __declspec(naked) void Shine()
{
 _asm
    {
  CMP ECX, 0x1CA6 // [Original]
  JNE Item1
  mov edi, 0x0069776E
  JMP edi

Item1:
  CMP ECX, ITEM2(14,89)
  JNE Item2
  mov edi, 0x0069776E
  JMP edi

Item2:
  CMP ECX, ITEM2(14,90)
  JNE Item3
  mov edi, 0x0069776E
  JMP edi

Item3:
  CMP ECX, ITEM2(14,91)
  JNE Item4
  mov edi, 0x0069776E
  JMP edi

Item4://1
  CMP ECX, ITEM2(14,102)
  JNE Item5
  mov edi, 0x0069776E
  JMP edi

Item5:
  CMP ECX, ITEM2(14,103)
  JNE Item6
  mov edi, 0x0069776E
  JMP edi

Item6:
  CMP ECX, ITEM2(14,104)
  JNE Item7
  mov edi, 0x0069776E
  JMP edi

Item7:
  CMP ECX, ITEM2(14,105)
  JNE Item8
  mov edi, 0x0069776E
  JMP edi

Item8:
  CMP ECX, ITEM2(14,106)
  JNE Item9
  mov edi, 0x0069776E
  JMP edi

Item9:
  CMP ECX, ITEM2(14,107)
  JNE Item10
  mov edi, 0x0069776E
  JMP edi

Item10:
  CMP ECX, ITEM2(14,108)
  JNE Item11
  mov edi, 0x0069776E
  JMP edi

Item11:
  CMP ECX, ITEM2(14,109)
  JNE Item12
  mov edi, 0x0069776E
  JMP edi

Item12:
  CMP ECX, ITEM2(14,110)
  JNE Item13
  mov edi, 0x0069776E
  JMP edi

Item13:
  CMP ECX, ITEM2(14,101)
  JNE Item14
  mov edi, 0x0069776E
  JMP edi

Item14:
  CMP ECX, ITEM2(14,98)
  JNE Item15
  mov edi, 0x0069776E
  JMP edi

Item15:
  CMP ECX, ITEM2(14,97)
  JNE Exit
  mov edi, 0x0069776E
  JMP edi

Exit:
  mov edi, 0x0069784E
  JMP edi
// 0069784E = Медленая скорость блеска
// 00697917 = Средняя скорость блеска
// 006979DD = Быстрая скорость блеска
 }
}
//=======================================================================================================================
// Item Shine Adder 2
//=======================================================================================================================
__inline __declspec(naked) void Shine2()
{
 _asm
    {
 CMP EDX, 0x1CAF // Original
 JE CheckOK
 CMP EDX, ITEM2(14,89)
 JE CheckOK
 CMP EDX, ITEM2(14,90)
 JE CheckOK
 CMP EDX, ITEM2(14,91)
 JE CheckOK
 CMP EDX, ITEM2(14,92)
 JE CheckOK
  CMP EDX, ITEM2(14,102)
 JE CheckOK
  CMP EDX, ITEM2(14,103)
 JE CheckOK
  CMP EDX, ITEM2(14,104)
 JE CheckOK
  CMP EDX, ITEM2(14,105)
 JE CheckOK
  CMP EDX, ITEM2(14,106)
 JE CheckOK
  CMP EDX, ITEM2(14,107)
 JE CheckOK
  CMP EDX, ITEM2(14,101)
 JE CheckOK
   CMP EDX, ITEM2(14,98)
 JE CheckOK
    CMP EDX, ITEM2(14,101)
 JE CheckOK
    CMP EDX, ITEM2(14,97)
 JE CheckOK

 mov edi, 0x0068F2E3
 JMP edi

CheckOK:
  mov edi, 0x0068F269
  JMP edi
	}
}
//=======================================================================================================================
// Drop Item Title Color
//=======================================================================================================================
__inline __declspec(naked) void ItemDropText()
{   
    _asm
    {
CMP AX,0x1E88  // [Original]
JE Exit 

CMP AX,ITEM2(14,89)  // Bronze Coin
JE Exit

CMP AX,ITEM2(14,90)  // Silver Coin
JE Exit

CMP AX,ITEM2(14,91)  // Golden Coin
JE Exit

CMP AX,ITEM2(14,92)  // Platina Coin
JE Exit

CMP AX,ITEM2(14,98)  // Platina Coin
JE Exit

CMP AX,ITEM2(14,101)  // Platina Coin
JE Exit

CMP AX,ITEM2(14,102)  
JE Exit

CMP AX,ITEM2(14,103)  
JE Exit

CMP AX,ITEM2(14,104)  
JE Exit

CMP AX,ITEM2(14,105)  
JE Exit

CMP AX,ITEM2(14,106)  
JE Exit

CMP AX,ITEM2(14,107)  
JE Exit

CMP AX,ITEM2(14,97)  
JE Exit

mov esi, 0x0061E69E
JMP esi

Exit:
mov esi, 0x0061F873
JMP esi
//0061E8F7 = Dark Orange Normal
//0061F879 = Gold Normal
//0061F873 = Gold Bold
 }
}
//=======================================================================================================================
// Item Protect 1 [Drop Block]
//=======================================================================================================================
__inline __declspec(naked) void ItemDropBlock()
{   
    _asm
    {
CMP AX,0x1A35
JE Exit

CMP AX,ITEM(14,89) // Bronze Coin
JE Exit

CMP AX,ITEM(14,90) // Silver Coin
JE Exit

CMP AX,ITEM(14,91) // Golden Coin
JE Exit

CMP AX,ITEM(14,98) // Golden Coin
JE Exit

CMP AX,ITEM(14,92) // Platina Coin
JE Exit

CMP AX,ITEM(14,102) 
JE Exit

CMP AX,ITEM(14,103) 
JE Exit

CMP AX,ITEM(14,104) 
JE Exit

CMP AX,ITEM(14,105) 
JE Exit

CMP AX,ITEM(14,106) 
JE Exit

CMP AX,ITEM(14,97) 
JE Exit

CMP AX,ITEM(14,107) 
JE Exit

mov esi,0x006476EA
jmp esi

Exit:
mov esi,0x006476EE
jmp esi
 }
} 
//=======================================================================================================================
// Item Protect 2 [Drop & Sale Block]
//=======================================================================================================================
__inline __declspec(naked) void ItemDropBlock2()
{   
    _asm
    {
CMP AX,0x1A3B
JE Exit 

CMP AX,0x1C33
JE Exit 

mov esi,0x00647595
jmp esi

Exit:
mov esi,0x006475BC
jmp esi
 }
}
 //=======================================================================================================================
// Item Description Adder
//=======================================================================================================================
__inline __declspec(naked) void ItemText()
{
 _asm
    {
//------------------------------------------------------------------------
// Original 
//------------------------------------------------------------------------
  CMP WORD PTR SS:[EBP],0x180F 
  JNZ Item1
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH 0x078141DC 
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],EBX
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],EBX
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Bronze Coin 
//------------------------------------------------------------------------
Item1:
  CMP WORD PTR SS:[EBP],ITEM(14,89)
  JNZ Item2
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine2
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Silver Coin
//------------------------------------------------------------------------
Item2:
  CMP WORD PTR SS:[EBP],ITEM(14,90)
  JNZ Item3
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine3
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  JMP Exit
//------------------------------------------------------------------------
// Golden Coin
//------------------------------------------------------------------------
Item3:
  CMP WORD PTR SS:[EBP],ITEM(14,91)
  JNZ Item4
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine4
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Platina Coin
//------------------------------------------------------------------------
Item4:
  CMP WORD PTR SS:[EBP],ITEM(14,92)
  JNZ Item5
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine5
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Knight Art
//------------------------------------------------------------------------
Item5:
  CMP WORD PTR SS:[EBP],ITEM(14,101)
  JNZ Item6
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine6
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Jewel Of Everest
//------------------------------------------------------------------------
Item6:
  CMP WORD PTR SS:[EBP],ITEM(14,102)
  JNZ Item7
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine7
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// Jewel Of wings
//------------------------------------------------------------------------
Item7:
  CMP WORD PTR SS:[EBP],ITEM(14,103)
  JNZ Item8
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine8
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  JMP Exit
//------------------------------------------------------------------------
// 14.104
//------------------------------------------------------------------------
Item8:
  CMP WORD PTR SS:[EBP],ITEM(14,104)
  JNZ Item9
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine9
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//------------------------------------------------------------------------
// 14.105
//------------------------------------------------------------------------
Item9:
  CMP WORD PTR SS:[EBP],ITEM(14,105)
  JNZ Item10
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine10
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
// My TEST NEW ITEMS
//====================================================
//= Pack of Chaos
//====================================================
Item10:
  CMP WORD PTR SS:[EBP],ITEM(14,106)
  JNZ Item11
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine11
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= Pack of Life
//==================================================== 
Item11:
  CMP WORD PTR SS:[EBP],ITEM(14,107)
  JNZ Item12
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine12
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= Pack of Creation
//==================================================== 
Item12:
  CMP WORD PTR SS:[EBP],ITEM(14,108)
  JNZ Item13
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine13
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= Pack of Guardian
//==================================================== 
Item13:
  CMP WORD PTR SS:[EBP],ITEM(14,109)
  JNZ Item14
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine14
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= Pack of Harmony
//==================================================== 
Item14:
  CMP WORD PTR SS:[EBP],ITEM(14,110)
  JNZ Item15
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine15
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //====================================================
//= Jewel Of Ancent
//==================================================== 
Item15:
  CMP WORD PTR SS:[EBP],ITEM(14,98)
  JNZ Item16
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine16
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //====================================================
//= Jewel Of Justice
//==================================================== 
Item16:
  CMP WORD PTR SS:[EBP],ITEM(14,97)
  JNZ Item17
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine17
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= GEM
//==================================================== 
Item17:
  CMP WORD PTR SS:[EBP],ITEM(14,96)
  JNZ Item18
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextLine1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor9
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX

  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]
  PUSH TextLine18
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor1
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
//====================================================
//= Items New Options
//==================================================== 
//====================================================
//= Ignore Damage +5
//==================================================== 
Item18:
  CMP WORD PTR SS:[EBP],ITEM(0,32)
  JNZ Item19
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextOption1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor5
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //----------------------------------------------------
Item19:
  CMP WORD PTR SS:[EBP],ITEM(0,42)
  JNZ Item20
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextOption1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor5
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //----------------------------------------------------
Item20:
  CMP WORD PTR SS:[EBP],ITEM(2,25)
  JNZ Item21
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextOption1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor5
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //----------------------------------------------------
Item21:
  CMP WORD PTR SS:[EBP],ITEM(4,21)
  JNZ Item22
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextOption1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor5
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //----------------------------------------------------
 Item22:
  CMP WORD PTR SS:[EBP],ITEM(5,18)
  JNZ Exit
  LEA EAX,DWORD PTR DS:[EAX+EAX*0x4]

  PUSH TextOption1
  LEA EDX,DWORD PTR DS:[EAX+EAX*0x4]
  LEA EAX,DWORD PTR DS:[EDX*0x4+0x79FAD30]
  PUSH EAX
  mov esi, 0x00791CF0
  CALL esi
  MOV EAX,DWORD PTR DS:[0x7A2DA28]
  ADD ESP,0x8
  MOV DWORD PTR DS:[EAX*0x4+0x79FBECC],TextColor5
  MOV DWORD PTR DS:[EAX*0x4+0x7A2AEC8],TextNormal
  INC EAX
  MOV DWORD PTR DS:[0x7A2DA28],EAX
  JMP Exit
  //Exit
Exit:
  mov esi,0x0061927C
  jmp esi
 }
} 

void JewelsLoad()
{
// Item Text Color
SetNop(0x00615345,10);
HookOffset((DWORD)&ItemTextColor, 0x00615345, 0xE9);
// Item Info Text
SetNop(0x00619240,60);
HookOffset((DWORD)&ItemText, 0x00619240, 0xE9);
// Item Drop Text
SetNop(0x0061E694,9);
HookOffset((DWORD)&ItemDropText, 0x0061E694, 0xE9); 
// Item Drop Block 
SetNop(0x006476E4,6);
HookOffset((DWORD)&ItemDropBlock, 0x006476E4, 0xE9);
/*
 //Item Shine Adder
SetNop(0x00697762,12);
HookOffset((DWORD)&Shine, 0x00697762, 0xE9); 
//Item Shine Adder 2
SetNop(0x0068F261,7);
HookOffset((DWORD)&Shine2, 0x0068F261, 0xE9); 
*/

// Jewel On Item Allow
SetNop(0x006331B2,20);
HookOffset((DWORD)&JewelUpAllow, 0x006331B2, 0xE9);  

// Jewel On Item Insert
SetNop(0x0064684C,20);
HookOffset((DWORD)&JewelInsertAllow, 0x0064684C, 0xE9); 

} 