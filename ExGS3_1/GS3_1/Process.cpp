#include "USER.h"
#include "StdAfx.h"
#include "Defines.h"

//void ExBattleRingProcess (int aIndex)
//{
//	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
//	int LoraRingPvP = GetPrivateProfileInt("Common","LoraRingPK",0,"..\\Settings\\PvPSystem.ini");
//	if(LoraRingPvP==0 && gObj->MapNumber!=0)
//		return;
//	//Ëîðà Ðèíã ÏâÏ
//	if(gObj->X >= 137 && gObj->X <= 144 && gObj->Y >= 124 && gObj->Y <= 131)
//	{
//		if(ExUser[aIndex].BattleRing == true)
//			return;
//		
//		GCPkLevelSend(aIndex, 6);
//		ExUser[aIndex].BattleRing = true;
//	}
//	else 
//	{
//		if(ExUser[aIndex].BattleRing == false)
//			return;
//
//		GCPkLevelSend(aIndex, gObj->m_PK_Level);
//		ExUser[aIndex].BattleRing = false;
//
//	}
//}