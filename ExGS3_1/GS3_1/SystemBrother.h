#include "USER.h"

#ifndef _SystemBrother
#define _SystemBrother

#define SystemBrother_DIR "..\\Settings\\SystemBrother.ini"

class cSystemBrother
{
public:
	int Enable;

	int NPC;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;

	int TaxGem;
	int TelGem;
	int OffGem;

	int AddExp;
	int AddDMG;
	int AddDEF;
	int AddIgn;
	int AddDD;


	void StartConfigs();
	void StartStruct(int aIndex);
	void NPCClick(int aIndex, int aNPC);
	void TimeTick(int aIndex);
	void AddedCharacter(int aIndex);
	void BrothCMD(int aIndex);
	void BrothTeleportCMD(int aIndex, char* msg);
	void BrothOffCharCMD(int aIndex);
	void BrotherInformation(int aIndex);
	bool CheckSimbol(char* String);

	bool OperationGem(int aIndex, int Gems);

	struct  
	{
		bool InBrotherd;
		char Brother[36];
		bool okey;
		int Off;

		//char Name[6][11];

	}User[OBJECT_MAX];

};
extern cSystemBrother SystemBrother;

#endif _SystemBrother