#include "StdAfx.h"

#if(DEV_OFFEXP)

#define OFF_EXP_DIR "..\\ExTeam\\OffExp.ini"

#define MAX_VIEWPORT_MONSTER 75
#define MAX_USER_IN_PARTY	 5

#define UseSkill				((int(*) (int a1, CMagicInf *a2, char a3, char a4, char a5, char a6, int a7))0x4010AF)
#define gObjAttack				((signed int(__cdecl*) (LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf* lpMagic, int magicsend, BYTE MSBFlag, int AttackDamage))0x40691A)
#define CObjUseSkillUseSkill	((int(__thiscall*) (void *This, int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex))0x4010AF)
#define MapClassGetAttr			((BYTE(__thiscall*) (int This, int a1, int a2))0x403E18)
#define gObjGetMagicSearch		((CMagicInf*(__cdecl*)(LPOBJ lpObj, int skillnumber))0x40524F)
#define GCManaSend				((int(__cdecl*)(int aIndex, __int16 Mana, BYTE Ipos, BYTE flag,  __int16 BP))0x4031C5)
#define gObjSearchItemMinus		((int(__cdecl*) (LPOBJ lpObj, int pos, int m_dur))0x406A0A)
#define CObjUseSkillUseSkill2	((int(__thiscall*) (void *This, int aIndex, int aTargetIndex, CMagicInf * lpMagic))0x542020)

class COffExp
{
public:
	void LoadConfig();
	void OffExpStart(int aIndex);
	void MainFunction(int aIndex);
	void DarkKnightOff(LPOBJ lpObj);
	void DarkWizardOff(LPOBJ lpObj);
	void FairyElfOff(LPOBJ lpObj);
	void MagicGladiatorOff(LPOBJ lpObj);
	void DarkLordOff(LPOBJ lpObj);
	void SummonerOff(LPOBJ lpObj);
	void UseMana(int aIndex);
	int SearchTarget(LPOBJ lpObj);
	bool CheckTerrain(LPOBJ lpObj);

	BOOL IsItem(LPOBJ lpObj, int pos);
	void ItemClear(LPOBJ lpObj, int pos);
	int GetManaItemPos(int aIndex);

	int Enable;
	int KickFallen;
	int EnableTime;
	int TimeEnd;
};

extern COffExp OffExp;

#endif