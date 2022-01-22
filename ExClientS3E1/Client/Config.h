void ConfigLoad();

struct Configs
{
	char* CustomFile;
	char ImagesFolder[45]; 
	char MainIP[30];
	char MainSerial[17];
	char MainName[18];
	int ChaosPrice;
	int SoulPrice;
	int LifePrice;
	int GuardianPrice;
	int CreationPrice;
	int DecryptLogs;
	int InGameEffects;
	int MaxAnisotropy;
	int Anisotropy;
	int Linear;
	int ShieldView;

	bool Ctrl;

	char* TextFile;
	char iText[50]; 
	char iText2[50]; 
	char iText3[50]; 
	char iText4[50]; 
	char iText5[50]; 
	char iText6[50]; 
	char iText7[50]; 
	char iText8[50]; 
	char iText9[50]; 
	char iText10[50]; 
	char iText11[50]; 
	char iText12[50]; 
	char iText13[50]; 
	char iText14[50]; 
	char iText15[50]; 
	char iText16[50]; 
	char iText17[50]; 
	char iText18[50];

	char Options1[50];
};
extern Configs Config;