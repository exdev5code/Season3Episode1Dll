class Q_PGW
{
public:
	void Q_Load();
	void Q_Num();
	void Q_CreateStruct(int aIndex);
	void Q_NPC (int aIndex,int aNPC);
	void KilledMob(int aIndex);
	bool Presents(int aIndex,int Present,int Gifts);
	bool IsBadFileLine(char *FileLine, int &Flag);
	struct
	{
		int Mob;
		int Coun;
		int proc;
		int rew;
		int gift;
		char msg[100];
		char msg2[100];
	} Number[1000];
	int Count;
}; extern Q_PGW Qest_PGW;