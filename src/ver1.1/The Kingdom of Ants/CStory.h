/*
////////////////////////////////////////////////////////////

	CStory

	게임의 주스토리를 관리한다. 주스토리가 진행될 때는
	게임이 정지되며 정해진 기일에 무조건 발생한다.

////////////////////////////////////////////////////////////
*/

#ifndef CSTORY
#define CSTORY

#include <stdio.h> 
#include <ddraw.h>
#include <stdlib.h>
#include "t3dlib1.h"
#include "ddutil.h"
#include "GlobalDeclaration.h"

class CStory
{
public:
	CStory() {}
	~CStory() {}

private:
	char buffer[200];

	LPDIRECTDRAWSURFACE7 chapter01;
	LPDIRECTDRAWSURFACE7 chapter01_1;
	LPDIRECTDRAWSURFACE7 chapter01_2;
	LPDIRECTDRAWSURFACE7 chapter02;
	LPDIRECTDRAWSURFACE7 chapter02_1;
	LPDIRECTDRAWSURFACE7 chapter02_2;
	LPDIRECTDRAWSURFACE7 chapter02_3;
	LPDIRECTDRAWSURFACE7 chapter03;
	LPDIRECTDRAWSURFACE7 chapter03_1;
	LPDIRECTDRAWSURFACE7 chapter04;
	LPDIRECTDRAWSURFACE7 chapter04_1;
	LPDIRECTDRAWSURFACE7 none;

	// restore을 위해 저장해야 하는 것
	struct _restore
	{
		LPDIRECTDRAWSURFACE7 *surface;
		char *name;
		char *script;
	}restore;
	
	// script 모음
	struct _story
	{
		char *chap_1_intro[7];
		char *chap_1_2_1[3];
		char *chap_1_2_2[2];
		char *chap_1_3[2];
		char *chap_1_4[2];
		char *chap_1_5[2];
		char *chap_2_intro[2];
		char *chap_2_3[2];
		char *cahp_3_intro[4];
		char *chap_3_2[7];
		char *chap_3_3[3];
		char *chap_4_intro[3];
	}story;

	BOOL baphidroom;	// 진딧물 축사가 존재?

	int countdown;		// 종교 집회소 건설 가능 기한

	static HWND hWndDlg_story;
	static INT_PTR CALLBACK NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK AphidDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	int WaitSpace();
	int DrawBitmap(LPDIRECTDRAWSURFACE7 *sur);
	int PrintScript(char *name, char *script, int delay = 500);

	int Restore();

	int ShowDialog(char *firstpage[], int total);
	
	static DWORD WINAPI ThreadChapter_1_Intro(LPVOID temp);
	int Chap_1_2();
	static DWORD WINAPI ThreadChapter_1_2(LPVOID temp);
	int Chap_1_3();
	int Chap_1_4();
	int Chap_1_5();
	int Chap_2_Intro();
	int Chap_2_2();
	int Chap_2_3();
	int Chap_2_4();
	int Chap_3_Intro();
	int Chap_3_2();
	int Chap_3_3();
	int Chap_4_Intro();

	int storyflag;
public:
	int Story_Init();

	int Chap_1_Intro();
	int CheckStory();
	int GetStoryFlag();
	BOOL IsAphidRoomBuilt();

	static HWND GetHwnDia_Story();

	int reload();

	int Save();
	int Load();

	int Story_Shutdown();
};

#endif
