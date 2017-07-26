// 많은 함수에서 공유하고 시간에 따라 변화하는 변수

#pragma once

enum {GAME_RUN, GAME_PAUSE, GAME_OVER}GAME_STATE;

enum {CHAP_1 ,CHAP_2 ,CHAP_3 ,CHAP_4}CHAPTER;

enum {SCREEN_GAME, SCREEN_MAP, SCREEN_ITEM, SCREEN_GAMEINFO}SCREEN_STATE;
enum {MOUSE_SHOW, MOUSE_HIDE}MOUSE_STATE;

enum {SCROLL_RUN, SCROLL_STOP}SCROLL_STATE;
enum {LBUTTON_RUN, LBUTTON_STOP}LBUTTON_STATE;
enum {KEY_SPACE_RUN, KEY_SPACE_STOP}KEY_SPACE_STATE;
enum {KEY_S_RUN, KEY_S_STOP}KEY_S_STATE;
enum {KEY_M_RUN, KEY_M_STOP}KEY_M_STATE;
enum {KEY_I_RUN, KEY_I_STOP}KEY_I_STATE;
enum {KEY_ESC_RUN, KEY_ESC_STOP}KEY_ESC_STATE;

enum {LBUTTON_DOWN, LBUTTON_UP}LBUTTON_STATE2;
enum {KEY_I_DOWN, KEY_I_UP}KEY_I_STATE2;
enum {KEY_M_DOWN, KEY_M_UP}KEY_M_STATE2;
enum {KEY_S_DOWN, KEY_S_UP}KEY_S_STATE2;
enum {KEY_SPACE_DOWN, KEY_SPACE_UP}KEY_SPACE_STATE2;
enum {KEY_ESC_DOWN, KEY_ESC_UP}KEY_ESC_STATE2;

enum {BATTLE_OUT_BREAK, BATTLE_OUT_NO}BATTLE_OUT_STATE;
enum {BATTLE_IN_BREAK, BATTLE_IN_INIT ,BATTLE_IN_NO}BATTLE_IN_STATE;

enum {BUILDING_STOP, BUILDING_RUN}BUILDING_STATE;

enum {FADE_IN, FADE_OUT, FADE_NONE}FADE_STATE;

HWND main_window_handle = NULL;	// globally track main window
HINSTANCE main_instance = NULL;	// globally track hinstance

int off_x;						// 게임 스크린에서 offset
int off_y;
int moff_x;						// 게임 스크린에서 최대 offset
int moff_y;

int mouse_x,					// used to track mouse
    mouse_y;
int mouse_off_x,                    
    mouse_off_y;

HANDLE hthread = NULL;			// CStory, CBuilding, CBattle,
								// CEvent에서 사용하는 thread의 핸들

int window_closed = 0;			 // tracks if window is closed

HANDLE hfile;
DWORD dwWritten;

HWND hWndDlg_gameover = NULL;
