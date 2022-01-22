//======================================
// LCTeam Project GS 1.00.89/1.00.90 JPN
// Coder : SmallHabit
// Start Date : 07.09.2009
//======================================
#include "StdAfx.h"

class COFFTrade
{
public:
	void Init();
	void CreateOfflineTrade(int aIndex);
}; extern COFFTrade OFFTrade;

struct _PER_SOCKET_CONTEXT
{
	char unk[4];
	int nIndex;	

	char Unk[0x5E2C];
}; 

void CGPShopAnsCloseHook(int aIndex, BYTE btResult); 
void ResponErrorCloseClientHook(int aIndex); 
void CloseClient2Hook(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result); 
void CloseClientHook(int aIndex); 