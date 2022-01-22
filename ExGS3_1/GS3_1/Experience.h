
class Experience 
{
public:
	int Enable;
	void ExpLoad();
	void ExpConfig();
	bool IsBadFileLine(char *FileLine, int &Flag);
	struct 
	{
		int Res;
		int Exp;
	} Number[250];
	int Count;
}; extern Experience cExperience;

void iExpAdder (int aIndex, int TargetIndex, int Exp, int AttackDamage, BOOL MSBFlag);
