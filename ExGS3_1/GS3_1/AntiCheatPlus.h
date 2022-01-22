#pragma once

#include "StdAfx.h"
//#include "..\\include\prodef.h"
#include "Protocol.h"
#if(ANTI_CHEAT_PLUS==TRUE)
// ----------------------------------------------------------------------------------------------

#define CLIENT_HDD_BLOCK	TRUE

#define MAX_AH_DB		256
// ----------------------------------------------------------------------------------------------

#define AH_PLUS_PATH

enum eAH
{
	eTitleType,
	eClassType,
	eInjectType,
	eProcessType,
};
// ----------------------------------------------------------------------------------------------

enum eProtocolAHSub
{
	eAH_Config,
	eAH_Init,
	eAH_Title,
	eAH_Class,
	eAH_Inject,
	eAH_Process,
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_SUB
{
	PBMSG_HEAD2 h;
	BYTE type;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_CONFIG
{
	PBMSG_HEAD2 h;
	BYTE type;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;
	bool MultiWindows;
	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;
};
// ----------------------------------------------------------------------------------------------
/*
struct PMSG_CheatBase
{
	PBMSG_HEAD2 h;
	BYTE type;
	char Name[16];
};
*/
// ----------------------------------------------------------------------------------------------

struct PMSG_CheatBase
{
	PBMSG_HEAD2 h;
	BYTE type;
	BYTE len;
};
// ----------------------------------------------------------------------------------------------

struct PMST_CheaterUser
{
	PBMSG_HEAD2 h;
	BYTE Result;
	char CheatText[64];
};
// ----------------------------------------------------------------------------------------------

struct CG_PMSG_HDDKEY
{
	PBMSG_HEAD2 h;
	DWORD hdd_id;
};
// ----------------------------------------------------------------------------------------------

struct BlockHDD_DATA
{
	BlockHDD_DATA()
	{
		this->hddid = 0;
	}
	DWORD hddid;
};
// ----------------------------------------------------------------------------------------------

class AntiCheatPlus
{
public:
	void Init();
	void Load();
	void ReadConfig(char* File);
	void Read(int type, char* File);
	void ReadBlockHdd(char* filename);

	void GC_Cheat(int UserIndex);
	void CG_Cheater(PMST_CheaterUser* aRecv, int UserIndex);
	void CG_HddSend(CG_PMSG_HDDKEY* aRecv, int UserIndex);

	void GC_Config(int UserIndex);
	void GC_Init(int UserIndex);
	void GC_Title(int UserIndex);
	void GC_Class(int UserIndex);
	void GC_Inject(int UserIndex);
	void GC_Process(int UserIndex);

	void CheckMultiWindow(int UserIndex);

	bool Enable;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;
	bool MultiWindows;

	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;

	char TitleName[MAX_AH_DB][64];
	char ClassName[MAX_AH_DB][64];
	char InjectName[MAX_AH_DB][64];
	char ProcessName[MAX_AH_DB][64];

	int TitleCount;
	int ClassCount;
	int InjectCount;
	int ProcessCount;

	std::vector<BlockHDD_DATA> blockhdd;
};
extern AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

#endif