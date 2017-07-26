
#include <stdio.h>
#include "CBuilding.h"
#include "CMainMenu.h"
#include "CItem.h"
#include "CObjDialog.h"
#include "CDiplomatic.h"
#include "CDomestic.h"
#include "CBattle.h"
#include "CTime.h"
#include "CDataFile.h"
#include "CStory.h"
#include "Sound.h"
#include "CInterface.h"
#include "CScreen.h"
#include "resource.h"

extern CStory story_;
extern CItem item_;
extern CScreen screen_;
extern CInterface interface_;
extern CDataFile datafile_;
extern CTime time_;

HWND CMainMenu::hWndDlg_mainmenu = NULL;

extern int SoundClick();
extern int CheckLButton();
extern int CheckESCKey();
extern int Game_Init(void *parms = NULL, int num_parms = 0);
extern int Game_Shutdown(void *parms, int num_parms);
extern BOOL g_bActive;
extern CSound *g_pSMusic[MAX_SMUSIC];
extern CSound *g_pSSound[MAX_SSOUND];

int CMainMenu::MainMenu_Init()
{
	mainmenu = DDLoadBitmap(lpdd, "art/etc/mainmenu.bmp", 0, 0);

	SetRect(&rectmainmenu, 577, 8, 627, 36);

	mainmenuarray[0].menutype = "게임 계속하기";
	SetRect(&mainmenuarray[0].menurect, 216, 201, 427, 235);
	mainmenuarray[0].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[0].middlepoint.y = 201 + (235-201)/2;
	mainmenuarray[0].Disalbed = TRUE;

	mainmenuarray[1].menutype = "새 게임";
	SetRect(&mainmenuarray[1].menurect, 216, 238, 427, 271);
	mainmenuarray[1].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[1].middlepoint.y = 238 + (271-238)/2;
	mainmenuarray[1].Disalbed = FALSE;

	mainmenuarray[2].menutype = "저장하기";
	SetRect(&mainmenuarray[2].menurect, 216, 274, 427, 308);
	mainmenuarray[2].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[2].middlepoint.y = 274 + (308-274)/2;
	mainmenuarray[2].Disalbed = TRUE;

	mainmenuarray[3].menutype = "불러오기";
	SetRect(&mainmenuarray[3].menurect, 216, 311, 427, 344);
	mainmenuarray[3].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[3].middlepoint.y = 311 + (344-311)/2; 
	mainmenuarray[3].Disalbed = FALSE;

	mainmenuarray[4].menutype = "옵션";
	SetRect(&mainmenuarray[4].menurect, 216, 347, 427, 381);
	mainmenuarray[4].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[4].middlepoint.y = 347 + (381-347)/2;
	mainmenuarray[4].Disalbed = FALSE;

	mainmenuarray[5].menutype = "제작자";
	SetRect(&mainmenuarray[5].menurect, 216, 384, 427, 416);
	mainmenuarray[5].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[5].middlepoint.y = 384 + (416-384)/2;
	mainmenuarray[5].Disalbed = FALSE;

	mainmenuarray[6].menutype = "나가기";
	SetRect(&mainmenuarray[6].menurect, 216, 421, 427, 454);
	mainmenuarray[6].middlepoint.x = 216 + (427-216)/2;
	mainmenuarray[6].middlepoint.y = 421 + (454-421)/2;
	mainmenuarray[6].Disalbed = FALSE;

	return 1;
}

int CMainMenu::ShowMainMenu(BOOL brectcheck, BOOL except)
{
	if(CTime::GetPauseRef() != 0)
		return 0;

	if(brectcheck == TRUE)
	{
		if(except == FALSE)
			if(!CheckRect(&rectmainmenu, mouse_x, mouse_y))
				return 0;
		SoundClick();
		mainmenuarray[0].Disalbed = FALSE;
		mainmenuarray[2].Disalbed = FALSE;
	}
	else
	{
		mainmenuarray[0].Disalbed = TRUE;
		mainmenuarray[2].Disalbed = TRUE;
	}

	if(GAME_STATE == GAME_OVER)
	{
		Game_Shutdown((void *)1, 0);
		Game_Init((void *)1);
		
		window_closed = 0;
		GAME_STATE = GAME_RUN;
	}

	int temp_return = -1;
	
	CTime::SetPause();

	// 모든 다이얼로그 박스를 숨긴다.
	HideAllDialog();

	MSG msg;
	while(TRUE)
	{
		for(int i=0; i<20; i++)
		{
			// test if there is a message in queue, if so get it
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{ 
				// test if this is a quit
				if (msg.message == WM_QUIT)
				   break;
			
				// translate any accelerator keys
				TranslateMessage(&msg);

				// send the message to the window proc
				DispatchMessage(&msg);
			} // end if
		}

		if(g_bActive == FALSE)
			continue;

		if(CheckESCKey() == KEY_DOWN)
		{
			if(mainmenuarray[0].Disalbed == FALSE)
			{
				SoundClick();
				break;
			}
		}

		SetCursor(LoadCursor(main_instance, MAKEINTRESOURCE(CURSOR_CROSSHAIR)));

	    lpddsback->Blt(NULL, mainmenu, NULL, DDBLT_WAIT, NULL);

		PrintMainMenu();

		HRESULT hRet = lpddsprimary->Blt(NULL, lpddsback, NULL, DDBLT_WAIT, NULL);
		if((hRet == DDERR_SURFACELOST) && (g_bActive == TRUE))
		{
			for(int i=0; i<4000; i++)
			{
				if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
				{ 
					// test if this is a quit
					if (msg.message == WM_QUIT)
					   break;

					// translate any accelerator keys
					TranslateMessage(&msg);

					// send the message to the window proc
					DispatchMessage(&msg);
				} // end if
				hRet = lpdd->RestoreAllSurfaces();
				if (hRet == DD_OK)
					break;
				if(i == 3999)
					return ErrorMessage(main_window_handle, "restore 실패");
			}

			item_.reload();
			screen_.reload();
			interface_.reload();
			this->reload();
			story_.reload();
		}

		temp_return = CheckInput();

		if(temp_return == 1)
			break;
		if(temp_return == 2)
		{
			Game_Shutdown((void *)1, 0);
			Game_Init((void *)1);
			time_.SetPausePlayer(FALSE);
			story_.Chap_1_Intro();

			return 1;
		}
		if(temp_return == 3)
			datafile_.Save();
		if(temp_return == 4)
		{
			if(datafile_.Load() == 1)
			{
				mainmenuarray[0].Disalbed = FALSE;
				mainmenuarray[2].Disalbed = FALSE;
			}
		}
		if(temp_return == 5)
		{
			if(hWndDlg_mainmenu)
				EndDialog(hWndDlg_mainmenu, TRUE );
			hWndDlg_mainmenu = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_OPTION),
				main_window_handle,  (DLGPROC)OptionDlgProc );
			ShowWindow(hWndDlg_mainmenu, SW_SHOWNORMAL );

			WaitDialog();
		}
		if(temp_return == 6)
		{
			if(hWndDlg_mainmenu)
				EndDialog(hWndDlg_mainmenu, TRUE );
			hWndDlg_mainmenu = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_MAKER),
				main_window_handle,  (DLGPROC)NormalDlgProc );
			ShowWindow(hWndDlg_mainmenu, SW_SHOWNORMAL );

			WaitDialog();
		}
		if(temp_return == 7)
		{
			SendMessage(main_window_handle, WM_CLOSE, 0, 0);
			window_closed = 1;
			return GO_OUT;
		}

		SendMessage(main_window_handle, WM_LBUTTONUP, NULL, NULL);
		
	   
	} // end while

	ShowAllDialog();

	WaitDialog();
	
	CTime::ReleasePause();

	return 1;
}
int CMainMenu::CheckInput()
{
	if(CheckLButton() == BUTTON_DOWN)
	{
		for(int i=0; i<MAX_MAINMENU; i++)
		{
			if(CheckRect(&mainmenuarray[i].menurect , mouse_x, mouse_y))
			{
				if(mainmenuarray[i].Disalbed == FALSE)
				{
					SoundClick();

					EndDialog( hWndDlg_mainmenu, TRUE );
					hWndDlg_mainmenu = NULL;

					if(mainmenuarray[i].menutype == "게임 계속하기")
						return 1;
					if(mainmenuarray[i].menutype == "새 게임")
						return 2;
					if(mainmenuarray[i].menutype == "저장하기")
						return 3;
					if(mainmenuarray[i].menutype == "불러오기")
						return 4;
					if(mainmenuarray[i].menutype == "옵션")
						return 5;
					if(mainmenuarray[i].menutype == "제작자")
						return 6;
					if(mainmenuarray[i].menutype == "나가기")
						return 7;
				}
			}
		}
	}

	return 0;
}

int CMainMenu::PrintMainMenu()
{
	for(int i=0; i<MAX_MAINMENU; i++)
	{
		if(mainmenuarray[i].Disalbed == FALSE)
			DDraw_Text(mainmenuarray[i].menutype, 
			mainmenuarray[i].middlepoint.x,
			mainmenuarray[i].middlepoint.y,
			17,
			lpddsback,
			RGB(255,255,255),
			TA_CENTER,
			NULL,
			TRANSPARENT);
		else
			DDraw_Text(mainmenuarray[i].menutype, 
			mainmenuarray[i].middlepoint.x,
			mainmenuarray[i].middlepoint.y,
			17,
			lpddsback,
			RGB(160,160,160),
			TA_CENTER,
			NULL,
			TRANSPARENT);
	}

	return 1;
}


INT_PTR CALLBACK CMainMenu::NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_mainmenu = NULL;
                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				RECT dest_rect = {0, 0, 640, 480};
				lpddsprimary->Blt(&dest_rect,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             &dest_rect,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_mainmenu = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CMainMenu::OptionDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static HWND hedit1;

	static HWND hbutton1;

	char cheatkey[30];

	switch (msg)
    {
        case WM_INITDIALOG:
			hedit1 = GetDlgItem(hDlg, IDC_OPT_EDIT1);
			hbutton1 = GetDlgItem(hDlg, IDOK);
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_mainmenu = NULL;
                    return TRUE;
                case IDOK:
					GetWindowText(hedit1, cheatkey, 30);
					SetWindowText(hedit1, "");
					SetDlgItemTextA(hDlg, IDC_STATIC_OPT, "invalid cheatkey");
					if(strcmp(CHEAT_SPEED_1X, cheatkey) == 0)
					{
						KillTimer(main_window_handle, 1);
						SetTimer(main_window_handle, 1, HALFTICK, NULL);
						SetDlgItemTextA(hDlg, IDC_STATIC_OPT, "valid cheatkey : speed 1x");
					}
					if(strcmp(CHEAT_SPEED_2X, cheatkey) == 0)
					{
						KillTimer(main_window_handle, 1);
						SetTimer(main_window_handle, 1, HALFTICK/2, NULL);
						SetDlgItemTextA(hDlg, IDC_STATIC_OPT, "valid cheatkey : speed 2x");
					}
					if(strcmp(CHEAT_SPEED_3X, cheatkey) == 0)
					{
						KillTimer(main_window_handle, 1);
						SetTimer(main_window_handle, 1, HALFTICK/3, NULL);
						SetDlgItemTextA(hDlg, IDC_STATIC_OPT, "valid cheatkey : speed 3x");
					}
					if(strcmp(CHEAT_SPEED_4X, cheatkey) == 0)
					{
						KillTimer(main_window_handle, 1);
						SetTimer(main_window_handle, 1, HALFTICK/4, NULL);
						SetDlgItemTextA(hDlg, IDC_STATIC_OPT, "valid cheatkey : speed 4x");
					}

                    return TRUE;
            }
            break;
        case WM_MOVE:
			{
				RECT dest_rect = {0, 0, 640, 480};
				lpddsprimary->Blt(&dest_rect,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             &dest_rect,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_mainmenu = NULL;
            break;
    }

    return FALSE;
}
int CMainMenu::reload()
{
	mainmenu = DDLoadBitmap(lpdd, "art/etc/mainmenu.bmp", 0, 0);

	return 1;
}
int CMainMenu::MainMenu_Shutdown()
{
	if(mainmenu)
		mainmenu->Release();

	return 1;
}

