
#include <windows.h>
#include <stdio.h>
#include "CEvent.h"
#include "CTime.h"
#include "CDiplomatic.h"
#include "CSpecies.h"
#include "CDebug.h"
#include "CObject.h"
#include "CItem.h"
#include "CPlayer.h"
#include "resource.h"

extern CDebug debug_;
extern CItem item_;
extern CObject object_;
extern CDiplomatic diplomatic_;
extern CTime time_;

HWND CEvent::hWndDlg_event = NULL;
HWND CEvent::hWndDlg_event_dialog = NULL;
HWND CEvent::hWndDlg_event_normal = NULL;

extern int ReturnScreenGamma(BOOL blong, int delay = 70);
extern int ChangeScreenGamma(int effect, BOOL blong, int delay = 70);

int CEvent::Event_Init()
{
	eventarray[0].Exist = FALSE;
	eventarray[0].eventtype = EVENT_FIGHT;
	eventarray[0].remaintime = LENGTH_TIME_EVENT_FIGHT;
	eventarray[0].temp[0] = 0;	// 종족 인덱스를 위해 사용
	eventarray[0].temp[1] = 0;	// 종족 인덱스를 위해 사용

	eventarray[1].Exist = TRUE;
	eventarray[1].eventtype = EVENT_SELLER;
	eventarray[1].remaintime = LENGTH_TIME_EVENT_SELLER;

	eventarray[2].Exist = TRUE;
	eventarray[2].eventtype = EVENT_DIALOG;
	eventarray[2].remaintime = LENGTH_TIME_EVENT_DIALOG;
	eventarray[2].temp[0] = 0;	// 대화 flag를 위해 사용

	debug_.GetValue("temp[0]", &eventarray[EVENTARRAY_DIALOG].temp[0], 0, lpddsback, 22, ONLY_V1);

	return 1;
}
int CEvent::EventFight()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	int temp_spe1_index;
	int temp_spe2_index;

	eventarray[EVENTARRAY_FIGHT].remaintime = LENGTH_TIME_EVENT_FIGHT;

	if(diplomatic_.PickUpSpe(&eventarray[EVENTARRAY_FIGHT].temp[0], 
			&eventarray[EVENTARRAY_FIGHT].temp[1]) == FALSE)
		return 0;

	CTime::SetPause();

	temp_spe1_index = eventarray[EVENTARRAY_FIGHT].temp[0];
	temp_spe2_index = eventarray[EVENTARRAY_FIGHT].temp[1];

	if(hWndDlg_event)
		EndDialog(hWndDlg_event, TRUE );
	hWndDlg_event = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_EVENT_FIGHT),
		main_window_handle,  (DLGPROC)EveFightDlgProc );
	sprintf(buffer, "참모 개미\n\n\"영지 근처에서 '%s'종과 '%s'종 사이의 전투가 벌어지고 있습니다.\"",
		CSpecies::speciesarray[temp_spe1_index].name,
		CSpecies::speciesarray[temp_spe2_index].name);
	SetDlgItemTextA(hWndDlg_event, IDC_STATIC_FIGHT, buffer);
	SendMessage(hWndDlg_event, WM_GETPOINT, NULL, (LPARAM)this);
	SendMessage(hWndDlg_event, WM_GETINFO,
		(WPARAM)CSpecies::speciesarray[temp_spe1_index].name,
		(LPARAM)CSpecies::speciesarray[temp_spe2_index].name);
	ShowWindow( hWndDlg_event, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CEvent::EventSeller()
{
	int temp_rand;

	temp_rand = rand()%2;

	// 초기화하고 obj를 enable시킨다. 시간 초기화하면 여기는 끝
	if(temp_rand == 0)
	{
		if(item_.GetItem(4) != PLAYER)
		{
			object_.ShowObjBob(OBJARRAY_SELLER);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_DIALOG, 0);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_FOOD, 130);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_TIMBER, 200);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_MINERAL, 120);
		}
	}
	else
	{
		if(item_.GetItem(6) != PLAYER)
		{
			object_.ShowObjBob(OBJARRAY_SELLER);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_DIALOG, 1);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_FOOD, 150);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_TIMBER, 100);
			object_.ChangeObjTemp(OBJARRAY_SELLER, BOB_INT_SELLER_COST_MINERAL, 70);
		}
	}

	eventarray[EVENTARRAY_SELLER].remaintime = LENGTH_TIME_EVENT_SELLER;

	return 1;
}
int CEvent::EventDialog()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	int temp_rand;

	temp_rand = rand()%13;

	if(temp_rand <= 9)
	{
		if(temp_rand == 0)
		{
			if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_1_DONE))
			{
				if(hWndDlg_event_dialog)
					EndDialog(hWndDlg_event_dialog, TRUE );
				hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				sprintf(buffer, "참모 개미\n\n\"방금 영지 근처를 많은 수의 손가락들이 지나갔습니다. 많은 개미들이 "
						"숨죽여 지켜보았지만 그들은 문제를 일으키지는 않았습니다.\"");
				SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
				ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

				SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_1_DONE);
			}
		}
		if(temp_rand == 1)
		{
			if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_2_DONE))
			{
				if(hWndDlg_event_dialog)
					EndDialog(hWndDlg_event_dialog, TRUE );
				hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				sprintf(buffer, "유모 개미\n\n\"벨로캉 왕국을 떠나온 이래로 어떤 소식도 접하지 못했습니다. "
						"가끔은 그곳이 그리워 지는건 어쩔 수 없네요.\"");
				SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
				ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

				SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_2_DONE);
			}
		}
		if(temp_rand == 2)
		{
			if(time_.GetSeason() == WINTER)
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_3_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "유모 개미\n\n\"날씨가 서늘하면 애벌레들의 발육이 늦어집니다. "
								"감기에나 걸리지 않을까 걱정이에요.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_3_DONE);
				}
			}
		}
		if(temp_rand == 3)
		{
			if((CSpecies::speciesarray[SPEARRAY_BEE].Disalbed == FALSE)
				&& (CSpecies::speciesarray[SPEARRAY_SHORT_ANT].Disalbed == FALSE)
				&& (CSpecies::speciesarray[SPEARRAY_BEE].state != SPECIES_STATE_OCCUPIED)
				&& (CSpecies::speciesarray[SPEARRAY_SHORT_ANT].state != SPECIES_STATE_OCCUPIED)
				&& (BATTLE_OUT_STATE == BATTLE_OUT_NO))
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_4_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "참모 개미\n\n\" '메뚜기'종이 '꿀벌'과의 전투에서 처참히 패패했다고 합니다. "
							"로열 젤리를 노리다가 손해만 봤군요.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_4_DONE);
				}
			}
		}
		if(temp_rand == 4)
		{
			if((CSpecies::speciesarray[SPEARRAY_RED_ANT].Disalbed == FALSE)
				&& (CSpecies::speciesarray[SPEARRAY_SHORT_ANT].Disalbed == FALSE)
				&& (CSpecies::speciesarray[SPEARRAY_RED_ANT].state != SPECIES_STATE_OCCUPIED)
				&& (CSpecies::speciesarray[SPEARRAY_SHORT_ANT].state != SPECIES_STATE_OCCUPIED)
				&& (BATTLE_OUT_STATE == BATTLE_OUT_NO))
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_5_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "참모 개미\n\n\" '불개미'종이 '난쟁이개미'종의 보물을 "
								"노리는 모양입니다. 글쎄요. 아무리 '불개미'라 할지라도 "
								"끈질긴 '난쟁이개미'를 어떻게 하지는 못하겠지요.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_5_DONE);
				}
			}
		}
		if(temp_rand == 5)
		{
			if((time_.GetSeason() == WINTER) && (CHAPTER == CHAP_1))
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_6_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "참모 개미\n\n\"여왕이시어, 이 길고 지루한 겨울을 "
								"견뎌내는 자만이 달콤한 열매를 딸 수 있는 법입니다.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_6_DONE);
				}
			}
		}
		if(temp_rand == 6)
		{
			if((item_.GetItem(0) != PLAYER) && (CPlayer::num_soldier_hunt > 0))
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_7_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "병정 개미\n\n\"죽기 전에 '난쟁이개미 토템'을 한번 "
								"보는 것이 소원입니다. 그것은 토템중에서도 "
								"신비롭고 신성한 것으로 소문이 자자합니다.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_7_DONE);
				}
			}
		}
		if(temp_rand == 7)
		{
			if(CPlayer::num_soldier_hunt > 0)
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_8_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "병정 개미\n\n\"여왕님의 고향인 벨로캉은 '벨로캉 전투'로 "
								"유명합니다. 연방군에 반기를 든 혁명군과 연방군의 전투는 "
								"개미 역사에 길이 남을 대 혈투였습니다.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_8_DONE);
				}
			}
		}
		if(temp_rand == 8)
		{
			if(CPlayer::num_worker_aphid > 0)
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_9_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "일꾼 개미\n\n\"먼 동쪽에 사는 개미들은 "
							"뿔매미, 매미충, 깍지벌레 등을 가지고 목축업을 한다고 "
							"합니다. 이곳에서 진딧물을 보호하고 먹이를 얻는 것처럼 "
							"말이죠.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_9_DONE);
				}
			}
		}
		if(temp_rand == 9)
		{
			if(CPlayer::num_worker_aphid > 0)
			{
				if(!(eventarray[EVENTARRAY_DIALOG].temp[0] & EVENT_DIALOG_10_DONE))
				{
					if(hWndDlg_event_dialog)
						EndDialog(hWndDlg_event_dialog, TRUE );
					hWndDlg_event_dialog = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					sprintf(buffer, "일꾼 개미\n\n\"사실 진딧물 고기는 연하고 맛이 기가 "
						"막힘니다. 하지만 달콤한 감로수를 포기하면서 잡아먹을 개미는 "
						"없을 겁니다.\"");
					SetDlgItemTextA(hWndDlg_event_dialog, IDC_NORMAL, buffer);
					ShowWindow( hWndDlg_event_dialog, SW_SHOWNORMAL );

					SET_BIT(eventarray[EVENTARRAY_DIALOG].temp[0], EVENT_DIALOG_10_DONE);
				}
			}
		}

		WaitDialog();
	}

	eventarray[EVENTARRAY_DIALOG].remaintime = LENGTH_TIME_EVENT_DIALOG;

	return 1;
}
int CEvent::CheckEvent()
{
	for(int i=0; i<MAX_EVENT; i++)
	{
		if(eventarray[i].Exist == TRUE)
		{
			eventarray[i].remaintime--;
			debug_.GetValue("remaintime", &eventarray[i].remaintime, 0, lpddsback, 5, ONLY_V1);
			if(eventarray[i].remaintime == 0)
			{
				if(eventarray[i].eventtype == EVENT_DIALOG)
					EventDialog();
				if(eventarray[i].eventtype == EVENT_FIGHT)
					EventFight();
				if(eventarray[i].eventtype == EVENT_SELLER)
					EventSeller();
			}
		}
		else
		{
			// 처음 시작한 후 겨울이 지나 봄이 되야 이 이벤트는 유효
			if(time_.GetSeason() == SPRING)
				SetEvent(EVENTARRAY_FIGHT);
		}
	}

	return 1;
}
int CEvent::SetEvent(int EVENTARRAY_INDEX)
{
	eventarray[ EVENTARRAY_INDEX].Exist = TRUE;

	return 1;
}
DWORD WINAPI CEvent::ThreadEventFight(LPVOID temp)
{
	int **temp_array = (int **)temp;

	CEvent *pThis = (CEvent *)temp_array[0];

	int temp_spe_help;
	int temp_spe_other;

	if(temp_array[1] == (int *)1)
	{
		temp_spe_help = pThis->eventarray[EVENTARRAY_FIGHT].temp[0];
		temp_spe_other = pThis->eventarray[EVENTARRAY_FIGHT].temp[1];
	}
	else
	{
		temp_spe_help = pThis->eventarray[EVENTARRAY_FIGHT].temp[1];
		temp_spe_other = pThis->eventarray[EVENTARRAY_FIGHT].temp[0];
	}

	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);

	Sleep(500);
	
	ReturnScreenGamma(TRUE);

	CTime::ReleasePause();
	
	sprintf(pThis->buffer, "참모 개미\n\n\" '%s'종을 도와 '%s'종을 물리쳤습니다. '%s'종은 "
			"이를 갈며 복수를 기다릴 것입니다.\"",
			CSpecies::speciesarray[temp_spe_help].name,
			CSpecies::speciesarray[temp_spe_other].name,
			CSpecies::speciesarray[temp_spe_other].name);
	SetDlgItemTextA(hWndDlg_event_normal, IDC_NORMAL, pThis->buffer);
	ShowWindow( hWndDlg_event_normal, SW_SHOWNORMAL );

	WaitDialog();

	diplomatic_.ChangeRelation(temp_spe_help, 5000);
	diplomatic_.ChangeRelation(temp_spe_other, -8000);
	
	hthread = NULL;

	return 0;
}

INT_PTR CALLBACK CEvent::EveFightDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CEvent *pThis;

	static HWND hradio1;
	static HWND hradio2;
	static HWND hradio3;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_EVE_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_EVE_RADIO2);
			hradio3 = GetDlgItem(hDlg, IDC_EVE_RADIO3);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CEvent *)lParam;

			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);

			return TRUE;
		case WM_GETINFO:
			sprintf(pThis->buffer, "'%s'종을 돕는다.", (char *)wParam);
			SetWindowTextA(hradio2, pThis->buffer);
			sprintf(pThis->buffer, "'%s'종을 돕는다.", (char *)lParam);
			SetWindowTextA(hradio3, pThis->buffer);

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_event = NULL;

				if(SendMessage(hradio1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
				{
					CTime::ReleasePause();
					return TRUE;
				}

				int *temp_point[2];
				temp_point[0] = (int *)pThis;

				DWORD ThreadID;
				if(SendMessage(hradio2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					temp_point[1] = (int *)1;
				else
					temp_point[1] = (int *)2;

				hthread = CreateThread(NULL, 0, ThreadEventFight, (LPVOID)temp_point, 0, &ThreadID);

				if(hWndDlg_event_normal)
					EndDialog( hWndDlg_event_normal, TRUE );
				hWndDlg_event_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );

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
			hWndDlg_event = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CEvent::NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
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
					hWndDlg_event_normal = NULL;
					if(hWndDlg_event_dialog)
						hWndDlg_event_dialog = NULL;
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
			hWndDlg_event_normal = NULL;
			if(hWndDlg_event_dialog)
				hWndDlg_event_dialog = NULL;
            break;
    }

    return FALSE;
}
HWND CEvent::GetHwnDia_Event()
{
	return hWndDlg_event;
}
HWND CEvent::GetHwnDia_Event_Dialog()
{
	return hWndDlg_event_dialog;
}
HWND CEvent::GetHwnDia_Event_Normal()
{
	return hWndDlg_event_normal;
}
int CEvent::Save()
{
	for(int i=0; i<MAX_EVENT; i++)
		WriteFile(hfile, &eventarray[i], sizeof(eventarray[i]), &dwWritten, NULL);

	return 1;
}
int CEvent::Load()
{
	for(int i=0; i<MAX_EVENT; i++)
		ReadFile(hfile, &eventarray[i], sizeof(eventarray[i]), &dwWritten, NULL);

	return 1;
}
int CEvent::Event_Shutdown()
{

	return 1;
}
