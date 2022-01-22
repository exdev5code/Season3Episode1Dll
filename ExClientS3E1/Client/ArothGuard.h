#ifndef AROTHGUARD_H
#define AROTHGUARD_H

class ArothGuard
{
public:
	void Init();
	void UpdateList(char* url, char filename[260]);
	void Load();
	void Configs();
	void Protect();
	char* ListFile;
	char* ListURL;
	
private:
	struct Checker
	{
		char Hash[100];
		char File[100];
	};
	Checker GuardStruct[200];
	int FileCount;

};extern ArothGuard Guard;
#endif