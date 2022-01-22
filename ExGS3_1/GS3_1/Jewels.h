struct PBMSG_HEADIT	   
{
	BYTE c;
	BYTE size;
	BYTE headcode;
};
struct PMSG_USEITEM
{
	PBMSG_HEADIT h;
	BYTE inventoryPos;	    
	BYTE invenrotyTarget;	
	BYTE btItemUseType;	    
};

void CGUseItemRecv(PMSG_USEITEM* lpMsg, int aIndex);
void ItemClear(int aIndex,int pos);
bool IsItem(int aIndex,int pos);