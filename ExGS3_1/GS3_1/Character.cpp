#include "StdAfx.h"
#include "Defines.h"
#include "USER.h"
#include "BMQuest.h"	//BMQuest
#include "NewOptions.h"


void MyCharacter (int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);
	//Log.GameLogs("[MyCharacter][Name]: %s",gObj->Name);
	j_gObjCalCharacter(aIndex);
	BMQuest.AddedCharacter(aIndex);	//BMQuest
	ExNewOptions (aIndex);
	
	//gObj->DamageReflect += BMQuest.Char[aIndex].BMDamageReflect;

	//gObj->m_AttackDamageMaxLeft += BMQuest.Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMinLeft += BMQuest.Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMaxRight += BMQuest.Char[aIndex].BMDamage;
	//gObj->m_AttackDamageMinRight += BMQuest.Char[aIndex].BMDamage;
	//gObj->m_MagicDamageMin += BMQuest.Char[aIndex].BMDamage;
	//gObj->m_MagicDamageMax += BMQuest.Char[aIndex].BMDamage;

	//gObj->m_Defense += BMQuest.Char[aIndex].BMDefense;
	//gObj->m_MagicDefense += BMQuest.Char[aIndex].BMDefense;

	//gObj->m_CriticalDamage += BMQuest.Char[aIndex].BMCriticalDamage;
	//gObj->m_ExcelentDamage += BMQuest.Char[aIndex].BMExcelentDamage;

	//gObj->MaxLife += BMQuest.Char[aIndex].BMLife;
}