#pragma once

#include "stdafx.h"

#define oDataRecv			0x00509F6D
#define pDataRecv			((void(*)(BYTE,PBYTE,DWORD,DWORD,...)) 0x0050A070)
#define pActiveSocket		*(SOCKET*)(*(DWORD*)0x7D3B70 + 0x0C)
#define oXORFilterStart		0x004039E9

#define SET_NUMBERH(x)			( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)			( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)			( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)			( (WORD)((DWORD)(x) & 0xFFFF) )
#define SET_NUMBERHDW(x)		( (DWORD)((unsigned __int64)(x)>>(DWORD)32) )
#define SET_NUMBERLDW(x)		( (DWORD)((unsigned __int64)(x) & 0xFFFFFFFF) )
#define MAKE_NUMBERW(x,y)		( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERQW(x,y)		( (unsigned __int64)(((DWORD)((y)&0xFFFFFFFF)) | ((DWORD)((x)&0xFFFFFFFF)<<32))  )
#define MAKE_NUMBERDW(x,y)		( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
#define MAKEQWORD(a, b)			((__int64)(((DWORD)((__int64)(a) & 0xffffffff)) | ((__int64)((DWORD)((__int64)(b) & 0xffffffff))) << 32))  
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))   
#define HIDWORD(h)				((DWORD)(__int64(h) >> __int64(32)))

struct PBMSG_HEAD
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
};

struct PBMSG_HEAD2
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

struct PWMSG_HEAD
{
public:
	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};
	void setE( LPBYTE lpBuf, BYTE head, int size)
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

struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

class CProtocol
{
public:
	void Load();
	void DataSend(LPBYTE Data, int Size);
	static void	DataRecv(DWORD Case, LPBYTE Data, int Len, int aIndex);

	BYTE byXorFilter[32];

};
extern CProtocol g_Protocol;