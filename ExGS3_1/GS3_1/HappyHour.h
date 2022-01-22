#define HH_DIR			"..\\Settings\\HappyHour.ini"
#define MAX_HH_STRUCT	128

class cHappyHour
{
public:
	int Enable;
	int PlusExp;
	int PlusDrop;
	bool StartHappyHour;

	void LoadConfig();
	void LoadFile();
	void Timetick();

	struct  
	{
		int Hour;
		int Min;

		int EndHour;
		int EndMin;
	}HappyStruct[128];

	int Count;
	
};extern cHappyHour HappyHour;