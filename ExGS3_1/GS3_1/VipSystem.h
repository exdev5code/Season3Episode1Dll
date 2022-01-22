#define VIP_DIR "..\\Settings\\VipSystem.ini"

#ifndef _VIPSYSTEM_H
#define _VIPSYSTEM_H

class cVipSystem
{
public:
	int EnableVipSystem;
	int PlusExp;
	int PlusDrop;
	int ShowConnect;

	void LoadConfigs();
	void VipCreateStruct(int aIndex);
	void BuyVip(int aIndex,char* msg);
	void VipTimeTick(int aIndex);
	void ConnectGameVip(int aIndex);
	void SellVipPoint(int aIndex,char* msg);
};
extern cVipSystem Vip;

#endif _VIPSYSTEM_H