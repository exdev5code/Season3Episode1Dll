#include "StdAfx.h"
#include "USER.h"

bool IsBadFileLine(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)
	{
		Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}
//====================================================
int GenExcOpt(int amount)
{
	// User input errors
	if (amount > 6) amount = 6;
	if (amount < 1) amount = 1;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	std::random_shuffle(opt_db, opt_db + 6);

	for(int n=0; n < amount; n++)
		exc += opt_db[n];

	return exc;
}