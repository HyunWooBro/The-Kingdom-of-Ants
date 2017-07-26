
#include <stdio.h>
#include <math.h>
#include "CBuilding.h"
#include "CObject.h"
#include "resource.h"
#include "CDomestic.h"
#include "CObjDialog.h"
#include "CScreen.h"
#include "CDiplomatic.h"
#include "CPlayer.h"
#include "CTime.h"
#include "CBuilding.h"
#include "CDebug.h"

extern CDebug debug_;
extern CObject object_;
extern CDomestic domestic_;
extern CScreen screen_;
extern CObjDialog objdialog_;
extern CDiplomatic diplomatic_;
extern CBuilding building_;

extern int SoundClick();
extern int ReturnScreenGamma(BOOL blong, int delay = 70);
extern int ChangeScreenGamma(int effect, BOOL blong, int delay = 70);

HWND CBuilding::hWndDlg_building = NULL;

int CBuilding::Building_Init()
{
	// 도서관
	buildingarray[0].bexist = FALSE;
	buildingarray[0].bshow = TRUE;
	buildingarray[0].Disabled = FALSE;
	buildingarray[0].remaintime = BUILDING_LIBARAY_TIME(10);
	buildingarray[0].inittime = buildingarray[0].remaintime;
	SetRect(&buildingarray[0].buildingrect, 581, 201, 631, 226);
	buildingarray[0].middlepoint.x = 581 + (631-581)/2;
	buildingarray[0].middlepoint.y = 201 + (226-201)/2;
	buildingarray[0].buildingtype = "도서관";
	buildingarray[0].describe_building = "도서관\n\n선조들의 지혜와 재미있는 이야기가 "
										 "가득 들어있는 장소, 간혹 게으른 일꾼 개미가 "
										 "숨어있기도 합니다.";
	buildingarray[0].building_cost[0] = 70;
	buildingarray[0].building_cost[1] = 130;
	buildingarray[0].building_cost[2] = 0;
	

	// 자원 보관소
	buildingarray[1].bexist = FALSE;
	buildingarray[1].bshow = FALSE;		// 쳅터1 중후반에 등장한다.
	buildingarray[1].Disabled = FALSE;
	buildingarray[1].remaintime = BUILDING_DEPOSITORY_TIME(13);
	buildingarray[1].inittime = buildingarray[1].remaintime;
	SetRect(&buildingarray[1].buildingrect, 581, 233, 631, 257);
	buildingarray[1].middlepoint.x = 581 + (631-581)/2;
	buildingarray[1].middlepoint.y = 233 + (257-233)/2;
	buildingarray[1].buildingtype = "자원 보관소";
	buildingarray[1].describe_building = "자원 보관소\n\n자원을 보관할 수 있는 한계를 증가시킵니다."
										"\n식량 : 4000 -> 12000"
										"\n목재 : 1000 -> 3000"
										"\n광석 :  500 -> 1500";
	buildingarray[1].building_cost[0] = 200;
	buildingarray[1].building_cost[1] = 250;
	buildingarray[1].building_cost[2] = 0;

	// 화학 연구소
	buildingarray[2].bexist = FALSE;
	buildingarray[2].bshow = FALSE;		// 쳅터2 시작에 등장한다.
	buildingarray[2].Disabled = FALSE;
	buildingarray[2].remaintime = BUILDING_LAB_TIME(15);
	buildingarray[2].inittime = buildingarray[2].remaintime;
	SetRect(&buildingarray[2].buildingrect, 581, 264, 631, 287);
	buildingarray[2].middlepoint.x = 581 + (631-581)/2;
	buildingarray[2].middlepoint.y = 264 + (287-264)/2;
	buildingarray[2].buildingtype = "화학 연구소";
	buildingarray[2].describe_building = "화학 연구소\n\n개미 문명의 미래를 책임지는 "
										"중요한 장소입니다. 이곳 주위에서는 지독한 화학약품 "
										"냄새와 시끄러운 소리가 들립니다.";
	buildingarray[2].building_cost[0] = 150;
	buildingarray[2].building_cost[1] = 350;
	buildingarray[2].building_cost[2] = 70;

	// 전투 연습실
	buildingarray[3].bexist = FALSE;
	buildingarray[3].bshow = FALSE;		// 쳅터2 시작에 등장한다.
	buildingarray[3].Disabled = FALSE;
	buildingarray[3].remaintime = BUILDING_TRAINING_TIME(15);
	buildingarray[3].inittime = buildingarray[3].remaintime;
	SetRect(&buildingarray[3].buildingrect, 581, 294, 631, 318);
	buildingarray[3].middlepoint.x = 581 + (631-581)/2;
	buildingarray[3].middlepoint.y = 294 + (318-294)/2;
	buildingarray[3].buildingtype = "전투 연습실";
	buildingarray[3].describe_building = "전투 연습실\n\n용맹한 개미 전사들을 길러내는 "
										"곳입니다. 이곳을 거쳐야 비로소 병정 개미들이 어떤 적과도 "
										"맞서 싸울 수 있습니다.";
	buildingarray[3].building_cost[0] = 250;
	buildingarray[3].building_cost[1] = 350;
	buildingarray[3].building_cost[2] = 50;

	// 버섯 재배실
	buildingarray[4].bexist = FALSE;
	buildingarray[4].bshow = FALSE;		// 쳅터2 중반쯤에 등장한다.
	buildingarray[4].Disabled = FALSE;
	buildingarray[4].remaintime = BUILDING_MUSHROOM_TIME(12);
	buildingarray[4].inittime = buildingarray[4].remaintime;
	SetRect(&buildingarray[4].buildingrect, 581, 326, 631, 349);
	buildingarray[4].middlepoint.x = 581 + (631-581)/2;
	buildingarray[4].middlepoint.y = 326 + (349-326)/2;
	buildingarray[4].buildingtype = "버섯 재배실";
	buildingarray[4].describe_building = "버섯 재배실\n\n참나무에 버섯을 기릅니다. "
										"버섯을 기르기 위해서는 소량의 목재가 소비됩니다.";
	buildingarray[4].building_cost[0] = 250;
	buildingarray[4].building_cost[1] = 400;
	buildingarray[4].building_cost[2] = 0;

	// 용병 양성소1
	buildingarray[5].bexist = FALSE;
	buildingarray[5].bshow = FALSE;		// 쳅터3 시작에 등장한다.
	buildingarray[5].Disabled = FALSE;
	buildingarray[5].remaintime = BUILDING_HIRED_1_TIME(15);
	buildingarray[5].inittime = buildingarray[5].remaintime;
	SetRect(&buildingarray[5].buildingrect, 581, 357, 631, 379);
	buildingarray[5].middlepoint.x = 581 + (631-581)/2;
	buildingarray[5].middlepoint.y = 357 + (379-357)/2;
	buildingarray[5].buildingtype = "용병양성소1";
	buildingarray[5].describe_building = "용병양성소-장수풍뎅이\n\n방어를 전문적으로 하는 종입니다. "
										"이들은 믿음직스럽고 평소에는 평화로워 많은 이들이 선호하는 "
										"용병입니다. (주의 : 용병 양성소를 건설하기 위해서는 "
										"그들의 언어를 먼저 배워야 하며, 용병 양성소는 단 1개만 "
										"건설할 수 있습니다.)";
	buildingarray[5].building_cost[0] = 450;
	buildingarray[5].building_cost[1] = 450;
	buildingarray[5].building_cost[2] = 220;

	// 용병 양성소2
	buildingarray[6].bexist = FALSE;
	buildingarray[6].bshow = FALSE;		// 쳅터3 시작에 등장한다.
	buildingarray[6].Disabled = FALSE;
	buildingarray[6].remaintime = BUILDING_HIRED_2_TIME(15);
	buildingarray[6].inittime = buildingarray[6].remaintime;
	SetRect(&buildingarray[6].buildingrect, 581, 387, 631, 409);
	buildingarray[6].middlepoint.x = 581 + (631-581)/2;
	buildingarray[6].middlepoint.y = 387 + (409-387)/2;
	buildingarray[6].buildingtype = "용병양성소2";
	buildingarray[6].describe_building = "용병양성소-사슴벌레\n\n공격을 전문적으로 하는 종입니다. "
										"이들이 지나간 자리는 적들의 시체가 산더미만치 쌓여 있습니다. "
										"(주의 : 용병 양성소를 건설하기 위해서는 그들의 언어를 "
										"먼저 배워야 하며, 용병 양성소는 단 1개만 건설할 수 있습니다.)";
	buildingarray[6].building_cost[0] = 500;
	buildingarray[6].building_cost[1] = 450;
	buildingarray[6].building_cost[2] = 200;

	// 교회
	buildingarray[7].bexist = FALSE;
	buildingarray[7].bshow = FALSE;	// 쳅터3 중반에 등장한다. 10일안에 건설안하면 사라진다.
	buildingarray[7].Disabled = FALSE;
	buildingarray[7].remaintime = BUILDING_CHURCH_TIME(20);
	buildingarray[7].inittime = buildingarray[7].remaintime;
	SetRect(&buildingarray[7].buildingrect, 581, 416, 631, 439);
	buildingarray[7].middlepoint.x = 581 + (631-581)/2;
	buildingarray[7].middlepoint.y = 416 + (439-416)/2;
	buildingarray[7].buildingtype = "종교 회관";
	buildingarray[7].describe_building = "종교 회관\n\n지나가던 성자 개미가 그들의 신을 "
										"위한 회관를 지어주기를 원합니다. 그들의 신은 손가락 "
										"입니다. 당신이 뜸을 들인다면 그들은 떠날 것입니다.";
	buildingarray[7].building_cost[0] = 650;
	buildingarray[7].building_cost[1] = 550;
	buildingarray[7].building_cost[2] = 240;

	// 예술의 전당
	buildingarray[8].bexist = FALSE;
	buildingarray[8].bshow = FALSE;		// 쳅터4 시작에 등장한다.
	buildingarray[8].Disabled = FALSE;
	buildingarray[8].remaintime = BUILDING_ART_TIME(25);
	buildingarray[8].inittime = buildingarray[8].remaintime;
	SetRect(&buildingarray[8].buildingrect, 581, 447, 631, 468);
	buildingarray[8].middlepoint.x = 581 + (631-581)/2;
	buildingarray[8].middlepoint.y = 447 + (468-447)/2;
	buildingarray[8].buildingtype = "예술의 전당";
	buildingarray[8].describe_building = "예술의 전당\n\n평생 일만 할 줄 알았던 "
										"개미 왕국에 활기를 주는 대전당입니다. 그곳에서 "
										"개미들은 지친몸을 추스리며 노래를 부르거나 "
										"다른 개미의 작품을 감상합니다.";
	buildingarray[8].building_cost[0] = 920;
	buildingarray[8].building_cost[1] = 1200;
	buildingarray[8].building_cost[2] = 650;

	building_under_construction = NULL;

	return 1;
}

int CBuilding::PrintBuildingMenu()
{
	DDraw_Text("건설",
			BUILDING_TITLE_X,
			BUILDING_TITLE_Y,
			15,
			lpddsback,
			RGB(255,0,0),
			TA_CENTER,
			NULL,
			TRANSPARENT);

	if(BUILDING_STATE == BUILDING_RUN)
	{
		for(int i=0; i<MAX_BUILDING; i++)
		{
			if(buildingarray[i].bshow == TRUE)
			{
				if((buildingarray[i].bexist == TRUE) || (buildingarray[i].Disabled == TRUE))
				{
					DDraw_Text(buildingarray[i].buildingtype, 
							buildingarray[i].middlepoint.x,
							buildingarray[i].middlepoint.y,
							11,
							lpddsback,
							RGB(60,60,60),
							TA_CENTER,
							NULL,
							TRANSPARENT);
				}
				else
				{
					DDraw_Text(buildingarray[i].buildingtype, 
							buildingarray[i].middlepoint.x,
							buildingarray[i].middlepoint.y,
							11,
							lpddsback,
							RGB(160,160,160),
							TA_CENTER,
							NULL,
							TRANSPARENT);
				}
			}
		}
	}
	else
	{
		for(int i=0; i<MAX_BUILDING; i++)
		{
			if(buildingarray[i].bshow == TRUE)
			{
				if((buildingarray[i].bexist == TRUE) || (buildingarray[i].Disabled == TRUE))
				{
					DDraw_Text(buildingarray[i].buildingtype, 
							buildingarray[i].middlepoint.x,
							buildingarray[i].middlepoint.y,
							11,
							lpddsback,
							RGB(60,60,60),
							TA_CENTER,
							NULL,
							TRANSPARENT);
				}
				else
				{
					DDraw_Text(buildingarray[i].buildingtype, 
							buildingarray[i].middlepoint.x,
							buildingarray[i].middlepoint.y,
							11,
							lpddsback,
							RGB(255,255,255),
							TA_CENTER,
							NULL,
							TRANSPARENT);
				}
			}
		}
	}
	return 1;
}

int CBuilding::ShowDialog()
{
	for(int i=0; i<MAX_BUILDING; i++)
	{
		if(BUILDING_STATE == BUILDING_STOP)
		{
			if(buildingarray[i].bshow == TRUE)
			{
				if(buildingarray[i].Disabled == FALSE)
				{
					if(buildingarray[i].bexist == FALSE)
					{
						if(CheckRect(&buildingarray[i].buildingrect, mouse_x, mouse_y))
						{
							SoundClick();

							if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
							{
								if(hWndDlg_building)
									EndDialog(hWndDlg_building, TRUE );
								hWndDlg_building = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
									main_window_handle,  (DLGPROC)BuildingErrorDlgProc );
								SetDlgItemTextA(hWndDlg_building, IDC_NORMAL, "경고\n\n전쟁중에는 건설할 수 없습니다.");
								ShowWindow( hWndDlg_building, SW_SHOWNORMAL );

								WaitDialog();
								return 0;
							}

							if(hWndDlg_building)
								EndDialog( hWndDlg_building, TRUE );
							hWndDlg_building = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_UNDER_CONSTRUCTION),
								main_window_handle,  (DLGPROC)BuildingDlgProc );
							SendMessage(hWndDlg_building, WM_GETPOINT, (WPARAM)&buildingarray[i], (LPARAM)this);
							ShowWindow(hWndDlg_building, SW_SHOWNORMAL );
							SetDlgItemTextA(hWndDlg_building, IDC_STATIC_BUILDING, buildingarray[i].describe_building);
							sprintf(buffer,
								"필요 자원\n식량 : %d, 목재 : %d, 광석 : %d",
								buildingarray[i].building_cost[0],
								buildingarray[i].building_cost[1],
								buildingarray[i].building_cost[2]);
							SetDlgItemTextA(hWndDlg_building, IDC_STATIC_COST, buffer);
							if(CPlayer::num_worker_building == 0)
							{
								sprintf(buffer, "예상 공사기간 : '경고'건설을 담당하는 일꾼 개미들이 없습니다.");
								SetDlgItemTextA(hWndDlg_building, IDC_STATIC_PERIOD, buffer);
							}
							else
							{
								sprintf(buffer, "예상 공사기간 : %d일", buildingarray[i].inittime/CPlayer::num_worker_building/UNIT_PER_TICK/UNIT_PER_DAY);
								SetDlgItemTextA(hWndDlg_building, IDC_STATIC_PERIOD, buffer);
							}
							
							WaitDialog();
						}
					}
				}
			}
		}
	}

	return 1;
}

HWND CBuilding::GetHwnDia_Building()
{
	return hWndDlg_building;
}

int CBuilding::CheckBuildingTime()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	int temp_building;

	for(int i=0; i<MAX_BUILDING; i++)
	{
		if(buildingarray[i].bshow == TRUE)
		{
			if(buildingarray[i].bexist == FALSE)
			{
				if(building_under_construction == buildingarray[i].buildingtype)
				{
					temp_building = CPlayer::num_worker_building;

					if(objdialog_.labflag & LAB_3_DONE)
						temp_building *= 1.4;
					if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
						temp_building *= 1.1;
					buildingarray[i].remaintime -= temp_building;
					debug_.GetValue("remaintime", &buildingarray[i].remaintime, 0, lpddsback, 15, ONLY_V1);
					if(buildingarray[i].remaintime < 0)
					{
						buildingarray[i].bexist = TRUE;
						BUILDING_STATE = BUILDING_STOP;
						building_under_construction = NULL;
						if(buildingarray[i].buildingtype == "도서관")
						{
							object_.ChangeObjTemp(OBJARRAY_BUILDING_LIBARAY, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_LIBARAY], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "자원 보관소")
						{
							domestic_.UpgradeMaxResource();
							object_.ChangeObjTemp(OBJARRAY_BUILDING_DEPOSITORY, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_DEPOSITORY], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "화학 연구소")
						{
							object_.ChangeObjTemp(OBJARRAY_BUILDING_LAB, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_LAB], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "전투 연습실")
						{
							object_.ChangeObjTemp(OBJARRAY_BUILDING_TRAINING, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_TRAINING], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "버섯 재배실")
						{
							object_.ChangeObjTemp(OBJARRAY_BUILDING_MUSHROOM, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_MUSHROOM], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "용병양성소1")
						{
							buildingarray[BUILDINGARRAY_HIRED_2].Disabled = TRUE;
							object_.ChangeObjTemp(OBJARRAY_BUILDING_HIRED_1, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_HIRED_1], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "용병양성소2")
						{
							buildingarray[BUILDINGARRAY_HIRED_1].Disabled = TRUE;
							object_.ChangeObjTemp(OBJARRAY_BUILDING_HIRED_2, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_HIRED_2], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "종교 회관")
						{
							diplomatic_.EnablePropagation();
							object_.ChangeObjTemp(OBJARRAY_BUILDING_CHURCH, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_CHURCH], 0, &ThreadID);
						}
						if(buildingarray[i].buildingtype == "예술의 전당")
						{
							object_.ChangeObjTemp(OBJARRAY_BUILDING_ART, BULIDING_INT_STATE, BUILDING_DONE);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_ART], 0, &ThreadID);
						}
					}
				}
			}
		}
	}

	return 1;
}


int CBuilding::ShowBuilding(int BUILDINGARRAY_INDEX)
{
	buildingarray[BUILDINGARRAY_INDEX].bshow = TRUE;

	return 1;
}
int CBuilding::DisableBuilding(int BUILDINGARRAY_INDEX)
{
	buildingarray[BUILDINGARRAY_INDEX].Disabled = TRUE;

	return 1;
}
int CBuilding::Building_Shutdown()
{

	return 1;
}

DWORD WINAPI CBuilding::ThreadBuilding(LPVOID temp)
{
	CObject::_object *pobject = (CObject::_object *)temp;

	CTime::SetPause();

	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);

	if((pobject->name == "도서관") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Libaray_Init();
	if((pobject->name == "도서관") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
		screen_.Upgrade_Libaray_Done();

	if((pobject->name == "자원 보관소") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Depository_Init();
	if((pobject->name == "자원 보관소") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
		screen_.Upgrade_Depository_Done();

	if((pobject->name == "화학 연구소") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Lab_Init();
	if((pobject->name == "화학 연구소") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_SCIENTIST);
		screen_.Upgrade_Lab_Done();
	}

	if((pobject->name == "전투 연습실") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Training_Init();
	if((pobject->name == "전투 연습실") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_TRAING_ANT);
		screen_.Upgrade_Training_Done();
	}

	if((pobject->name == "버섯 재배실") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Mushroom_Init();
	if((pobject->name == "버섯 재배실") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_MUSHROOM_ANT);
		screen_.Upgrade_Mushroom_Done();
	}

	if((pobject->name == "용병양성소-장수풍뎅이") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Hired_Init();
	if((pobject->name == "용병양성소-장수풍뎅이") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_HIRED_1);
		screen_.Upgrade_Hired_Done();
	}

	if((pobject->name == "용병양성소-사슴벌레") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Hired_Init();
	if((pobject->name == "용병양성소-사슴벌레") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_HIRED_2);
		screen_.Upgrade_Hired_Done();
	}

	if((pobject->name == "종교 회관") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Church_Init();
	if((pobject->name == "종교 회관") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_CHURCH_ANT);
		screen_.Upgrade_Church_Done();
	}

	if((pobject->name == "예술의 전당") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION))
		screen_.Upgrade_Art_Init();
	if((pobject->name == "예술의 전당") && (pobject->temp[BULIDING_INT_STATE] == BUILDING_DONE))
	{
		object_.ShowObjBob(OBJARRAY_ART_ANT_1);
		object_.ShowObjBob(OBJARRAY_ART_ANT_2);
		screen_.Upgrade_Art_Done();
	}
	
	Sleep(100);

	ReturnScreenGamma(FALSE);

	CTime::ReleasePause();

	hthread = NULL;

	return 1;
}



INT_PTR CALLBACK CBuilding::BuildingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CBuilding *pThis = NULL; 
	static _building *pbuilding = NULL;
	RECT rt;

    switch (msg)
    {
        case WM_INITDIALOG:
			
            return TRUE;
		case WM_GETPOINT:
			pThis = (CBuilding *)lParam; 
			pbuilding = (_building *)wParam;
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_building = NULL;
					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_building = NULL;

					if((pbuilding->building_cost[0] > CPlayer::food/NUM_CIPHER)
						|| (pbuilding->building_cost[1] > CPlayer::timber/NUM_CIPHER)
						|| (pbuilding->building_cost[2] > CPlayer::mineral/NUM_CIPHER))
					{
						if(hWndDlg_building)
							EndDialog(hWndDlg_building, TRUE );
						hWndDlg_building = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)BuildingErrorDlgProc );
						SetDlgItemTextA(hWndDlg_building, IDC_NORMAL, "경고\n\n자원이 부족합니다.");
						ShowWindow( hWndDlg_building, SW_SHOWNORMAL );

						WaitDialog();
						return TRUE;

					}
					if(pbuilding->buildingtype == "도서관")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_LIBARAY);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_LIBARAY], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "자원 보관소")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_DEPOSITORY);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_DEPOSITORY], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "화학 연구소")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_LAB);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_LAB], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "전투 연습실")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_TRAINING);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_TRAINING], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "버섯 재배실")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_MUSHROOM);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_MUSHROOM], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "용병양성소1")
					{
						if(objdialog_.labflag & LAB_12_DONE)
						{
							object_.EnableBuildingObj(OBJARRAY_BUILDING_HIRED_1);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_HIRED_1], 0, &ThreadID);
						}
						else
						{
							if(hWndDlg_building)
								EndDialog(hWndDlg_building, TRUE );
							hWndDlg_building = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
								main_window_handle,  (DLGPROC)BuildingErrorDlgProc );
							SetDlgItemTextA(hWndDlg_building, IDC_NORMAL, "경고\n\n고용하려는 용병의 언어를 배우지 않았습니다.");
							ShowWindow( hWndDlg_building, SW_SHOWNORMAL );

							WaitDialog();
							return TRUE;
						}
					}
					if(pbuilding->buildingtype == "용병양성소2")
					{
						if(objdialog_.labflag & LAB_13_DONE)
						{
							object_.EnableBuildingObj(OBJARRAY_BUILDING_HIRED_2);
							DWORD ThreadID;
							hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_HIRED_2], 0, &ThreadID);
						}
						else
						{
							if(hWndDlg_building)
								EndDialog(hWndDlg_building, TRUE );
							hWndDlg_building = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
								main_window_handle,  (DLGPROC)BuildingErrorDlgProc );
							SetDlgItemTextA(hWndDlg_building, IDC_NORMAL, "경고\n\n고용하려는 용병의 언어를 배우지 않았습니다.");
							ShowWindow( hWndDlg_building, SW_SHOWNORMAL );

							WaitDialog();
							return TRUE;
						}
					}
					if(pbuilding->buildingtype == "종교 회관")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_CHURCH);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_CHURCH], 0, &ThreadID);
					}
					if(pbuilding->buildingtype == "예술의 전당")
					{
						object_.EnableBuildingObj(OBJARRAY_BUILDING_ART);
						DWORD ThreadID;
						hthread = CreateThread(NULL, 0,ThreadBuilding, (LPVOID)&object_.objarray[OBJARRAY_BUILDING_ART], 0, &ThreadID);
					}
					pThis->building_under_construction = pbuilding->buildingtype;
					BUILDING_STATE = BUILDING_RUN;
					domestic_.ChangeResource(-pbuilding->building_cost[0]*NUM_CIPHER,
											 -pbuilding->building_cost[1]*NUM_CIPHER,
											 -pbuilding->building_cost[2]*NUM_CIPHER);
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
           hWndDlg_building = NULL;
            break;
    }

    return FALSE;
}

INT_PTR CALLBACK CBuilding::BuildingErrorDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
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
					hWndDlg_building = NULL;

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
			hWndDlg_building = NULL;
            break;
    }

    return FALSE;
}
int CBuilding::Save()
{
	for(int i=0; i<MAX_BUILDING; i++)
		WriteFile(hfile, &buildingarray[i], sizeof(buildingarray[i]), &dwWritten, NULL);

	WriteFile(hfile, &building_under_construction, sizeof(building_under_construction), &dwWritten, NULL);

	return 1;
}
int CBuilding::Load()
{
	for(int i=0; i<MAX_BUILDING; i++)
		ReadFile(hfile, &buildingarray[i], sizeof(buildingarray[i]), &dwWritten, NULL);

	ReadFile(hfile, &building_under_construction, sizeof(building_under_construction), &dwWritten, NULL);

	return 1;
}
