#include "stdafx.h"
#include "Protocol.h"
//#include "Defines.h"

#if(ANTI_CHEAT_PLUS==TRUE)
// ----------------------------------------------------------------------------------------------
#define MAX_AH_DB				256
#define AH_TITLE				"Anti-Cheat"
#define DAMP_LOG_TEXT			"Hack: %s"
#define TITLE_WINDOW_TEXT		"Hack: %s"
#define CLASS_WINDOW_TEXT		"Hack: %s"
#define INJECT_TEXT				"Inject: %s"
#define PROCESS_ID_TEXT			"ProcessID: %s"
#define MULTI_WIN_TEXT			"Multi Windows Blockd"

#define DISK_DIR				"c:\\"
// ----------------------------------------------------------------------------------------------

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
	char Name[64];
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

#define MAX_DUMP_OFFSETS	3
#define MAX_DUMP_SIZE		32
#define MAX_PROCESS_DUMP	706

struct ANITHACK_PROCDUMP
{
	unsigned int m_aOffset;
	unsigned char m_aMemDump[MAX_DUMP_SIZE];
	char Name[100];
};
extern ANITHACK_PROCDUMP g_ProcessesDumps[MAX_PROCESS_DUMP];
// ----------------------------------------------------------------------------------------------

class AntiCheatPlus
{
public:
	void Init();
	void Load();
	void Splash();

	void GC_Recv(LPBYTE aRecv);
	void CG_Cheater(char* szText);
	void CG_HddSend();

	static DWORD WINAPI OtherTimer(LPVOID lpParam);
	static DWORD WINAPI DampTimer(LPVOID lpParam);
	static DWORD WINAPI TitleTimer(LPVOID lpParam);
	static DWORD WINAPI ClassTimer(LPVOID lpParam);
	static DWORD WINAPI InjectTimer(LPVOID lpParam);
	static DWORD WINAPI ProcessTimer(LPVOID lpParam);

	bool DumpCheck(HANDLE hProcess);
	void Dump();
	void TitleWindowCheck(LPCSTR WindowTitle);
	void ClassWindowCheck(LPCSTR WindowClasse);
	void InjectCheck(LPCSTR InjectHandle);
	void ProcessIDCheck(LPCSTR ProcName);
	void MultiWindowCheck();
	//static void _TC  EliteClickerCheck(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);

	void Write(LPSTR Text, ...);
	void Exit();
	
	static DWORD WINAPI End(LPVOID lpParam);

	bool ExitCheat;
	int ExitCount;
	// ----
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

	DWORD hdd_id;
};
extern AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------
#endif
