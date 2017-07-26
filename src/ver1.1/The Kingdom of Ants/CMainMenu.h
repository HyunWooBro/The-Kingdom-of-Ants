/*
///////////////////////////////////////////

	CMainMenu

	메뉴를 담당한다.

///////////////////////////////////////////
*/
#pragma once

#include <ddraw.h>
#include "t3dlib1.h"
#include "ddutil.h"
#include "GlobalDeclaration.h"

class CMainMenu
{
public:
	CMainMenu() {}
	~CMainMenu() {}

private:
	LPDIRECTDRAWSURFACE7 mainmenu;
	RECT rectmainmenu;
	char buffer[15];

	struct _mainmenu
	{
		char* menutype;
		RECT menurect;
		POINT middlepoint;
		BOOL Disalbed;
	}mainmenuarray[MAX_MAINMENU];

	int CheckInput();

	static HWND hWndDlg_mainmenu;
	static INT_PTR CALLBACK NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK OptionDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	
public:
	int MainMenu_Init();

	int ShowMainMenu(BOOL brectcheck, BOOL except = FALSE);
	int PrintMainMenu();

	int reload();

	int MainMenu_Shutdown();
};
