#include "StdAfx.h"
#include "Protocol.h"
#include "user.h"
#include "Message.h"
#include "Item.h"
#include "AddFunctions.h"
#include "Defines.h"
#include "MagicInf.h"
#include "OffExp.h"

#if(DEV_OFFEXP)

COffExp OffExp;

BOOL COffExp::IsItem(LPOBJ lpObj, int pos)
{
	if (lpObj->pInventory[pos].m_Type < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void COffExp::ItemClear(LPOBJ lpObj, int pos)
{
	lpObj->pInventory[pos].m_Type =-1;
	lpObj->pInventory[pos].m_Level =0;
	lpObj->pInventory[pos].m_Part=0;
	lpObj->pInventory[pos].m_Class=0;
	lpObj->pInventory[pos].m_TwoHand=0;
	lpObj->pInventory[pos].m_AttackSpeed=0;
	lpObj->pInventory[pos].m_DamageMin=0;
	lpObj->pInventory[pos].m_DamageMax=0;
	lpObj->pInventory[pos].m_SuccessfulBlocking=0;
	lpObj->pInventory[pos].m_Defense=0;
	lpObj->pInventory[pos].m_MagicDefense =0;
	lpObj->pInventory[pos].m_Durability=0;
	lpObj->pInventory[pos].m_SpecialNum=0;
	lpObj->pInventory[pos].m_Value=0;
	lpObj->pInventory[pos].m_SetiSkill =0;
	lpObj->pInventory[pos].m_SetiLuck =0;
	lpObj->pInventory[pos].m_SetiOption =0;
	lpObj->pInventory[pos].m_SetiExcellent =0;
	lpObj->pInventory[pos].m_Number =0;
	lpObj->pInventory[pos].m_DurabilitySmall =0;
	lpObj->pInventory[pos].m_iPShopValue=-1;
	lpObj->pInventory[pos].m_bItemExist=true;
	lpObj->pInventory[pos].m_CurrentDurabilityState=-1;
	lpObj->pInventory[pos].m_SetOption=0;
	lpObj->pInventory[pos].m_QuestItem=false;


	memset(lpObj->pInventory[pos].m_Special, 0, sizeof(lpObj->pInventory[pos].m_Special));
	memset(lpObj->pInventory[pos].m_SpecialValue, 0, sizeof(lpObj->pInventory[pos].m_SpecialValue));
	memset(lpObj->pInventory[pos].m_Resistance, 0, sizeof(lpObj->pInventory[pos].m_Resistance));

	lpObj->pInventory[pos].m_IsLoadPetItemInfo=0;
	lpObj->pInventory[pos].m_PetItem_Level =1;
	lpObj->pInventory[pos].m_PetItem_Exp =0;
	lpObj->pInventory[pos].m_Leadership=0;
	lpObj->pInventory[pos].m_JewelOfHarmonyOption = 0;
	lpObj->pInventory[pos].m_ItemOptionEx = 0;
}

int COffExp::GetManaItemPos(int aIndex)
{
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*) OBJECT_POINTER(aIndex);

	int count = 0;
	
	for ( int n = 0; n < MAIN_INVENTORY_SIZE; n++)
	{
		if(this->IsItem(lpObj, n) == TRUE)
		{
			if ( lpObj->pInventory[n].m_Type == ITEMGET(14,4) || 
				 lpObj->pInventory[n].m_Type == ITEMGET(14,5) || 
				 lpObj->pInventory[n].m_Type == ITEMGET(14,6) )
			{
				return n;
			}
		}
	}

	return -1;
}

void COffExp::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",1,OFF_EXP_DIR);
	this->KickFallen = GetPrivateProfileInt("Common","KickFallen",0,OFF_EXP_DIR);
	this->EnableTime = GetPrivateProfileInt("Common","EnableTime",0,OFF_EXP_DIR);
	this->TimeEnd = GetPrivateProfileInt("Common","Time",0,OFF_EXP_DIR);
}

void COffExp::OffExpStart(int aIndex)
{
	if(!this->Enable) return;
	
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if (CheckTerrain(lpObj))
	{
		CloseClient(aIndex);
		ExUser[aIndex].OffAfk = true;
	}
	else
	{
		MsgNormal(aIndex,"[OffExp] Works just outside of town");
	}
}

void COffExp::MainFunction(int aIndex)
{
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if(!ExUser[aIndex].OffAfk) return;

	if(!this->CheckTerrain(lpObj))
	{
		return;
	}

	switch(lpObj->Class)
	{
		case 0:	this->DarkWizardOff(lpObj);		break;
		case 1:	this->DarkKnightOff(lpObj);		break;
		case 2:	this->FairyElfOff(lpObj);		break;
		case 3:	this->MagicGladiatorOff(lpObj);	break;
		case 4:	this->DarkLordOff(lpObj);		break;
		case 5:	this->SummonerOff(lpObj);		break;
	}
}
//=====================================
//	Dark Wizard Offline Experience
//=====================================

void COffExp::DarkWizardOff(OBJECTSTRUCT * lpObj)
{
	int aIndex = lpObj->m_Index;
	int SearchSkill = 9;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);

	if(lpMagic==NULL) return;

	CObjUseSkillUseSkill((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum = -1;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if(lpObj->VpPlayer2[n].state == 0) continue;

		if ( tObjNum >= 0 )
		{
			OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);

				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);
					if(6 >= dis)
					{
						gObjAttack(lpObj, targetObjNum, lpMagic, FALSE, 1, 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Knight Offline Experience
//=====================================
void COffExp::DarkKnightOff(LPOBJ lpObj)
{
	int SearchSkill = 0;

	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);

	if(lpMagic==NULL) return;

	CObjUseSkillUseSkill((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;

	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if(lpObj->VpPlayer2[n].state == 0) continue;

		if ( tObjNum >= 0 )
		{
			OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);

				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);

					if(2 >= dis)
					{
						gObjAttack(lpObj, targetObjNum, lpMagic, FALSE, 1, 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

//=====================================
//	Fairy Elf Offline Experience
//=====================================
void COffExp::FairyElfOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	int dis;
	int tObjNum;
	BYTE attr;

	CMagicInf * lpMagic;

	SYSTEMTIME time;

	GetLocalTime(&time);

	if(lpObj->m_SkillDefenseTime < 1)
	{				
		lpMagic = gObjGetMagicSearch( lpObj, 27);
		if(lpMagic!=NULL) 
		{
			CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpObj->m_Index, lpMagic);
			this->UseMana(lpObj->m_Index);
			return;
		}
	}

	if(lpObj->m_SkillDefenseTime < 1)
	{
		lpMagic = gObjGetMagicSearch( lpObj, 28);
		if(lpMagic!=NULL) 
		{
			CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpObj->m_Index, lpMagic);
			this->UseMana(lpObj->m_Index);
			return;
		}
	}

	if( time.wSecond == 0  || time.wSecond == 10 || 
	    time.wSecond == 20 || time.wSecond == 30 ||
	    time.wSecond == 40 || time.wSecond == 50 )
	{
		if((lpObj->MaxLife + lpObj->AddLife) > lpObj->Life)
		{
			lpMagic = gObjGetMagicSearch( lpObj, 26);
			if(lpMagic!=NULL) 
			{
				CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpObj->m_Index, lpMagic);
				this->UseMana(lpObj->m_Index);
				return;
			}
		}
	}

	if(lpObj->PartyNumber != -1)
	{
		for(int number = OBJECT_MIN; number < OBJECT_MAX; number++)
		{
			OBJECTSTRUCT * lpPartyObj = (OBJECTSTRUCT*)OBJECT_POINTER(number);

			if(lpPartyObj->Connected != PLAYER_PLAYING)
			{
				continue;
			}

			if(lpObj->PartyNumber != lpPartyObj->PartyNumber)
			{
				continue;
			}

			if(lpObj->MapNumber != lpPartyObj->MapNumber)
			{
				continue;
			}

			if(lpObj->m_Index == lpPartyObj->m_Index)
			{
				continue;
			}

			dis = gObjCalDistance(lpObj,lpPartyObj);

			if(dis < 6)
			{
				if(lpPartyObj->m_SkillDefenseTime < 1)
				{				
					lpMagic = gObjGetMagicSearch( lpObj, 27);
					if(lpMagic!=NULL) 
					{
						CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
						this->UseMana(lpObj->m_Index);
						return;
					}
				}

				if(lpPartyObj->m_SkillAttackTime < 1)
				{
					lpMagic = gObjGetMagicSearch( lpObj, 28);
					if(lpMagic!=NULL) 
					{
						CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
						this->UseMana(lpObj->m_Index);
						return;
					}
				}

				if( time.wSecond == 0  || time.wSecond == 10 || 
					time.wSecond == 20 || time.wSecond == 30 ||
					time.wSecond == 40 || time.wSecond == 50 )
				{
					if((lpPartyObj->MaxLife + lpPartyObj->AddLife) > lpPartyObj->Life)
					{
						lpMagic = gObjGetMagicSearch( lpObj, 26);
						if(lpMagic!=NULL) 
						{
							CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							this->UseMana(lpObj->m_Index);
							return;
						}
					}
				}
			}
		}
	}

	lpMagic = gObjGetMagicSearch( lpObj, 24);

	if(lpMagic==NULL) return;

	int NumDir[6] = {0, 50, 100, 150, 200, 250 };
	int StartDir = NumDir[rand()%6];

	CObjUseSkillUseSkill((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,StartDir,0,-1);

	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);

				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);

					if(5 >= dis)
					{
						gObjAttack(lpObj, targetObjNum, lpMagic, FALSE, 1, 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Magic Gladiator Offline Experience
//=====================================
void COffExp::MagicGladiatorOff(LPOBJ lpObj)
{
	int skill;
	int NormDis;
	CMagicInf * lpMagic;
	int SearchSkill = 0;

	if(lpObj->pInventory[0].m_Type >= ITEMGET(5,0) && lpObj->pInventory[0].m_Type < ITEMGET(6,0))
	{
		if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
		else return;
		skill = SearchSkill;
		NormDis = 6;
	}
	else
	{
		if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
		else return;
		skill = SearchSkill;
		NormDis = 2;
	}

	lpMagic = gObjGetMagicSearch( lpObj, skill);	//Twisting Slash 41
	if(lpMagic==NULL) return;

	CObjUseSkillUseSkill((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);
	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{

			OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);

				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);

					if(NormDis >= dis)
					{
						gObjAttack(lpObj, targetObjNum, lpMagic, FALSE, 1, 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Lord Offline Experience
//=====================================
void COffExp::DarkLordOff(LPOBJ lpObj)	//Work
{
	int Target = this->SearchTarget(lpObj);

	if(Target == -1) return;

	int SearchSkill = 0;

	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 61) != NULL) SearchSkill = 61;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	//gObjUseSkill.UseSkill(lpObj->m_Index,Target, lpMagic); //
	CObjUseSkillUseSkill2((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index,Target, lpMagic);
	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Summoner Offline Experience
//=====================================
void COffExp::SummonerOff(LPOBJ lpObj)
{
	CMagicInf * lpMagic;

	lpMagic = gObjGetMagicSearch( lpObj, 230);	//Lightning Shock

	if(lpMagic==NULL) return;


	CObjUseSkillUseSkill((LPVOID)*(DWORD*)0x9D3F2E8,lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);
	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);

				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);

					if(6 >= dis)
					{
						gObjAttack(lpObj, targetObjNum, lpMagic, FALSE, 1, 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

int COffExp::SearchTarget(LPOBJ lpObj)
{
	int dis;
	int searchtarget = -1;
	int tObjNum;
	BYTE attr;
	int TargetIndex[MAX_VIEWPORT_MONSTER];
	int TargetCount = 0;
	int IndexNumber;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		OBJECTSTRUCT * targetObjNum = (OBJECTSTRUCT*)OBJECT_POINTER(tObjNum);

		if(lpObj->VpPlayer2[n].state == 0) continue;

		if ( tObjNum >= 0 )
		{
			if ( targetObjNum->Type == OBJ_MONSTER )
			{
				attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * targetObjNum->MapNumber), targetObjNum->X, targetObjNum->Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, targetObjNum);
					if(6 >= dis)
					{
						TargetIndex[TargetCount] = tObjNum;
						TargetCount++;
					}
				}
			}
		}
	}

	if(TargetCount == 0)	return -1;
	
	IndexNumber = rand()%TargetCount;

	searchtarget = TargetIndex[IndexNumber];

	return searchtarget;
}



void COffExp::UseMana(int aIndex)
{
	OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*) OBJECT_POINTER(aIndex);

	if(lpObj->Mana > 100) return;
		
	int pos;

	pos = this->GetManaItemPos(aIndex);

	if(pos == -1) return;

	if( lpObj->pInventory[pos].m_Type == ITEMGET(14,4) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,5) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,6)  )
	{
		int tMana = (lpObj->pInventory[pos].m_Value*10) - (lpObj->Level);

		if ( tMana < 0 )
		{
			tMana=0;
		}

		switch ( lpObj->pInventory[pos].m_Type )
		{
		case ITEMGET(14,4):
			tMana += ((int)(lpObj->MaxMana + lpObj->AddMana))*20/100; 
			break;
		case ITEMGET(14,5):
			tMana += ((int)(lpObj->MaxMana + lpObj->AddMana))*30/100; 
			break;
		case ITEMGET(14,6):
			tMana += ((int)(lpObj->MaxMana + lpObj->AddMana))*40/100; 
			break;
		}

		lpObj->Mana += tMana;

		if ( lpObj->Mana > (lpObj->MaxMana+lpObj->AddMana-1.0f) )
		{
			lpObj->Mana = lpObj->MaxMana+lpObj->AddMana;
		}

		GCManaSend(aIndex, lpObj->Mana, 0xFF, 0, lpObj->BP);

		if ( !gObjSearchItemMinus(lpObj, pos, 1) )
		{
			gObjInventoryItemSet(aIndex, pos, -1);
			this->ItemClear(lpObj, pos);
			GCInventoryItemDeleteSend(aIndex, pos, 1);
		}
	}
}

bool COffExp::CheckTerrain(LPOBJ lpObj)
{	
	BYTE attr;

	attr = MapClassGetAttr((int)&*(DWORD*)(0x1012DE0 + 83010 * lpObj->MapNumber), lpObj->X, lpObj->Y);

	if ( (attr&1) != 1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif