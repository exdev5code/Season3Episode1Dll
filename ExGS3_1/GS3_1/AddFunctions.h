int TypeItemInt (int ItemCode);
void PlayerConnect(int aIndex);
void AddCommandsDarkLodr (DWORD gObjId,char* msg);			//Add Commands
void BuyGemFun (DWORD gObjId,char* msg);					//Покупка Гем
void FireCracker(int aIndex, BYTE X, BYTE Y);				//FireCracker
void Credits(DWORD gObjId);									//Credits
void CreateMyStruct(int aIndex);
void ChatInfoChar(int aIndex,char* msg);
void ChatAccMode(int aIndex,char* msg);
void ExPointsForOnline(int aIndex);
void Ex_PkClear(int aIndex);
void ErrorConnectDataBase(int aIndex);
void EliteClickerCick(int aIndex);
void CriticalExError(int aIndex);
void RestartStats (int aIndex);
int  gObjCalDistance(OBJECTSTRUCT * lpObj1, OBJECTSTRUCT * lpObj2);