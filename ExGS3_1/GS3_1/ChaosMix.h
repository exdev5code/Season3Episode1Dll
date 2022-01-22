struct PMSG_C1C3HEAD 
{
	unsigned char head;
	unsigned char len;
	unsigned char type;
};

struct PMSG_CHAOSBOX_RESULT 
{
	PMSG_C1C3HEAD	head;
	unsigned char	info[7];
};

#define ChaosBoxInit ((void(*) (OBJECTSTRUCT*)) 0x004047B9)
#define GCUserChaosBoxSend ((void(*) (OBJECTSTRUCT*, int)) 0x0040573B)
int ItemRange (DWORD gObjId, WORD ItemIDStart, WORD ItemIDEnd);
void ChaosBoxItemsRegardingEx();
void ChaosBoxHook(DWORD gObjID , DWORD MixID);
void ChaosMixSendFail(int gObjID);
void ChaosboxFailure(int aIndex);
int gObjGetItemLevelInChaosbox(int aIndex, short type);
int gObjGetItemLuckInChaosbox(int aIndex);
bool gObjGetItemInChaosbox(int aIndex, short type);
void ChaosMixSendSuccess(ITEMSTRUCT *prize, int aIndex);
