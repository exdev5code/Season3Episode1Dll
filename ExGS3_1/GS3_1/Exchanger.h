#define EXCHANGER_DIR "..\\Settings\\NPCExchanger.ini"

class cExExchanger
{
public:
	int Enable;

	int ExchangerItem;
	int ExchangerGem;
	int MyCreds;

	int NPCNum;
	int NPCMap;
	int NPCX;
	int NPCY;

	int ExItemType;
	int ExItemIndex;
	int ExItemLevel;
	int ExCount;

	int ExGEM;

	char cr_table[50];
	char cr_column[50];
	char cr_acc[50];

	int ExCr;
	int ItemCount;

	void StartConfig();
	void NPCClick(int aIndex, int aNPC);
	void NPCExchanger(int aIndex);

	struct
	{
		int Type;
		int Index;
		int Level;
		int Skill;
		int Luck;
		int Opt;
		int Exl;
		int Anc;
	}Item[256];

	int Count;

};
extern cExExchanger Exchanger;