#include <Windows.h>
#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include "md5.h"
#include "ArothGuard.h"

ArothGuard Guard;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void ArothGuard::Configs()
{
	this->ListFile  = "ProtectList.tmp";	// ���� �����
	this->ListURL	= "http://127.0.0.1/Files.txt";		// URL
}

void ArothGuard::UpdateList(char* URL, char FileName[260])
{
	CURL *curl;
	FILE *fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) 
	{
		fp = fopen(FileName,"wb");	
		curl_easy_setopt(curl, CURLOPT_URL, URL);	// ������
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);	// ����������
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);	// ���������
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);	// �������
		fclose(fp);		// ���������
	}
}

void ArothGuard::Init()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	this->FileCount = 0;

	this->UpdateList(this->ListURL, this->ListFile);	// ��������� ����
	fp = fopen(this->ListFile,"r");		// ��������� ����

	rewind(fp);
	while(fgets(sLineTxt, 255, fp) != NULL)		// ������ ������
	{
		if(sLineTxt[0] == '/')continue;			
		if(sLineTxt[0] == ';')continue;
		if(sLineTxt[0] == 'e' && sLineTxt[1] == 'n' && sLineTxt[2] == 'd')continue;
		if(strlen(sLineTxt) <= 1)continue;
		char Hash[100];
		char File[100];

		sscanf(sLineTxt, "%s %s",Hash,File);
		sprintf(GuardStruct[FileCount].Hash,"%s",Hash);
		sprintf(GuardStruct[FileCount].File,"%s",File);

		this->FileCount++;		// ������� ������
	}
	rewind(fp);
	fclose(fp);
	DeleteFile(this->ListFile);		// ������� ����
}

void ArothGuard::Protect()
{
	this->Init();	// �������� �����
	for(int x=1; x < this->FileCount; x++)
	{
		std::string FileHash = MD5File(GuardStruct[x].File);	// ���������� ��� �� �����
		if(GuardStruct[x].Hash != FileHash)		// ���������� ����
		{					
			char Error[300];	// ��� �����
			sprintf(Error,"File '%s' is damaged\nPlease reinstall game client.",GuardStruct[x].File);
			MessageBoxA(NULL,Error,"Aroth Protect",MB_ICONERROR);	// ����������, ��� �� ������
			ExitProcess(0);
		}
	}
}

void ArothGuard::Load()
{
	this->Configs();	// �������
	this->Init();		// �������� �����
	this->Protect();	// �������� ����
}