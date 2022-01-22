#pragma once


#include "StdAfx.h"
/*#include <Windows.h>
#include <Time.h>
#include <atltime.h>*/

#define SET_NUMBERH(x)		( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)		( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)		( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)		( (WORD)((DWORD)(x) & 0xFFFF) )
#define MAKE_NUMBERW(x,y)	( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERDW(x,y)	( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
#define MAKE_NUMBERQW(x,y)	( (unsigned __int64)(((DWORD)((y)&0xFFFFFFFF)) | ((DWORD)((x)&0xFFFFFFFF)<<32))  )
#define MAKEQWORD(a, b)     ((__int64)(((DWORD)((__int64)(a) & 0xffffffff)) | ((__int64)((DWORD)((__int64)(b) & 0xffffffff))) << 32))  
#define LODWORD(l)          ((DWORD)(__int64(l) & __int64(0xffffffff)))   
#define HIDWORD(l)          ((DWORD)(__int64(l) >> __int64(32)))   

struct PBMSG_HEAD
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 18
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 22

	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 25
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 29

	BYTE c; //0
	BYTE size; //1
	BYTE headcode; //2
};

struct PBMSG_HEAD2	// Packet - Byte Type
{

public:

	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

struct PWMSG_HEAD	// Packet - Word Type
{
public:

	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	void setE( LPBYTE lpBuf, BYTE head, int size)	// line : 49
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};

struct PWMSG_HEAD2
{

public:

	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
	BYTE subcode;
};

struct PMSG_DEFAULT
{
	PBMSG_HEAD h;
};


struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PMSG_C1C3HEAD_Q {
	unsigned char head;
	unsigned char len;
	unsigned char type;
};

struct PMSG_QUEST_DIALOG{
	PMSG_C1C3HEAD_Q	head;
	unsigned char	quest_id;
	unsigned char	dialog_id;
	unsigned char	dialog_empty;
};
/*
struct PBMSG_HEAD2	// Packet - Byte Type
{

public:
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};
*/

struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};

bool ProtocolCore(BYTE protoNum,LPBYTE aRecv,DWORD aLen,DWORD aIndex,DWORD Encrypt,int Serial);
bool ProtocolCoreSend(int aIndex,unsigned char* aSend, int aLen);
void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset);

enum CREATURES 
{
    //---------------------------

	DEATHVIM_KNIGHT	        = 63,
	PHOENIX			        = 77,
	GOLDEN_ARCHER	        = 236,
	HELL_MAINE		        = 309,
    ELITESOLDIER_LEO        = 371,
	DRINKSELLER_HILLARY     = 376,
	DRINKSELLER_LINDSAY     = 377,
	STONE_STATUE	        = 380,
	BLUE_STORAGE	        = 383,
	RED_STORAGE		        = 384,
	MUMMY			        = 385,
	PRIEST_DEVIN	        = 406,
	WAREWOLF		        = 407,
	GATEKEEPER		        = 408,
	BALRAM_H		        = 409,
	DEATHSPIRIT_H	        = 410,
	SORAM_H			        = 411,
	DARK_ELF_H		        = 412,

	LIMA			        = 103,
	SANTA_GIRL              = 374,
	FIREWORKS_GIRL          = 379,
	ILLUSION_GUARD          = 382,
	SILVIA                  = 415,
	LEAH                    = 416,
	MARSEILLE               = 371,

    //---------------------------
};

