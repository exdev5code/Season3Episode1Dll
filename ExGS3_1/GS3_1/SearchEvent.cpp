#include "StdAfx.h"
#include "USER.h"
#include "Defines.h"
#include "SearchEvent.h"
#include "Utilits.h"
#include "Message.h"
#include "CQuery.h"
#include "AddFunctions.h"

cSearchEvent SearchEvent;

void cSearchEvent::LoadingEvent()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",1,SEARCH_EVENT_DIR);
	this->NPC = GetPrivateProfileInt("Common","NPC",377,SEARCH_EVENT_DIR);
	this->PresGem = GetPrivateProfileInt("Common","PresGem",10,SEARCH_EVENT_DIR);
	this->Map = GetPrivateProfileInt("Common","Map",0,SEARCH_EVENT_DIR);
	this->Time = GetPrivateProfileInt("Common","Time",60,SEARCH_EVENT_DIR);
	this->ItemCount = GetPrivateProfileInt("Common","ItemCount",5,SEARCH_EVENT_DIR);

	this->Start = false;

	for(int i=0;i<10;i++)
	{
		this->TickTime[i].Hour = 0;
		this->TickTime[i].Min = 0;
	}

	for(int i(0);i < 255; i++)
	{
		this->Item[i].Index = 0;
		this->Item[i].Type  = 0;
		this->Item[i].Level = 0;
		this->Item[i].Skill = 0;
		this->Item[i].Luck  = 0;
		this->Item[i].Opt   = 0;
		this->Item[i].Exl	  = 0;
		this->Item[i].Anc   = 0;
	}

	for(int i=0;i<3;i++)
	{
		for(int l=0;l<100;l++)
		{
			this->Cord[i][l].X = 0;
			this->Cord[i][l].Y = 0;
		}
	}

	FILE *file = fopen(SEARCH_EVENT_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,"Settings\\SearchEvent.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	this->Count = 0;
	this->Count2 = 0;

	this->CountCord[1] = 0;
	this->CountCord[2] = 0;
	this->CountCord[3] = 0;

	while(!feof(file)) 
	{
		fgets(Buff,256,file);
		if(IsBadFileLine(Buff, Flag))
			continue;

		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->TickTime[this->Count].Hour  = n[0];
			this->TickTime[this->Count].Min   = n[1];
			this->Count++;
		}
		if(Flag == 2)
		{
			int n[10];
			sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);

			this->Item[this->Count2].Type  = n[0];
			this->Item[this->Count2].Index = n[1];
			this->Item[this->Count2].Level = n[2];
			this->Item[this->Count2].Skill = n[3];
			this->Item[this->Count2].Luck  = n[4];
			this->Item[this->Count2].Opt   = n[5];
			this->Item[this->Count2].Exl   = n[6];
			this->Item[this->Count2].Anc   = n[7];
			this->Count2++;
		}
		//----------------------------------------
		//Lorencia
		if(Flag == 3)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[1][this->CountCord[1]].X  = n[0];
			this->Cord[1][this->CountCord[1]].Y   = n[1];
			this->CountCord[1]++;
		}
		//Noria
		if(Flag == 4)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[2][this->CountCord[2]].X  = n[0];
			this->Cord[2][this->CountCord[2]].Y   = n[1];
			this->CountCord[2]++;
		}
		//Devias
		if(Flag == 5)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[3][this->CountCord[3]].X  = n[0];
			this->Cord[3][this->CountCord[3]].Y   = n[1];
			this->CountCord[3]++;
		}
	}
	fclose(file);
}

void cSearchEvent::SearchIndexNPC()
{
	if(!this->Enable)
		return;

	for(int i=0;i<OBJECT_MAX;i++)
	{
		OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (i);
		if(gObjNPC->Class == this->NPC)
		{
			this->IndexNPC = i;
			return;
		}
	}
}

void cSearchEvent::NPCClick(int aIndex, int aNPC)
{
	if(!this->Enable)
		return;
	if(this->Start == false)
		return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);

	if(gObjNPC->Class == this->NPC)
	{
		srand(time(NULL));	//Test

		if(this->Stage == 1)
		{
			if(gObj->MapNumber != 0)
				return;
		}
		else if(this->Stage == 2)
		{
			if(gObj->MapNumber != 3)
				return;
		}
		else if(this->Stage == 3)
		{
			if(gObj->MapNumber != 2)
				return;
		}


		this->Present(aIndex);

		if(this->Stage == 1)
		{
			MessaageAllGlobal("[Evangelion] Lorencia Win %s!",gObj->Name);
			//To Noria
			int Num = rand()%CountCord[2];
			int X = Cord[2][Num].X;
			int Y = Cord[2][Num].Y;

			gObjNPC->MapNumber = 3;	//noria
			gObjNPC->X = X;
			gObjNPC->Y = Y;
			MessaageAllGlobal("[Evangelion] In Noria!");

			//MessaageAllGlobal("[Evangelion] %d %d %d",gObjNPC->MapNumber,X,Y);	//Test
			this->Stage++;
		}
		else if(this->Stage == 2)
		{
			MessaageAllGlobal("[Evangelion] Noria Win %s!",gObj->Name);
			//To Devias
			int Num = rand()%CountCord[3];

			gObjNPC->MapNumber = 2;	//Devias
			int X = Cord[3][Num].X;
			int Y = Cord[3][Num].Y;

			gObjNPC->X = X;
			gObjNPC->Y = Y;
			MessaageAllGlobal("[Evangelion] In Devias!");

			//MessaageAllGlobal("[Evangelion] %d %d %d",gObjNPC->MapNumber,X,Y);	//Test
			this->Stage++;
		}
		else if(this->Stage == 3)
		{
			MessaageAllGlobal("[Evangelion] Devias Win %s!",gObj->Name);
			//To End
			this->EventEnd();
			this->Stage = 0;
		}
	}
}

void cSearchEvent::EventStart()
{
	this->SearchIndexNPC();

	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (this->IndexNPC);

	srand(time(NULL));

	int Num = rand()%CountCord[1];
	int X = Cord[1][Num].X;
	int Y = Cord[1][Num].Y;

	gObjNPC->MapNumber = 0;
	gObjNPC->X = X;
	gObjNPC->Y = Y;

	MessaageAllGlobal("[Evangelion] In Lorencia!");
	this->Start = true;
	this->Stage = 1;


	//MessaageAllGlobal("[Evangelion] %d %d %d",gObjNPC->MapNumber,X,Y);	//Test
}

void cSearchEvent::StartNPC()
{
	if(!this->Enable)
		return;

	if(this->Start == true)
	{
		this->Tick++;
		if(this->Tick >= this->Time)
		{
			this->EventEnd();
			return;
		}
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
	if(t.wSecond == 00)
	{
		for(int i = 0; i < this->Count; i++)
		{
			if(this->TickTime[i].Hour == t.wHour && this->TickTime[i].Min == t.wMinute)
			{
				this->EventStart();
				return;
			}
		}
	}
}

void cSearchEvent::Present(int aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	if(this->ItemCount > 0)
	{
		for(int i=0;i<this->ItemCount;i++)
		{
			int Ran = rand()%Count2;

			int NewExl = 0;
			int NewAnc = 0;

			int DropItem = ITEMGET(this->Item[Ran].Type,this->Item[Ran].Index);

			if(Item[Ran].Exl > 0)
				NewExl = GenExcOpt(Item[Ran].Exl);

			if(Item[Ran].Anc == 5 || Item[Ran].Anc == 10)
				NewAnc = Item[Ran].Anc;

			ItemSerialCreateSend(aIndex,gObj->MapNumber,gObj->X,gObj->Y,DropItem,this->Item[Ran].Level,0,
				this->Item[Ran].Skill,this->Item[Ran].Luck,this->Item[Ran].Opt,aIndex,NewExl,NewAnc);
		}
	}

	if(this->PresGem > 0)
	{
		exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint + %d WHERE memb___id='%s'", this->PresGem, gObj->AccountID);
		MsgNormal(aIndex,"[LoraBattle] Reward Gem: +%d",this->PresGem);
	}
}

void cSearchEvent::EventEnd()
{
	this->Start = false;
	this->Tick = 0;
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (this->IndexNPC);
	gObjNPC->MapNumber = DEF_MAP;
	gObjNPC->X = DEF_X;
	gObjNPC->Y = DEF_Y;
	MessaageAllGlobal("[Evangelion] End!");
}