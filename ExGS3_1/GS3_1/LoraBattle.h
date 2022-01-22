#include "USER.h"
#include "StdAfx.h"
#include "Defines.h"

#define LORABATTLE_DIR "..\\Settings\\LoraBattleEvent.ini"

class cLoraBattle
{
public:
	int Enable;
	int Start;

	int RewardGem;
	int RewardItem;

	int GEM;
	int ITEM;
	int ITEM_LEVEL;

	int Fallen_DROP;
	int Fallen_ITEM;
	int Fallen_ITEM_LEVEL;

	int KillSocer[OBJECT_MAX];

	bool BattleRing[OBJECT_MAX];

	int m_PK_Level[OBJECT_MAX];

	int MaxSocer;
	int MaxIndex;

	char MSG[256];

	void LoadConfigs();
	void StartEvent();
	void EndEvent();
	void TickTime();
	void Process(int aIndex);
	void BattleKillSocer(int aIndex,int aIndex2);
	void Reward(int aIndex);
	void Start1min();

	struct
	{
		int StrHour;
		int StrMin;
		int Hour;
		int Min;
		int EndHour;
		int EndMin;
	}Time[128];

	int Count;
	int EndCount;
};
extern cLoraBattle LoraBattle;