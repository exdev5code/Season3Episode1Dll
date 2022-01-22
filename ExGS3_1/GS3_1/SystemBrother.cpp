#include "StdAfx.h"
#include "USER.h"
#include "SystemBrother.h"
#include "CQuery.h"
#include "Message.h"
#include "AddFunctions.h"

cSystemBrother SystemBrother;

void cSystemBrother::StartConfigs()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,SystemBrother_DIR);

	this->AddExp = GetPrivateProfileInt("Common","AddExp",0,SystemBrother_DIR);
	this->AddDMG = GetPrivateProfileInt("Common","AddDMG",0,SystemBrother_DIR);
	this->AddDEF = GetPrivateProfileInt("Common","AddDEF",0,SystemBrother_DIR);

	this->TaxGem = GetPrivateProfileInt("Common","TaxGem",0,SystemBrother_DIR);
	this->TelGem = GetPrivateProfileInt("Common","TelGem",0,SystemBrother_DIR);
	this->OffGem = GetPrivateProfileInt("Common","OffGem",0,SystemBrother_DIR);
	this->AddIgn = GetPrivateProfileInt("Common","AddIgn",0,SystemBrother_DIR);
	this->AddDD = GetPrivateProfileInt("Common","AddDD",0,SystemBrother_DIR);

	this->NPC = GetPrivateProfileInt("NPC","NPC",0,SystemBrother_DIR);
	this->NPC_Map = GetPrivateProfileInt("NPC","NPC_Map",0,SystemBrother_DIR);
	this->NPC_X = GetPrivateProfileInt("NPC","NPC_X",0,SystemBrother_DIR);
	this->NPC_Y = GetPrivateProfileInt("NPC","NPC_Y",0,SystemBrother_DIR);
}

void cSystemBrother::StartStruct(int aIndex)
{
	if(!this->Enable)
		return;

	this->User[aIndex].okey = false;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	


	exQueryReturnStr(this->User[aIndex].Brother,"SELECT Brother FROM Character WHERE Name='%s'", gObj->Name);
	//MySQL.GetString(this->User[aIndex].Brother);

	//MsgNormal(aIndex,"%s",this->User[aIndex].Brother);

	if(!strcmp(this->User[aIndex].Brother,"One"))
		this->User[aIndex].InBrotherd = false;
	else
		this->User[aIndex].InBrotherd = true;

	//if(strcmp(this->User[aIndex].Brother,"-1"))
	//{
	//	MsgNormal(aIndex,"1",this->User[aIndex].Brother);
	//	MySQL.Execute("SELECT user1 FROM SystemBrother WHERE Brother='%s'",this->User[aIndex].Brother); 
	//	MySQL.GetString(this->User[aIndex].Name[1]);

	//	MySQL.Execute("SELECT user2 FROM SystemBrother WHERE Brother='%s'",this->User[aIndex].Brother); 
	//	MySQL.GetString(this->User[aIndex].Name[2]);

	//	MySQL.Execute("SELECT user3 FROM SystemBrother WHERE Brother='%s'",this->User[aIndex].Brother); 
	//	MySQL.GetString(this->User[aIndex].Name[3]);

	//	MySQL.Execute("SELECT user4 FROM SystemBrother WHERE Brother='%s'",this->User[aIndex].Brother); 
	//	MySQL.GetString(this->User[aIndex].Name[4]);

	//	MySQL.Execute("SELECT user5 FROM SystemBrother WHERE Brother='%s'",this->User[aIndex].Brother); 
	//	MySQL.GetString(this->User[aIndex].Name[5]);
	//}
	//MsgNormal(aIndex,"2",this->User[aIndex].Brother);
}

void cSystemBrother::NPCClick(int aIndex, int aNPC)
{
	if(!this->Enable)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (aNPC);

	if((gObjNPC->Class == this->NPC) && (gObjNPC->MapNumber == this->NPC_Map) && (gObjNPC->X == this->NPC_X) && (gObjNPC->Y == this->NPC_Y))
	{
		if(this->User[aIndex].InBrotherd == false)
		{
			if(gObj->m_bPShopOpen == false)
			{
				MsgNormal(aIndex,"[Brother] No Name");
				return;
			}
			//Проверка на состояние в партии
			if(gObj->PartyNumber == -1)
			{
				MsgNormal(aIndex,"[Brother] No Party");
				return;
			}
			//Проверка на разрешенные символы
			if(this->CheckSimbol(gObj->m_szPShopText) == false)
			{
				MsgNormal(aIndex,"[Brother] Word Error");
			}
			//Проверяем фулл парти или нет
			int CountNumPaty = 0;
			char NewName[6][11];
			int NewIndex[6];
			for(int i=OBJECT_MIN;i<=OBJECT_MAX;i++)
			{
				OBJECTSTRUCT *sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);	
				if(sObj->Connected != PLAYER_PLAYING)
					continue;

				if((gObj->PartyNumber == sObj->PartyNumber) && (!strcmp(gObj->m_szPShopText,sObj->m_szPShopText)))
				{
					if(this->User[i].InBrotherd == true)
					{
						MsgNormal(aIndex,"[Brother]: %s in Brotherd: %s",sObj->Name,this->User[i].Brother);
						return;
					}
					CountNumPaty++;
					NewIndex[CountNumPaty] = i;
					strcpy(NewName[CountNumPaty],sObj->Name);
					//MsgNormal(aIndex,"Name[%d] %s - %s",CountNumPaty,NewName[CountNumPaty],sObj->Name);	//DeBug
				}
			}

			if(CountNumPaty != 5)
			{
				MsgNormal(aIndex,"[Brother]: Brother Party %d/5",CountNumPaty);
				return;
			}

			char TestChar[36];
			exQueryReturnStr(TestChar,"SELECT Brother FROM Character WHERE Brother='%s'", gObj->m_szPShopText);
			//MySQL.GetString(TestChar);
			if(!strcmp(gObj->m_szPShopText,TestChar))
			{
				MsgNormal(aIndex,"[Brother]: Error Name");
				return;
			}


			if(!OperationGem(aIndex,this->TaxGem))
				return;
			//if(MySQL.Execute("SELECT CashPoint FROM MEMB_INFO WHERE memb___id='%s'",gObj->AccountID))
			//{
			//	int MyGems = MySQL.GetInt();
			//	if(MyGems < this->TaxGem)
			//	{
			//		MsgNormal(aIndex,"[Brother]: Need %d GEM",this->TaxGem);
			//		return;
			//	}

			//	if(!MySQL.Execute("UPDATE MEMB_INFO SET CashPoint = CashPoint - %d WHERE memb___id='%s'",this->TaxGem,gObj->AccountID))
			//	{
			//		MsgNormal(aIndex,"[Connect]: Error");
			//		return;
			//	}
			//}
			//else
			//{
			//	MsgNormal(aIndex,"[Connect]: Error");
			//	return;
			//}

			if (exQueryUpdate("UPDATE Character SET Brother = '%s' WHERE Name='%s'", gObj->m_szPShopText, NewName[1]) &&
				exQueryUpdate("UPDATE Character SET Brother = '%s' WHERE Name='%s'", gObj->m_szPShopText, NewName[2]) &&
				exQueryUpdate("UPDATE Character SET Brother = '%s' WHERE Name='%s'", gObj->m_szPShopText, NewName[3]) &&
				exQueryUpdate("UPDATE Character SET Brother = '%s' WHERE Name='%s'", gObj->m_szPShopText, NewName[4]) &&
				exQueryUpdate("UPDATE Character SET Brother = '%s' WHERE Name='%s'", gObj->m_szPShopText, NewName[5]))
			{
				MsgNormal(aIndex,"%s, %s, %s, %s, %s",NewName[1],NewName[2],NewName[3],NewName[4],NewName[5]);	//DeBug
				MessaageAllGlobal("[NewBrotherd] %s",gObj->m_szPShopText);

				FireCracker(aIndex, gObj->X, gObj->Y);

				for(int j=1;j<=5;j++)
				{
					this->User[NewIndex[j]].InBrotherd = true;
					this->User[NewIndex[j]].okey = true;
				}
			}
			else
			{
				MsgNormal(aIndex,"[Connect]: Error");
				return;
			}
			//if(!MySQL.Execute("INSERT INTO SystemBrother (Brother,user1,user2,user3,user4,user5)VALUES('%s','%s','%s','%s','%s','%s')",
			//	gObj[aIndex].m_szPShopText,NewName[1],NewName[2],NewName[3],NewName[4],NewName[5]))
			//{
			//	MessageChat(aIndex,"~[Brother]: Error");
			//	return;
			//}

		}
		else
		{
			//MessageChat(aIndex,"~[Brother]: %s",this->User[aIndex].Name[1]);
			//MessageChat(aIndex,"~[Brother]: %s",this->User[aIndex].Name[2]);
			//MessageChat(aIndex,"~[Brother]: %s",this->User[aIndex].Name[3]);
			//MessageChat(aIndex,"~[Brother]: %s",this->User[aIndex].Name[4]);
			//MessageChat(aIndex,"~[Brother]: %s",this->User[aIndex].Name[5]);
		}
	}
}

void cSystemBrother::TimeTick(int aIndex)
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	

	if(gObj->PartyNumber == -1)
	{
		//MsgNormal(aIndex,"[Brother] No Party");
		return;
	}
	int CountNumPaty = 0;
	for(int i=OBJECT_MIN;i<=OBJECT_MAX;i++)
	{
		OBJECTSTRUCT *sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);	
		if(sObj->Connected != PLAYER_PLAYING)
			continue;
		//MsgNormal(aIndex,"Debug 1");
		if( ( gObj->PartyNumber == sObj->PartyNumber ) && ( !strcmp(this->User[aIndex].Brother,this->User[i].Brother) ) )
		{
			//MsgNormal(aIndex,"Debug 2");
			CountNumPaty++;
			//strcat(NewName[CountNumPaty],gObj[i].Name);
		}
	}

	if(CountNumPaty == 5)
	{
		//MsgNormal(aIndex,"[Brother]: Brother Party %d/5",CountNumPaty);
		this->User[aIndex].okey = true;
		//return;
	}
	else
	{
		this->User[aIndex].okey = false;
		//return;
	}
}

void cSystemBrother::AddedCharacter(int aIndex)
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	if(!this->User[aIndex].okey)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	//pBonusExp = ((Exp/100)*cExperience.Number[i].Exp);

	//Damage
	gObj->m_AttackDamageMaxLeft += ((gObj->m_AttackDamageMaxLeft/100)*this->AddDMG);
	gObj->m_AttackDamageMinLeft += ((gObj->m_AttackDamageMinLeft/100)*this->AddDMG);
	gObj->m_AttackDamageMaxRight += ((gObj->m_AttackDamageMaxRight/100)*this->AddDMG);
	gObj->m_AttackDamageMinRight += ((gObj->m_AttackDamageMinRight/100)*this->AddDMG);
	//Ignore
	gObj->SetOpIgnoreDefense += this->AddIgn;
	//Double Damage
	gObj->SetOpDoubleDamage += this->AddDD;

	gObj->m_MagicDamageMin += ((gObj->m_MagicDamageMin/100)*this->AddDMG);
	gObj->m_MagicDamageMax += ((gObj->m_MagicDamageMax/100)*this->AddDMG);
	//Defense
	gObj->m_Defense += ((gObj->m_Defense/100)*this->AddDEF);
	gObj->m_MagicDefense += ((gObj->m_MagicDefense/100)*this->AddDEF);
}

void cSystemBrother::BrothCMD(int aIndex)	//Command Information
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	if(this->User[aIndex].okey == true)
	{
		MessageChat(aIndex,"~[Brother]: Active");
	}
	else
	{
		MessageChat(aIndex,"~[Brother]: No Active");
	}
}

void cSystemBrother::BrothTeleportCMD(int aIndex, char* msg)	//Command Tp Brother in Spot
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	if(this->User[aIndex].okey == false)
		return;
	if (strlen(msg) > 10) return;
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	char Nick[11];
	sscanf(msg,"%s",&Nick);
	for(int i=OBJECT_MIN;i<=OBJECT_MAX;i++)
	{
		OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(sObj->Connected != PLAYER_PLAYING)
			continue;
		if(!strcmp(sObj->Name,Nick))
		{

			if(gObj->PartyNumber == sObj->PartyNumber && strcmp(this->User[aIndex].Brother,this->User[i].Brother) == NULL)
			{
				if(this->User[i].Off == 1)
				{
					MessageChat(aIndex,"~[Brother]: %s - OffExp",sObj->Name);
					return;
				}

				if(!OperationGem(aIndex,this->TelGem))
					return;

				gObjTeleport(i,gObj->MapNumber,gObj->X,gObj->Y);
				MessageChat(aIndex,"~[Brother]: Teleport in Spot '%s'",sObj->Name);
				return;
			}

			//for(int l=1;l<=5;l++)
			//{
			//	if(!strcmp(this->User[aIndex].Name[i],Nick))
			//	{
			//		gObjTeleport(i,gObj->MapNumber,gObj->X,gObj->Y);
			//		MessageChat(aIndex,"~[Brother]: Teleport in Spot '%s'",this->User[aIndex].Name[i]);
			//		return;
			//	}
			//}
		}
	}
	MessageChat(aIndex,"~[Brother]: NoCharacter '%s'",Nick);
	//MessageChat(aIndex,"~[Brother]: NoCharacter '%s'",Nick);
}

void cSystemBrother::BrothOffCharCMD(int aIndex)	//Command Information
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if(this->User[aIndex].okey == true)
	{
		if(!this->OperationGem(aIndex,this->OffGem))
			return;
		this->User[aIndex].Off = 1;
		MessageChat(aIndex,"~[Brother]: OffExp");
		CloseClient(aIndex);
		//MessageChat(aIndex,"~[Brother]: ON");
	}
	else
	{
		MessageChat(aIndex,"~[Brother]: No Active");
	}
}

void cSystemBrother::BrotherInformation(int aIndex)
{
	if(!this->Enable)
		return;

	if(this->User[aIndex].InBrotherd == false)
		return;

	int num = 0;
	for(int i=OBJECT_MIN;i<=OBJECT_MAX;i++)
	{
		OBJECTSTRUCT * sObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(sObj->Connected != PLAYER_PLAYING)
			continue;

		if(!strcmp(this->User[aIndex].Brother,this->User[i].Brother))
		{
			MessageChat(aIndex,"~[Brother]:%s Online",sObj->Name);
			num++;
		}
	}
	MessageChat(aIndex,"~[Brother]: %d/5",num);
}

bool cSystemBrother::CheckSimbol(char* String)
{
	if(String[0] == ' ')
		return false;

	for(int i(0);i<36;i++)
	{
		if(String[i] == NULL)
			continue;

		switch(String[i])
		{
		case 'a': continue ; break;
		case 'b': continue ; break;
		case 'c': continue ; break;
		case 'd': continue ; break;
		case 'e': continue ; break;
		case 'f': continue ; break;
		case 'g': continue ; break;
		case 'h': continue ; break;
		case 'i': continue ; break;
		case 'j': continue ; break;
		case 'k': continue ; break;
		case 'l': continue ; break;
		case 'm': continue ; break;
		case 'n': continue ; break;
		case 'o': continue ; break;
		case 'p': continue ; break;
		case 'q': continue ; break;
		case 'r': continue ; break;
		case 's': continue ; break;
		case 't': continue ; break;
		case 'u': continue ; break;
		case 'v': continue ; break;
		case 'w': continue ; break;
		case 'x': continue ; break;
		case 'y': continue ; break;
		case 'z': continue ; break;
		case 'A': continue ; break;
		case 'B': continue ; break;
		case 'C': continue ; break;
		case 'D': continue ; break;
		case 'E': continue ; break;
		case 'F': continue ; break;
		case 'G': continue ; break;
		case 'H': continue ; break;
		case 'I': continue ; break;
		case 'J': continue ; break;
		case 'K': continue ; break;
		case 'L': continue ; break;
		case 'M': continue ; break;
		case 'N': continue ; break;
		case 'O': continue ; break;
		case 'P': continue ; break;
		case 'Q': continue ; break;
		case 'R': continue ; break;
		case 'S': continue ; break;
		case 'T': continue ; break;
		case 'U': continue ; break;
		case 'V': continue ; break;
		case 'W': continue ; break;
		case 'X': continue ; break;
		case 'Y': continue ; break;
		case 'Z': continue ; break;
		case '0': continue ; break;
		case '1': continue ; break;
		case '2': continue ; break;
		case '3': continue ; break;
		case '4': continue ; break;
		case '5': continue ; break;
		case '6': continue ; break;
		case '7': continue ; break;
		case '8': continue ; break;
		case '9': continue ; break;
		case ' ': continue ; break;
		default: return false;
		}
	}
	return true;
}

bool cSystemBrother::OperationGem(int aIndex,int Gems)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	int MyGems = exQueryReturnInt("SELECT CashPoint FROM MEMB_INFO WHERE memb___id='%s'", gObj->AccountID);

	if(MyGems < Gems)
	{
		MsgNormal(aIndex,"[Brother]: Need %d GEM",Gems);
		return false;
	}

	exQueryUpdate("UPDATE MEMB_INFO SET CashPoint = CashPoint - %d WHERE memb___id='%s'", Gems, gObj->AccountID);
	
	MsgNormal(aIndex,"[Brother]: -%d GEM",Gems);

	return true;
}