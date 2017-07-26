
#include <stdio.h> 
#include "CTime.h"
#include "CDebug.h"

extern CDebug debug_;

extern int SoundLockTime();

BOOL CTime::pause_check[2];
int CTime::pause_ref = 0;
BOOL CTime::pause_player = 0;

int CTime::Time_Init()
{
	time.day = 0;
	time.month3 = 0;
	time.season = WINTER;
	time.year = 0;

	BITMAP_FILE bitmap_sun;
	ZeroMemory(&bitmap_sun, sizeof(BITMAP_FILE));
	Load_Bitmap_File(&bitmap_sun, "art/etc/sun.BMP");
	
	Create_BOB(&sun,66,37,32,34,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY); 
	
	Load_Frame_BOB(&sun,&bitmap_sun,0,1,2,BITMAP_EXTRACT_MODE_CELL);
	
	Unload_Bitmap_File(&bitmap_sun);

	// 상인
	pause_check[0] = FALSE;
	// 외교 메뉴 - 공격
	pause_check[1] = FALSE;
	// 외교 메뉴 - 증정
	pause_check[2] = FALSE;

	pause_ref = 0;

	pause_player = FALSE;

	return 1;
}

int CTime::TickTime()
{
	time.day++;
	if(time.day > 60)
	{
		time.day = 0;
		time.month3++;
		if(time.month3 == 90)
		{
			time.month3 = 0;
			if(time.season == SPRING)
				time.season = SUMMER;
			else if(time.season == SUMMER)
				time.season = FALL;
			else if(time.season == FALL)
			{
				time.year++;
				time.season = WINTER;
			}
			else if(time.season == WINTER)
				time.season = SPRING;
		}
	}

	debug_.GetValue("month3, day", &time.month3, &time.day, lpddsback, 16, NULL);

	return 1;
}

int CTime::GetDay()
{
	return time.day;
}

int CTime::GetMonth3()
{
	return time.month3;
}

int CTime::GetSeason()
{
	return time.season;
}

int CTime::GetYear()
{
	return time.year;
}

int CTime::DrawSun()
{
	int temp = 155 - 65;
	int timetemp = time.day/UNIT_PER_TICK;
	temp /= 30;
	temp *= timetemp;

	sun.x = temp + 50;
	sun.y = 19;
	Draw_BOB(&sun,lpddsback);
	return 1;
}

int CTime::DrawMonth3()
{
	int temp = 155 - 65;
	int timetemp = time.month3;
	temp = 1;
	temp *= timetemp;
	temp += 65;
	
	RECT rect = {65, 9, temp, 21};
	DDraw_Fill_Rect(lpddsback, &rect, 200);

	return 1;
}

int CTime::PrintSeason()
{
	if(time.season == SPRING)
		sprintf(buffer,"봄");
	if(time.season == SUMMER)
		sprintf(buffer,"여름");
	if(time.season == FALL)
		sprintf(buffer,"가을");
	if(time.season == WINTER)
		sprintf(buffer,"겨울");

	DDraw_Text(buffer, 
				PRINT_SEASON_X,
				PRINT_SEASON_Y,
				17,
				lpddsback,
				RGB(255,255,255),
				TA_LEFT,
				NULL,
				TRANSPARENT);

	return 1;
}

int CTime::PrintPause()
{
	DWORD exitcode;
	static int show = 0;

	if(GAME_STATE == GAME_PAUSE)
	{
		GetExitCodeThread(hthread, &exitcode);
		// thread가 없을 때 '게임 일시 정지' 출력
		if(exitcode != STILL_ACTIVE)			
		{	
			show++;
			if(show >= 0 && show <= 30)
			{
				sprintf(buffer,"게임 일시 정지");
				DDraw_Text(buffer, 
						PRINT_PAUSE_X,
						PRINT_PAUSE_Y,
						17,
						lpddsback,
						RGB(255,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT);
			}
			if(show >= 60)
				show = 0;
		}
	}
	
	return 1;
}
int CTime::SetPause(int pause_check_index)
{
	if(pause_check_index == -1)
	{
		pause_ref++;
		GAME_STATE = GAME_PAUSE;
		return 1;
	}
	if(pause_check[pause_check_index] == FALSE)
	{
		pause_check[pause_check_index] = TRUE;
		pause_ref++;
		GAME_STATE = GAME_PAUSE;
		return 1;
	}
}
int CTime::ReleasePause(int pause_check_index)
{
	if(pause_check_index == -1)
	{
		pause_ref--;
		if(GAME_STATE == GAME_OVER)
			pause_ref = 0;
		else
		{
			if(pause_ref == 0)
				if(pause_player == FALSE)
					GAME_STATE = GAME_RUN;
		}
		
		return 1;
	}
	if(pause_check[pause_check_index] == TRUE)
	{
		pause_check[pause_check_index] = FALSE;
		pause_ref--;
		if(pause_ref == 0)
			if(pause_player == FALSE)
				GAME_STATE = GAME_RUN;
		return 1;
	}
}
int CTime::SwitchPause()
{
	SoundLockTime();

	if(pause_ref == 0)
	{
		if(GAME_STATE == GAME_RUN)
		{
			pause_player = TRUE;
			GAME_STATE = GAME_PAUSE;
		}
		else
		{
			pause_player = FALSE;
			GAME_STATE = GAME_RUN;
		}
	}

	return 1;
}
int CTime::GetPauseRef()
{
	return pause_ref;
}
BOOL CTime::GetPauseCheck(int pause_check_index)
{
	return pause_check[pause_check_index];
}
int CTime::SetPausePlayer(BOOL pause)
{
	pause_player = pause;

	return 1;
}
int CTime::DDraw_Fill_Rect(LPDIRECTDRAWSURFACE7 lpdds, PRECT rect, int color)
{
DDBLTFX ddbltfx; // this contains the DDBLTFX structure

// clear out the structure and set the size field 
DDRAW_INIT_STRUCT(ddbltfx);

// set the dwfillcolor field to the desired color
ddbltfx.dwFillColor = color; 

// ready to blt to surface
lpdds->Blt(rect,       // ptr to dest rectangle
           NULL,       // ptr to source surface, NA            
           NULL,       // ptr to source rectangle, NA
           DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
           &ddbltfx);  // ptr to DDBLTFX structure

// return success
return(1);
}

int CTime::Save()
{
	WriteFile(hfile, &time, sizeof(time), &dwWritten, NULL);
	WriteFile(hfile, &pause_ref, sizeof(pause_ref), &dwWritten, NULL);
	WriteFile(hfile, &pause_player, sizeof(pause_player), &dwWritten, NULL);

	return 1;
}
int CTime::Load()
{
	ReadFile(hfile, &time, sizeof(time), &dwWritten, NULL);
	ReadFile(hfile, &pause_ref, sizeof(pause_ref), &dwWritten, NULL);
	ReadFile(hfile, &pause_player, sizeof(pause_player), &dwWritten, NULL);

	return 1;
}
int CTime::Time_Shutdown()
{
	Destroy_BOB(&sun);

	return 1;
}
