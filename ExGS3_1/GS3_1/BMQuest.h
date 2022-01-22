#include "USER.h"
#include "Defines.h"
#define _MAX_BMQUEST 1000
#define _DIR_BMQUEST "..\\Settings\\BMQuest.ini"
#define _MAX_CLASS_BMQUEST 5

class cBMQuest
{
public:
	int Enable;
	int NPC;
	int NPC_Map;
	int	NPC_X;
	int	NPC_Y;

	int Reset;

	struct
	{
		int Mob;
		int Coun;
		int proc;
		int rew;
		int gift;
		char msg[100];
		char msg2[100];
	}Quest[_MAX_CLASS_BMQUEST][_MAX_BMQUEST];

	struct  
	{
		//Quest System
		int BMQuest_num;
		int BMQuest_kill;
		int BMQuest_start;
		//Character
		int BMDamageReflect;
		int BMDamage;
		int BMDefense;
		int BMCriticalDamage;
		int BMExcelentDamage;
		int BMLife;
	}Char[OBJECT_MAX];

	void StartConfig();
	void StartUP();
	void StartStruct(int aIndex);
	void AddedCharacter(int aIndex);
	void CharacterInformation(int aIndex);
	void NPCClick(int aIndex,int aNPC);
	void NPCdialogue(int aIndex,int aNPC);
	void MonsterKill(int aIndex, int aMob);
	void Presents(int aIndex, int Present, int Gifts);

	int Count[6];
};
extern cBMQuest BMQuest;