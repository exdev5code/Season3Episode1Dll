#include "StdAfx.h"
#include "Exchanger.h"
#include "Utilits.h"
#include "USER.h"
#include "Message.h"
#include "CQuery.h"


cExExchanger Exchanger;

void cExExchanger::StartConfig()
{
	Enable = GetPrivateProfileInt("Common","Enable",1,EXCHANGER_DIR);

	ExchangerItem = GetPrivateProfileInt("Common","ExchangerItem",1,EXCHANGER_DIR);
	ExchangerGem = GetPrivateProfileInt("Common","ExchangerGem",1,EXCHANGER_DIR);
	MyCreds	= GetPrivateProfileInt("Common","MyCreds",1,EXCHANGER_DIR);

	NPCNum = GetPrivateProfileInt("Common","NPCNum",371,EXCHANGER_DIR);
	NPCMap = GetPrivateProfileInt("Common","NPCMap",0,EXCHANGER_DIR);
	NPCX = GetPrivateProfileInt("Common","NPCX",123,EXCHANGER_DIR);
	NPCY = GetPrivateProfileInt("Common","NPCY",123,EXCHANGER_DIR);

	ExItemType = GetPrivateProfileInt("Common","ExItemType",14,EXCHANGER_DIR);
	ExItemIndex = GetPrivateProfileInt("Common","ExItemIndex",21,EXCHANGER_DIR);
	ExItemLevel = GetPrivateProfileInt("Common","ExItemLevel",1,EXCHANGER_DIR);
	ExCount = GetPrivateProfileInt("Common","ExCount",1,EXCHANGER_DIR);

	ExGEM = GetPrivateProfileInt("Common","ExGEM",1,EXCHANGER_DIR);

	ExCr = GetPrivateProfileInt("Common","ExCr",1,EXCHANGER_DIR);

	GetPrivateProfileStringA("Common", "cr_table","MEMB_INFO",cr_table,sizeof(cr_table),EXCHANGER_DIR);
	GetPrivateProfileStringA("Common", "cr_column","credits",cr_column,sizeof(cr_column),EXCHANGER_DIR);
	GetPrivateProfileStringA("Common", "cr_acc","memb___id",cr_acc,sizeof(cr_acc),EXCHANGER_DIR);
	//GetPrivateProfileStringA("Reward","VotedTable3","test",VotedTable3,sizeof(VotedTable3),ConfigsDir);

	ItemCount = GetPrivateProfileInt("Common","ItemCount",1,EXCHANGER_DIR);

	for(int i(0);i<256;i++)
	{
		Item[i].Type  = 0;
		Item[i].Index = 0;
		Item[i].Level = 0;
		Item[i].Skill = 0;
		Item[i].Luck  = 0;
		Item[i].Opt   = 0;
		Item[i].Exl	  = 0;
		Item[i].Anc   = 0;
	}

	FILE *file = fopen(EXCHANGER_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\NPCExchanger.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;
	
	Count = 0;

	while(!feof(file)) // Check line in file
	{
		fgets(Buff,256,file);// function read string
		if(IsBadFileLine(Buff, Flag)) //Check Bad File line
			continue;
		if(Flag == 1)
		{
			int n[10];
			sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
			
			Item[Count].Type  = n[0];
			Item[Count].Index = n[1];
			Item[Count].Level = n[2];
			Item[Count].Skill = n[3];
			Item[Count].Luck  = n[4];
			Item[Count].Opt   = n[5];
			Item[Count].Exl	 = n[6];
			Item[Count].Anc   = n[7];
			Count++;
		}
	}
	fclose(file);
}

void cExExchanger::NPCClick(int aIndex, int aNPC)
{
	if(!Enable)
		return;
	if(time(NULL) >= ExUser[aIndex].ClickNPC)
	{
		OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);
		if ((gObjNPC->Class == NPCNum) && (gObjNPC->MapNumber == NPCMap) && (gObjNPC->X == NPCX) && (gObjNPC->Y == NPCY)) 
			NPCExchanger(aIndex);
	}
}

void cExExchanger::NPCExchanger(int aIndex)
{
	if(!Enable)
		return;
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);



	if(gObjGetItemCountInInventory(aIndex,ITEMGET(ExItemType,ExItemIndex),ExItemLevel) < ExCount)
	{
		MsgNormal(aIndex,"[Exchanger] Need %d Items",ExCount);
		return;
	}

	gObjDeleteItemsCount(aIndex,ITEMGET(ExItemType,ExItemIndex),ExItemLevel,ExCount);

	if(ExchangerItem)
	{
		for(int i=0;i<ItemCount;i++)
		{
			int num = rand()%Count;
			int Exe = 0;
			int Anc = 0;
			int Type = ITEMGET(Item[num].Type,Item[num].Index);
			if ( Item[num].Exl > 0 )
				Exe = GenExcOpt(Item[num].Exl);

			if ( Item[num].Anc == 5 || Item[num].Anc == 10 )
				Anc = Item[num].Anc;

			ItemSerialCreateSend(aIndex,gObj->MapNumber,gObj->X,gObj->Y,Type,Item[num].Level,0,Item[num].Skill,Item[num].Luck,Item[num].Opt,aIndex,Exe,Anc);
		}	
	}

	if(ExchangerGem)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", ExGEM, gObj->AccountID);
		MsgNormal(aIndex,"[Exchanger] + %d GEM",ExGEM);

	}

	if(MyCreds)
	{
		exQueryUpdate("UPDATE %s SET %s = %s + %d WHERE %s='%s'", cr_table, cr_column, cr_column, ExGEM, cr_acc, gObj->AccountID);
		MsgNormal(aIndex,"[Exchanger] + %d Cred",ExCr);
	}
	ExUser[aIndex].ClickNPC = (time(NULL)+5);
}