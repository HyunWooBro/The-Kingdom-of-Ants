
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "CDomestic.h"
#include "resource.h"
#include "CBuilding.h"
#include "CDiplomatic.h"
#include "CObjDialog.h"
#include "CEvent.h"
#include "CDebug.h"
#include "CSpecies.h"
#include "CStory.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CTime.h"
#include "CInfo.h"

extern CDebug debug_;
extern CStory story_;
extern CInfo info_;
extern CObjDialog objdialog_;
extern CBuilding building_;
extern CItem item_;
extern CTime time_;
extern CDiplomatic diplomatic_;

extern int SoundClick();
extern int ReturnScreenGamma(BOOL blong, int delay = 70);
extern int ChangeScreenGamma(int effect, BOOL blong, int delay = 70);

INT_PTR CALLBACK DomWorkerDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

HWND CDomestic::hWndDlg_dom = NULL;


int CDomestic::Domestic_Init()
{
	domarray[0].domtype = "일꾼";
	domarray[0].remaintime = 0;
	domarray[0].Disalbed = FALSE;
	SetRect(&domarray[0].domrect, 582, 82, 629, 104);
	domarray[0].middlepoint.x = 582 + (629-582)/2;
	domarray[0].middlepoint.y = 82 + (104-82)/2;
	domarray[0].panel[0] = 10;
	domarray[0].panel[1] = 0;
	domarray[0].panel[2] = 0;
	domarray[0].panel[3] = 0;
	domarray[0].changeday = 3;
	sprintf(domarray[0].describe_dom, "일꾼 개미들의 작업을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[0].changeday);
	domarray[0].changevalue = 3;
	
	domarray[1].domtype = "병정";
	domarray[1].remaintime = 0;
	domarray[1].Disalbed = FALSE;
	SetRect(&domarray[1].domrect, 581, 112, 628, 137);
	domarray[1].middlepoint.x = 581 + (628-581)/2;
	domarray[1].middlepoint.y = 112 + (137-112)/2;
	domarray[1].panel[0] = 5;
	domarray[1].panel[1] = 0;
	domarray[1].panel[2] = 0;
	domarray[1].panel[3] = 0;
	domarray[1].changeday = 3;
	sprintf(domarray[1].describe_dom, "병정 개미들의 작업을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[1].changeday);
	domarray[1].changevalue = 2;

	domarray[2].domtype = "여왕";
	domarray[2].remaintime = 0;
	domarray[2].Disalbed = FALSE;
	SetRect(&domarray[2].domrect, 580, 141, 630, 165);
	domarray[2].middlepoint.x = 580 + (630-580)/2;
	domarray[2].middlepoint.y = 141 + (165-141)/2;
	domarray[2].panel[0] = 4;
	domarray[2].panel[1] = 0;
	domarray[2].panel[2] = 0;
	domarray[2].panel[3] = 0;
	domarray[2].changeday = 5;
	sprintf(domarray[2].describe_dom, "여왕 개미의 알을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[2].changeday);
	domarray[2].changevalue = 1;

	return 1;
}

int CDomestic::Resource_Init()
{
	CPlayer::foodgap = CPlayer::food;
	CPlayer::timbergap = CPlayer::timber;
	CPlayer::mineralgap = CPlayer::mineral;

	if(CPlayer::food < 0)
		CPlayer::food = 0;
	if(CPlayer::timber < 0)
		CPlayer::timber = 0;
	if(CPlayer::mineral < 0)
		CPlayer::mineral = 0;

	return 1;
}
int CDomestic::Resource_Final()
{
	CPlayer::foodgap = CPlayer::food - CPlayer::foodgap;
	CPlayer::timbergap = CPlayer::timber - CPlayer::timbergap;
	CPlayer::mineralgap = CPlayer::mineral - CPlayer::mineralgap;

	return 1;
}

int CDomestic::CheckPrintTime()
{
	for(int i=0; i<MAX_DOM; i++)
	{
		if(domarray[i].Disalbed == TRUE)
		{
			domarray[i].remaintime--;
			if(domarray[i].remaintime == 0)
				domarray[i].Disalbed = FALSE;
		}
	}

	return 1;
}

int CDomestic::PrintDomMenu()
{

	if(SCREEN_STATE != SCREEN_MAP)
		DDraw_Text("내정",
				DOM_TITLE_X,
				DOM_TITLE_Y,
				15,
				lpddsback,
				RGB(255,0,0),
				TA_CENTER,
				NULL,
				TRANSPARENT);

	for(int i=0; i<MAX_DOM; i++)
	{
		if(SCREEN_STATE != SCREEN_MAP)
		{
			if(domarray[i].Disalbed == FALSE)
				DDraw_Text(domarray[i].domtype, 
						domarray[i].middlepoint.x,
						domarray[i].middlepoint.y,
						17,
						lpddsback,
						RGB(255,255,255),
						TA_CENTER,
						NULL,
						TRANSPARENT);

			else
				DDraw_Text(domarray[i].domtype, 
						domarray[i].middlepoint.x,
						domarray[i].middlepoint.y,
						17,
						lpddsback,
						RGB(160,160,160),
						TA_CENTER,
						NULL,
						TRANSPARENT);
		}
	}
	
	return 1;
}

int CDomestic::ShowDialog()
{
	for(int i=0; i<MAX_DOM; i++)
	{
		if(SCREEN_STATE != SCREEN_MAP)
		{
			if(domarray[i].Disalbed == FALSE)
			{
				if(CheckRect(&domarray[i].domrect, mouse_x, mouse_y))
				{
					SoundClick();

					if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
					{
						if(hWndDlg_dom)
							EndDialog(hWndDlg_dom, TRUE );
						hWndDlg_dom = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dom, IDC_NORMAL, "경고\n\n전쟁중에는 변경할 수 없습니다.");
						ShowWindow(hWndDlg_dom, SW_SHOWNORMAL );

						WaitDialog();

						return 0;
					}
					if(domarray[i].domtype == "일꾼")
					{
						if(hWndDlg_dom)
							EndDialog( hWndDlg_dom, TRUE );
						hWndDlg_dom = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DOM_WORKER),
							main_window_handle,  (DLGPROC)DomWorkerDlgProc );
						SendMessage(hWndDlg_dom, WM_GETPOINT, NULL, (LPARAM)this);
						ShowWindow( hWndDlg_dom, SW_SHOWNORMAL );

						WaitDialog();
					}
					if(domarray[i].domtype == "병정")
					{
						if(hWndDlg_dom)
							EndDialog( hWndDlg_dom, TRUE );
						hWndDlg_dom = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DOM_SOLDIER),
							main_window_handle,  (DLGPROC)DomSoldierDlgProc );
						SendMessage(hWndDlg_dom, WM_GETPOINT, NULL, (LPARAM)this);
						ShowWindow( hWndDlg_dom, SW_SHOWNORMAL );

						WaitDialog();
					}
					if(domarray[i].domtype == "여왕")
					{
						if(hWndDlg_dom)
							EndDialog( hWndDlg_dom, TRUE );
						hWndDlg_dom = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DOM_QUEEN),
							main_window_handle,  (DLGPROC)DomQueenDlgProc );
						SendMessage(hWndDlg_dom, WM_GETPOINT, NULL, (LPARAM)this);
						ShowWindow( hWndDlg_dom, SW_SHOWNORMAL );

						WaitDialog();
					}
				}
			}
		}
	}


	return 1;
}

int CDomestic::PrintResource()
{
	itoa(CPlayer::food/NUM_CIPHER, buffer, 10);
	if(CPlayer::foodgap >= 0)
		DDraw_Text(buffer, 
					FOOD_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,255,255),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
	else
		DDraw_Text(buffer, 
					FOOD_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,0,0),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");

	itoa(CPlayer::timber/NUM_CIPHER, buffer, 10);
	if(CPlayer::timbergap >= 0)
		DDraw_Text(buffer, 
					TIMBER_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,255,255),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
	else
		DDraw_Text(buffer, 
					TIMBER_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,0,0),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
	
	itoa(CPlayer::mineral/NUM_CIPHER, buffer, 10);
	if(CPlayer::mineralgap >= 0)
		DDraw_Text(buffer, 
					MINERAL_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,255,255),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
	else
		DDraw_Text(buffer, 
					MINERAL_X,
					RESOURCE_Y,
					NULL,
					lpddsback,
					RGB(255,0,0),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
	
	return 1;
}

int CDomestic::ProduceResource()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	int find;
	int death;
	float temp_upgrade_lab = 1;
	float temp_upgrade_art = 1;

	// 영양 교환의 개선을 연구했다면 수색, 사냥의 효과 증가
	if(objdialog_.labflag & LAB_2_DONE)
		temp_upgrade_lab += 0.2;

	// 예술의 전당을 건설했다면 모든 활동의 효과 증가
	if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
		temp_upgrade_art += 0.1;

	// 수색
	find = rand()%10;
	if(time_.GetSeason() == SPRING)
	{
		if(find < 3)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0, (CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_SPRING * temp_upgrade_lab * temp_upgrade_art)*1.7);
		if((find > 2) && (find < 8))
			CPlayer::timber = CPlayer::timber + info_.ComputeResource(1,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_SPRING * temp_upgrade_lab * temp_upgrade_art)/1.9);
		if(find == 9)
			CPlayer::mineral = CPlayer::mineral + info_.ComputeResource(2,CPlayer::num_worker_search * temp_upgrade_lab * temp_upgrade_art);

		death = rand()%46;
		if(death == 0)
			if(CPlayer::num_worker_search > 0)
				CPlayer::num_worker_total -= NUM_SEARCH_COST_DEATH(CPlayer::num_worker_search);
	}
	if(time_.GetSeason() == SUMMER)
	{
		if(find < 3)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_SUMMER * temp_upgrade_lab * temp_upgrade_art)*1.7);
		if((find > 2) && (find < 8))
			CPlayer::timber = CPlayer::timber + info_.ComputeResource(1,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_SUMMER * temp_upgrade_lab * temp_upgrade_art)/1.9);
		if(find == 9)
			CPlayer::mineral = CPlayer::mineral + info_.ComputeResource(2,CPlayer::num_worker_search * temp_upgrade_lab * temp_upgrade_art);

		death = rand()%36;
		if(death == 0)
			if(CPlayer::num_worker_search > 0)
				CPlayer::num_worker_total -= NUM_SEARCH_COST_DEATH(CPlayer::num_worker_search);
	}
	if(time_.GetSeason() == FALL)
	{
		if(find < 3)
			CPlayer::food =  CPlayer::food +info_.ComputeResource(0, (CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_FALL * temp_upgrade_lab * temp_upgrade_art)*1.7);
		if((find > 2) && (find < 8))
			CPlayer::timber = CPlayer::timber + info_.ComputeResource(1,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_FALL * temp_upgrade_lab * temp_upgrade_art)/1.9);
		if(find == 9)
			CPlayer::mineral = CPlayer::mineral + info_.ComputeResource(2,CPlayer::num_worker_search * temp_upgrade_lab * temp_upgrade_art);

		death = rand()%42;
		if(death == 0)
			if(CPlayer::num_worker_search > 0)
				CPlayer::num_worker_total -= NUM_SEARCH_COST_DEATH(CPlayer::num_worker_search);
	}
	if(time_.GetSeason() == WINTER)
	{
		if(find < 3)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_WINTER * temp_upgrade_lab * temp_upgrade_art)*1.7);
		if((find > 2) && (find < 8))
			CPlayer::timber = CPlayer::timber + info_.ComputeResource(1,(CPlayer::num_worker_search * NUM_SEARCH_PRODUCE_WINTER * temp_upgrade_lab * temp_upgrade_art)/1.9);
		if(find == 9)
			CPlayer::mineral = CPlayer::mineral + info_.ComputeResource(2,CPlayer::num_worker_search * temp_upgrade_lab * temp_upgrade_art);

		death = rand()%50;
		if(death == 0)
			if(CPlayer::num_worker_search > 0)
				CPlayer::num_worker_total -= NUM_SEARCH_COST_DEATH(CPlayer::num_worker_search);
	}

	// 버섯 재배
	if(CPlayer::timber > CPlayer::num_worker_mushroom * NUM_MUSHROOM_COST_TIMBER)
	{
		CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::num_worker_mushroom * NUM_MUSHROOM_PRODUCE * temp_upgrade_art);
		CPlayer::timber = CPlayer::timber + info_.ComputeResource(1, -CPlayer::num_worker_mushroom * NUM_MUSHROOM_COST_TIMBER);
	}
	else
	{
		CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::timber * NUM_MUSHROOM_COST_TIMBER * NUM_MUSHROOM_PRODUCE * temp_upgrade_art);
		info_.ComputeResource(1, -CPlayer::timber);
		CPlayer::timber = 0;
	}
	

	// 진딧물 축사
	CPlayer::food = CPlayer::food + info_.ComputeResource(0,(CPlayer::num_worker_aphid * NUM_APHID_PRODUCE * temp_upgrade_art)/2);
	int lotte = rand()%140;
	if(lotte == 0)
		CPlayer::food = CPlayer::food + info_.ComputeResource(0,(CPlayer::num_worker_aphid * NUM_APHID_LOTTE_PRODUCE * temp_upgrade_art)/2);

	// 사냥
	find = rand()%10;
	if(time_.GetSeason() == SPRING)
	{
		if(find < 9)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::num_soldier_hunt * NUM_HUNT_PRODUCE_SPRING * temp_upgrade_lab * temp_upgrade_art);
		death = rand()%39;
		if(death == 0)
			if(CPlayer::num_soldier_hunt > 0)
				CPlayer::num_soldier_total -= NUM_HUNT_COST_DEATH(CPlayer::num_soldier_hunt);
								
	}
	if(time_.GetSeason() == SUMMER)
	{
		if(find < 9)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::num_soldier_hunt * NUM_HUNT_PRODUCE_SUMMER * temp_upgrade_lab * temp_upgrade_art);
		death = rand()%32;
		if(death == 0)
			if(CPlayer::num_soldier_hunt > 0)
				CPlayer::num_soldier_total -= NUM_HUNT_COST_DEATH(CPlayer::num_soldier_hunt);
	}
	if(time_.GetSeason() == FALL)
	{
		if(find < 9)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::num_soldier_hunt * NUM_HUNT_PRODUCE_FALL * temp_upgrade_lab * temp_upgrade_art);
		death = rand()%37;
		if(death == 0)
			if(CPlayer::num_soldier_hunt > 0)	
				CPlayer::num_soldier_total -= NUM_HUNT_COST_DEATH(CPlayer::num_soldier_hunt);
	}
	if(time_.GetSeason() == WINTER)
	{
		if(find < 9)
			CPlayer::food = CPlayer::food + info_.ComputeResource(0,CPlayer::num_soldier_hunt * NUM_HUNT_PRODUCE_WINTER * temp_upgrade_lab * temp_upgrade_art);
		death = rand()%47;
		if(death == 0)
			if(CPlayer::num_soldier_hunt > 0)
				CPlayer::num_soldier_total -= NUM_HUNT_COST_DEATH(CPlayer::num_soldier_hunt);
	}
	
	// 기타

	//광산의 개발
	if(objdialog_.labflag & LAB_9_DONE)
		CPlayer::mineral += info_.ComputeResource(2,NUM_MINE_PRODUCE * temp_upgrade_art);

	return 1;
}
int CDomestic::ConsumeFood()
{
	CPlayer::food += info_.ComputeResource(0,-(CPlayer::num_worker_total * NUM_CONSUME_WORKER));
	CPlayer::food += info_.ComputeResource(0,-((CPlayer::num_soldier_total-CPlayer::num_soldier_attack)
						* NUM_CONSUME_SOLDIER));
	CPlayer::food += info_.ComputeResource(0,-((CPlayer::num_hired_total-CPlayer::num_hired_attack) 
						* NUM_CONSUME_HIRED));
	if(story_.GetStoryFlag() & CHAP_2_4_DONE)
		CPlayer::food += info_.ComputeResource(0,-NUM_CONSUME_FINGER);

	return 1;
}

int CDomestic::CoputeAnts()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;
	
	int temp_penel;

	temp_penel = domarray[0].panel[3];
	CPlayer::num_worker_aphid =  temp_penel / 10.0 * CPlayer::num_worker_total;
	temp_penel = domarray[0].panel[2];
	CPlayer::num_worker_mushroom =  temp_penel / 10.0 * CPlayer::num_worker_total;
	temp_penel = domarray[0].panel[1];
	CPlayer::num_worker_building =  temp_penel / 10.0 * CPlayer::num_worker_total;
	CPlayer::num_worker_search = CPlayer::num_worker_total
							- CPlayer::num_worker_aphid
							- CPlayer::num_worker_mushroom
							- CPlayer::num_worker_building;

	temp_penel = domarray[1].panel[0];
	CPlayer::num_soldier_defence =  temp_penel / 10.0 * (CPlayer::num_soldier_total - CPlayer::num_soldier_attack);
	CPlayer::num_soldier_hunt =  (CPlayer::num_soldier_total - CPlayer::num_soldier_attack) 
							- CPlayer::num_soldier_defence;

	CPlayer::num_hired_defence =  CPlayer::num_hired_total - CPlayer::num_hired_attack;

	CPlayer::num_ants_total = CPlayer::num_worker_total
						+ CPlayer::num_soldier_total
						+ CPlayer::num_hired_total;

	return 1;
}

int CDomestic::ProduceAnts()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	// 현재 세력으로 다스릴 수 있는 개미 수에서 현재 개미 수를 빼서 생산해 낼 수
	// 있는 수를 구한다.
	int temp_produce_ants = (CPlayer::strength/NUM_CIPHER/MAX_STRENGTH_OVER_MAX_ANTS_AND_NUM_CIPHER)
						- CPlayer::num_ants_total;

	debug_.GetValue("num_worker, num_soldier", &CPlayer::num_worker_total, &CPlayer::num_soldier_total, lpddsback, 20, NULL);
	debug_.GetValue("num_soldier_defence, num_soldier_attack", &CPlayer::num_soldier_defence, &CPlayer::num_soldier_attack, lpddsback, 17, NULL);
	debug_.GetValue("num_hired_defence, num_hired_attack", &CPlayer::num_hired_defence, &CPlayer::num_hired_attack, lpddsback, 14, NULL);

	if(temp_produce_ants > 0)
	{
		if(temp_produce_ants > 30)
			temp_produce_ants = 30;		// 최고 30마리만 생산 가능

		// 로열젤리가 있으면 15마리가 더 증가
		if(item_.GetItem(2) == PLAYER)
			temp_produce_ants += 15;

		// 유충이 먹는 식량
		CPlayer::food += info_.ComputeResource(0,-temp_produce_ants/2);
		
		int temp_penel = domarray[2].panel[0];
		int temp_num_soldier = temp_penel / 10.0 * temp_produce_ants;
		int temp_num_worker = temp_produce_ants - temp_num_soldier;

		CPlayer::num_worker_total += temp_num_worker;
		CPlayer::num_soldier_total += temp_num_soldier;	
	}
	
	return 1;
}

int CDomestic::hire()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	if((building_.buildingarray[BUILDINGARRAY_HIRED_1].bexist == TRUE) ||
		(building_.buildingarray[BUILDINGARRAY_HIRED_2].bexist == TRUE))
	{
		if(objdialog_.GetHiredCheck() == FALSE)
		{
			int temp_hire = (CPlayer::strength/NUM_CIPHER/MAX_STRENGTH_OVER_MAX_HIRED_AND_NUM_CIPHER)
						- CPlayer::num_hired_total;
			if(temp_hire > 0)
			{
				if(temp_hire > 5)
					temp_hire = 5;

				CPlayer::num_hired_total += temp_hire;
			}
		}
	}

	return 1;
}
int CDomestic::ComputeOther()
{
	int temp_strength = 0;

	int temp_player_strength = 0;
	int temp_NPC_strength = 0;
	int temp_occupation = 0;

	//// 불만 //////////////////////////////////////////////////

	if(building_.buildingarray[BUILDINGARRAY_CHURCH].bexist == TRUE)
		CPlayer::unsatisfactory += NUM_UNSATISFACTORY_CHURCH;

	if(CPlayer::food < 0)
		CPlayer::unsatisfactory += abs(CPlayer::food);
	else
		CPlayer::unsatisfactory -= RELEASE_UNSATISFACTORY;

	if(objdialog_.labflag & LAB_11_DONE)
		CPlayer::unsatisfactory -= UPGRADE_RELEASE_UNSATISFACTORY;
	if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
		CPlayer::unsatisfactory -= UPGRADE_RELEASE_UNSATISFACTORY;

	if(CPlayer::unsatisfactory > MAX_UNSATISFACTORY)
	{
		CloseAllDialog();

		CTime::SetPause();

		if(hWndDlg_gameover)
			EndDialog(hWndDlg_gameover, TRUE );
		hWndDlg_gameover = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_GAMEOVER),
			main_window_handle,  (DLGPROC)GameoverDlgProc );
		SetDlgItemTextA(hWndDlg_gameover, IDC_STATIC_GAMEOVER, 
			"알림\n\n결국 개미들에게 쌓여 있던 불만이 폭발했습니다. "
			"개미들은 왕국을 파괴하고 여왕을 살해했습니다. 암개미 1호의 "
			"왕국은 역사의 뒤안길로 사라졌습니다.");
		ShowWindow(hWndDlg_gameover, SW_SHOWNORMAL );

		WaitDialog();

		return 0;
	}
	if(CPlayer::unsatisfactory < 0)
			CPlayer::unsatisfactory = 0;

	debug_.GetValue("불만", &CPlayer::unsatisfactory, 0, lpddsback, 18, ONLY_V1);

	//// 세력 ////////////////////////////////////////////

	// 시간에 따른

	if(CPlayer::food > 0)
	{
		if(BATTLE_IN_STATE == BATTLE_IN_NO)
			CPlayer::strength_time += PERIODICAL_STRENGTH_INCREASE;
	}

	// 데미지에 따른
	temp_strength -= CPlayer::strength_damege;
		
	// 자원에 따른
	temp_strength += CPlayer::food/NUM_CIPHER;
	temp_strength += CPlayer::timber/NUM_CIPHER*1.5;
	temp_strength += CPlayer::mineral/NUM_CIPHER*2;

	// 개미 수에 따른
	temp_strength += CPlayer::num_ants_total*4;

	// 건물에 따른
	if(building_.buildingarray[0].bexist == TRUE)
		temp_strength += NUM_LIBRARY_STRENGTH;
	if(building_.buildingarray[1].bexist == TRUE)
		temp_strength += NUM_DEPOSITORY_STRENGTH;
	if(building_.buildingarray[2].bexist == TRUE)
		temp_strength += NUM_LAB_STRENGTH;
	if(building_.buildingarray[3].bexist == TRUE)
		temp_strength += NUM_TRAINING_STRENGTH;
	if(building_.buildingarray[4].bexist == TRUE)
		temp_strength += NUM_MUSHROOM_STRENGTH;
	if(building_.buildingarray[5].bexist == TRUE)
		temp_strength += NUM_HIRED_1_STRENGTH;
	if(building_.buildingarray[6].bexist == TRUE)
		temp_strength += NUM_HIRED_2_STRENGTH;
	if(building_.buildingarray[7].bexist == TRUE)
		temp_strength += NUM_CHURCH_STRENGTH;
	if(building_.buildingarray[8].bexist == TRUE)
		temp_strength += NUM_ART_STRENGTH;

	// 아이템에 따른
	if(item_.GetItem(0) == PLAYER)
		temp_strength += 150*NUM_CIPHER;
	if(item_.GetItem(1) == PLAYER)
		temp_strength += 25*NUM_CIPHER;
	if(item_.GetItem(6) == PLAYER)
		temp_strength += 20*NUM_CIPHER;
	if(item_.GetItem(8) == PLAYER)
		temp_strength += 30*NUM_CIPHER;
	if(item_.GetItem(9) == PLAYER)
		temp_strength += 40*NUM_CIPHER;

	// 연구에 따른
	if(objdialog_.labflag & LAB_1_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_2_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_3_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_4_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_5_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_6_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_7_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_8_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_9_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_10_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_11_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_12_DONE)
		temp_strength += NUM_EXP_STRENGTH;
	if(objdialog_.labflag & LAB_13_DONE)
		temp_strength += NUM_EXP_STRENGTH;

	// 불만에 따른
	temp_strength -= CPlayer::unsatisfactory/10;
	if(temp_strength < -INIT_STRENGTH)
		temp_strength = 0;
	
	// 세력 총합
	CPlayer::strength = INIT_STRENGTH +  temp_strength + CPlayer::strength_time;
	if(CPlayer::strength > MAX_STRENGTH)
		CPlayer::strength = MAX_STRENGTH;

	//// 장악력 ////////////////////////////////////////////

	temp_player_strength = CPlayer::strength;

	for(int i=0; i<MAX_SPECIES; i++)
	{
		if(CSpecies::speciesarray[i].Disalbed == FALSE)
		{
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_OCCUPIED)
				temp_player_strength += CSpecies::speciesarray[i].strength;
			else
				temp_NPC_strength += CSpecies::speciesarray[i].strength;
		}
	}
	
	CPlayer::occupation = GETPERCENT(temp_player_strength, (temp_player_strength+temp_NPC_strength));
	
	debug_.GetValue("strength, occupation", &CPlayer::strength, &CPlayer::occupation, lpddsback, 19, NULL);



	//// 보정 ///////////////////////////////////////////////

	if(CPlayer::food < 0)
		CPlayer::food = 0;
	if(CPlayer::timber < 0)
		CPlayer::timber = 0;
	if(CPlayer::mineral < 0)
		CPlayer::mineral = 0;

	if(CPlayer::food > CPlayer::max_food)
		CPlayer::food = CPlayer::max_food;
	if(CPlayer::timber > CPlayer::max_timber)
		CPlayer::timber = CPlayer::max_timber;
	if(CPlayer::mineral > CPlayer::max_mineral)
		CPlayer::mineral = CPlayer::max_mineral;

	return 1;
}

int CDomestic::ChangeResource(int food, int timber, int mineral)
{
	CPlayer::food += food;
	CPlayer::timber += timber;
	CPlayer::mineral += mineral;

	if(CPlayer::food < 0)
	{
		CPlayer::unsatisfactory += abs(CPlayer::food);
		CPlayer::food = 0;
	}
	if(CPlayer::timber < 0)
		CPlayer::timber = 0;
	if(CPlayer::mineral < 0)
		CPlayer::mineral = 0;

	if(CPlayer::food > CPlayer::max_food)
		CPlayer::food = CPlayer::max_food;
	if(CPlayer::timber > CPlayer::max_timber)
		CPlayer::timber = CPlayer::max_timber;
	if(CPlayer::mineral > CPlayer::max_mineral)
		CPlayer::mineral = CPlayer::max_mineral;

	return 1;
}
int CDomestic::ChangeUnsatisfactory(int value)
{
	CPlayer::unsatisfactory += value;
	if(CPlayer::unsatisfactory > MAX_UNSATISFACTORY)
	{
		CPlayer::unsatisfactory = MAX_UNSATISFACTORY;
		// game over
	}
	if(CPlayer::unsatisfactory < 0)
		CPlayer::unsatisfactory = 0;

	return 1;
}

int CDomestic::UpgradeDom(int LAB_INDEX)
{
	if(LAB_INDEX == LAB_7_DONE)
		for(int i=0; i<MAX_DOM; i++)
			domarray[i].changevalue++;
	if(LAB_INDEX == LAB_9_DONE)
	{
		domarray[0].changeday--;
		sprintf(domarray[0].describe_dom, "일꾼 개미들의 작업을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[0].changeday);

		domarray[1].changeday--;
		sprintf(domarray[1].describe_dom, "병정 개미들의 작업을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[1].changeday);

		domarray[2].changeday--;
		sprintf(domarray[2].describe_dom, "여왕 개미의 알을 배분하십시오.변경 후 %d일동안은 조작할 수 없습니다.", domarray[2].changeday);
	}

	return 1;
}
int CDomestic::UpgradeMaxResource()
{
	CPlayer::max_food = UPGRADE_MAX_FOOD;
	CPlayer::max_timber = UPGRADE_MAX_TIMBER;
	CPlayer::max_mineral = UPGRADE_MAX_MINERAL;

	return 1;
}
int CDomestic::HelpAhpid()
{
	if(CPlayer::num_soldier_defence > 3)
	{
		CPlayer::num_soldier_total -= 3;
		return 1;
	}
	else
		return 0;
}
int CDomestic::ReturnFromBattle()
{
	CPlayer::num_soldier_attack = 0;
	CPlayer::num_hired_attack = 0;

	return 1;
}
int CDomestic::ComputeAttAnts(int num_soldier_attack, int num_hired_attack)
{	
	int temp_num_soldier_attack;
	int temp_num_hired_attack;

	temp_num_soldier_attack = CPlayer::num_soldier_attack - num_soldier_attack;
	temp_num_hired_attack = CPlayer::num_hired_attack - num_hired_attack;

	CPlayer::num_soldier_attack = num_soldier_attack;
	CPlayer::num_hired_attack = num_hired_attack;

	CPlayer::num_soldier_total -= temp_num_soldier_attack;
	CPlayer::num_hired_total -= temp_num_hired_attack;

	CPlayer::num_ants_total = CPlayer::num_worker_total
						+ CPlayer::num_soldier_total
						+ CPlayer::num_hired_total;

	return 1;
}
int CDomestic::ComputeDefAnts(int num_soldier_defence, int num_hired_defence)
{
	int temp_num_soldier_defence;
	int temp_num_hired_defence;

	temp_num_soldier_defence = CPlayer::num_soldier_defence - num_soldier_defence;
	temp_num_hired_defence = CPlayer::num_hired_defence - num_hired_defence;

	CPlayer::num_soldier_defence = num_soldier_defence;
	CPlayer::num_hired_defence = num_hired_defence;

	CPlayer::num_soldier_total -= temp_num_soldier_defence;
	CPlayer::num_hired_total -= temp_num_hired_defence;

	CPlayer::num_ants_total = CPlayer::num_worker_total
						+ CPlayer::num_soldier_total
						+ CPlayer::num_hired_total;

	return 1;
}
HWND CDomestic::GetHwnDialog_Dom()
{
	return hWndDlg_dom;
}
int CDomestic::GetMaxPanel(int firstpanel, int secondpanel, int thirdpanel, 
						  int firstcheck, int secondcheck, int thirdcheck)
{
	int value;
	int maxpanel;

	_3C3_123
	{
		if(firstpanel > secondpanel)
		{
			maxpanel = FIRST_PANEL;
			value = firstpanel;
		}
		else
		{
			maxpanel = SECOND_PANEL;
			value = secondpanel;
		}
		if(value > thirdpanel)
		{
			return maxpanel;
		}
		else
			return THIRD_PANEL;
	}

	_3C2_12
	{
		if(firstpanel > secondpanel)
			return FIRST_PANEL;
		else
			return SECOND_PANEL;
	}

	_3C2_13
	{
		if(firstpanel > thirdpanel)
			return FIRST_PANEL;
		else
			return THIRD_PANEL;
	}

	_3C2_23
	{
		if(secondpanel > thirdpanel)
			return SECOND_PANEL;
		else
			return THIRD_PANEL;
	}

	_3C1_1
		return FIRST_PANEL;

	_3C1_2
		return SECOND_PANEL;

	_3C1_3
		return THIRD_PANEL;

	return 0;
}



int CDomestic::GetMinPanel(int firstpanel, int secondpanel, int thirdpanel, 
					int firstcheck, int secondcheck, int thirdcheck)
{
	int value;
	int minpanel;

	_3C3_123
	{
		if(firstpanel > secondpanel)
		{
			minpanel = SECOND_PANEL;
			value = secondpanel;
		}
		else
		{
			minpanel = FIRST_PANEL;
			value = firstpanel;
		}
		if(value > thirdpanel)
		{
			minpanel = THIRD_PANEL;
			return minpanel;	
		}
		else
		{
			return minpanel;	
		}
	}

	_3C2_12
	{
		if(firstpanel > secondpanel)
			return SECOND_PANEL;
		else
			return FIRST_PANEL;
	}

	_3C2_13
	{
		if(firstpanel > thirdpanel)
			return THIRD_PANEL;
		else
			return FIRST_PANEL;
	}
	
	_3C2_23
	{
		if(secondpanel > thirdpanel)
			return THIRD_PANEL;
		else
			return SECOND_PANEL;
	}

	_3C1_1
	{
		return FIRST_PANEL;
	}

	_3C1_2
	{
		return SECOND_PANEL;
	}

	_3C1_3
	{
		return THIRD_PANEL;
	}

	return 0;
}

DWORD WINAPI CDomestic::ThreadGameover(LPVOID temp)
{
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE, 100);
	
	window_closed = 1;
	GAME_STATE = GAME_OVER;
	CTime::ReleasePause();
	
	// 마무리와 초기화할 시간동안
	Sleep(2500);

	ReturnScreenGamma(FALSE);

	return 1;
}
INT_PTR CALLBACK CDomestic::DomWorkerDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDomestic* pThis; 
	static HWND hslider1;
	static HWND hslider2;
	static HWND hslider3;
	static HWND hslider4;
	static HWND hcheck1;
	static HWND hcheck2;
	static HWND hcheck3;
	static HWND hcheck4;
	static HWND hstatic_mushroom;
	static HWND hstatic_aphid;
	static HWND hedit1;

	static int changevalue;
	static int oldpanel1;
	static int oldpanel2;
	static int oldpanel3;
	static int oldpanel4;

	static int initpanel1;
	static int initpanel2;
	static int initpanel3;
	static int initpanel4;

	char buf[10];

	int panel1;
	int panel2;
	int panel3;
	int panel4;

	int testvalue;

    switch (msg)
    {
		SetCursor(LoadCursor(main_instance, MAKEINTRESOURCE(CURSOR_CROSSHAIR)));

        case WM_INITDIALOG:
			hslider1 = GetDlgItem(hDlg, IDC_DOM_SLIDER1);
			hslider2 = GetDlgItem(hDlg, IDC_DOM_SLIDER2);
			hslider3 = GetDlgItem(hDlg, IDC_DOM_SLIDER3);
			hslider4 = GetDlgItem(hDlg, IDC_DOM_SLIDER4);
			hcheck1 = GetDlgItem(hDlg, IDC_DOM_CHECK1);
			hcheck2 = GetDlgItem(hDlg, IDC_DOM_CHECK2);
			hcheck3 = GetDlgItem(hDlg, IDC_DOM_CHECK3);
			hcheck4 = GetDlgItem(hDlg, IDC_DOM_CHECK4);
			hstatic_mushroom = GetDlgItem(hDlg, IDC_WORKER_MUSHROOM);
			hstatic_aphid = GetDlgItem(hDlg, IDC_WORKER_APHID);
			hedit1 = GetDlgItem(hDlg, IDC_DOM_EDIT1);
			
			SendMessage(hslider1, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));
			SendMessage(hslider2, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));
			SendMessage(hslider3, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));
			SendMessage(hslider4, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));

            return TRUE;
		case WM_HSCROLL:
			panel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);
			panel2 = SendMessage(hslider2, TBM_GETPOS, 0, 0);
			panel3 = SendMessage(hslider3, TBM_GETPOS, 0, 0);
			panel4 = SendMessage(hslider4, TBM_GETPOS, 0, 0);

			if((HWND)lParam == hslider1)
			{
				if((IsWindowEnabled(hslider1) == TRUE) && 
					(SendMessage(hcheck1, BM_GETCHECK, 0, 0) == BST_UNCHECKED))
				{
					int whichpenel;
					int value;

					if(oldpanel1 > panel1)
					{
						whichpenel = pThis->GetMinPanel(
									panel2, 
									panel3, 
									panel4,
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = oldpanel1 - panel1;
						if(whichpenel == FIRST_PANEL)
							panel2 += value;
						if(whichpenel == SECOND_PANEL)
							panel3 += value;
						if(whichpenel == THIRD_PANEL)
							panel4 += value;
					}
					if(oldpanel1 < panel1)
					{
						
						whichpenel = pThis->GetMaxPanel(
									panel2, 
									panel3, 
									panel4,
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = panel1 - oldpanel1;
						if(whichpenel == FIRST_PANEL)
							panel2 -= value;
						if(whichpenel == SECOND_PANEL)
							panel3 -= value;
						if(whichpenel == THIRD_PANEL)
							panel4 -= value;
					}

					if(whichpenel != 0)
					{
						testvalue = abs(initpanel1 - panel1)
								+ abs(initpanel2 - panel2)
								+ abs(initpanel3 - panel3)
								+ abs(initpanel4 - panel4);
						testvalue /= 2;
					}
					else
						testvalue = 0xffff;
				}
				else
				{
					SendMessage(hslider1, TBM_SETPOS, oldpanel1, oldpanel1);
					return TRUE;
				}
			}

			if((HWND)lParam == hslider2)
			{
				if((IsWindowEnabled(hslider2) == TRUE) && 
					(SendMessage(hcheck2, BM_GETCHECK, 0, 0) == BST_UNCHECKED))
				{
					int whichpenel;
					int value;

					if(oldpanel2 > panel2)
					{
						whichpenel = pThis->GetMinPanel(
									panel1, 
									panel3, 
									panel4,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = oldpanel2 - panel2;
						if(whichpenel == FIRST_PANEL)
							panel1 += value;
						if(whichpenel == SECOND_PANEL)
							panel3 += value;
						if(whichpenel == THIRD_PANEL)
							panel4 += value;
					}
					if(oldpanel2 < panel2)
					{
						whichpenel = pThis->GetMaxPanel(
									panel1, 
									panel3, 
									panel4,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = panel2 - oldpanel2;
						if(whichpenel == FIRST_PANEL)
							panel1 -= value;
						if(whichpenel == SECOND_PANEL)
							panel3 -= value;
						if(whichpenel == THIRD_PANEL)
							panel4 -= value;
					}

					if(whichpenel != 0)
					{
						testvalue = abs(initpanel1 - panel1)
								+ abs(initpanel2 - panel2)
								+ abs(initpanel3 - panel3)
								+ abs(initpanel4 - panel4);
						testvalue /= 2;
					}
					else
						testvalue = 0xffff;
				}
				else
				{
					SendMessage(hslider2, TBM_SETPOS, oldpanel2, oldpanel2);
					return TRUE;
				}
			}

			if((HWND)lParam == hslider3)
			{
				if((IsWindowEnabled(hslider3) == TRUE) && 
					(SendMessage(hcheck3, BM_GETCHECK, 0, 0) == BST_UNCHECKED))
				{
					int whichpenel;
					int value;

					if(oldpanel3 > panel3)
					{
						whichpenel = pThis->GetMinPanel(
									panel1, 
									panel2, 
									panel4,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = oldpanel3 - panel3;
						if(whichpenel == FIRST_PANEL)
							panel1 += value;
						if(whichpenel == SECOND_PANEL)
							panel2 += value;
						if(whichpenel == THIRD_PANEL)
							panel4 += value;

					}
					if(oldpanel3 < panel3)
					{
						whichpenel = pThis->GetMaxPanel(
									panel1, 
									panel2, 
									panel4,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck4, BM_GETCHECK, 0, 0));
						value = panel3 - oldpanel3;
						if(whichpenel == FIRST_PANEL)
							panel1 -= value;
						if(whichpenel == SECOND_PANEL)
							panel2 -= value;
						if(whichpenel == THIRD_PANEL)
							panel4 -= value;
					}

					if(whichpenel != 0)
					{
						testvalue = abs(initpanel1 - panel1)
								+ abs(initpanel2 - panel2)
								+ abs(initpanel3 - panel3)
								+ abs(initpanel4 - panel4);
						testvalue /= 2;
					}
					else
						testvalue = 0xffff;
				}
				else
				{
					SendMessage(hslider3, TBM_SETPOS, oldpanel3, oldpanel3);
					return TRUE;
				}
			}

			if((HWND)lParam == hslider4)
			{
				if((IsWindowEnabled(hslider4) == TRUE) && 
					(SendMessage(hcheck4, BM_GETCHECK, 0, 0) == BST_UNCHECKED))
				{
					int whichpenel;
					int value;

					if(oldpanel4 > panel4)
					{
						whichpenel = pThis->GetMinPanel(
									panel1, 
									panel2, 
									panel3,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0));
						value = oldpanel4 - panel4;
						if(whichpenel == FIRST_PANEL)
							panel1 += value;
						if(whichpenel == SECOND_PANEL)
							panel2 += value;
						if(whichpenel == THIRD_PANEL)
							panel3 += value;
					}
					if(oldpanel4 < panel4)
					{
						whichpenel = pThis->GetMaxPanel(
									panel1, 
									panel2, 
									panel3,
									SendMessage(hcheck1, BM_GETCHECK, 0, 0),
									SendMessage(hcheck2, BM_GETCHECK, 0, 0),
									SendMessage(hcheck3, BM_GETCHECK, 0, 0));
						value = panel4 - oldpanel4;
						if(whichpenel == FIRST_PANEL)
							panel1 -= value;
						if(whichpenel == SECOND_PANEL)
							panel2 -= value;
						if(whichpenel == THIRD_PANEL)
							panel3 -= value;
					}

					if(whichpenel != 0)
					{
						testvalue = abs(initpanel1 - panel1)
								+ abs(initpanel2 - panel2)
								+ abs(initpanel3 - panel3)
								+ abs(initpanel4 - panel4);
						testvalue /= 2;
					}
					else
						testvalue = 0xffff;
				}
				else
				{
					SendMessage(hslider4, TBM_SETPOS, oldpanel4, oldpanel4);
					return TRUE;
				}
			}

			if((panel1 > MAX_PANEL) || (panel1 < 0))
				testvalue = 0xffff;
			if((panel2 > MAX_PANEL) || (panel2 < 0))
				testvalue = 0xffff;
			if((panel3 > MAX_PANEL) || (panel3 < 0))
				testvalue = 0xffff;
			if((panel4 > MAX_PANEL) || (panel4 < 0))
				testvalue = 0xffff;
			
			if(testvalue > pThis->domarray[0].changevalue)
			{		
				SendMessage(hslider1, TBM_SETPOS, TRUE, oldpanel1);
				SendMessage(hslider2, TBM_SETPOS, TRUE, oldpanel2);
				SendMessage(hslider3, TBM_SETPOS, TRUE, oldpanel3);
				SendMessage(hslider4, TBM_SETPOS, TRUE, oldpanel4);
				return TRUE;
			}
			changevalue = pThis->domarray[0].changevalue - testvalue;
			SendMessage(hslider1, TBM_SETPOS, TRUE, panel1);
			SendMessage(hslider2, TBM_SETPOS, TRUE, panel2);
			SendMessage(hslider3, TBM_SETPOS, TRUE, panel3);
			SendMessage(hslider4, TBM_SETPOS, TRUE, panel4);
			oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);
			oldpanel2 = SendMessage(hslider2, TBM_GETPOS, 0, 0);
			oldpanel3 = SendMessage(hslider3, TBM_GETPOS, 0, 0);
			oldpanel4 = SendMessage(hslider4, TBM_GETPOS, 0, 0);

			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);

			return TRUE;
		case WM_GETPOINT:
			pThis = (CDomestic *)lParam; 
			SendMessage(hslider1, TBM_SETPOS, pThis->domarray[0].panel[0], pThis->domarray[0].panel[0]);
			SendMessage(hslider2, TBM_SETPOS, pThis->domarray[0].panel[1], pThis->domarray[0].panel[1]);
			SendMessage(hslider3, TBM_SETPOS, pThis->domarray[0].panel[2], pThis->domarray[0].panel[2]);
			SendMessage(hslider4, TBM_SETPOS, pThis->domarray[0].panel[3], pThis->domarray[0].panel[3]);
			changevalue = pThis->domarray[0].changevalue;
			initpanel1 = oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);
			initpanel2 = oldpanel2 = SendMessage(hslider2, TBM_GETPOS, 0, 0);
			initpanel3 = oldpanel3 = SendMessage(hslider3, TBM_GETPOS, 0, 0);
			initpanel4 = oldpanel4 = SendMessage(hslider4, TBM_GETPOS, 0, 0);
			if(building_.buildingarray[BUILDINGARRAY_MUSHROOM].bexist == FALSE)
				SendMessage(hcheck3, BM_SETCHECK, BST_CHECKED, BST_CHECKED);
			else
			{
				EnableWindow(hstatic_mushroom, TRUE);
				EnableWindow(hslider3, TRUE);
			}
			if(story_.IsAphidRoomBuilt() == FALSE)
				SendMessage(hcheck4, BM_SETCHECK, BST_CHECKED, BST_CHECKED);
			else
			{
				EnableWindow(hstatic_aphid, TRUE);
				EnableWindow(hslider4, TRUE);
			}
			SetDlgItemTextA(hWndDlg_dom, IDC_STATIC_DOM, pThis->domarray[0].describe_dom);
			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);
			return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDC_DOM_CHECK3:
				if(building_.buildingarray[BUILDINGARRAY_MUSHROOM].bexist == FALSE)
					SendMessage(hcheck3, BM_SETCHECK, BST_CHECKED, 0);
				return TRUE;
			case IDC_DOM_CHECK4:
				if(story_.IsAphidRoomBuilt() == FALSE)
					SendMessage(hcheck4, BM_SETCHECK, BST_CHECKED, 0);
				return TRUE;
            case IDCANCEL:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_dom = NULL;
				return TRUE;
            case IDOK:
                EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_dom = NULL;

				pThis->domarray[0].panel[0] = oldpanel1;
				pThis->domarray[0].panel[1] = oldpanel2;
				pThis->domarray[0].panel[2] = oldpanel3;
				pThis->domarray[0].panel[3] = oldpanel4;
				pThis->domarray[0].Disalbed = TRUE;
				pThis->domarray[0].remaintime = DOM_WORKER_TIME(pThis->domarray[0].changeday);
				
				//domarray[0];
                return TRUE;
            }
            break;

        case WM_MOVE:
            // The window is moving around, so re-draw the backbuffer
            //DisplayFrame();
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
			hWndDlg_dom = NULL;
            break;
    }

    return FALSE;
}

INT_PTR CALLBACK CDomestic::DomSoldierDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDomestic* pThis; 
	static HWND hslider1;
	static HWND hedit1;
	static HWND hedit2;
	static HWND hedit3;

	static int changevalue;
	static int oldpanel1;

	static int initpanel1;

	char buf[10];

	int panel1;

	int testvalue;

    switch (msg)
    {
        case WM_INITDIALOG:
            {
				hslider1 = GetDlgItem(hDlg, IDC_DOM_SLIDER1);
				hedit1 = GetDlgItem(hDlg, IDC_DOM_EDIT1);
				hedit2 = GetDlgItem(hDlg, IDC_DOM_EDIT2);
				hedit3 = GetDlgItem(hDlg, IDC_DOM_EDIT3);
				
				SendMessage(hslider1, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));
            }
            return TRUE;
		case WM_HSCROLL:
			panel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);

			testvalue = abs(initpanel1 - panel1);

			if(testvalue > pThis->domarray[1].changevalue)
			{		
				SendMessage(hslider1, TBM_SETPOS, oldpanel1, oldpanel1);
				return TRUE;
			}
			changevalue = pThis->domarray[1].changevalue - testvalue;
			SendMessage(hslider1, TBM_SETPOS, TRUE, panel1);
			oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);

			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);

			sprintf(buf, "%d", MAX_PANEL-panel1);
			SetWindowTextA(hedit2, buf);
			sprintf(buf, "%d", panel1);
			SetWindowTextA(hedit3, buf);


			return TRUE;
		case WM_GETPOINT:
			pThis = (CDomestic *)lParam; 
			SendMessage(hslider1, TBM_SETPOS, TRUE, pThis->domarray[1].panel[0]);
			changevalue = pThis->domarray[1].changevalue;
			initpanel1 = oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);
			SetDlgItemTextA(hWndDlg_dom, IDC_STATIC_DOM, pThis->domarray[1].describe_dom);
			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);

			sprintf(buf, "%d", MAX_PANEL-initpanel1);
			SetWindowTextA(hedit2, buf);
			sprintf(buf, "%d", initpanel1);
			SetWindowTextA(hedit3, buf);
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dom = NULL;
					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dom = NULL;

					pThis->domarray[1].panel[0] = oldpanel1;
					pThis->domarray[1].Disalbed = TRUE;
					pThis->domarray[1].remaintime = DOM_SOLDIER_TIME(pThis->domarray[1].changeday);
                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_dom = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CDomestic::DomQueenDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDomestic* pThis; 
	static HWND hslider1;
	static HWND hedit1;
	static HWND hedit2;
	static HWND hedit3;

	static int changevalue;
	static int oldpanel1;

	static int initpanel1;

	char buf[10];

	int panel1;

	int testvalue;

    switch (msg)
    {
        case WM_INITDIALOG:
            {
				hslider1 = GetDlgItem(hDlg, IDC_DOM_SLIDER1);
				hedit1 = GetDlgItem(hDlg, IDC_DOM_EDIT1);
				
				SendMessage(hslider1, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAX_PANEL));
				hedit2 = GetDlgItem(hDlg, IDC_DOM_EDIT2);
				hedit3 = GetDlgItem(hDlg, IDC_DOM_EDIT3);

            }
            return TRUE;
		case WM_HSCROLL:
			panel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);

			testvalue = abs(initpanel1 - panel1);

			if(testvalue > pThis->domarray[2].changevalue)
			{		
				SendMessage(hslider1, TBM_SETPOS, TRUE, oldpanel1);
				return TRUE;
			}
			changevalue = pThis->domarray[2].changevalue - testvalue;
			SendMessage(hslider1, TBM_SETPOS, TRUE, panel1);
			oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);

			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);

			sprintf(buf, "%d", MAX_PANEL-panel1);
			SetWindowTextA(hedit2, buf);
			sprintf(buf, "%d", panel1);
			SetWindowTextA(hedit3, buf);

			return TRUE;
		case WM_GETPOINT:
			pThis = (CDomestic *)lParam; 
			SendMessage(hslider1, TBM_SETPOS, TRUE, pThis->domarray[2].panel[0]);
			changevalue = pThis->domarray[2].changevalue;
			initpanel1 = oldpanel1 = SendMessage(hslider1, TBM_GETPOS, 0, 0);
			SetDlgItemTextA(hWndDlg_dom, IDC_STATIC_DOM, pThis->domarray[2].describe_dom);
			itoa(changevalue, (char *)buf, 10);
			SetWindowTextA(hedit1, (char *)buf);

			sprintf(buf, "%d", MAX_PANEL-initpanel1);
			SetWindowTextA(hedit2, buf);
			sprintf(buf, "%d", initpanel1);
			SetWindowTextA(hedit3, buf);
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dom = NULL;
					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dom = NULL;

					pThis->domarray[2].panel[0] = oldpanel1;
					pThis->domarray[2].Disalbed = TRUE;
					pThis->domarray[2].remaintime = DOM_SOLDIER_TIME(pThis->domarray[2].changeday);
                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_dom = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CDomestic::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
    {
        case WM_INITDIALOG:
            {
            }
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dom = NULL;

                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_dom = NULL;
            break;
    }

    return FALSE;
}

INT_PTR CALLBACK CDomestic::GameoverDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
    {
        case WM_INITDIALOG:
            {
            }
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;

					hWndDlg_gameover = NULL;

					DWORD ThreadID;
					hthread = CreateThread(NULL, 0,ThreadGameover, NULL, 0, &ThreadID);

                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_gameover = NULL;
            break;
    }

    return FALSE;
}
int CDomestic::Save()
{
	for(int i=0; i<MAX_DOM; i++)
		WriteFile(hfile, &domarray[i], sizeof(domarray[i]), &dwWritten, NULL);

	return 1;
}
int CDomestic::Load()
{
	for(int i=0; i<MAX_DOM; i++)
		ReadFile(hfile, &domarray[i], sizeof(domarray[i]), &dwWritten, NULL);

	return 1;
}
int CDomestic::Domestic_Shutdown()
{
	return 1;
}
