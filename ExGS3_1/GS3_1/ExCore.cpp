#include "StdAfx.h"
#include "USER.h"
#include "Message.h"
#include "CQuery.h"
#include "Quest_PGW.h"
#include "Buffer.h"
#include "NPCTeleport.h"
#include "AddFunctions.h"
#include "VipSystem.h"
#include "HappyHour.h"
#include "Experience.h"
#include "DropEvent.h"
#include "Process.h"
#include "LoraBattle.h"
#include "Exchanger.h"	//Exchanger
#include "BMQuest.h"	//BMQuest
#include "ItemDropManager.h"	//ItemDropManager
#include "SearchEvent.h"
#include "SystemBrother.h"


#include "OffExp.h"
#include "AntiCheatPlus.h"

Ex_User ExUser[OBJECT_MAX];

//==================================================================================================
// Привязка к железу
//==================================================================================================
bool ExCoreSecurity()
{
	return true;
	unsigned long SerialNumber;
	GetVolumeInformationA("c:\\",0,0,&SerialNumber,0,0,0,0); 
	switch(SerialNumber)
	{
		case 350207589:  return true; break;
		case 1625061858: return true; break;
		case 711123740:	 return true; break;
		case 3021482233: return true; break;
		default: return false;
	}
}
//==================================================================================================
// Connect Start
//==================================================================================================
void ConnectStart (int aIndex)
{
	PlayerConnect(aIndex);
	Qest_PGW.Q_CreateStruct(aIndex);
	ExUser[aIndex].ExTimeTick = 0;		//Сброс набраного времени при входе
	ExUser[aIndex].ClickNPC = 0;
	Vip.VipCreateStruct(aIndex);		//VipSystem
	Vip.ConnectGameVip(aIndex);			//VipSystem
	BMQuest.StartStruct(aIndex);		//BMQuest
	SystemBrother.StartStruct(aIndex);	//SystemBrother
#if(ANTI_CHEAT_PLUS==TRUE)
	g_AntiCheatPlus.GC_Cheat(aIndex);
	g_AntiCheatPlus.CheckMultiWindow(aIndex);
#endif
}
//==================================================================================================
// NPC Click
//==================================================================================================
void ExClickNPC (int aIndex, int aNPC)
{
	NewNPC(aIndex,aNPC);
	NPCTeleportStart(aIndex,aNPC);
	Qest_PGW.Q_NPC(aIndex,aNPC);
	Exchanger.NPCClick(aIndex,aNPC);	//Exchanger
	BMQuest.NPCClick(aIndex,aNPC);		//BMQuest
	SearchEvent.NPCClick(aIndex,aNPC);
	SystemBrother.NPCClick(aIndex,aNPC);	//SystemBrother
}
//==================================================================================================
// Поток времени Ивентов
//==================================================================================================
void ExEventTimeTick(void)
{
	while(true)
	{
		LoraBattle.TickTime();			//LoraBattle
		HappyHour.Timetick();			//HappyHour
		DropEvent.TickTime();			//DropEvent
		SearchEvent.StartNPC();
		
		Sleep(1000);					//1 sec		60000
	}
}
//==================================================================================================
// Поток времени Играков
//==================================================================================================
void ExPlayerTimeTick(void)
{
	while(true)
	{
		for(int i=OBJECT_MIN; i<OBJECT_MAX; i++)
		{
			//LogAddText(2,"TEST");
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);	
			if(gObj->Connected != PLAYER_PLAYING)
				continue;
			//LogAddText(2,"TEST 2");
			//ExPointsForOnline(i);
			//Vip.VipTimeTick(i);			//VipSystem
			////ExBattleRingProcess(i);	//ExBattleRingProcess
			//LoraBattle.Process(i);		//LoraBattle
			////MyCharacter (i);
			//SystemBrother.TimeTick(i);	//SystemBrother
			#if(DEV_OFFEXP)
			OffExp.MainFunction(i);
			#endif
		}
		Sleep(1000);					//1 sec		60000
	}
}
//==================================================================================================
// Загрузка файлов
//==================================================================================================
void ExCoreLoader()
{
	Vip.LoadConfigs();
	HappyHour.LoadFile();	
	HappyHour.LoadConfig();			//HappyHour
	DropEvent.LoadFile();			//DropEvent
	LoraBattle.LoadConfigs();		//LoraBattle
	Exchanger.StartConfig();		//Exchanger
	BMQuest.StartUP();				//BMQuest
	ItemDropManager.LoadFiles();	//ItemDropManager
	SearchEvent.LoadingEvent();
	SystemBrother.StartConfigs();	//SystemBrother
#if(DEV_OFFEXP)
	OffExp.LoadConfig();
#endif
#if(ANTI_CHEAT_PLUS==TRUE)
	g_AntiCheatPlus.Load();
#endif
}