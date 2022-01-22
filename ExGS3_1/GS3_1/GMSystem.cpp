#include "USER.h"
#include "Defines.h"
#include "Message.h"
#include "StdAfx.h"
#include "AddFunctions.h"
#include "CQuery.h"

int TraceGM = GetPrivateProfileInt("GameMaster","trace",0,"..\\Settings\\Command.ini");
int PkSetGM = GetPrivateProfileInt("GameMaster","pkset",0,"..\\Settings\\Command.ini");
int MoveGM = GetPrivateProfileInt("GameMaster","teleport",0,"..\\Settings\\Command.ini");
//Телепортация к персонажу
void ChatTrace(int aIndex,char* msg)
{	
	if(!TraceGM)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->Authority == 8 || gObj->Authority == 32)
	{	
		int isFind = 0;
		char Name[11];
		sscanf(msg,"%s",&Name);
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(strcmp(Name,sObj->Name) == 0)
			{
				gObjTeleport(aIndex,sObj->MapNumber,sObj->X,sObj->Y);
				isFind = 1;
				break;
			}
		}
		if(isFind)
			MsgNormal(aIndex,"[GMTrace] You move to player '%s'",Name);
		else 
			MsgNormal(aIndex,"[GMTrace] Player '%s' not found.",Name);
	}
}
//Присваивает чару уровень пк
void ChatPkSet(int aIndex,char* msg)
{
	if(!PkSetGM)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->Authority == 8 || gObj->Authority == 32)
	{
		int isFind = 0;
		char Name[11];
		int PkStatus = 0;
		sscanf(msg,"%s %d",&Name,&PkStatus);
		//sscanf_s(msg," %s %d",&Name,&PkStatus);
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(strcmp(Name,sObj->Name) == 0)
			{
				if(PkStatus>=0 && PkStatus<=1000)
				{
					sObj->m_PK_Level = PkStatus;
					GCPkLevelSend(i, PkStatus);
					isFind = 1;
					break;
				}
				else
					break;
			}
		}
		if(isFind)
			MsgNormal(aIndex,"[GM_PkSet] Nick: '%s' PkLevel: '%d' .",Name,PkStatus);
		else 
			MsgNormal(aIndex,"[GM_PkSet] Player '%s' not found.",Name);
	}
}
//Функция для телепорта персонажа
void ChatMove(int aIndex,char* msg)
{
	if(!MoveGM)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->Authority == 8 || gObj->Authority == 32)
	{
		int isFind = 0;
		char Name[100];
		int Map=0,X=123,Y=123;
		sscanf(msg,"%s %d %d %d",&Name,&Map,&X,&Y);
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(strcmp(Name,sObj->Name) == 0)
			{
				if(Map>=0 && Map<=50 && X>=0 && X<=255 && Y>=0 && Y<=255)
				{
					gObjTeleport(i,Map,X,Y);
					isFind = 1;
					break;
				}
				else
				{
					isFind = 2;
					break;
				}
			}
		}
		if(isFind == 1)
			MsgNormal(aIndex,"[GM_Move][%s]Map:%d X:%d Y:%d",Name,Map,X,Y);
		else if(isFind == 2)
			MsgNormal(aIndex,"[GM_Move]Max Map 50 X 255 Y 255");
		else 
			MsgNormal(aIndex,"[GM_Move] Player '%s' not found.",Name);
	}
}

//void CharacterBan (int aIndex,char* msg)
//{
//	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
//	if(gObj->Authority == 8 || gObj->Authority == 32)
//	{	
//		int isFind = 0;
//		char Name[11];
//		int Time;
//		sscanf(msg,"%s %d",&Name,&Time);
//		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
//		{
//			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
//			if(strcmp(Name,sObj->Name) == 0)
//			{
//				if(!MySQL.Execute("UPDATE Character SET BanTime = %d WHERE Name='%s'",Time,UserName))
//				{
//					ErrorConnectDataBase(aIndex);
//					return;
//				}
//				sObj->Authority = 1;
//				EliteClickerCick(i);
//				//gObjTeleport(aIndex,sObj->MapNumber,sObj->X,sObj->Y);
//
//				isFind = 1;
//				break;
//			}
//		}
//		if(isFind)
//			MsgNormal(aIndex,"[Ban] You Ban to player '%s'",Name);
//		else 
//			MsgNormal(aIndex,"[Ban] Player Ban '%s' not found.",Name);
//	}
//}

//void CharacterBan()
//{
//	MySQL.Execute("SELECT Resets FROM Character WHERE Name='%s'",UserName);
//}

void MinusGemForADM (int aIndex,char* msg)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->Authority == 8 || gObj->Authority == 32)
	{	
		if (strlen(msg) > 10) return;
		int isFind = 0;
		char Name[11];
		int minusgem;
		sscanf(msg,"%s %d",&Name,&minusgem);
		for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
		{
			OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(strcmp(Name,sObj->Name) == 0)
			{
				exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint - %d WHERE memb___id='%s'", minusgem, sObj->AccountID);

				//sObj->Authority = 1;
				//EliteClickerCick(i);
				//gObjTeleport(aIndex,sObj->MapNumber,sObj->X,sObj->Y);

				MsgNormal(aIndex,"[MinusGem] You Ban to player '%s'",Name);
				return;
			}
		}
		MsgNormal(aIndex,"[MinusGem] Player Ban '%s' not found.",Name);
	}
}