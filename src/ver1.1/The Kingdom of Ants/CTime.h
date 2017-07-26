/*
///////////////////////////////////////////

	CTime

	게임 상의 시간을 관리한다. 시간은 계절, 
	일(90일 마다 계절이 바뀐다.), 
	하루(12초)로 이루어져 있다.

///////////////////////////////////////////
*/
#ifndef CTIME
#define CTIME

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CTime
{
public:
	CTime() {}
	~CTime() {}

private:
	char buffer[30];

	struct _time
	{
		int day;
		int month3;
		SEASON season;
		int year;
	}time;

	static BOOL pause_check[2];
	static int pause_ref;
	static BOOL pause_player;

	BOB sun;

	int DDraw_Fill_Rect(LPDIRECTDRAWSURFACE7 lpdds, PRECT rect, int color);

public:
	int Time_Init();

	int TickTime();

	int GetDay();
	int GetMonth3();
	int GetSeason();
	int GetYear();

	int DrawSun();
	int DrawMonth3();
	int PrintSeason();
	int PrintPause();

	static int SetPause(int pause_check_index = -1);
	static int ReleasePause(int pause_check_index = -1);
	static int SwitchPause();
	static int GetPauseRef();
	static BOOL GetPauseCheck(int pause_check_index);
	static int SetPausePlayer(BOOL pause);

	int Save();
	int Load();

	int Time_Shutdown();
};

#endif
