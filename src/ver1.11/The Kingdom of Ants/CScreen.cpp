#include "CScreen.h"
#include "ddutil.h"
#include "CTime.h"
#include "CBuilding.h"
#include "CDebug.h"

extern CDebug debug_;
extern CBuilding building_;
extern CTime time_;

int CScreen::Screen_Init()
{
	screen_game_spring = DDLoadBitmap(lpdd, "art/screen/screen_game_spring.bmp", 0, 0);
	screen_game_summer = DDLoadBitmap(lpdd, "art/screen/screen_game_summer.bmp", 0, 0);
	screen_game_fall = DDLoadBitmap(lpdd, "art/screen/screen_game_fall.bmp", 0, 0);
	screen_game_winter = DDLoadBitmap(lpdd, "art/screen/screen_game_winter.bmp", 0, 0);

	screen_map_spring = DDLoadBitmap(lpdd, "art/screen/screen_map_spring.bmp", 0, 0);
	screen_map_summer = DDLoadBitmap(lpdd, "art/screen/screen_map_summer.bmp", 0, 0);
	screen_map_fall = DDLoadBitmap(lpdd, "art/screen/screen_map_fall.bmp", 0, 0);
	screen_map_winter = DDLoadBitmap(lpdd, "art/screen/screen_map_winter.bmp", 0, 0);

	screen_item = DDLoadBitmap(lpdd, "art/screen/screen_item.bmp", 0, 0);

	screen_gameinfo = DDLoadBitmap(lpdd, "art/screen/screen_gameinfo.bmp", 0, 0);

	room_libaray_init = DDLoadBitmap(lpdd, "art/room/room_libaray_init.bmp", 0, 0);
	room_libaray_done = DDLoadBitmap(lpdd, "art/room/room_libaray_done.bmp", 0, 0);

	room_depository_init = DDLoadBitmap(lpdd, "art/room/room_depository_init.bmp", 0, 0);
	room_depository_done = DDLoadBitmap(lpdd, "art/room/room_depository_done.bmp", 0, 0);

	room_lab_init = DDLoadBitmap(lpdd, "art/room/room_lab_init.bmp", 0, 0);
	room_lab_done = DDLoadBitmap(lpdd, "art/room/room_lab_done.bmp", 0, 0);

	room_training_init = DDLoadBitmap(lpdd, "art/room/room_training_init.bmp", 0, 0);
	room_training_done = DDLoadBitmap(lpdd, "art/room/room_training_done.bmp", 0, 0);

	room_mushroom_init = DDLoadBitmap(lpdd, "art/room/room_mushroom_init.bmp", 0, 0);
	room_mushroom_done = DDLoadBitmap(lpdd, "art/room/room_mushroom_done.bmp", 0, 0);

	room_hired_init = DDLoadBitmap(lpdd, "art/room/room_hired_init.bmp", 0, 0);
	room_hired_done = DDLoadBitmap(lpdd, "art/room/room_hired_done.bmp", 0, 0);

	room_church_init = DDLoadBitmap(lpdd, "art/room/room_church_init.bmp", 0, 0);
	room_church_done = DDLoadBitmap(lpdd, "art/room/room_church_done.bmp", 0, 0);

	room_art_init = DDLoadBitmap(lpdd, "art/room/room_art_init.bmp", 0, 0);
	room_art_done = DDLoadBitmap(lpdd, "art/room/room_art_done.bmp", 0, 0);

	brokenstone = DDLoadBitmap(lpdd, "art/etc/brokenstone.bmp", 0, 0);

	DDCOLORKEY colorkey;
	colorkey.dwColorSpaceHighValue = _RGB32BIT(0, 0, 0, 0);
	colorkey.dwColorSpaceLowValue = _RGB32BIT(0, 0, 0, 0);
	room_libaray_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_libaray_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_depository_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_depository_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_lab_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_lab_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_training_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_training_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_mushroom_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_mushroom_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_hired_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_hired_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_church_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_church_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_art_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_art_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	brokenstone->SetColorKey(DDCKEY_SRCBLT, &colorkey);

	return 1;
}

int CScreen::Screen_Shutdown()
{
	if(screen_game_spring)
		screen_game_spring->Release();
	if(screen_game_summer)
		screen_game_summer->Release();
	if(screen_game_fall)
		screen_game_fall->Release();
	if(screen_game_winter)
		screen_game_winter->Release();

	if(screen_map_spring)
		screen_map_spring->Release();
	if(screen_map_summer)
		screen_map_summer->Release();
	if(screen_map_fall)
		screen_map_fall->Release();
	if(screen_map_winter)
		screen_map_winter->Release();

	if(screen_item)
		screen_item->Release();

	if(screen_gameinfo)
		screen_gameinfo->Release();

	if(room_libaray_init)
		room_libaray_init->Release();
	if(room_libaray_done)
		room_libaray_done->Release();

	if(room_depository_init)
		room_depository_init->Release();
	if(room_depository_done)
		room_depository_done->Release();

	if(room_lab_init)
		room_lab_init->Release();
	if(room_lab_done)
		room_lab_done->Release();

	if(room_training_init)
		room_training_init->Release();
	if(room_training_done)
		room_training_done->Release();

	if(room_mushroom_init)
		room_mushroom_init->Release();
	if(room_mushroom_done)
		room_mushroom_done->Release();

	if(room_hired_init)
		room_hired_init->Release();
	if(room_hired_done)
		room_hired_done->Release();

	if(room_church_init)
		room_church_init->Release();
	if(room_church_done)
		room_church_done->Release();

	if(room_art_init)
		room_art_init->Release();
	if(room_art_done)
		room_art_done->Release();

	if(brokenstone)
		brokenstone->Release();

	return 1;
}

int CScreen::DrawScreen()
{

	RECT dest_rect = {0, INTERFACE1_HEIGHT, SCREEN_WIDTH-INTERFACE2_WIDTH, SCREEN_HEIGHT};
	
	if(SCREEN_STATE == SCREEN_GAME)
	{
		RECT sour_rect = {off_x, off_y, SCREEN_WIDTH+off_x-INTERFACE2_WIDTH, SCREEN_HEIGHT+off_y-INTERFACE1_HEIGHT};
		if(time_.GetSeason() == SPRING)
			lpddsback->Blt(&dest_rect, screen_game_spring, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == SUMMER)
			lpddsback->Blt(&dest_rect, screen_game_summer, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == FALL)
			lpddsback->Blt(&dest_rect, screen_game_fall, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == WINTER)
			lpddsback->Blt(&dest_rect, screen_game_winter, &sour_rect, DDBLT_WAIT, NULL);
	}

	RECT sour_rect = {0, 0, SCREEN_WIDTH-INTERFACE2_WIDTH, SCREEN_HEIGHT-INTERFACE1_HEIGHT};
	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(time_.GetSeason() == SPRING)
			lpddsback->Blt(&dest_rect, screen_map_spring, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == SUMMER)
			lpddsback->Blt(&dest_rect, screen_map_summer, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == FALL)
			lpddsback->Blt(&dest_rect, screen_map_fall, &sour_rect, DDBLT_WAIT, NULL);
		if(time_.GetSeason() == WINTER)
			lpddsback->Blt(&dest_rect, screen_map_winter, &sour_rect, DDBLT_WAIT, NULL);
	}
	if(SCREEN_STATE == SCREEN_ITEM)
	{
		lpddsback->Blt(&dest_rect, screen_item, &sour_rect, DDBLT_WAIT, NULL);
	}
	if(SCREEN_STATE == SCREEN_GAMEINFO)
	{
		lpddsback->Blt(&dest_rect, screen_gameinfo, &sour_rect, DDBLT_WAIT, NULL);
	}

	return 1;
}

int CScreen::Upgrade_Libaray_Init()
{
	screen_game_spring->Blt(NULL, room_libaray_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_libaray_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_libaray_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_libaray_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Libaray_Done()
{
	screen_game_spring->Blt(NULL, room_libaray_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_libaray_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_libaray_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_libaray_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Depository_Init()
{
	screen_game_spring->Blt(NULL, room_depository_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_depository_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_depository_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_depository_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Depository_Done()
{
	screen_game_spring->Blt(NULL, room_depository_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_depository_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_depository_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_depository_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Lab_Init()
{
	screen_game_spring->Blt(NULL, room_lab_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_lab_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_lab_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_lab_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Lab_Done()
{
	screen_game_spring->Blt(NULL, room_lab_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_lab_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_lab_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_lab_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Training_Init()
{
	screen_game_spring->Blt(NULL, room_training_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_training_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_training_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_training_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Training_Done()
{
	screen_game_spring->Blt(NULL, room_training_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_training_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_training_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_training_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Mushroom_Init()
{
	screen_game_spring->Blt(NULL, room_mushroom_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_mushroom_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_mushroom_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_mushroom_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Mushroom_Done()
{
	screen_game_spring->Blt(NULL, room_mushroom_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_mushroom_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_mushroom_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_mushroom_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Hired_Init()
{
	screen_game_spring->Blt(NULL, room_hired_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_hired_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_hired_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_hired_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Hired_Done()
{
	screen_game_spring->Blt(NULL, room_hired_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_hired_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_hired_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_hired_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Church_Init()
{
	screen_game_spring->Blt(NULL, room_church_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_church_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_church_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_church_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Church_Done()
{
	screen_game_spring->Blt(NULL, room_church_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_church_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_church_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_church_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}

int CScreen::Upgrade_Art_Init()
{
	screen_game_spring->Blt(NULL, room_art_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_art_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_art_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_art_init, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Upgrade_Art_Done()
{
	screen_game_spring->Blt(NULL, room_art_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, room_art_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, room_art_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, room_art_done, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::Scroll()
{
	if(SCROLL_STATE != SCROLL_RUN)
		return 0;

	if((mouse_x >= SCREEN_WIDTH-10) && (off_x <= moff_x))
	{
		if(MOUSE_STATE == MOUSE_SHOW)
			off_x += 8;
		else
			off_x += 4;
	}
	if((mouse_x <= 10) && (off_x >= 0))
	{
		if(MOUSE_STATE == MOUSE_SHOW)
			off_x -= 8;
		else
			off_x -= 4;
	}
	if((mouse_y >= SCREEN_HEIGHT-10) && (off_y <= moff_y))
	{
		if(MOUSE_STATE == MOUSE_SHOW)
			off_y += 8;
		else
			off_y += 4;
	}
	if((mouse_y <= 10) && (off_y >= 0))
	{
		if(MOUSE_STATE == MOUSE_SHOW)
			off_y -= 8;
		else
			off_y -= 4;
	}

	if(off_x > moff_x)
		off_x = moff_x;
	if(off_x < 0)
		off_x = 0;
	if(off_y > moff_y)
		off_y = moff_y;
	if(off_y < 0)
		off_y = 0;

	return 1;
}
int CScreen::ChangeStrangeStone()
{
	screen_game_spring->Blt(NULL, brokenstone, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_summer->Blt(NULL, brokenstone, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_fall->Blt(NULL, brokenstone, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	screen_game_winter->Blt(NULL, brokenstone, NULL, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	return 1;
}
int CScreen::reload()
{
	screen_game_spring = DDLoadBitmap(lpdd, "art/screen/screen_game_spring.bmp", 0, 0);
	screen_game_summer = DDLoadBitmap(lpdd, "art/screen/screen_game_summer.bmp", 0, 0);
	screen_game_fall = DDLoadBitmap(lpdd, "art/screen/screen_game_fall.bmp", 0, 0);
	screen_game_winter = DDLoadBitmap(lpdd, "art/screen/screen_game_winter.bmp", 0, 0);

	screen_map_spring = DDLoadBitmap(lpdd, "art/screen/screen_map_spring.bmp", 0, 0);
	screen_map_summer = DDLoadBitmap(lpdd, "art/screen/screen_map_summer.bmp", 0, 0);
	screen_map_fall = DDLoadBitmap(lpdd, "art/screen/screen_map_fall.bmp", 0, 0);
	screen_map_winter = DDLoadBitmap(lpdd, "art/screen/screen_map_winter.bmp", 0, 0);

	screen_item = DDLoadBitmap(lpdd, "art/screen/screen_item.bmp", 0, 0);

	screen_gameinfo = DDLoadBitmap(lpdd, "art/screen/screen_gameinfo.bmp", 0, 0);

	room_libaray_init = DDLoadBitmap(lpdd, "art/room/room_libaray_init.bmp", 0, 0);
	room_libaray_done = DDLoadBitmap(lpdd, "art/room/room_libaray_done.bmp", 0, 0);

	room_depository_init = DDLoadBitmap(lpdd, "art/room/room_depository_init.bmp", 0, 0);
	room_depository_done = DDLoadBitmap(lpdd, "art/room/room_depository_done.bmp", 0, 0);

	room_lab_init = DDLoadBitmap(lpdd, "art/room/room_lab_init.bmp", 0, 0);
	room_lab_done = DDLoadBitmap(lpdd, "art/room/room_lab_done.bmp", 0, 0);

	room_training_init = DDLoadBitmap(lpdd, "art/room/room_training_init.bmp", 0, 0);
	room_training_done = DDLoadBitmap(lpdd, "art/room/room_training_done.bmp", 0, 0);

	room_mushroom_init = DDLoadBitmap(lpdd, "art/room/room_mushroom_init.bmp", 0, 0);
	room_mushroom_done = DDLoadBitmap(lpdd, "art/room/room_mushroom_done.bmp", 0, 0);

	room_hired_init = DDLoadBitmap(lpdd, "art/room/room_hired_init.bmp", 0, 0);
	room_hired_done = DDLoadBitmap(lpdd, "art/room/room_hired_done.bmp", 0, 0);

	room_church_init = DDLoadBitmap(lpdd, "art/room/room_church_init.bmp", 0, 0);
	room_church_done = DDLoadBitmap(lpdd, "art/room/room_church_done.bmp", 0, 0);

	room_art_init = DDLoadBitmap(lpdd, "art/room/room_art_init.bmp", 0, 0);
	room_art_done = DDLoadBitmap(lpdd, "art/room/room_art_done.bmp", 0, 0);

	brokenstone = DDLoadBitmap(lpdd, "art/etc/brokenstone.bmp", 0, 0);

	DDCOLORKEY colorkey;
	colorkey.dwColorSpaceHighValue = _RGB32BIT(0, 0, 0, 0);
	colorkey.dwColorSpaceLowValue = _RGB32BIT(0, 0, 0, 0);
	room_libaray_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_libaray_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_depository_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_depository_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_lab_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_lab_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_training_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_training_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_mushroom_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_mushroom_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_hired_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_hired_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_church_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_church_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_art_init->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	room_art_done->SetColorKey(DDCKEY_SRCBLT, &colorkey);
	brokenstone->SetColorKey(DDCKEY_SRCBLT, &colorkey);

	if(building_.building_under_construction == "도서관")
		Upgrade_Libaray_Init();
	if(building_.buildingarray[BUILDINGARRAY_LIBARAY].bexist == TRUE)
		Upgrade_Libaray_Done();

	if(building_.building_under_construction == "자원 보관소")
		Upgrade_Depository_Init();
	if(building_.buildingarray[BUILDINGARRAY_DEPOSITORY].bexist == TRUE)
		Upgrade_Depository_Done();

	if(building_.building_under_construction == "화학 연구소")
		Upgrade_Lab_Init();
	if(building_.buildingarray[BUILDINGARRAY_LAB].bexist == TRUE)
		Upgrade_Lab_Done();

	if(building_.building_under_construction == "전투 연습실")
		Upgrade_Training_Init();
	if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
		Upgrade_Training_Done();

	if(building_.building_under_construction == "버섯 재배실")
		Upgrade_Mushroom_Init();
	if(building_.buildingarray[BUILDINGARRAY_MUSHROOM].bexist == TRUE)
		Upgrade_Mushroom_Done();

	if(building_.building_under_construction == "용병양성소1")
		Upgrade_Hired_Init();
	if(building_.buildingarray[BUILDINGARRAY_HIRED_1].bexist == TRUE)
		Upgrade_Hired_Done();

	if(building_.building_under_construction == "용병양성소2")
		Upgrade_Hired_Init();
	if(building_.buildingarray[BUILDINGARRAY_HIRED_2].bexist == TRUE)
		Upgrade_Hired_Done();

	if(building_.building_under_construction == "종교 회관")
		Upgrade_Church_Init();
	if(building_.buildingarray[BUILDINGARRAY_CHURCH].bexist == TRUE)
		Upgrade_Church_Done();

	if(building_.building_under_construction == "예술의 전당")
		Upgrade_Art_Init();
	if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
		Upgrade_Art_Done();

	return 1;
}
int CScreen::Save()
{
	int lpitch = 0;
	UCHAR *filebuffer;
	UCHAR *memory;

	filebuffer = new UCHAR[GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER];

	memory = DDraw_Lock_Surface(screen_game_spring, &lpitch);
	memcpy(filebuffer, memory, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	WriteFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	DDraw_Unlock_Surface(screen_game_spring);

	memory = DDraw_Lock_Surface(screen_game_summer, &lpitch);
	memcpy(filebuffer, memory, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	WriteFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	DDraw_Unlock_Surface(screen_game_summer);

	memory = DDraw_Lock_Surface(screen_game_fall, &lpitch);
	memcpy(filebuffer, memory, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	WriteFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	DDraw_Unlock_Surface(screen_game_fall);

	memory = DDraw_Lock_Surface(screen_game_winter, &lpitch);
	memcpy(filebuffer, memory, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	WriteFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	DDraw_Unlock_Surface(screen_game_winter);

	delete [] filebuffer;

	return 1;
}
int CScreen::Load()
{
	int lpitch = 0;
	UCHAR *filebuffer;
	UCHAR *memory;

	filebuffer = new UCHAR[GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER];

	ReadFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	memory = DDraw_Lock_Surface(screen_game_spring, &lpitch);
	memcpy(memory, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	DDraw_Unlock_Surface(screen_game_spring);

	ReadFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	memory = DDraw_Lock_Surface(screen_game_summer, &lpitch);
	memcpy(memory, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	DDraw_Unlock_Surface(screen_game_summer);

	ReadFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	memory = DDraw_Lock_Surface(screen_game_fall, &lpitch);
	memcpy(memory, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	DDraw_Unlock_Surface(screen_game_fall);

	ReadFile(hfile, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER, &dwWritten, NULL);
	memory = DDraw_Lock_Surface(screen_game_winter, &lpitch);
	memcpy(memory, filebuffer, GAMESCREEN_WIDTH * GAMESCREEN_HEIGHT * BYTE_PER_PIXER);
	DDraw_Unlock_Surface(screen_game_winter);

	delete [] filebuffer;

	return 1;
}
