#include "stdafx.h"
#include "Protocol.h"
#include "AntiCheatPlus.h"

CProtocol g_Protocol;

void CProtocol::Load()
{
	this->byXorFilter[0] = 0xE7;
	this->byXorFilter[1] = 0x6D;
	this->byXorFilter[2] = 0x3A;
	this->byXorFilter[3] = 0x89;
	this->byXorFilter[4] = 0xBC;
	this->byXorFilter[5] = 0xB2;
	this->byXorFilter[6] = 0x9F;
	this->byXorFilter[7] = 0x73;
	this->byXorFilter[8] = 0x23;
	this->byXorFilter[9] = 0xA8;
	this->byXorFilter[10] = 0xFE;
	this->byXorFilter[11] = 0xB6;
	this->byXorFilter[12] = 0x49;
	this->byXorFilter[13] = 0x5D;
	this->byXorFilter[14] = 0x39;
	this->byXorFilter[15] = 0x5D;
	this->byXorFilter[16] = 0x8A;
	this->byXorFilter[17] = 0xCB;
	this->byXorFilter[18] = 0x63;
	this->byXorFilter[19] = 0x8D;
	this->byXorFilter[20] = 0xEA;
	this->byXorFilter[21] = 0x7D;
	this->byXorFilter[22] = 0x2B;
	this->byXorFilter[23] = 0x5F;
	this->byXorFilter[24] = 0xC3;
	this->byXorFilter[25] = 0xB1;
	this->byXorFilter[26] = 0xE9;
	this->byXorFilter[27] = 0x83;
	this->byXorFilter[28] = 0x29;
	this->byXorFilter[29] = 0x51;
	this->byXorFilter[30] = 0xE8;
	this->byXorFilter[31] = 0x56;

	SetOp((LPVOID)oDataRecv, (LPVOID)this->DataRecv, ASM::CALL);
}

void CProtocol::DataSend(LPBYTE Data, int Size)
{
	int StartPos = 0;

	if( Data[0] == 0xC1 || Data[0] == 0xC3 )
	{
		StartPos = 3;
	}
	else if( Data[0] == 0xC2 || Data[0] == 0xC4 )
	{
		StartPos = 4;
	}

	for( int i = StartPos; i < Size; i++ )
	{
		Data[i] ^= Data[i - 1] ^ this->byXorFilter[i%32];
	}

	send(pActiveSocket, (char*)Data, Size, 0);
}

void CProtocol::DataRecv(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	BYTE ProtocolType = Data[0];

	if(ProtocolType == 0xC1)
	{
		switch(BYTE(Case))
		{
			case 0xF1:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;

				switch(lpDef->subcode)
				{
				#if(ANTI_CHEAT_PLUS==TRUE)
				case 0x00:
					g_AntiCheatPlus.CG_HddSend();
					break;
				#endif
				}
			}
			break;
			case 0xFB:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)Data;

				switch ( lpDef->subcode )
				{
					#if(ANTI_CHEAT_PLUS==TRUE)
					case 0xFF:
						g_AntiCheatPlus.GC_Recv(Data);
						break;
					#endif
				}
				//return;
			}
			break;
		}
	}

	pDataRecv(Case, Data, Len, aIndex);
}