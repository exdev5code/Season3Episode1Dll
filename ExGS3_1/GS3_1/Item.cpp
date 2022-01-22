#include <Windows.h>
#include "Protocol.h"
#include <stdio.h>
#include "USER.h"
#include <time.h>
#include "Defines.h"

int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel)
{
	if(aIndex >= OBJECT_MAX)
		return 0;

	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER(aIndex);
	int Count = 0;
	for (int i = 0; i < 76; i++)
	{
		if (gObj->pInventory[i].m_Type == ItemID && gObj->pInventory[i].m_Level == ItemLevel)
			Count++;
	}
	return Count;
}
int gObjDeleteItemsCount(int gObjId, short Type, short Level, int Count)
{
	if(gObjId >= OBJECT_MAX)
		return 0;

	int count = 0;
	for(int i = 0; i < 76; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(gObjId);
		if(gObj->pInventory[i].m_Type == Type && gObj->pInventory[i].m_Level == Level)
		{
			gObjInventoryDeleteItem(gObjId, i);
			GCInventoryItemDeleteSend(gObjId, i, 1);
			count++;

			if(Count == count)
				break;
		}
	}
	return count;
}
