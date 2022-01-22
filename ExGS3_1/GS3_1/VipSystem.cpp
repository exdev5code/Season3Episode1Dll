#include "StdAfx.h"
#include "USER.h"
#include "VipSystem.h"
#include "CQuery.h"
#include "AddFunctions.h"
#include "ExCore.h"
#include "Message.h"


cVipSystem Vip;

void cVipSystem::LoadConfigs()
{
	EnableVipSystem = GetPrivateProfileInt("VipSystem","Enable",0,VIP_DIR);
	PlusExp = GetPrivateProfileInt("VipSystem","PlusExp",0,VIP_DIR);
	PlusDrop = GetPrivateProfileInt("VipSystem","PlusDrop",0,VIP_DIR);
	ShowConnect = GetPrivateProfileInt("VipSystem","ShowConnect",0,VIP_DIR);
}

void cVipSystem::VipCreateStruct(int aIndex)
{
	if(!EnableVipSystem)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	


	ExUser[aIndex].VipStatus = exQueryReturnInt("SELECT VipStatus FROM Character WHERE Name='%s'", gObj->Name);
	//-------------------------------------------------------------------------
	//MySQL.Execute("SELECT VipTimeTick FROM Character WHERE Name='%s'",gObj->Name);
	//ExUser[aIndex].VipTimeTick = time(NULL);	//VipTimeTick
	//-------------------------------------------------------------------------
	if(ExUser[aIndex].VipStatus)
	{
		ExUser[aIndex].VipTimeEnd = exQueryReturnInt("SELECT VipTimeEnd FROM Character WHERE Name='%s'", gObj->Name);
	}
	//-------------------------------------------------------------------------

}

void cVipSystem::BuyVip(int aIndex,char* msg)
{
	if(!EnableVipSystem)
		return;

	if (strlen(msg) > 10) return;
	
	unsigned int VipPoint = 0;
	sscanf_s(msg,"%d",&VipPoint);

	if(ExUser[aIndex].VipStatus)
		return;

	if(VipPoint > 0 && VipPoint <= 1000000)
	{
		OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		int sqlVipPoints = exQueryReturnInt("SELECT VipPoints FROM Character WHERE Name='%s'", gObj->Name);

		if(VipPoint > sqlVipPoints)
			return;

		int Times = time(NULL);

		exQueryUpdate("UPDATE Character SET VipPoints = VipPoints - %d WHERE Name='%s'",VipPoint,gObj->Name);

		ExUser[aIndex].VipStatus = 1;
		exQueryUpdate("UPDATE Character SET VipStatus = 1 WHERE Name='%s'", gObj->Name);

		//ExUser[aIndex].VipTimeTick = Times;
		//MySQL.Execute("UPDATE Character SET VipTimeTick = %d WHERE Name='%s'",Times,gObj->Name);

		ExUser[aIndex].VipTimeEnd = (VipPoint*60)+Times;
		exQueryUpdate("UPDATE Character SET VipTimeEnd = %d WHERE Name='%s'", ExUser[aIndex].VipTimeEnd, gObj->Name);

		MsgNormal(aIndex,"[VIP] Buy %d Min",VipPoint);


	}
}

void cVipSystem::VipTimeTick(int aIndex)
{
	if(!ExUser[aIndex].VipStatus)
		return;
	int Times = time(NULL);
	if(Times >= ExUser[aIndex].VipTimeEnd)
	{
		OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

		ExUser[aIndex].VipStatus = 0;
		exQueryUpdate("UPDATE Character SET VipStatus = 0 WHERE Name='%s'",gObj->Name);

		//ExUser[aIndex].VipTimeTick = 0;
		//MySQL.Execute("UPDATE Character SET VipTimeTick = 0 WHERE Name='%s'",gObj->Name);

		//ExUser[aIndex].VipTimeEnd = 0;
		//MySQL.Execute("UPDATE Character SET VipTimeEnd = 0 WHERE Name='%s'",gObj->Name);

		MsgNormal(aIndex,"[VIP] Time is over Vip");


	}
}

void cVipSystem::ConnectGameVip(int aIndex)
{
	if(!EnableVipSystem)
		return;
	if(!ExUser[aIndex].VipStatus)
		return;
	if(!ShowConnect)
		return;
	int Times = time(NULL);

	

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	int Minutes;

	Minutes = ExUser[aIndex].VipTimeEnd - Times;
	Minutes = Minutes / 60;

	if(Minutes <= 0 )
	{
		ExUser[aIndex].VipStatus = 0;
		exQueryUpdate("UPDATE Character SET VipStatus = 0 WHERE Name='%s'", gObj->Name);

		return;
	}

	MsgNormal(aIndex,"[VIP] %d Vip minutes",Minutes);
}

void cVipSystem::SellVipPoint(int aIndex,char* msg)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	if(gObj->Authority == 8 || gObj->Authority == 32)
	{
		if (strlen(msg) > 10) return;
		int isFind = 0;
		char Name[11];
		int SellVip = 0;
		sscanf(msg,"%s %d",&Name,&SellVip);
		if(SellVip > 0 && SellVip < 1000000)
		{
			for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
			{
				OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
				if(sObj->Connected != PLAYER_PLAYING)
					continue;
				
				if(!strcmp(Name,sObj->Name))
				{
					exQueryUpdate("UPDATE Character SET VipPoints = VipPoints + %d WHERE Name='%s'", SellVip, sObj->Name);
					isFind = 1;
					break;
				}
			}
			if(isFind)
				MsgNormal(aIndex,"[VIP]: Sell VipPoint %d Nick: '%s'.",SellVip,Name);
			else
				MsgNormal(aIndex,"[VIP] Player '%s' not found.",Name);
		}
	}
}