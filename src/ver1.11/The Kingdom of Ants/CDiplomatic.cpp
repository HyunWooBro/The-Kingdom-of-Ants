
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "CDiplomatic.h"
#include "CObject.h"
#include "CDomestic.h"
#include "CSpecies.h"
#include "CEvent.h"
#include "CBattle.h"
#include "resource.h"
#include "CTime.h"
#include "CPlayer.h"
#include "CInfo.h"
#include "CDebug.h"

extern CDebug debug_;
extern CBattle battle_;
extern CObject object_;
extern CDomestic domestic_;
extern CEvent event_;
extern CInfo info_;

extern int SoundClick();

HWND CDiplomatic::hWndDlg_dip = NULL;
HWND CDiplomatic::hWndDlg_dip_normal = NULL;

int CDiplomatic::Diplomatic_Init()
{
	diparray[0].diptype = "공격";
	diparray[0].bshow = TRUE;
	diparray[0].Disalbed = FALSE;
	SetRect(&diparray[0].diprect, 582, 82, 629, 104);
	diparray[0].middlepoint.x = 582 + (629-582)/2;
	diparray[0].middlepoint.y = 82 + (104-82)/2;
	
	diparray[1].diptype = "증정";
	diparray[1].bshow = TRUE;
	diparray[1].Disalbed = FALSE;
	SetRect(&diparray[1].diprect, 581, 112, 628, 137);
	diparray[1].middlepoint.x = 581 + (628-581)/2;
	diparray[1].middlepoint.y = 112 + (137-112)/2;

	diparray[2].diptype = "포교";
	diparray[2].bshow = FALSE;
	diparray[2].Disalbed = TRUE;
	SetRect(&diparray[2].diprect, 580, 141, 630, 165);
	diparray[2].middlepoint.x = 580 + (630-580)/2;
	diparray[2].middlepoint.y = 141 + (165-141)/2;

	return 1;
}

int CDiplomatic::PrintMapinfo()
{
	if(SCREEN_STATE == SCREEN_MAP)
	{
		for(int i=0; i<MAX_SPECIES; i++)
		{
			if(CheckRect(&CSpecies::speciesarray[i].sperect, mouse_x, mouse_y))
			{
				if(CSpecies::speciesarray[i].Disalbed == FALSE)
				{
					sprintf(buffer,"세력 : %d", CSpecies::speciesarray[i].strength/NUM_CIPHER);
					DDraw_Text(buffer, 
							PRINT_STRENGTH_X,
							PRINT_STRENGTH_Y,
							NULL,
							lpddsback,
							RGB(0,0,0),
							TA_LEFT,
							NULL,
							TRANSPARENT,
							"System");

					if(CSpecies::speciesarray[i].state == SPECIES_STATE_NORMAL)
						sprintf(buffer,"상태 : 정상");
					if(CSpecies::speciesarray[i].state == SPECIES_STATE_OCCUPIED)
						sprintf(buffer,"상태 : 종속");
					if(CSpecies::speciesarray[i].state == SPECIES_STATE_BATTLE)
						sprintf(buffer,"상태 : 전쟁중");
					DDraw_Text(buffer, 
							PRINT_STATE_X,
							PRINT_STATE_Y,
							NULL,
							lpddsback,
							RGB(0,0,0),
							TA_LEFT,
							NULL,
							TRANSPARENT,
							"System");

					if(CSpecies::speciesarray[i].relation <= 10000)
						sprintf(buffer,"관계 : 험악");
					else if(CSpecies::speciesarray[i].relation <= 20000)
						sprintf(buffer,"관계 : 불화");
					else if(CSpecies::speciesarray[i].relation <= 30000)
						sprintf(buffer,"관계 : 중립");
					else if(CSpecies::speciesarray[i].relation <= 40000)
						sprintf(buffer,"관계 : 호의");
					else if(CSpecies::speciesarray[i].relation <= MAX_RELATION)
						sprintf(buffer,"관계 : 동맹");
					DDraw_Text(buffer, 
							PRINT_RELATION_X,
							PRINT_RELATION_Y,
							NULL,
							lpddsback,
							RGB(0,0,0),
							TA_LEFT,
							NULL,
							TRANSPARENT,
							"System");

					if(CSpecies::speciesarray[i].blanguage == TRUE)
						sprintf(buffer,"언어 : 알려짐");
					else
						sprintf(buffer,"언어 : 알려지지 않음");
					DDraw_Text(buffer, 
							PRINT_LANGUAGE_X,
							PRINT_LANGUAGE_Y,
							NULL,
							lpddsback,
							RGB(0,0,0),
							TA_LEFT,
							NULL,
							TRANSPARENT,
							"System");

						// 교화된 정도 나타내기
					if(diparray[2].bshow == TRUE)
					{
						sprintf(buffer,"교화 : %d%%", CSpecies::speciesarray[i].religion);
						DDraw_Text(buffer, 
								PRINT_RELIGION_X,
								PRINT_RELIGION_Y,
								NULL,
								lpddsback,
								RGB(0,0,0),
								TA_LEFT,
								NULL,
								TRANSPARENT,
								"System");
					}

					return 1;
				}	
			}
		}
	}

	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(CheckRect(&object_.objarray[OBJARRAY_MAP_PLAYER].objrect, mouse_x, mouse_y))
		{
			sprintf(buffer,"세력 : %d", CPlayer::strength/NUM_CIPHER);
			DDraw_Text(buffer, 
					PRINT_STRENGTH_X,
					PRINT_STRENGTH_Y,
					NULL,
					lpddsback,
					RGB(0,0,0),
					TA_LEFT,
					NULL,
					TRANSPARENT,
					"System");
			return 1;
		}
	}

	return 1;
}

int CDiplomatic::PrintDipMenu()
{
	if(SCREEN_STATE == SCREEN_MAP)
		DDraw_Text("외교",
				DIP_TITLE_X,
				DIP_TITLE_Y,
				15,
				lpddsback,
				RGB(255,0,0),
				TA_CENTER,
				NULL,
				TRANSPARENT);

	if(SCREEN_STATE == SCREEN_MAP)
	{
		for(int i=0; i<MAX_DIP; i++)
		{
			if(CSpecies::Selectedindex > -1)
			{
				if(diparray[i].bshow == TRUE)
				{
					if((CSpecies::speciesarray[CSpecies::Selectedindex].blanguage == TRUE) || (i == 0))
					{
						if(diparray[i].Disalbed == FALSE)
							DDraw_Text(diparray[i].diptype, 
									diparray[i].middlepoint.x,
									diparray[i].middlepoint.y,
									17,
									lpddsback,
									RGB(255,255,255),
									TA_CENTER,
									NULL,
									TRANSPARENT);
						else
							DDraw_Text(diparray[i].diptype, 
									diparray[i].middlepoint.x,
									diparray[i].middlepoint.y,
									17,
									lpddsback,
									RGB(60,60,60),
									TA_CENTER,
									NULL,
									TRANSPARENT);
					}
					else
					{
						DDraw_Text(diparray[i].diptype, 
								diparray[i].middlepoint.x,
								diparray[i].middlepoint.y,
								17,
								lpddsback,
								RGB(160,160,160),
								TA_CENTER,
								NULL,
								TRANSPARENT);
					}
				}
			}
			else
			{
				if(diparray[i].bshow == TRUE)
				{
					if(diparray[i].Disalbed == FALSE)
						DDraw_Text(diparray[i].diptype, 
								diparray[i].middlepoint.x,
								diparray[i].middlepoint.y,
								17,
								lpddsback,
								RGB(160,160,160),
								TA_CENTER,
								NULL,
								TRANSPARENT);
					else
						DDraw_Text(diparray[i].diptype, 
								diparray[i].middlepoint.x,
								diparray[i].middlepoint.y,
								17,
								lpddsback,
								RGB(60,60,60),
								TA_CENTER,
								NULL,
								TRANSPARENT);
				}
			}
		}
	}


	return 1;
}

int CDiplomatic::ShowDialog()
{
	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(CSpecies::Selectedindex > -1)
		{
			for(int i=0; i<MAX_DIP; i++)
			{
				if(CheckRect(&diparray[i].diprect, mouse_x, mouse_y))
				{
					if(diparray[i].Disalbed == FALSE)
					{
						if((CSpecies::speciesarray[CSpecies::Selectedindex].blanguage == TRUE) || (i == 0))
						{
							// 공격과 증정에서 강제 정지를 했으면 일단 해제한다.
							if(CTime::GetPauseCheck(PAUSE_DIP) == TRUE)
								CTime::ReleasePause(PAUSE_DIP);

							SoundClick();

							if(diparray[i].diptype == "공격")
							{
								if((BATTLE_IN_STATE == BATTLE_IN_BREAK) || (BATTLE_IN_STATE == BATTLE_IN_INIT))
								{
									if(hWndDlg_dip_normal)
										EndDialog(hWndDlg_dip_normal, TRUE );
									hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
										main_window_handle,  (DLGPROC)NormalDlgProc );
									SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "경고\n\n전쟁중에는 공격을 할 수 없습니다.");
									ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

									WaitDialog();
									return 0;
								}
								if(CSpecies::speciesarray[CSpecies::Selectedindex].state == SPECIES_STATE_OCCUPIED)
								{
									if(hWndDlg_dip_normal)
										EndDialog(hWndDlg_dip_normal, TRUE );
									hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
										main_window_handle,  (DLGPROC)NormalDlgProc );
									SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "경고\n\n왕국에 종속된 종족은 공격할 수 없습니다.");
									ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

									WaitDialog();
									return 0;
								}

								CTime::SetPause(PAUSE_DIP);

								if(hWndDlg_dip)
									EndDialog( hWndDlg_dip, TRUE );
								hWndDlg_dip = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DIP_ATTACK),
									main_window_handle,  (DLGPROC)DipAttackDlgProc );
								SendMessage(hWndDlg_dip, WM_GETPOINT, NULL, (LPARAM)this);
								ShowWindow(hWndDlg_dip, SW_SHOWNORMAL );
							}
							if(diparray[i].diptype == "증정")
							{
								CTime::SetPause(PAUSE_DIP);

								if(hWndDlg_dip)
									EndDialog( hWndDlg_dip, TRUE );
								hWndDlg_dip = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DIP_SUPPORT),
									main_window_handle,  (DLGPROC)DipSupportDlgProc );
								SendMessage(hWndDlg_dip, WM_GETPOINT, NULL, (LPARAM)this);
								ShowWindow(hWndDlg_dip, SW_SHOWNORMAL );
							}
							if(diparray[i].diptype == "포교")
							{
								if(hWndDlg_dip)
									EndDialog( hWndDlg_dip, TRUE );
								hWndDlg_dip = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_DIP_PROPAGATION),
									main_window_handle,  (DLGPROC)DipPropagationDlgProc );
								SendMessage(hWndDlg_dip, WM_GETPOINT, NULL, (LPARAM)this);
								ShowWindow( hWndDlg_dip, SW_SHOWNORMAL );
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

int CDiplomatic::SelectSpecies()
{
	BOOL Selected = FALSE;

	if(SCREEN_STATE == SCREEN_MAP)
	{
		for(int i=0; i<MAX_SPECIES; i++)
		{
			RECT screen_rect = {0, INTERFACE1_HEIGHT, SCREEN_WIDTH-INTERFACE2_WIDTH, SCREEN_HEIGHT};
			if(CheckRect(&screen_rect, mouse_x, mouse_y, TRUE))
			{
				if(CheckRect(&CSpecies::speciesarray[i].sperect, mouse_x, mouse_y, TRUE))
				{
					if(CSpecies::speciesarray[i].Disalbed == FALSE)
					{		
						object_.ChangeObjBobFrame(i, 1);

						CSpecies::Selectedindex = i;

						Selected = TRUE;
					}
				}
				else
					object_.ChangeObjBobFrame(i, 0);
			}
			else
				return 1;
		}
		if(!Selected)
			CSpecies::Selectedindex = -1;
	}

	return 1;
}
int CDiplomatic::ComputeSpecies()
{
	for(int i=0; i<MAX_SPECIES; i++)
	{
		int temp_strength = 0;
		int temp_lotte;

		// 시간에 따른
		if(CSpecies::speciesarray[i].state != SPECIES_STATE_BATTLE)
		{
			CSpecies::speciesarray[i].strength_time += PERIODICAL_STRENGTH_INCREASE_NPC;
			temp_lotte = rand()%100;
			if(temp_lotte == 0)
				CSpecies::speciesarray[i].strength_time += PERIODICAL_STRENGTH_INCREASE_NPC*40;
			if(temp_lotte == 99)
				CSpecies::speciesarray[i].strength_time -= PERIODICAL_STRENGTH_INCREASE_NPC*15;
			if(CSpecies::speciesarray[i].religion > 30)
				CSpecies::speciesarray[i].strength_time -= 1;
			if(CSpecies::speciesarray[i].religion > 60)
				CSpecies::speciesarray[i].strength_time -= 1;
			if(CSpecies::speciesarray[i].religion > 90)
				CSpecies::speciesarray[i].strength_time -= 1;
		}

		// 데미지에 따른
		temp_strength -= CSpecies::speciesarray[i].strength_damege;

		// 결과
		CSpecies::speciesarray[i].strength 
			= CSpecies::speciesarray[i].initstrength 
				+ temp_strength + CSpecies::speciesarray[i].strength_time;

		// 어떤 종족과의 관계가 호의 이상이면 중립으로 향해간다.
		if(CSpecies::speciesarray[i].relation > 30000)
			CSpecies::speciesarray[i].relation--;

		// 종교 교화된 정도 계산하기
		
	}

	return 1;
}
int CDiplomatic::GetPresent()
{
	for(int i=0 ;i<MAX_SPECIES; i++)
	{
		if(CSpecies::speciesarray[i].Disalbed == FALSE)
		{
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_OCCUPIED)
			{
				domestic_.ChangeResource(info_.ComputeResource(0,NUM_PRESENT_FOOD),
										 info_.ComputeResource(1,NUM_PRESENT_TIMBER),
										 info_.ComputeResource(2,NUM_PRESENT_MINERAL));
			}
		}
	}
	return 1;
}
int CDiplomatic::ChangeRelation(int food, int timber, int mineral)
{
	int temp_relation = 0;

	temp_relation += food*5;
	temp_relation += timber*7.5;
	temp_relation += mineral*10;

	CSpecies::speciesarray[CSpecies::Selectedindex].relation += temp_relation;
	if(CSpecies::speciesarray[CSpecies::Selectedindex].relation > MAX_RELATION)
		CSpecies::speciesarray[CSpecies::Selectedindex].relation = MAX_RELATION;

	return 1;
}
int CDiplomatic::ChangeRelation(int SPEARRAY_INDEX, int value)
{
	CSpecies::speciesarray[SPEARRAY_INDEX].relation += value;
	if(CSpecies::speciesarray[CSpecies::Selectedindex].relation > MAX_RELATION)
		CSpecies::speciesarray[CSpecies::Selectedindex].relation = MAX_RELATION;
	if(CSpecies::speciesarray[CSpecies::Selectedindex].relation < 0)
		CSpecies::speciesarray[CSpecies::Selectedindex].relation = 0;

	return 1;
}
int CDiplomatic::ChangeSpeStrength(int SPEARRAY_INDEX, int value)
{
	CSpecies::speciesarray[SPEARRAY_INDEX].strength_time += value;
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strength_time < 0)
		CSpecies::speciesarray[SPEARRAY_INDEX].strength_time = 0;

	return 1;
}
int CDiplomatic::LearnLanguage(int SPEARRAY_INDEX)
{
	if(SPEARRAY_INDEX == SPEARRAY_SNAIL)
		CSpecies::speciesarray[SPEARRAY_SNAIL].blanguage = TRUE;
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
		CSpecies::speciesarray[SPEARRAY_GRASSHOPPER].blanguage = TRUE;
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
		CSpecies::speciesarray[SPEARRAY_BEE].blanguage = TRUE;
	return 1;
}
int CDiplomatic::EnablePropagation()
{
	diparray[2].bshow = TRUE;
	diparray[2].Disalbed = FALSE;

	return 1;
}
int CDiplomatic::ChangeReligion()
{
	int temp_return = 0;

	if(CSpecies::speciesarray[CSpecies::Selectedindex].religion < 50)
	{
		temp_return = (1 + rand()%3);
		CSpecies::speciesarray[CSpecies::Selectedindex].religion += temp_return;
	}
	else if(CSpecies::speciesarray[CSpecies::Selectedindex].religion < 70)
	{
		temp_return = (1 + rand()%2);
		CSpecies::speciesarray[CSpecies::Selectedindex].religion += temp_return;
	}
	else
	{
		CSpecies::speciesarray[CSpecies::Selectedindex].religion += 1;
		temp_return = 1;
	}

	return temp_return;
}
int CDiplomatic::CheckPropagation()
{
	int temp_test;

	temp_test = rand()%10;

	if(CSpecies::speciesarray[CSpecies::Selectedindex].relation < MAX_RELATION/2)
	{
		if(temp_test < 6)
			return 1;
		else
			return 0;
	}
	else
	{
		if(temp_test < 8)
			return 1;
		else
			return 0;
	}

	return 1;
}
int CDiplomatic::ChangeSpeState(int SPEARRAY_INDEX, int STATE)
{
	CSpecies::speciesarray[SPEARRAY_INDEX].state = STATE;

	return 1;
}
int CDiplomatic::EnableSpecies(int SPEARRAY_INDEX)
{
	CSpecies::speciesarray[SPEARRAY_INDEX].Disalbed = FALSE;
	return 1;
}
int CDiplomatic::SetAttempt_to_Attack(int SPEARRAY_INDEX, int value)
{
	CSpecies::speciesarray[SPEARRAY_INDEX].attempt_to_attck += value;
	if(CSpecies::speciesarray[SPEARRAY_INDEX].attempt_to_attck < 0)
		CSpecies::speciesarray[SPEARRAY_INDEX].attempt_to_attck = 0;

	return 1;
}
int CDiplomatic::EnableDipAtt()
{
	diparray[0].Disalbed = FALSE;

	return 1;
}
BOOL CDiplomatic::PickUpSpe(int *spe1_index, int *spe2_index)
{
	// 종속이 아닌 2 종족을 인수로 넘어온 포인터 변수에 넣는다.
	// 해당 사항이 없으면 FALSE을 리턴

	if((spe1_index == NULL) || (spe2_index == NULL))
		return FALSE;
	
	int temp_rand;
	int temp_check;

	int temp_count = 0;

	for(int i=0; i<MAX_SPECIES; i++)
	{
		if(CSpecies::speciesarray[i].Disalbed == FALSE)
		{
			if(CSpecies::speciesarray[i].state != SPECIES_STATE_OCCUPIED)
				temp_count++;
		}
	}

	if(temp_count < 2)
		return FALSE;

	while(1)
	{
		temp_check = temp_rand = rand()%5;
		if(CSpecies::speciesarray[temp_rand].Disalbed == FALSE)
		{
			if(CSpecies::speciesarray[temp_rand].state != SPECIES_STATE_OCCUPIED)
			{
				*spe1_index = temp_rand;
				break;
			}
		}
	}

	while(1)
	{
		temp_rand = rand()%5;
		if(CSpecies::speciesarray[temp_rand].Disalbed == FALSE)
		{
			if(CSpecies::speciesarray[temp_rand].state != SPECIES_STATE_OCCUPIED)
			{
				if(temp_check != temp_rand)
				{
					*spe2_index = temp_rand;
					break;
				}
			}
		}
	}

	return TRUE;
}
HWND CDiplomatic::GetHwnDia_Dip()
{	
	return hWndDlg_dip;
}
HWND CDiplomatic::GetHwnDia_Dip_Error()
{
	return hWndDlg_dip_normal;
}

INT_PTR CALLBACK CDiplomatic::DipAttackDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDiplomatic *pThis; 

	static HWND hslider1;
	static HWND hedit1;
	static HWND hedit2;
	static HWND hedit3;
	static HWND hedit4;

	char buf[10];

	int temp_slider;
	static int temp_solider_attack = 0;
	static int temp_solider_defence = 0;
	static int temp_hired_attack = 0;
	static int temp_hired_defence = 0;

    switch (msg)
    {
        case WM_INITDIALOG:
			hslider1 = GetDlgItem(hDlg, IDC_DIP_SLIDER1);
			hedit1 = GetDlgItem(hDlg, IDC_DIP_EDIT1);
			hedit2 = GetDlgItem(hDlg, IDC_DIP_EDIT2);
			hedit3 = GetDlgItem(hDlg, IDC_DIP_EDIT3);
			hedit4 = GetDlgItem(hDlg, IDC_DIP_EDIT4);
            return TRUE;
		case WM_HSCROLL:
			temp_slider = SendMessage(hslider1, TBM_GETPOS, 0, 0);	
			temp_solider_attack = CPlayer::num_soldier_defence/100.0*temp_slider;
			temp_solider_defence = CPlayer::num_soldier_defence - temp_solider_attack;
			temp_hired_attack = CPlayer::num_hired_defence/100.0*temp_slider;
			temp_hired_defence = CPlayer::num_hired_defence - temp_hired_attack;
		
			sprintf(buf, "%d", temp_solider_defence);
			SetWindowTextA(hedit1, buf);
			sprintf(buf, "%d", temp_solider_attack);
			SetWindowTextA(hedit2, buf);
			sprintf(buf, "%d", temp_hired_defence);
			SetWindowTextA(hedit3, buf);
			sprintf(buf, "%d", temp_hired_attack);
			SetWindowTextA(hedit4, buf);
			
			return TRUE;
		case WM_GETPOINT:
			pThis = (CDiplomatic *)lParam; 

			SendMessage(hslider1, TBM_SETRANGE, FALSE, MAKELPARAM(0, 100));	
			sprintf(buf, "%d", CPlayer::num_soldier_defence);
			SetWindowTextA(hedit1, buf);
			SetWindowTextA(hedit2, "0");
			sprintf(buf, "%d", CPlayer::num_hired_defence);
			SetWindowTextA(hedit3, buf);
			SetWindowTextA(hedit4, "0");

			temp_solider_defence = CPlayer::num_soldier_defence;
			temp_hired_defence = CPlayer::num_hired_defence;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;

					CTime::ReleasePause(PAUSE_DIP);

					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;

					CTime::ReleasePause(PAUSE_DIP);

					if((CPlayer::num_soldier_defence != (temp_solider_attack + temp_solider_defence)) 
						|| (CPlayer::num_hired_defence != (temp_hired_attack + temp_hired_defence))
						|| ((CPlayer::num_soldier_defence == temp_solider_defence) 
							&& (CPlayer::num_hired_defence == temp_hired_defence)))
					{
						if(hWndDlg_dip_normal)
							EndDialog(hWndDlg_dip_normal, TRUE );
						hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "경고\n\n개체수에 요류가 있습니다.");
						ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

						WaitDialog();

						return TRUE;
					}

					CPlayer::num_soldier_attack = temp_solider_attack;
					CPlayer::num_hired_attack = temp_hired_attack;

					pThis->diparray[0].Disalbed = TRUE;
					battle_.PlayerDecideStr(CSpecies::Selectedindex);

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
			hWndDlg_dip = NULL;
			
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CDiplomatic::DipSupportDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDiplomatic *pThis; 

	static HWND hslider1;
	static HWND hslider2;
	static HWND hslider3;

	char buf[10];

    switch (msg)
    {
		SetCursor(LoadCursor(main_instance, MAKEINTRESOURCE(CURSOR_CROSSHAIR)));

        case WM_INITDIALOG:
			hslider1 = GetDlgItem(hDlg, IDC_DIP_SLIDER1);
			hslider2 = GetDlgItem(hDlg, IDC_DIP_SLIDER2);
			hslider3 = GetDlgItem(hDlg, IDC_DIP_SLIDER3);
            return TRUE;
		case WM_HSCROLL:
			return TRUE;
		case WM_GETPOINT:
			pThis = (CDiplomatic *)lParam; 

			SendMessage(hslider1, TBM_SETRANGE, FALSE, MAKELPARAM(0, CPlayer::food/NUM_CIPHER));
			SendMessage(hslider2, TBM_SETRANGE, FALSE, MAKELPARAM(0, CPlayer::timber/NUM_CIPHER));	
			SendMessage(hslider3, TBM_SETRANGE, FALSE, MAKELPARAM(0, CPlayer::mineral/NUM_CIPHER));	
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;

					CTime::ReleasePause(PAUSE_DIP);

					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;

					CTime::ReleasePause(PAUSE_DIP);

					if((SendMessage(hslider1, TBM_GETPOS, 0, 0) > CPlayer::food/NUM_CIPHER)
						|| (SendMessage(hslider2, TBM_GETPOS, 0, 0) > CPlayer::timber/NUM_CIPHER)
						|| (SendMessage(hslider3, TBM_GETPOS, 0, 0) > CPlayer::mineral/NUM_CIPHER))
					{
						if(hWndDlg_dip_normal)
							EndDialog(hWndDlg_dip_normal, TRUE );
						hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "경고\n\n자원이 부족합니다.");
						ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

						WaitDialog();
						return TRUE;
					}

					domestic_.ChangeResource(-SendMessage(hslider1, TBM_GETPOS, 0, 0)*NUM_CIPHER,
										 -SendMessage(hslider2, TBM_GETPOS, 0, 0)*NUM_CIPHER,
										 -SendMessage(hslider3, TBM_GETPOS, 0, 0)*NUM_CIPHER);

					pThis->ChangeRelation(SendMessage(hslider1, TBM_GETPOS, 0, 0),
										  SendMessage(hslider2, TBM_GETPOS, 0, 0),
										  SendMessage(hslider3, TBM_GETPOS, 0, 0));

					if(hWndDlg_dip_normal)
						EndDialog(hWndDlg_dip_normal, TRUE );
					hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "알림\n\n증정을 완료하여 관계가 개선되었습니다.");
					ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

					WaitDialog();

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
			hWndDlg_dip = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CDiplomatic::DipPropagationDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CDiplomatic *pThis; 

	char buf[10];
	int temp_return;

    switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
		case WM_HSCROLL:

			return TRUE;
		case WM_GETPOINT:
			pThis = (CDiplomatic *)lParam; 
	
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;
					return TRUE;
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_dip = NULL;

					if(CPlayer::food < COST_FOOD_PROPAGATION)
					{
						if(hWndDlg_dip_normal)
							EndDialog(hWndDlg_dip_normal, TRUE );
						hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "경고\n\n자원이 부족합니다.");
						ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

						WaitDialog();
						return TRUE;
					}

					domestic_.ChangeResource(-COST_FOOD_PROPAGATION*NUM_CIPHER, 0, 0);

					if(pThis->CheckPropagation())
					{
						pThis->ChangeRelation(CSpecies::Selectedindex, 400);
						temp_return = pThis->ChangeReligion();
						CSpecies::speciesarray[CSpecies::Selectedindex].strength -= temp_return*70;

						if(hWndDlg_dip_normal)
							EndDialog(hWndDlg_dip_normal, TRUE );
						hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "알림\n\n포교가 성공적으로 마무리되었습니다.");
						ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

						WaitDialog();
					}
					else
					{
						pThis->ChangeRelation(CSpecies::Selectedindex, -400*2);

						if(hWndDlg_dip_normal)
							EndDialog(hWndDlg_dip_normal, TRUE );
						hWndDlg_dip_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_dip_normal, IDC_NORMAL, "알림\n\n포교가 실패로 끝났습니다.");
						ShowWindow(hWndDlg_dip_normal, SW_SHOWNORMAL );

						WaitDialog();
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
			hWndDlg_dip = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CDiplomatic::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
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
					hWndDlg_dip_normal = NULL;

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
			hWndDlg_dip_normal = NULL;
            break;
    }

    return FALSE;
}


int CDiplomatic::Save()
{
	for(int i=0; i<MAX_DIP; i++)
		WriteFile(hfile, &diparray[i], sizeof(diparray[i]), &dwWritten, NULL);

	return 1;
}
int CDiplomatic::Load()
{
	for(int i=0; i<MAX_DIP; i++)
		ReadFile(hfile, &diparray[i], sizeof(diparray[i]), &dwWritten, NULL);

	return 1;
}
int CDiplomatic::Diplomatic_Shutdown()
{

	return 1;
}


