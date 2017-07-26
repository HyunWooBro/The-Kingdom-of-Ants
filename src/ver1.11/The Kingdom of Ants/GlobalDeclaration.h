// define 으로 만들때는 여러 곳에서 쓰일 때, 숫자만으로는 의미 파악이 안될 때
// , 복잡해서 간략하게 나타낼때 등

#pragma once

#include <windows.h>
#include <stdio.h>
#include <ddraw.h>
#include "Sound.h"

// GLOBALVALUE and GLOBALFUNCTION's EXTERN DECLATION //////////////////////

#ifndef MAIN_PASS		// main.cpp 에서는 여기를 무시한다.

// GLOBALVALUE ////////////////////////////////////

extern enum {GAME_RUN, GAME_PAUSE, GAME_OVER}GAME_STATE;

extern enum {CHAP_1 ,CHAP_2 ,CHAP_3 ,CHAP_4}CHAPTER;

extern enum {SCREEN_GAME, SCREEN_MAP, SCREEN_ITEM, SCREEN_GAMEINFO}SCREEN_STATE;
extern enum {MOUSE_SHOW, MOUSE_HIDE}MOUSE_STATE;

extern enum {SCROLL_RUN, SCROLL_STOP}SCROLL_STATE;
extern enum {LBUTTON_RUN, LBUTTON_STOP}LBUTTON_STATE;
extern enum {KEY_SPACE_RUN, KEY_SPACE_STOP}KEY_SPACE_STATE;
extern enum {KEY_S_RUN, KEY_S_STOP}KEY_S_STATE;
extern enum {KEY_M_RUN, KEY_M_STOP}KEY_M_STATE;
extern enum {KEY_I_RUN, KEY_I_STOP}KEY_I_STATE;
extern enum {KEY_ESC_RUN, KEY_ESC_STOP}KEY_ESC_STATE;

extern enum {LBUTTON_DOWN, LBUTTON_UP}LBUTTON_STATE2;
extern enum {KEY_I_DOWN, KEY_I_UP}KEY_I_STATE2;
extern enum {KEY_M_DOWN, KEY_M_UP}KEY_M_STATE2;
extern enum {KEY_S_DOWN, KEY_S_UP}KEY_S_STATE2;
extern enum {KEY_SPACE_DOWN, KEY_SPACE_UP}KEY_SPACE_STATE2;
extern enum {KEY_ESC_DOWN, KEY_ESC_UP}KEY_ESC_STATE2;

extern enum {BATTLE_OUT_BREAK, BATTLE_OUT_NO}BATTLE_OUT_STATE;
extern enum {BATTLE_IN_BREAK, BATTLE_IN_INIT ,BATTLE_IN_NO}BATTLE_IN_STATE;

extern enum {BUILDING_STOP, BUILDING_RUN}BUILDING_STATE;

extern enum {FADE_IN, FADE_OUT, FADE_NONE}FADE_STATE;

extern HWND main_window_handle;
extern HINSTANCE main_instance;

extern int off_x;
extern int off_y;
extern int moff_x;
extern int moff_y;

extern int mouse_x;
extern int mouse_y;
extern int mouse_off_x;                    
extern int mouse_off_y;

extern HANDLE hthread;

extern int window_closed;

extern HANDLE hfile;
extern DWORD dwWritten;

extern HWND hWndDlg_gameover;

// GLOBALFUNCTION ////////////////////////////////

extern int WaitDialog();
extern int CheckRect(RECT *rect, int point_x, int point_y, BOOL screen_only = FALSE);
extern int DDraw_Text(char *text, 
			   int x,
			   int y, 
			   int size, 
			   LPDIRECTDRAWSURFACE7 lpdds, 
			   COLORREF fcolor, 
			   int fmode, 
			   COLORREF bkcolor, 
			   int bkmode,
			   char *fonttype = "굴림");
extern int DDraw_Text_Rect(char *text, 
			   RECT *text_rect,
			   int size, 
			   LPDIRECTDRAWSURFACE7 lpdds, 
			   COLORREF fcolor, 
			   int fmode, 
			   COLORREF bkcolor, 
			   int bkmode,
			   char *fonttype = "굴림");
extern int HideAllDialog();
extern int ShowAllDialog();
extern int CloseAllDialog(int flag = 0);
extern int Select_State_Rand(int state1, int prob1,            
					  int state2, int prob2,    
					  int state3, int prob3,    
					  int state4, int prob4,    
					  int state5, int prob5,
				      int state6, int prob6);
extern BOOL ErrorMessage(HWND hwnd , char *str);
extern INT_PTR CALLBACK GameoverDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

#endif

// DEFINES, ENUMS and etc.////////////////////////////////////////////////

// CMainMenu ///////////////////////////////////////
#define MAX_MAINMENU	7

#define CHEAT_SPEED_1X	"orginal speed"
#define CHEAT_SPEED_2X	"need for speed"
#define CHEAT_SPEED_3X	"i have no time"
#define CHEAT_SPEED_4X	"flesh"

// CDebug ///////////////////////////////////////////
#define MAX_DINFO	25				// 최대 표시할 정보
#define ONLY_V1		1				// 인자 v1만 사용

// CItem ////////////////////////////////////////////
#define MAX_ITEM 10					// 최대 아이템

#define DDRAW_TEXT_RECT_ITEM(buffer, prect)	DDraw_Text_Rect(buffer,&prect,11,lpddsback,RGB(255,255,255),DT_LEFT | DT_WORDBREAK,NULL,TRANSPARENT)

#define DESCRIPTION_X(x)	(x+54)
#define DESCRIPTION_Y(y)	(y+INTERFACE1_HEIGHT+5)
#define DESCRIPTION_CX(cx)	(cx+54+177)
#define DESCRIPTION_CY(cy)	(cy+INTERFACE1_HEIGHT+64)

#define PICTURE_X(x)		(x+7)
#define PICTURE_Y(y)		(y+INTERFACE1_HEIGHT+7)
#define PICTURE_CX(cx)		(cx+7+40)
#define PICTURE_CY(cy)		(cy+INTERFACE1_HEIGHT+7+50)

#define ITEM_3_RELEASE	0x00000001
#define ITEM_1_RELEASE	0x00000002
#define ITEM_8_RELEASE	0x00000004
#define ITEM_9_RELEASE	0x00000008

enum WHERE_ITEM{PLAYER, BEE, SHORT_ANT, GRASSHOPPER, FINGER, FIELD_NORMAL, SELLER}; 

// CTime //////////////////////////////////////////
enum SEASON{SPRING, SUMMER, FALL, WINTER};

#define PRINT_SEASON_X	20
#define PRINT_SEASON_Y	6

#define PRINT_PAUSE_X	(screen_width/2 - 50)
#define PRINT_PAUSE_Y	(screen_height - 25)

#define PAUSE_SELLER		0
#define PAUSE_DIP			1

// CObject /////////////////////////////////////////
#define MAX_OBJECT 42

#define STRANGE_STONE_DIALOG				0
#define BUILDING_QUEEN_DIALOG				1
#define BUILDING_EGG_DIALOG					2
#define BUILDING_WAREHOUSE_DIALOG			3
#define BUILDING_UNDER_CONSTRUCTION_DIALOG	4
#define BUILDING_LIBRARY_DIALOG				5
#define BUILDING_DEPOSITORY_DIALOG			6
#define BUILDING_LAB_DIALOG					7
#define BUILDING_TRAINING_DIALOG			8
#define BUILDING_MUSHROOM_DIALOG			9
#define BUILDING_HIRED_1_DIALOG				10
#define BUILDING_HIRED_2_DIALOG				11
#define BUILDING_CHURCH_DIALOG				12
#define BUILDING_ART_DIALOG					13
#define WORKER_DIALOG						14
#define SOLDIER_DIALOG						15
#define QUEEN_DIALOG						16
#define ADVISER_DIALOG						17
#define NANNY_DIALOG						18
#define SCIENTIST_DIALOG					19
#define MUSHROOM_ANT_DIALOG					20
#define CHURCH_ANT_DIALOG					21
#define HIRED_1_DIALOG						22
#define HIRED_2_DIALOG						23
#define TRAINING_ANT_DIALOG					24
#define ART_ANT_DIALOG						25
#define APHID_DIALOG						26
#define EVENT_SELLER_DIALOG					27

#define OBJARRAY_MAP_SNAIL					0
#define OBJARRAY_MAP_GRASSHOPPER			1
#define OBJARRAY_MAP_SHORT_ANT				2
#define OBJARRAY_MAP_BEE					3
#define OBJARRAY_MAP_RED_ANT				4
#define OBJARRAY_MAP_PLAYER					5
#define OBJARRAY_BUILDING_STRANGE_STONE		6
#define OBJARRAY_BUILDING_WAREHOUSE			7
#define OBJARRAY_BUILDING_QUEEN				8
#define OBJARRAY_BUILDING_EGG				9
#define OBJARRAY_BUILDING_LIBARAY			10
#define OBJARRAY_BUILDING_DEPOSITORY		11
#define OBJARRAY_BUILDING_LAB				12
#define OBJARRAY_BUILDING_TRAINING			13
#define OBJARRAY_BUILDING_MUSHROOM			14
#define OBJARRAY_BUILDING_HIRED_1			15
#define OBJARRAY_BUILDING_HIRED_2			16
#define OBJARRAY_BUILDING_CHURCH			17
#define OBJARRAY_BUILDING_ART				18
#define OBJARRAY_WORKER_ANT_1				19
#define OBJARRAY_WORKER_ANT_2				20
#define OBJARRAY_WORKER_ANT_3				21
#define OBJARRAY_WORKER_ANT_4				22
#define OBJARRAY_WORKER_ANT_5				23
#define OBJARRAY_SOLDIER_ANT_1				24
#define OBJARRAY_SOLDIER_ANT_2				25
#define OBJARRAY_SOLDIER_ANT_3				26
#define OBJARRAY_SOLDIER_ANT_4				27
#define OBJARRAY_SOLDIER_ANT_5				28
#define OBJARRAY_QUEEN						29
#define OBJARRAY_ADVISER					30
#define OBJARRAY_NANNY						31
#define OBJARRAY_SCIENTIST					32
#define OBJARRAY_MUSHROOM_ANT				33
#define OBJARRAY_CHURCH_ANT					34
#define OBJARRAY_HIRED_1					35
#define OBJARRAY_HIRED_2					36
#define OBJARRAY_TRAING_ANT					37
#define OBJARRAY_ART_ANT_1					38
#define OBJARRAY_ART_ANT_2					39
#define OBJARRAY_AHPID						40
#define OBJARRAY_SELLER						41

enum OBJSCREEN{OBJSCREEN_GAME, OBJSCREEN_MAP, OBJSCREEN_ITEM, OBJSCREEN_STATUS, OBJSCREEN_HIDE};

#define OBJ_NAME_X		485
#define OBJ_NAME_Y		460

// CObjDialog ///////////////////////////////////
#define MAX_LAB			13
#define MAX_LIBRARY		9

#define LAB_1_DONE		0x00000001
#define LAB_2_DONE		0x00000002
#define LAB_3_DONE		0x00000004
#define LAB_4_DONE		0x00000008
#define LAB_5_DONE		0x00000010
#define LAB_6_DONE		0x00000020
#define LAB_7_DONE		0x00000040
#define LAB_8_DONE		0x00000080
#define LAB_9_DONE		0x00000100
#define LAB_10_DONE		0x00000200
#define LAB_11_DONE		0x00000400
#define LAB_12_DONE		0x00000800
#define LAB_13_DONE		0x00001000
#define LAB_UPGRADED	0x10000000

#define LAB_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY)

#define BOOK_3_RELEASE		0x00000001
#define BOOK_4_RELEASE		0x00000002
#define BOOK_5_RELEASE		0x00000004
#define BOOK_6_RELEASE		0x00000008
#define BOOK_7_RELEASE		0x00000010
#define BOOK_8_RELEASE		0x00000020
#define BOOK_9_RELEASE		0x00000040

// CEvent /////////////////////////////////////////
#define MAX_EVENT 3

#define LENGTH_TIME_EVENT_FIGHT		((30 + rand()%21) * UNIT_PER_DAY * UNIT_PER_TICK)
#define LENGTH_TIME_EVENT_SELLER	((40 + rand()%21) * UNIT_PER_DAY * UNIT_PER_TICK)
#define LENGTH_TIME_EVENT_DIALOG	((15 + rand()%21) * UNIT_PER_DAY * UNIT_PER_TICK)

#define EVENTARRAY_FIGHT		0
#define EVENTARRAY_SELLER		1
#define EVENTARRAY_DIALOG		2

#define EVENT_DIALOG_1_DONE		0x00000001
#define EVENT_DIALOG_2_DONE		0x00000002
#define EVENT_DIALOG_3_DONE		0x00000004
#define EVENT_DIALOG_4_DONE		0x00000008
#define EVENT_DIALOG_5_DONE		0x00000010
#define EVENT_DIALOG_6_DONE		0x00000020
#define EVENT_DIALOG_7_DONE		0x00000040
#define EVENT_DIALOG_8_DONE		0x00000080
#define EVENT_DIALOG_9_DONE		0x00000100
#define EVENT_DIALOG_10_DONE	0x00000200

enum EVENT_TYPE{EVENT_FIGHT, EVENT_SELLER, EVENT_DIALOG};

// CStory /////////////////////////////////////////////
#define CHAP_1_INTRO_DONE	0x00000001
#define CHAP_1_2_DONE		0x00000002
#define CHAP_1_3_DONE		0x00000004
#define CHAP_1_4_DONE		0x00000008
#define CHAP_1_5_DONE		0x00000010
#define CHAP_2_INTRO_DONE	0x00000100
#define CHAP_2_2_DONE		0x00000200
#define CHAP_2_3_DONE		0x00000400
#define CHAP_2_4_DONE		0x00000800
#define CHAP_3_INTRO_DONE	0x00001000
#define CHAP_3_2_DONE		0x00002000
#define CHAP_3_3_DONE		0x00004000
#define CHAP_4_INTRO_DONE	0x00100000

#define LENGTH_TIME_LEAVE	(10 * UNIT_PER_DAY * UNIT_PER_TICK)

// CDomestic //////////////////////////////////////////
#define MAX_DOM 3

#define DOM_TITLE_X		605
#define DOM_TITLE_Y		67

#define DOM_WORKER_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY)
#define DOM_SOLDIER_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY)
#define DOM_QUEEN_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY)

#define _3C3_123	if((firstcheck == BST_UNCHECKED) && (secondcheck == BST_UNCHECKED) && (thirdcheck == BST_UNCHECKED))
#define _3C2_12		if((firstcheck == BST_UNCHECKED) && (secondcheck == BST_UNCHECKED) && (thirdcheck == BST_CHECKED))
#define _3C2_13		if((firstcheck == BST_UNCHECKED) && (secondcheck == BST_CHECKED) && (thirdcheck == BST_UNCHECKED))
#define _3C2_23		if((firstcheck == BST_CHECKED) && (secondcheck == BST_UNCHECKED) && (thirdcheck == BST_UNCHECKED))
#define _3C1_1		if((firstcheck == BST_UNCHECKED) && (secondcheck == BST_CHECKED) && (thirdcheck == BST_CHECKED))
#define _3C1_2		if((firstcheck == BST_CHECKED) && (secondcheck == BST_UNCHECKED) && (thirdcheck == BST_CHECKED))
#define _3C1_3		if((firstcheck == BST_CHECKED) && (secondcheck == BST_CHECKED) && (thirdcheck == BST_UNCHECKED))
#define _3C0_X		if((firstcheck == BST_CHECKED) && (secondcheck == BST_CHECKED) && (thirdcheck == BST_CHECKED))

#define FIRST_PANEL		1
#define SECOND_PANEL	2
#define THIRD_PANEL		3

#define MAX_PANEL		10

#define INIT_NUM_WORKER		83
#define INIT_NUM_SOLDIER	32

#define NUM_CONSUME_WORKER	1
#define NUM_CONSUME_SOLDIER	2.5
#define NUM_CONSUME_HIRED	4
#define NUM_CONSUME_FINGER	200

#define INIT_FOOD		9500
#define INIT_TIMBER		1200
#define INIT_MINERAL	0

#define INIT_MAX_FOOD		400000
#define INIT_MAX_TIMBER		100000
#define INIT_MAX_MINERAL	50000
#define UPGRADE_MAX_FOOD	1200000
#define UPGRADE_MAX_TIMBER	300000
#define UPGRADE_MAX_MINERAL	150000

#define NUM_MUSHROOM_PRODUCE		(7 + rand()%2)
#define NUM_MUSHROOM_COST_TIMBER	0.5

#define NUM_MINE_PRODUCE			10

#define NUM_APHID_PRODUCE			(3 + rand()%3)
#define NUM_APHID_LOTTE_PRODUCE		(35 + rand()%8)

#define NUM_HUNT_PRODUCE_SPRING		(8 + rand()%3)
#define NUM_HUNT_PRODUCE_SUMMER		(9 + rand()%4)
#define NUM_HUNT_PRODUCE_FALL		(7 + rand()%3)
#define NUM_HUNT_PRODUCE_WINTER		(4.5 + rand()%2)
#define NUM_HUNT_COST_DEATH(num)	(rand()%2 + (num)/(16.0+rand()%6))		

#define NUM_SEARCH_PRODUCE_SPRING	(2.1 + rand()%2)
#define NUM_SEARCH_PRODUCE_SUMMER	(2.2 + rand()%3)
#define NUM_SEARCH_PRODUCE_FALL		(2.0 + rand()%2)
#define NUM_SEARCH_PRODUCE_WINTER	(1.4 + rand()%2)
#define NUM_SEARCH_COST_DEATH(num)	(rand()%2 + (num)/(19.0+rand()%7))		

#define INIT_UNSATISFACTORY				0
#define MAX_UNSATISFACTORY				100000
#define RELEASE_UNSATISFACTORY			5
#define UPGRADE_RELEASE_UNSATISFACTORY	10
#define NUM_UNSATISFACTORY_CHURCH		(rand()%31)

#define NUM_LIBRARY_STRENGTH		2000
#define NUM_DEPOSITORY_STRENGTH		3500
#define NUM_LAB_STRENGTH			5500	
#define NUM_TRAINING_STRENGTH		9000
#define NUM_MUSHROOM_STRENGTH		14000
#define NUM_HIRED_1_STRENGTH		20000
#define NUM_HIRED_2_STRENGTH		20000
#define NUM_CHURCH_STRENGTH			30000
#define NUM_ART_STRENGTH			45000

#define NUM_EXP_STRENGTH			600

#define MAX_ANTS									1700
#define MAX_STRENGTH_OVER_MAX_ANTS_AND_NUM_CIPHER	(MAX_STRENGTH/MAX_ANTS/NUM_CIPHER)
#define INIT_STRENGTH								(115*MAX_STRENGTH_OVER_MAX_ANTS_AND_NUM_CIPHER*NUM_CIPHER)
#define MAX_HIRED									300
#define MAX_STRENGTH_OVER_MAX_HIRED_AND_NUM_CIPHER	(MAX_STRENGTH/MAX_HIRED/NUM_CIPHER)
#define MAX_STRENGTH								510000
#define PERIODICAL_STRENGTH_INCREASE				(3 + rand()%2)


#define FOOD_X		214
#define TIMBER_X	297
#define MINERAL_X	372
#define RESOURCE_Y	14

// CDiplomatic /////////////////////////////////////////
#define MAX_DIP			3
#define MAX_SPECIES		5
#define MAX_RELATION	50000

#define SPEARRAY_SNAIL			0
#define SPEARRAY_GRASSHOPPER	1
#define SPEARRAY_SHORT_ANT		2
#define SPEARRAY_BEE			3
#define SPEARRAY_RED_ANT		4

#define SPEARRAY_MAP_PLAYER		0

#define DIP_TITLE_X		605
#define DIP_TITLE_Y		67

#define INIT_FOOD_NPC		(200 + rand()%100)
#define INIT_TIMBER_NPC		(100 + rand()%50)
#define INIT_MINERAL_NPC	(50 + rand()%25)

#define PRINT_STRENGTH_X	11
#define PRINT_STRENGTH_Y	375
#define PRINT_STATE_X		11
#define PRINT_STATE_Y		395
#define PRINT_RELATION_X	11
#define PRINT_RELATION_Y	415
#define PRINT_LANGUAGE_X	11
#define PRINT_LANGUAGE_Y	435
#define PRINT_RELIGION_X	11
#define PRINT_RELIGION_Y	455

#define PRINT_BATTLE_BREAK_OUT_X	560
#define PRINT_BATTLE_BREAK_OUT_Y	65
#define PRINT_PLAYER_GO_X			560
#define PRINT_PLAYER_GO_Y			82
#define PRINT_PLAYER_COME_X			560
#define PRINT_PLAYER_COME_Y			82
#define PRINT_SPE_COME_X			560
#define PRINT_SPE_COME_Y			99

#define SPECIES_STATE_NORMAL	1
#define SPECIES_STATE_OCCUPIED	2
#define SPECIES_STATE_BATTLE	3

#define PERIODICAL_STRENGTH_INCREASE_NPC		(3 + rand()%2)

#define COST_FOOD_PROPAGATION	20	

#define NUM_PRESENT_FOOD	(330 + rand()%60)
#define NUM_PRESENT_TIMBER	(700 + rand()%150)
#define NUM_PRESENT_MINERAL	(150 + rand()%30)

// CInfo /////////////////////////////////////////////////

//////section 1////////section 2//////////section 3//////
//S1_R1	  S1_R2	   /				/					/
//	.		.	   /				/					/
//C1..................................................../
//	.		.	   /				/					/
//	.		.      /				/					/
//	.		.      /				/					/
//	.		.      /				/					/ 
/////////////////////////////////////////////////////////

#define DDRAW_TEXT_GAMEINFO(buffer, x, y, color, align)	DDraw_Text(buffer,x,y,11,lpddsback,color,align,NULL,TRANSPARENT)

#define S1_R1		40		// row 1 of section 1
#define S1_R2		85
#define S1_R3		190

#define S_C1		140		// column 1
#define S_C2		300

#define S2_R1		210
#define S2_R2		255
#define S2_R3		360

#define S3_R1		380
#define S3_R2		425
#define S3_R3		530

// CInterface ////////////////////////////////////////////
#define INTERFACE1_WIDTH 640
#define INTERFACE1_HEIGHT 50

#define INTERFACE2_WIDTH 70
#define INTERFACE2_HEIGHT 430

// CBuilding /////////////////////////////////////////////
#define MAX_BUILDING		9

#define BUILDING_TITLE_X		605
#define BUILDING_TITLE_Y		184

#define BUILDINGARRAY_LIBARAY				0
#define BUILDINGARRAY_DEPOSITORY			1
#define BUILDINGARRAY_LAB					2
#define BUILDINGARRAY_TRAINING				3
#define BUILDINGARRAY_MUSHROOM				4
#define BUILDINGARRAY_HIRED_1				5
#define BUILDINGARRAY_HIRED_2				6
#define BUILDINGARRAY_CHURCH				7
#define BUILDINGARRAY_ART					8

#define NUM_ANTS_CRITERION1 50
#define NUM_ANTS_CRITERION2 150
#define NUM_ANTS_CRITERION3 300
#define NUM_ANTS_CRITERION4 500

#define BUILDING_LIBARAY_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION1)
#define BUILDING_DEPOSITORY_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION1)
#define BUILDING_MUSHROOM_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION2)
#define BUILDING_LAB_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION2)
#define BUILDING_TRAINING_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION2)
#define BUILDING_HIRED_1_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION3)
#define BUILDING_HIRED_2_TIME(t)	((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION3)
#define BUILDING_CHURCH_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION3)
#define BUILDING_ART_TIME(t)		((t) * UNIT_PER_TICK * UNIT_PER_DAY * NUM_ANTS_CRITERION4)

// CBattle ///////////////////////////////////////////////
#define LENGTH_TIME_FROM_RED_ANT		((7 + rand()%2)  * UNIT_PER_TICK * UNIT_PER_DAY)
#define LENGTH_TIME_FROM_SHORT_ANT		((6 + rand()%2)  * UNIT_PER_TICK * UNIT_PER_DAY)
#define LENGTH_TIME_FROM_GRASSHOPPER	((7 + rand()%2)  * UNIT_PER_TICK * UNIT_PER_DAY)
#define LENGTH_TIME_FROM_SNAIL			((5 + rand()%2)  * UNIT_PER_TICK * UNIT_PER_DAY)
#define LENGTH_TIME_FROM_BEE			((8 + rand()%2)  * UNIT_PER_TICK * UNIT_PER_DAY)

#define PRINT_BATTLE_X	200
#define PRINT_BATTLE_Y	395
#define PRINT_BATTLE_STRATT_X	200
#define PRINT_BATTLE_STRATT_Y	415
#define PRINT_BATTLE_STRDEF_X	200
#define PRINT_BATTLE_STRDEF_Y	435

#define POWER_SOLDIER_ANT	0.6
#define POWER_HIRED_1_ATT	0.9
#define POWER_HIRED_1_DEF	1.2
#define POWER_HIRED_2_ATT	1.2
#define POWER_HIRED_2_DEF	0.9
#define POWER_SANIL			0.5
#define POWER_GRSSHOPPER	0.6
#define POWER_SHORT_ANT		0.7
#define POWER_BEE			0.8
#define POWER_RED_ANT		1.0

#define TYPE_HIRED_1		1
#define TYPE_HIRED_2		2

#define EXCEPT_BATTLE		1

#define DEMAGE_UPGRADE_LAB		0.1
#define DEMAGE_UPGRADE_TRAINING	0.2

// Gloabal /////////////////////////////////////////////////

#define GAME_VERSION	110
#define GAME_SAVETITLE	"SaveFile of 'The Kingdom of Ants'"

#define MAX_SMUSIC		6		// 생성할 사운드 뮤직 오브젝트의 개수 
#define MAX_SSOUND		2		// 생성할 사운드 사운드 오브젝트의 개수 

#define RESTRICTED_INIT	1

#define NUM_CIPHER		100		// 자원, 세력, 전투에서 병사의 수를 실제로 게임 내부적으로
								// 사용할 단위
#define UNIT_PER_TICK 2
#define UNIT_PER_DAY 30

#define WM_GETPOINT	WM_USER+1
#define WM_GETPAGE	WM_USER+2
#define WM_GETINFO	WM_USER+3

#define HALFTICK 200

#define BYTE_PER_PIXER 4

#define GO_OUT	5

#define GAMESCREEN_WIDTH 896
#define GAMESCREEN_HEIGHT 643

#define MAPSCREEN_WIDTH (SCREEN_WIDTH - INTERFACE2_WIDTH)
#define MAPSCREEN_HEIGHT (SCREEN_HEIGHT - INTERFACE1_HEIGHT)

#define ITEMSCREEN_WIDTH (SCREEN_WIDTH - INTERFACE2_WIDTH)
#define ITEMSCREEN_HEIGHT (SCREEN_HEIGHT - INTERFACE1_HEIGHT)

#define DAY_X 66
#define DAY_CX 176

//#define TEST					// 정의되면 디버그 모드로 변수 값을 표시

#define KEY_KEEP 0
#define KEY_DOWN 1
#define KEY_UP 2

#define BUTTON_KEEP 0
#define BUTTON_DOWN 1
#define BUTTON_UP 2

#define SELLER_ANIM_LEFT    0

#define BATTLE_DIRT_ANIM    0

#define ANT_ANIM_UP      0
#define ANT_ANIM_RIGHT   1
#define ANT_ANIM_DOWN    2
#define ANT_ANIM_LEFT    3
#define ANT_ANIM_DEAD    4

#define ANT_GORIGHT				0   // moving around randomly
#define ANT_GOLEFT              1   // at a mnm eating it
#define ANT_RESTING             2   // sleeping :)
#define ANT_COMMUNICATING       3   // talking to another ant  

#define ANT_INT_CUR_STATE		0
#define ANT_INT_CUR_WAYPOINT	1
#define ANT_INT_OLD_WAYPOINT	2
#define ANT_INT_RESTING			3

#define BOB_INT_MOVE				0
#define BULIDING_INT_STATE			1
#define BOB_INT_SELLER_DIALOG		1
#define BOB_INT_SELLER_COST_FOOD	2
#define BOB_INT_SELLER_COST_TIMBER	3
#define BOB_INT_SELLER_COST_MINERAL	4

#define BOB_NOT_MOVE			0
#define BOB_MOVE_NORMAL			1
#define BOB_MOVE_SELLER			2

#define BUILDING_UNDER_CONSTRUCTION 1
#define BUILDING_DONE				2

#define NUM_WAYPOINTS 16 // number of waypoints in path

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
#define GETPERCENT(value, total) ((float)value * 100.0 / total)

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"









