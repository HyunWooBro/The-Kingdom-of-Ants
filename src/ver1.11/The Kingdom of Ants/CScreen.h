/*
///////////////////////////////////////////

	CScreen

	UI를 제외한 게임의 화면을 관리한다.

///////////////////////////////////////////
*/
#ifndef CSCREEN
#define CSCREEN

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CScreen
{
public:
	CScreen() {}
	~CScreen() {}

private:
	LPDIRECTDRAWSURFACE7 screen_game_spring;
	LPDIRECTDRAWSURFACE7 screen_game_summer;
	LPDIRECTDRAWSURFACE7 screen_game_fall;
	LPDIRECTDRAWSURFACE7 screen_game_winter;

	LPDIRECTDRAWSURFACE7 screen_map_spring;
	LPDIRECTDRAWSURFACE7 screen_map_summer;
	LPDIRECTDRAWSURFACE7 screen_map_fall;
	LPDIRECTDRAWSURFACE7 screen_map_winter;

	LPDIRECTDRAWSURFACE7 screen_item;

	LPDIRECTDRAWSURFACE7 screen_gameinfo;

	LPDIRECTDRAWSURFACE7 room_libaray_init;
	LPDIRECTDRAWSURFACE7 room_libaray_done;

	LPDIRECTDRAWSURFACE7 room_depository_init;
	LPDIRECTDRAWSURFACE7 room_depository_done;

	LPDIRECTDRAWSURFACE7 room_lab_init;
	LPDIRECTDRAWSURFACE7 room_lab_done;

	LPDIRECTDRAWSURFACE7 room_training_init;
	LPDIRECTDRAWSURFACE7 room_training_done;

	LPDIRECTDRAWSURFACE7 room_mushroom_init;
	LPDIRECTDRAWSURFACE7 room_mushroom_done;

	LPDIRECTDRAWSURFACE7 room_hired_init;
	LPDIRECTDRAWSURFACE7 room_hired_done;

	LPDIRECTDRAWSURFACE7 room_church_init;
	LPDIRECTDRAWSURFACE7 room_church_done;

	LPDIRECTDRAWSURFACE7 room_art_init;
	LPDIRECTDRAWSURFACE7 room_art_done;

	LPDIRECTDRAWSURFACE7 brokenstone;

public:
	int Screen_Init();
	
	int DrawScreen();

	int Upgrade_Libaray_Init();
	int Upgrade_Libaray_Done();

	int Upgrade_Depository_Init();
	int Upgrade_Depository_Done();

	int Upgrade_Lab_Init();
	int Upgrade_Lab_Done();

	int Upgrade_Training_Init();
	int Upgrade_Training_Done();
	
	int Upgrade_Mushroom_Init();
	int Upgrade_Mushroom_Done();

	int Upgrade_Hired_Init();
	int Upgrade_Hired_Done();

	int Upgrade_Church_Init();
	int Upgrade_Church_Done();

	int Upgrade_Art_Init();
	int Upgrade_Art_Done();

	int ChangeStrangeStone();

	int Scroll();

	int reload();

	int Save();
	int Load();

	int Screen_Shutdown();
};


#endif
