//=======================================================================================================================
// Wings Opt 28
//=======================================================================================================================
__inline __declspec(naked) void WingsOpt()
{
 _asm
    {
 CMP ECX,0x1828
 JNE Item1
 mov edi, 0x005988D6
 JMP edi

 Item1:
 CMP ECX,0x1829
 JNE CheckOK
 mov edi, 0x005988D6
 JMP edi

CheckOK:
  mov edi, 0x0059898B
  JMP edi
	}
}