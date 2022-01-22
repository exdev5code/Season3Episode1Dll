#define _MAX_DROP_ITEMS 1000
#define _ITEM_DROP_MANAGER_DIR "..\\Settings\\ItemDropManager.ini"

class cItemDropManager
{
public:
	void LoadFiles();
	void Process(int aIndex, int mIndex);
	void ClassProcessMob(int aIndex, int mIndex);
	void ClassProcessMap(int aIndex, int mIndex);
	struct 
	{
		int Mob;
		int Type;
		int Index;
		int Level;
		int Options;
		int Luck;
		int LuckDropRate;
		int Skill;
		int SkillDropRate;
		int Exe;
		int ExeDropRate;
		int Anc;
		int AncDropRate;
		int ItemDropRate;
	}ItemMob[_MAX_DROP_ITEMS];
	int CountMob;

	struct 
	{
		int Map;
		int Type;
		int Index;
		int Level;
		int Options;
		int Luck;
		int LuckDropRate;
		int Skill;
		int SkillDropRate;
		int Exe;
		int ExeDropRate;
		int Anc;
		int AncDropRate;
		int MobMinLvl;
		int MobMaxLvl;
		int ItemDropRate;
	}ItemMap[_MAX_DROP_ITEMS];
	int CountMap;
};
extern cItemDropManager ItemDropManager;