#include "StdAfx.h"
#include "USER.h"
#include "Message.h"

//Message Exp
//===========
void MsgNormal(int aIndex,char* szMsg,...)
{
	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	
	GCServerMsgStringSend(szTemp, aIndex,1); // 0 = Global MSG; 1 = System information; 2 = Guild notice
}
//Chat Message
//============
void MessageChat(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSend(aIndex,Packet, Len);
	free (Packet);
}
//All Chat Message
//================
void MessageAllChat(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
}
//Функция для рассылки массового сообщения
void AllServerMsgSend(char *message)
{
	for(int i = OBJECT_MIN; i < OBJECT_MAX; i++)
	{
		OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
		if(gObj->Connected == 3)
			GCServerMsgStringSend(message, i, 0);// 0 = Global MSG; 1 = System information; 2 = Guild notice
	}
}
//Message All Global
//==================
void MessaageAllGlobal(char* szMsg,...)
{
	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	AllServerMsgSend(szTemp);
}

