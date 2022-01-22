#include "StdAfx.h"
#include "USER.h"
#include "Defines.h"

void ExNewOptions (int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	if(gObj->pInventory[WEAPON_01].m_Type == ITEMGET(0,32) || gObj->pInventory[WEAPON_01].m_Type == ITEMGET(0,42) ||
	   gObj->pInventory[WEAPON_01].m_Type == ITEMGET(2,25) || gObj->pInventory[WEAPON_01].m_Type == ITEMGET(4,21) ||
	   gObj->pInventory[WEAPON_01].m_Type == ITEMGET(5,18))
	{
		gObj->SetOpIgnoreDefense += 5;
	}
	if(gObj->pInventory[WEAPON_02].m_Type == ITEMGET(0,32) || gObj->pInventory[WEAPON_02].m_Type == ITEMGET(0,42) ||
	   gObj->pInventory[WEAPON_02].m_Type == ITEMGET(2,25) || gObj->pInventory[WEAPON_02].m_Type == ITEMGET(4,21) ||
	   gObj->pInventory[WEAPON_02].m_Type == ITEMGET(5,18))
	{
		gObj->SetOpIgnoreDefense += 5;
	}
}