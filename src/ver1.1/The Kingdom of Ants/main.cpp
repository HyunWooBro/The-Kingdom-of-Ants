/*
///////////////////////////////////////////

	The Kingdom of Ants

	개발 기간 : 2008.2.11 ~ 2008.5.3 (ver 1.1)

	한 개미 왕국의 여왕이 되어 자신의 왕국을 발전시켜 나가며
	공원을 장악하는 것이 목표이다.

	by 김현우

///////////////////////////////////////////
*/

#define WIN32_LEAN_AND_MEAN  // just say no to MFC

// INCLUDES ///////////////////////////////////////////////

#include <windows.h>				// include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream>					// include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>

#include "resource.h"

#include <ddraw.h>					// 다이렉트x
#include <dinput.h>
#include <dsound.h>
#include <dmksctrl.h>
#include <dmusici.h>
#include <dmusicc.h>
#include <dmusicf.h>

#include "t3dlib1.h"				// 기타 라이브러리
#include "t3dlib2.h"
#include "t3dlib3.h"
#include "ddutil.h"
#include "Sound.h"
#include "Wave.h"

#define MAIN_PASS
#include "GlobalDeclaration.h"		// 내가 만든 소스
#include "GlobalFunction.h"
#include "GlobalValue.h"				
#include "CDebug.h"
#include "CItem.h"
#include "CObject.h"
#include "CObjDialog.h"
#include "CScreen.h"
#include "CTime.h"
#include "CEvent.h"
#include "CStory.h"
#include "CDomestic.h"
#include "CDiplomatic.h"
#include "CInterface.h"
#include "CBuilding.h"
#include "CMainMenu.h"
#include "CBattle.h"
#include "CInfo.h"
#include "CPlayer.h"
#include "CSpecies.h"
#include "CDataFile.h"

// NAMESPACE //////////////////////////////////////////////

using namespace std;

// GLOBALS ////////////////////////////////////////////////

LPDIRECTDRAWGAMMACONTROL lpddgammacontrol = NULL;
DDGAMMARAMP ddgammaramp;
DDGAMMARAMP ddgammachangedramp;			//새롭게 적용할 GammaRamp
float gamma = 0;

int Game_Shutdown(void *parms = NULL, int num_parms = 0);

char buffer[50];

LPDIRECTDRAWCLIPPER pClipper;

CSound *g_pSMusic[MAX_SMUSIC];
CSound *g_pSSound[MAX_SSOUND];

BOOL g_bActive;

// CLASS INSTANCE //////////////////////////////////////////

CDebug debug_;
CItem item_;
CObject object_;
CObjDialog objdialog_;
CScreen screen_;
CTime time_;
CEvent event_;
CStory story_;
CDomestic domestic_;
CInterface interface_;
CBuilding building_;
CMainMenu mainmenu_;
CDiplomatic diplomatic_;
CBattle battle_;
CInfo info_;
CDataFile datafile_;

// FUNCTIONS //////////////////////////////////////////////
#ifdef TEST
int Test()
{
	debug_.GetValue("Pointer", &mouse_x, &mouse_y, lpddsback, 1, NULL);
	debug_.GetValue("Pointer+Off", &mouse_off_x, &mouse_off_y, lpddsback, 2, NULL);

	return 1;
}
#endif
int Global_Init()
{
	CHAPTER = CHAP_1;

	GAME_STATE = GAME_RUN;
	SCREEN_STATE = SCREEN_GAME;

	LBUTTON_STATE = LBUTTON_RUN;
	LBUTTON_STATE2 = LBUTTON_UP;

	KEY_SPACE_STATE = KEY_SPACE_RUN;
	KEY_SPACE_STATE2 = KEY_SPACE_UP;

	KEY_M_STATE = KEY_M_RUN;
	KEY_M_STATE2 = KEY_M_UP;

	KEY_I_STATE = KEY_I_RUN;
	KEY_I_STATE2 = KEY_I_UP;

	KEY_S_STATE = KEY_S_RUN;
	KEY_S_STATE2 = KEY_S_UP;

	KEY_ESC_STATE = KEY_ESC_RUN;
	KEY_ESC_STATE2 = KEY_ESC_UP;

	SCROLL_STATE = SCROLL_RUN;

	MOUSE_STATE = MOUSE_SHOW;

	BATTLE_OUT_STATE = BATTLE_OUT_NO;
	BATTLE_IN_STATE = BATTLE_IN_NO;

	BUILDING_STATE = BUILDING_STOP;

	g_bActive = TRUE;

	return 1;
}

int InitDirectSound(HWND hWnd, HINSTANCE hInstance)
{
	//사운드 오브젝트에 메모리 할당.
	for(int i = 0 ; i < MAX_SMUSIC ; i++)
		g_pSMusic[i] = new CSound();
	for(int i = 0 ; i < MAX_SSOUND ; i++)
		g_pSSound[i] = new CSound();

	//다이렉트 사운드를 생성하고 초기화하는 작업.
	CreateDirectSound( hWnd );

	//웨이브 파일을 읽어와서 사운드 버퍼에 담는 작업. 
	g_pSMusic[0]->ReadyBufferFromWaveFile("sound/opening.wav");
	g_pSMusic[1]->ReadyBufferFromWaveFile("sound/spring_theme.wav");
	g_pSMusic[2]->ReadyBufferFromWaveFile("sound/summer_theme.wav");
	g_pSMusic[3]->ReadyBufferFromWaveFile("sound/fall_theme.wav");
	g_pSMusic[4]->ReadyBufferFromWaveFile("sound/winter_theme.wav");
	g_pSMusic[5]->ReadyBufferFromWaveFile("sound/battle_theme.wav");
	
	g_pSSound[0]->ReadyBufferFromWaveFile("sound/click.wav");
	g_pSSound[1]->ReadyBufferFromWaveFile("sound/locktime.wav");

	return 1;
}
DWORD WINAPI ThreadFadeoutMusic(LPVOID temp)
{
	// 음악을 fadeout시킨다.

	CSound *psound;

	psound = (CSound *)temp;

	if(psound->fadeout == TRUE)
		return 0;
	psound->fadeout = TRUE;

	psound->SetSoundVolume(0.9);
	Sleep(300);
	psound->SetSoundVolume(0.7);
	Sleep(300);
	psound->SetSoundVolume(0.5);
	Sleep(300);
	psound->SetSoundVolume(0.3);
	Sleep(300);
	psound->SetSoundVolume(0.1);
	Sleep(300);
	psound->SetSoundVolume(0.0);
	Sleep(1000);

	psound->Stop();
	psound->SetSoundVolume(1.0);
	psound->fadeout = FALSE;

	return 1;
}
int SelectMusic()
{
	DWORD ThreadID;

	if(g_pSMusic[0]->m_bPlaying == TRUE)
		CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[0], 0, &ThreadID);
	if(BATTLE_IN_STATE == BATTLE_IN_NO)
	{
		if(g_pSMusic[5]->m_bPlaying == TRUE)
			CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[5], 0, &ThreadID);
		if(time_.GetSeason() == SPRING)
		{
			if(g_pSMusic[2]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[2], 0, &ThreadID);
			if(g_pSMusic[3]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[3], 0, &ThreadID);
			if(g_pSMusic[4]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[4], 0, &ThreadID);
			g_pSMusic[1]->Play(LOOPING);
		}
		if(time_.GetSeason() == SUMMER)
		{
			if(g_pSMusic[1]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[1], 0, &ThreadID);
			if(g_pSMusic[3]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[3], 0, &ThreadID);
			if(g_pSMusic[4]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[4], 0, &ThreadID);
			g_pSMusic[2]->Play(LOOPING);
		}
		if(time_.GetSeason() == FALL)
		{
			if(g_pSMusic[1]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[1], 0, &ThreadID);
			if(g_pSMusic[2]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[2], 0, &ThreadID);
			if(g_pSMusic[4]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[4], 0, &ThreadID);
			g_pSMusic[3]->Play(LOOPING);
		}
		if(time_.GetSeason() == WINTER)
		{
			if(g_pSMusic[1]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[1], 0, &ThreadID);
			if(g_pSMusic[2]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[2], 0, &ThreadID);
			if(g_pSMusic[3]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[3], 0, &ThreadID);
			g_pSMusic[4]->Play(LOOPING);
		}
	}
	else
	{
		for(int i=0; i<MAX_SMUSIC-1; i++)
		{
			if(g_pSMusic[i]->m_bPlaying == TRUE)
				CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[i], 0, &ThreadID);
		}
		g_pSMusic[5]->Play(LOOPING);
	}

	return 1;
}
int SoundClick()
{
	g_pSSound[0]->Play(NOLOOPING);

	return 1;
}
int SoundLockTime()
{
	g_pSSound[1]->Play(NOLOOPING);

	return 1;
}
int StopAllMusic()
{
	for(int i=0; i<MAX_SMUSIC; i++)
		if(g_pSMusic[i]->m_bPlaying == TRUE)
		{
			DWORD ThreadID;
			hthread = CreateThread(NULL, 0, ThreadFadeoutMusic, (LPVOID)g_pSMusic[i], 0, &ThreadID);
		}
	return 1;
}
int ShowMouse()
{
	CURSORINFO curinfo;
	curinfo.cbSize = sizeof(curinfo);
	GetCursorInfo(&curinfo);

	if(MOUSE_STATE == MOUSE_SHOW)
	{
		if(!(curinfo.flags & CURSOR_SHOWING))
			ShowCursor(TRUE);
	}
	else
	{
		if(curinfo.flags & CURSOR_SHOWING)
			ShowCursor(FALSE);
	}

	mouse_off_x = mouse_x + off_x;
	mouse_off_y = mouse_y + off_y;

	return 1;
}
int Offset_init()
{
	moff_x = GAMESCREEN_WIDTH - SCREEN_WIDTH + INTERFACE2_WIDTH;
	moff_y = GAMESCREEN_HEIGHT - SCREEN_HEIGHT + INTERFACE1_HEIGHT;
	off_x = 0;
	off_y = 0;

	return 1;
}
int SetGamma(float percent)
{
    USHORT mixval = 0;                                  

    if(percent < 0)
          percent = -percent;
    else
          mixval = 0xffff;

     for(int i = 0 ; i < 256 ; i++)
     {
           ddgammachangedramp.red[i] = (USHORT)(ddgammaramp.red[i]+(mixval -  
                                                        ddgammaramp.red[i])*percent);
 
           ddgammachangedramp.green[i] = (USHORT)(ddgammaramp.green[i]+(mixval - 
                                                        ddgammaramp.green[i])*percent);
 
           ddgammachangedramp.blue[i] = (USHORT)(ddgammaramp.blue[i]+(mixval - 
                                                         ddgammaramp.blue[i])*percent);
     }
     lpddgammacontrol->SetGammaRamp(0,&ddgammachangedramp);
     return 1;
}

int ChangeScreenGamma(int effect, BOOL blong, int delay = 70)
{
	if(effect == SCREEN_DARKNESS)
	{
		if(blong == FALSE)
		{
			for(int i=0; i<5; i++)
			{
				gamma -= 0.2;

				SetGamma(gamma);

				Sleep(delay);
			}
		}
		else
		{
			for(int i=0; i<10; i++)
			{
				gamma -= 0.1;

				SetGamma(gamma);

				Sleep(delay);
			}
		}
	}

	return 1;
}
int ReturnScreenGamma(BOOL blong, int delay = 70)
{
	if(blong == FALSE)
	{
		for(int i=0; i<5; i++)
		{
			if(gamma < 0)
				gamma += 0.2;
			else
				gamma -= 0.2;

			SetGamma(gamma);

			Sleep(delay);
		}
	}
	else
	{
		for(int i=0; i<10; i++)
		{
			if(gamma < 0)
				gamma += 0.1;
			else
				gamma -= 0.1;

			SetGamma(gamma);

			Sleep(delay);
		}
	}
	return 1;
}
int CheckLButton()
{
	static int temp = BUTTON_UP;
	if((LBUTTON_STATE2 == LBUTTON_DOWN))
	{
		if(temp == BUTTON_UP)
			temp = BUTTON_DOWN;
		else
			temp = BUTTON_KEEP;
	}
	else
		temp = BUTTON_UP;
	debug_.GetValue("LButton", &temp, 0, lpddsback, 3, ONLY_V1);
	return temp;
}

int CheckSpaceKey()
{
	static int temp = KEY_UP;
	if((KEY_SPACE_STATE2 == KEY_SPACE_DOWN))
	{
		if(temp == KEY_UP)
			temp = KEY_DOWN;
		else
			temp = KEY_KEEP;
	}
	else
		temp = KEY_UP;
	
	return temp;
}

int CheckMKey()
{
	static int temp = KEY_UP;
	if((KEY_M_STATE2 == KEY_M_DOWN))
	{
		if(temp == KEY_UP)
			temp = KEY_DOWN;
		else
			temp = KEY_KEEP;
	}
	else
		temp = KEY_UP;
	return temp;
}

int CheckIKey()
{
	static int temp = KEY_UP;
	if((KEY_I_STATE2 == KEY_I_DOWN))
	{
		if(temp == KEY_UP)
			temp = BUTTON_DOWN;
		else
			temp = BUTTON_KEEP;
	}
	else
		temp = KEY_UP;
	return temp;
}

int CheckSKey()
{
	static int temp = KEY_UP;
	if((KEY_S_STATE2 == KEY_S_DOWN))
	{
		if(temp == KEY_UP)
			temp = KEY_DOWN;
		else
			temp = KEY_KEEP;
	}
	else
		temp = KEY_UP;
	return temp;
}

int CheckESCKey()
{
	static int temp = KEY_UP;
	if((KEY_ESC_STATE2 == KEY_ESC_DOWN))
	{
		if(temp == KEY_UP)
			temp = KEY_DOWN;
		else
			temp = KEY_KEEP;
	}
	else
		temp = KEY_UP;
	return temp;
}

int CheckInput()
{
	if(CheckLButton() == BUTTON_DOWN)
	{
		object_.ShowDialog();

		domestic_.ShowDialog();

		diplomatic_.ShowDialog();
		
		building_.ShowDialog();

		// Menu에서 나가기를 눌렀으면 GO_OUT을 리턴
		if(mainmenu_.ShowMainMenu(TRUE) == GO_OUT)
			return GO_OUT;

		diplomatic_.SelectSpecies();

		RECT pause_rect = {63, 8, 157, 42};

		if(CheckRect(&pause_rect, mouse_x, mouse_y))
			CTime::SwitchPause();

		RECT screen_gameinfo_rect = {438, 13, 473, 33};

		if(CheckRect(&screen_gameinfo_rect, mouse_x, mouse_y))
		{
			SoundClick();

			if(SCREEN_STATE == SCREEN_GAMEINFO)
			{
				if(BATTLE_IN_STATE == BATTLE_IN_NO)
				{	
					SCREEN_STATE = SCREEN_GAME;
					SCROLL_STATE = SCROLL_RUN;
				}
			}
			else
			{
				SCREEN_STATE = SCREEN_GAMEINFO;
				SCROLL_STATE = SCROLL_STOP;
			}
		}	

		RECT screen_map_rect = {481, 12, 514, 34};

		if(CheckRect(&screen_map_rect, mouse_x, mouse_y))
		{
			SoundClick();

			if(SCREEN_STATE == SCREEN_MAP)
			{
				if(BATTLE_IN_STATE == BATTLE_IN_NO)
				{
					SCREEN_STATE = SCREEN_GAME;
					SCROLL_STATE = SCROLL_RUN;
				}
			}
			else
			{
				SCREEN_STATE = SCREEN_MAP;
				SCROLL_STATE = SCROLL_STOP;
			}
		}	

		RECT screen_item_rect = {522, 11, 557, 34};

		if(CheckRect(&screen_item_rect, mouse_x, mouse_y))
		{
			SoundClick();

			if(SCREEN_STATE == SCREEN_ITEM)
			{
				if(BATTLE_IN_STATE == BATTLE_IN_NO)
				{
					SCREEN_STATE = SCREEN_GAME;
					SCROLL_STATE = SCROLL_RUN;
				}
			}
			else
			{
				SCREEN_STATE = SCREEN_ITEM;
				SCROLL_STATE = SCROLL_STOP;
			}
		}	
	}
	

	// ESC -> MainMenu
	if(CheckESCKey() == KEY_DOWN)
	{
		SoundClick();
		// Menu에서 나가기를 눌렀으면 GO_OUT을 리턴
		if(mainmenu_.ShowMainMenu(TRUE, TRUE) == GO_OUT)
			return GO_OUT;
	}

	if(CheckSpaceKey() == KEY_DOWN)
		CTime::SwitchPause();

	if(CheckMKey() == KEY_DOWN)
	{
		SoundClick();

		if(SCREEN_STATE == SCREEN_MAP)
		{
			if(BATTLE_IN_STATE == BATTLE_IN_NO)
			{
				SCREEN_STATE = SCREEN_GAME;
				SCROLL_STATE = SCROLL_RUN;
			}
		}
		else
		{
			SCREEN_STATE = SCREEN_MAP;
			SCROLL_STATE = SCROLL_STOP;
		}
	}

	if(CheckSKey() == KEY_DOWN)
	{
		SoundClick();

		if(SCREEN_STATE == SCREEN_GAMEINFO)
		{
			if(BATTLE_IN_STATE == BATTLE_IN_NO)
			{
				SCREEN_STATE = SCREEN_GAME;
				SCROLL_STATE = SCROLL_RUN;
			}
		}
		else
		{
			SCREEN_STATE = SCREEN_GAMEINFO;
			SCROLL_STATE = SCROLL_STOP;
		}
	}

	if(CheckIKey() == KEY_DOWN)
	{
		SoundClick();

		if(SCREEN_STATE == SCREEN_ITEM)
		{
			if(BATTLE_IN_STATE == BATTLE_IN_NO)
			{
				SCREEN_STATE = SCREEN_GAME;
				SCROLL_STATE = SCROLL_RUN;
			}
		}
		else
		{
			SCREEN_STATE = SCREEN_ITEM;
			SCROLL_STATE = SCROLL_STOP;
		}
	}


	return 1;

}

LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
// this is the main message handler of the system
PAINTSTRUCT		ps;		// used in WM_PAINT
HDC				hdc;	// handle to a device context

// what is the message 
switch(msg)
	{	
	case WM_CREATE: 
        {
		// do initialization stuff here
        // return success
		return(0);
		} break;
	case WM_DESTROY: 
		{
		//Game_Shutdown();
		// kill the application, this sends a WM_QUIT message 
		PostQuitMessage(0);

        // return success
		return(0);
		} break;
	case WM_SIZE:
        // Check to see if we are losing our window...
        if( SIZE_MAXHIDE==wparam || SIZE_MINIMIZED==wparam )
		{
			// 외부로 나가면 자원을 정리한다. 안하면
			// 해제가 안되서 게임이 진행하는 동안 계속 쌓인다.
			screen_.Screen_Shutdown();
			interface_.Interface_Shutdown();
			story_.Story_Shutdown();
			mainmenu_.MainMenu_Shutdown();

            g_bActive = FALSE;
		}
        else
            g_bActive = TRUE;
        break;
	case WM_MOUSEMOVE:
		{
			if(MOUSE_STATE == MOUSE_SHOW)
			{
				mouse_y = HIWORD(lparam);
				mouse_x = LOWORD(lparam);
			}
			return 0;
		}
	case WM_TIMER:
		{
			if(window_closed)
				return 0;

			if(g_bActive == FALSE)
				return 0;

			// 게임이 정지가 아닐 때 시간에 민감한 문제들을 
			// 해결한다.
			if(GAME_STATE == GAME_RUN)
			{
				domestic_.Resource_Init();

				story_.CheckStory();

				event_.CheckEvent();

				diplomatic_.ComputeSpecies();
	
				domestic_.CoputeAnts();
				domestic_.ProduceResource();
				if((time_.GetDay() == 0))
					diplomatic_.GetPresent();
				domestic_.ConsumeFood();
				domestic_.CoputeAnts();
				if(time_.GetDay() == 0)
				{
					domestic_.hire();
					domestic_.CoputeAnts();
				}
				if((time_.GetDay() == 0) && ((time_.GetMonth3() % 2) == 0))
				{
					domestic_.ProduceAnts();
					domestic_.CoputeAnts();
				}
				domestic_.ComputeOther();

				domestic_.CheckPrintTime();

				building_.CheckBuildingTime();		

				objdialog_.CheckLabTime();

				objdialog_.CheckLibraryTime();

				item_.CheckItemTime();
				if((time_.GetDay() % 2) == 0)
					item_.SearchItem();

				battle_.CheckReachTime();
				battle_.CheckReturnTime();

				battle_.SpeDecideAttack();

				battle_.BattleOutside();
				battle_.BattleInside();

				info_.MoveStackMem();

				time_.TickTime();

				domestic_.Resource_Final();
			}

			return 0;
		}
	case WM_KEYDOWN:
		{
			if(wparam == VK_SPACE)
				KEY_SPACE_STATE2 = KEY_SPACE_DOWN;
			if(wparam == VK_ESCAPE)
				KEY_ESC_STATE2 = KEY_ESC_DOWN;
			if(wparam == 'M')
				KEY_M_STATE2 = KEY_M_DOWN;
			if(wparam == 'I')
				KEY_I_STATE2 = KEY_I_DOWN;
			if(wparam == 'S')
				KEY_S_STATE2 = KEY_S_DOWN;

			return 0;
		}
	case WM_KEYUP:
		{
			if(wparam == VK_SPACE)
				KEY_SPACE_STATE2 = KEY_SPACE_UP;
			if(wparam == VK_ESCAPE)
				KEY_ESC_STATE2 = KEY_ESC_UP;
			if(wparam == 'M')
				KEY_M_STATE2 = KEY_M_UP;
			if(wparam == 'I')
				KEY_I_STATE2 = KEY_I_UP;
			if(wparam == 'S')
				KEY_S_STATE2 = KEY_S_UP;
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			LBUTTON_STATE2 = LBUTTON_DOWN;
			
			return 0;
		}
	case WM_LBUTTONUP:
		{
			LBUTTON_STATE2 = LBUTTON_UP;

			return 0;
		}
	case WM_CLOSE:
		{
			return (DefWindowProc(hwnd, msg, wparam, lparam));
		}
	default:break;

    } // end switch

// process any messages that we didn't take care of 
return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc


// GAME_MAIN /////////////////////////////////////////////////////

int Game_Main(void *parms = NULL, int num_parms = 0)
{
	// this is the main loop of the game, do all your processing
	// here

	POINT mousept;

///////////////////////////////////////기타////////////////////////////////////////
	if(window_closed)
		return 0;

	if(g_bActive == FALSE)
		return 0;

	// 배경 음악을 선택한다.
	SelectMusic();

	// 마우스를 지정된 게임중 사용될 마우스 이미지로 바꾼다.
	SetCursor(LoadCursor(main_instance, MAKEINTRESOURCE(CURSOR_CROSSHAIR)));

	// backbuffer를 지운다.
	DDraw_Fill_Surface(lpddsback, 0);

	// fps를 일정하게 하기 위한 함수(마지막 부분에 짝이 있다.)
	Start_Clock();

	// 마우스 위치를 읽어 스크롤한다.
	screen_.Scroll();
	
	// 움직일 수 있는 모든 object를 움직임을 계산한다.
	object_.MoveObjBob();

	// 개미굴을 따라 움직이는 개미 중 실제로 뿌려줄 개미를 결정한다.
	object_.ShowWanderingAnts();

///////////////////////////////////////출력//////////////////////////////////////////
	// UI와 Obj를 제외한 게임 화면(개미굴)을 출력한다.
	screen_.DrawScreen();

	// 아이템창이거나 게임정보창이면 적절한 화면을 뿌려준다.
	item_.PrintItem();
	info_.PrintGmaeInfo();

	// 모든 object를 그린다.
	object_.DrawObjBob();

	// map창에서 전투가 일어나는 곳의 전투연기를 그린다.
	battle_.DrawBattleDirt();

	// UI를 그린다.
	interface_.DrawInterface();

	// 내정과 관련된 명령창을 UI에 그리고 자원량을 표시한다.
	domestic_.PrintDomMenu();
	domestic_.PrintResource();

	// 외교와 관련된 명령창을 UI에 그린다.
	diplomatic_.PrintDipMenu();

	// 건설과 관련된 명령창을 UI에 그린다.
	building_.PrintBuildingMenu();
	
	// 마우스가 올라간 obj의 이름을 표시한다.
	object_.PrintObjName();

	// map창에서 종족영역 위에 마우스가 올라가면 그에 대한 정보를 표시
	diplomatic_.PrintMapinfo();

	// 전투가 발생했다면 전투 정보도 표시
	battle_.PrintBattleInfo();

	// 시간과 관련된 정보를 UI에 표시
	time_.DrawMonth3();
	time_.DrawSun();
	time_.PrintSeason();

	// 일시 정지면 하단에 표시
	time_.PrintPause();
	
	// 전투가 발생했다면 실제로 수행
	battle_.PrintBattleBreakOut();
	// 적이 쳐들어 오는지 아군이 진격중인지, 퇴각중인지 표시
	battle_.PrintSpeCome();
	battle_.PrintPlayerGo();
	battle_.PrintPlayerCome();

	// 디버그 용
#ifdef TEST
	Test();
	debug_.PrintDbInfo();
#endif

	// 마우스를 표시하거나 숨긴다.
	ShowMouse();
	
	///////////////////////////////////////입력/////////////////////////////////////////

	// 다른 윈도우에 의해 마우스 위치를 파악하지 못하는 것을 방지(다른 윈도우 위에 커서가 있으면
	// 스크롤이 안됨)
	GetCursorPos(&mousept);
	SendMessage(main_window_handle, WM_MOUSEMOVE, NULL, MAKELONG(mousept.x, mousept.y));

	if(CheckInput() == GO_OUT)
		return GO_OUT;	// 메뉴에서 나가기를 클릭한 경우

	// 다른 윈도우에 의해 마우스 버튼 누름 중지를 파악하지 못하는 것을 방지
	SendMessage(main_window_handle, WM_LBUTTONUP, NULL, NULL);

	//////////////////////플립(다이얼로그를 위해 blt으로 한다.)//////////////////////////////

	HRESULT hRet;

	hRet = lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);      // pointer to DDBLTFX holding info
	if((hRet == DDERR_SURFACELOST) && (g_bActive == TRUE))
	{
		MSG msg;
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
		mainmenu_.reload();
		story_.reload();
	}

	Wait_Clock(30);

// return success or failure or your own return code here
return(1);

} // end Game_Main

////////////////////////////////////////////////////////////

int Game_Init(void *parms = NULL, int num_parms = 0)
{
// this is called once after the initial window is created and
// before the main event loop is entered, do all your initialization
// here


	// parms가 NULL이 아니면 게임 오버되어 새로 시작하거나 게임 중 새로 시작할 때

	if(parms == NULL)
	{
		srand(Start_Clock());
		
		// tick를 설정한다.
		SetTimer(main_window_handle, 1, HALFTICK, NULL);
		
		// DirectX 초기화
		DDraw_Init(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

		// 화면 전체 클리퍼 설정
		RECT screen_rect = {0,0,screen_width,screen_height};
		lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);

		HRESULT hr;

		// Create a clipper when using GDI to draw on the primary surface 
		if( FAILED( hr = lpdd->CreateClipper( 0, &pClipper, NULL ) ) )
			return hr;

		pClipper->SetHWnd( 0, main_window_handle );

		if( FAILED( hr = lpddsprimary->SetClipper( pClipper ) ) )
			return hr;

		InitDirectSound(main_window_handle, main_instance);

		g_pSMusic[0]->Play(LOOPING);	//메뉴 음악은 시작하면서 바로 출력한다.

		lpddsprimary->QueryInterface(IID_IDirectDrawGammaControl,(void**)&lpddgammacontrol);
		lpddgammacontrol->GetGammaRamp(0,&ddgammaramp);
	}

	Global_Init();

	Offset_init();

	mouse_x = screen_height/2;
	mouse_y = screen_height/2;

	// 클래스 초기화
	object_.Obj_Init();
	objdialog_.ObjDialog_Init();
	screen_.Screen_Init();
	time_.Time_Init();
	event_.Event_Init();
	domestic_.Domestic_Init();
	story_.Story_Init();
	interface_.Interface_Init();
	item_.Item_Init();
	building_.Building_Init();
	// 메뉴는 초기화 안함
	if(parms == NULL)
		mainmenu_.MainMenu_Init();
	diplomatic_.Diplomatic_Init();
	battle_.Battle_Init();
	info_.Info_Init();
	datafile_.DataFile_Init();

	CPlayer::Player_Init();
	CSpecies::Species_Init();

// return success or failure or your own return code here
return 1;

} // end Game_Init

/////////////////////////////////////////////////////////////

int Game_Shutdown(void *parms, int num_parms)
{
// this is called after the game is exited and the main event
// loop while is exited, do all you cleanup and shutdown here

	// parms가 NULL이 아니면 게임 오버되어 새로 시작하거나 게임 중 새로 시작할 때

	object_.Obj_Shutdown();
	objdialog_.ObjDialog_Shutdown();
	screen_.Screen_Shutdown();
	domestic_.Domestic_Shutdown();
	time_.Time_Shutdown();
	interface_.Interface_Shutdown();
	item_.Item_Shutdown();
	building_.Building_Shutdown();
	if(parms == NULL)
		mainmenu_.MainMenu_Shutdown();
	diplomatic_.Diplomatic_Shutdown();
	event_.Event_Shutdown();
	
	story_.Story_Shutdown();
	battle_.Battle_Shutdown();
	info_.Info_Shutdown();
	datafile_.DataFile_Shutdown();
	CPlayer::Player_Shutdown();
	CSpecies::Species_Shutdown();
	
	if(parms == NULL)
	{
		for(int i=0; i<MAX_SMUSIC; i++)
			g_pSMusic[i]->Stop();

		for(int i=0; i<MAX_SSOUND; i++)
			g_pSSound[i]->Stop();


		DestroyDirectSound();

		pClipper->Release();

		lpddgammacontrol->Release();

		KillTimer(main_window_handle, 1);

		DDraw_Shutdown();
	}
	
// return success or failure or your own return code here
return 1;

} // end Game_Shutdown

// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hwnd;	 // generic window handle
	MSG		   msg;		 // generic message

	// first fill in the window class stucture
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
							  CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(hinstance, MAKEINTRESOURCE(CURSOR_CROSSHAIR)); //LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

	// save hinstance in global
	main_instance = hinstance;

	// register the window class
	if (!RegisterClassEx(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindowExA(NULL,                  // extended style
								WINDOW_CLASS_NAME,     // class
								"The Kingdom of Ants - Version 1.0", // title
								WS_POPUP | WS_VISIBLE,
					 			0,0,	  // initial x,y
								400,300,  // initial width, height
								NULL,	  // handle to parent 
								NULL,	  // handle to menu
								hinstance,// instance of this application
								NULL)))	// extra creation parms
	return(0);

	// save main window handle
	main_window_handle = hwnd;

	// initialize game here
	Game_Init();

	mainmenu_.ShowMainMenu(FALSE);

	// enter main event loop
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
		if (msg.message == WM_QUIT)
		{
			break;
		}

		if(GAME_STATE == GAME_OVER)
			mainmenu_.ShowMainMenu(FALSE);
		
		// main game processing goes here
		Game_Main();

	} // end while

	// closedown game here
	Game_Shutdown();

	// return to Windows like this
	return (int)msg.wParam;

} // end WinMain

///////////////////////////////////////////////////////////

