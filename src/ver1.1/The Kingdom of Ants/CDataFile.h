/*
///////////////////////////////////////////

	CDataFile

	저장과 불러오기를 담당한다. 다른 클래스의
	save(), load()를 부른다.

///////////////////////////////////////////
*/
#pragma once

class CDataFile
{
public:
	CDataFile() {}
	~CDataFile() {}

private:
	char buffer[100];

	struct tag_Header 
	{
     char desc[45];
     int ver;
	};

	int SaveGlobal();
	int LoadGlobal();

public:
	int DataFile_Init();

	int Save();
	int Load();

	int DataFile_Shutdown();
};
