#include "StdAfx.h"
#include "AntiCheatPlus.h"
#include "ReadScript_ex.h"
//#include "GameMain.h"
#include "LogToFile.h"
//#include "logproc.h"
#include "user.h"
//#include "ConnectEx.h"
//#include "ExLicense.h"

#if(ANTI_CHEAT_PLUS==TRUE)
// ----------------------------------------------------------------------------------------------

CLogToFile g_AntiCheatLog("AntiCheat", "..\\AntiCheat\\LOG", TRUE);
// ----------------------------------------------------------------------------------------------

AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Init()
{
	ZeroMemory(&this->TitleName, sizeof(this->TitleName));
	ZeroMemory(&this->ClassName, sizeof(this->ClassName));
	ZeroMemory(&this->InjectName, sizeof(this->InjectName));
	ZeroMemory(&this->ProcessName, sizeof(this->ProcessName));
	ZeroMemory(&this->blockhdd, sizeof(this->blockhdd));

	this->TitleCount = 0;
	this->ClassCount = 0;
	this->InjectCount = 0;
	this->ProcessCount = 0;

	this->Enable = false;

	this->DumpActive = false;
	this->TitleActive = false;
	this->ClassActive = false;
	this->InjectActive = false;
	this->ProcessActive = false;
	this->EliteActive = true;
	this->MultiWindows = true;

	this->DumpTime = 10000;
	this->TitleTime = 10000;
	this->ClassTime = 10000;
	this->InjectTime = 10000;
	this->ProcessTime = 10000;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Load()
{
	this->Init();

	/*if(!g_ExLicense.user.AntiCheatPlus)
	{
		return;
	}*/

	for(int n=0; n < 5; n++)
	{
		*(BYTE*)(0x004CAE0F+n) = 0x90;
		*(BYTE*)(0x004CAF38+n) = 0x90;
	}
	
	this->ReadConfig("..\\AntiCheat\\AntiCheatMain.ini");
	this->Read(eAH::eTitleType, "..\\AntiCheat\\CheatBase\\TitleCheat.txt");
	this->Read(eAH::eClassType, "..\\AntiCheat\\CheatBase\\ClassCheat.txt");
	this->Read(eAH::eInjectType, "..\\AntiCheat\\CheatBase\\InjectCheat.txt");
	this->Read(eAH::eProcessType, "..\\AntiCheat\\CheatBase\\ProcessCheat.txt");

	this->ReadBlockHdd("..\\AntiCheat\\BlackList\\HDD_Data.txt");
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::ReadConfig(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);

	this->DumpActive = GetPrivateProfileInt("ExTeam", "DumpActive", 0, File);
	this->TitleActive = GetPrivateProfileInt("ExTeam", "TitleActive", 0, File);
	this->ClassActive = GetPrivateProfileInt("ExTeam", "ClassActive", 0, File);
	this->InjectActive = GetPrivateProfileInt("ExTeam", "InjectActive", 0, File);
	this->ProcessActive = GetPrivateProfileInt("ExTeam", "ProcessActive", 0, File);
	this->EliteActive  = GetPrivateProfileInt("ExTeam", "EliteActive", 0, File);
	this->MultiWindows = GetPrivateProfileInt("ExTeam", "MultiWindows", 1, File);

	this->DumpTime = GetPrivateProfileInt("ExTeam", "DumpTime", 10000, File);
	this->TitleTime = GetPrivateProfileInt("ExTeam", "TitleTime", 10000, File);
	this->ClassTime = GetPrivateProfileInt("ExTeam", "ClassTime", 10000, File);
	this->InjectTime = GetPrivateProfileInt("ExTeam", "InjectTime", 10000, File);
	this->ProcessTime = GetPrivateProfileInt("ExTeam", "ProcessTime", 10000, File);
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Read(int type, char* File)
{
	SMDFile = fopen(File, "r");
	if( SMDFile == NULL )
	{
		return;
	}
	
	while(true)
	{
		SMDToken Token = GetToken();
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		if(type==eTitleType)
		{
			if(this->TitleCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->TitleName[this->TitleCount],TokenString,sizeof(this->TitleName[this->ClassCount]));
			this->TitleCount++;
		}
		if(type==eClassType)
		{
			if(this->ClassCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ClassName[this->ClassCount],TokenString,sizeof(this->ClassName[this->ClassCount]));
			this->ClassCount++;
		}
		if(type==eInjectType)
		{
			if(this->InjectCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->InjectName[this->InjectCount],TokenString,sizeof(this->InjectName[this->InjectCount]));
			this->InjectCount++;
		}
		if(type==eProcessType)
		{
			if(this->ProcessCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ProcessName[this->ProcessCount],TokenString,sizeof(this->ProcessName[this->ProcessCount]));
			this->ProcessCount++;
		}
	}
	
	/*if(type==eTitleType)
	{
		LogAddText(2,"[Anti-Cheat] [Title Window] Loaded: %d", this->TitleCount);
	}
	if(type==eClassType)
	{
		LogAddText(2,"[Anti-Cheat] [Class Window] Loaded: %d", this->ClassCount);
	}
	if(type==eInjectType)
	{
		LogAddText(2,"[Anti-Cheat] [Inject Dll] Loaded: %d", this->InjectCount);
	}
	if(type==eProcessType)
	{
		LogAddText(2,"[Anti-Cheat] [Process] Loaded: %d", this->ProcessCount);
	}*/

	fclose(SMDFile);
	SMDFile = NULL;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::ReadBlockHdd(char* filename)
{
	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}

		BlockHDD_DATA List;

		List.hddid = dwTokenNumber;	//NeedFix

		this->blockhdd.push_back(List);
	}

	fclose(SMDFile);
	SMDFile = NULL;
}

void AntiCheatPlus::GC_Cheat(int UserIndex)
{
	if(!this->Enable)
	{
		return;
	}

	this->GC_Init(UserIndex);
	this->GC_Config(UserIndex);
	this->GC_Title(UserIndex);
	this->GC_Class(UserIndex);
	this->GC_Inject(UserIndex);
	this->GC_Process(UserIndex);
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CG_Cheater(PMST_CheaterUser*aRecv, int UserIndex)
{
	if (UserIndex < 0 || UserIndex > OBJECT_MAX-1 )
	{
		return;
	}

	LPOBJ lpUser = (OBJECTSTRUCT*)OBJECT_POINTER(UserIndex);//&gObj[UserIndex];

	if(aRecv->Result)
	{
		g_AntiCheatLog.Output("[%s][%s] ip[%s] hdd[%d] -> %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, ExUser[UserIndex].hdd_id, aRecv->CheatText);

		char szAntiCheat[100];
		sprintf(szAntiCheat, "..:: Anti-Cheat %s ::..", aRecv->CheatText);
		GCServerMsgStringSend(szAntiCheat, lpUser->m_Index, 0);

		//LogAddText(2,"[%s][%s][%s][%d] %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, ExUser[UserIndex].hdd_id, aRecv->CheatText);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CG_HddSend(CG_PMSG_HDDKEY* aRecv, int UserIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!aRecv)
	{
		return;
	}

	if (UserIndex < 0 || UserIndex > OBJECT_MAX-1 )
	{
		return;
	}

	LPOBJ lpUser = (OBJECTSTRUCT*)OBJECT_POINTER(UserIndex);//&gObj[UserIndex];

	//lpUser->hdd_id = aRecv->hdd_id;
	ExUser[UserIndex].hdd_id = aRecv->hdd_id;

	for(int i = 0; i < this->blockhdd.size(); i++)
	{
		BlockHDD_DATA & CheckList = this->blockhdd[i];
		if(CheckList.hddid != ExUser[UserIndex].hdd_id)
		{
			continue;
		}
		//GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		//GCServerMsgStringSend("PC Block List", lpUser->m_Index, 0);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Config(int UserIndex)
{
	PMSG_AH_CONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Config;

	pMsg.DumpActive = this->DumpActive;
	pMsg.TitleActive = this->TitleActive;
	pMsg.ClassActive = this->ClassActive;
	pMsg.InjectActive = this->InjectActive;
	pMsg.ProcessActive = this->ProcessActive;
	pMsg.EliteActive = this->EliteActive;
	pMsg.MultiWindows = this->MultiWindows;

	pMsg.DumpTime = this->DumpTime;
	pMsg.TitleTime = this->TitleTime;
	pMsg.ClassTime = this->ClassTime;
	pMsg.InjectTime = this->InjectTime;
	pMsg.ProcessTime = this->ProcessTime;

	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Init(int UserIndex)
{
	PMSG_AH_SUB pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Init;
	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Title(int UserIndex)
{
	for(int i = 0; i < this->TitleCount; i++)
	{	
		/*
		PMSG_CheatBaseOLD pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Title;
		//pMsg.len = strlen(this->TitleName[i]);
		memcpy(pMsg.Name,this->TitleName[i],sizeof(pMsg.Name));
		g_AntiCheatDBG.Output("[Anti-Cheat] [Title] %d %s", i, this->TitleName[i]);
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
		*/

		BYTE byBuffer[128];
		int datasize = 6;
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Title;
		pMsg.len = strlen(this->TitleName[i]);
		memcpy(&byBuffer[datasize],this->TitleName[i],pMsg.len);
		datasize += pMsg.len;
		DataSend(UserIndex,byBuffer,datasize);
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Class(int UserIndex)
{
	for(int i = 0; i < this->ClassCount; i++)
	{
		/*
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Class;
		memcpy(pMsg.Name,this->ClassName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
		*/

		BYTE byBuffer[128];
		int datasize = 6;
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Class;
		pMsg.len = strlen(this->ClassName[i]);
		memcpy(&byBuffer[datasize],this->ClassName[i],pMsg.len);
		datasize += pMsg.len;
		DataSend(UserIndex,byBuffer,datasize);
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Inject(int UserIndex)
{
	for(int i = 0; i < this->InjectCount; i++)
	{
		/*
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Inject;
		memcpy(pMsg.Name,this->InjectName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
		*/

		BYTE byBuffer[128];
		int datasize = 6;
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Inject;
		pMsg.len = strlen(this->InjectName[i]);
		memcpy(&byBuffer[datasize],this->InjectName[i],pMsg.len);
		datasize += pMsg.len;
		DataSend(UserIndex,byBuffer,datasize);
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Process(int UserIndex)
{
	for(int i = 0; i < this->ProcessCount; i++)
	{
		/*
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Process;
		memcpy(pMsg.Name,this->ProcessName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
		*/

		BYTE byBuffer[128];
		int datasize = 6;
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Process;
		pMsg.len = strlen(this->ProcessName[i]);
		memcpy(&byBuffer[datasize],this->ProcessName[i],pMsg.len);
		datasize += pMsg.len;
		DataSend(UserIndex,byBuffer,datasize);
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CheckMultiWindow(int UserIndex)
{
	if(!this->Enable || this->MultiWindows)
	{
		return;
	}

	if (UserIndex < 0 || UserIndex > OBJECT_MAX-1 )
	{
		return;
	}

	LPOBJ lpUser = (OBJECTSTRUCT*)OBJECT_POINTER(UserIndex);	//&gObj[UserIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}	

	for(int n=OBJECT_MIN;n<OBJECT_MAX;n++)
	{
		LPOBJ lpTempObj = (OBJECTSTRUCT*)OBJECT_POINTER(n);//&gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING)
		{
			continue;
		}	

		if(lpTempObj->Type != OBJ_USER)
		{
			continue;
		}

		if(UserIndex == n)
		{
			continue;
		}

		if(ExUser[UserIndex].hdd_id != ExUser[n].hdd_id)
		{
			continue;
		}

		GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		GCServerMsgStringSend("Multi Windows Blocked", lpUser->m_Index, 0);
#ifdef _RECONNECT_				
		g_ConnectEx.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------
#endif