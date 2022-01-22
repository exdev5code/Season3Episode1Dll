#include "stdafx.h"
#include "utils.h"
#include "Config.h"

Configs Config;

void ConfigLoad()
{
	//Config
	Config.CustomFile	 = ".\\Data\\Custom\\Custom.ini";
	GetPrivateProfileStringA("Connect","ServerAdress","192.168.150.1",Config.MainIP,30,Config.CustomFile);
	GetPrivateProfileStringA("Connect","ClientExeSerial","1I8rk9srd4Klakg3",Config.MainSerial,17,Config.CustomFile);
	GetPrivateProfileStringA("Other","WindowName","MU",Config.MainName,18,Config.CustomFile);
	GetPrivateProfileStringA("Folders","ScreenShoots","Screen(%02d_%02d-%02d_%02d)-%04d.jpg",Config.ImagesFolder,45,Config.CustomFile);
	Config.ChaosPrice = GetPrivateProfileInt("Price","JewelOfChaos",2000000,Config.CustomFile);
	Config.SoulPrice = GetPrivateProfileInt("Price","JewelOfSoul",2000000,Config.CustomFile);
	Config.LifePrice = GetPrivateProfileInt("Price","JewelOfLife",2000000,Config.CustomFile);
	Config.GuardianPrice = GetPrivateProfileInt("Price","JewelOfGuardian",2000000,Config.CustomFile);
	Config.CreationPrice = GetPrivateProfileInt("Price","JewelOfCreation",2000000,Config.CustomFile);
	Config.DecryptLogs = GetPrivateProfileInt("Functions","DecryptLogs",1,Config.CustomFile);
	Config.InGameEffects = GetPrivateProfileInt("OpenGL","OnlyInGame",1,Config.CustomFile);
	Config.Anisotropy = GetPrivateProfileInt("OpenGL","Anisotropy",1,Config.CustomFile);
	Config.MaxAnisotropy = GetPrivateProfileInt("OpenGL","MaxAnisotropy",1,Config.CustomFile);
	Config.Linear = GetPrivateProfileInt("OpenGL","Linear",1,Config.CustomFile);
	Config.ShieldView = GetPrivateProfileInt("Functions","ShieldView",1,Config.CustomFile);
	//Text
	Config.TextFile = ".\\Data\\Custom\\Text.ini";
	GetPrivateProfileStringA("Description","Text1","Text1",Config.iText,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text2","Text2",Config.iText2,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text3","Text3",Config.iText3,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text4","Text4",Config.iText4,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text5","Text5",Config.iText5,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text6","Text6",Config.iText6,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text7","Text7",Config.iText7,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text8","Text8",Config.iText8,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text9","Text9",Config.iText9,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text10","Text10",Config.iText10,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text11","Text11",Config.iText11,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text12","Text12",Config.iText12,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text13","Text13",Config.iText13,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text14","Text14",Config.iText14,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text15","Text15",Config.iText15,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text16","Text16",Config.iText16,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text17","Text17",Config.iText17,50,Config.TextFile);
	GetPrivateProfileStringA("Description","Text18","Text18",Config.iText18,50,Config.TextFile);
	GetPrivateProfileStringA("Options","Options1","Options1",Config.Options1,50,Config.TextFile);
	//GetPrivateProfileStringA("Description","Text17","Text17",Config.iText17,50,Config.TextFile);

	Config.Ctrl = false;
}


