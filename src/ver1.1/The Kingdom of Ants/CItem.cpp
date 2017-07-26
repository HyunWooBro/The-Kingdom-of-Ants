
#include <stdio.h> 
#include <ddraw.h>
#include "t3dlib1.h"
#include "ddutil.h"
#include "CTime.h"
#include "CObjDialog.h"
#include "CDomestic.h"
#include "CDiplomatic.h"
#include "CBuilding.h"
#include "CItem.h"
#include "CPlayer.h"
#include "resource.h"
#include "CDebug.h"

extern CDebug debug_;
extern CTime time_;
extern CDomestic domestic_;
extern CDiplomatic diplomatic_;
extern CObjDialog objdialog_;
extern CBuilding building_;

HWND CItem::hWndDlg_item = NULL;

int CItem::Item_Init()
{
	itemarray[0].whereitem = SHORT_ANT;
	itemarray[0].description = "난쟁이개미 토템\n난쟁이개미 대대로 전해내려오는 "
						"신성한 상징물이다.\n(세력 +150)";
	SetRect(&itemarray[0].descriptionrect, DESCRIPTION_X(58), DESCRIPTION_Y(77), DESCRIPTION_CX(58), DESCRIPTION_CY(77));
	itemarray[0].picture = DDLoadBitmap(lpdd, "art/item/item0.bmp", 0, 0);
	SetRect(&itemarray[0].picturerect, PICTURE_X(58), PICTURE_Y(77), PICTURE_CX(58), PICTURE_CY(77));
	
	itemarray[1].whereitem = FIELD_NORMAL;
	itemarray[1].description = "젖꼭지\n윗부분이 투명하고 맛난 냄새가 나는 신기한 물체.\n(세력 + 25)";
	SetRect(&itemarray[1].descriptionrect, DESCRIPTION_X(58), DESCRIPTION_Y(143), DESCRIPTION_CX(58), DESCRIPTION_CY(143));
	itemarray[1].picture = DDLoadBitmap(lpdd, "art/item/item1.bmp", 0, 0);
	SetRect(&itemarray[1].picturerect, PICTURE_X(58), PICTURE_Y(143), PICTURE_CX(58), PICTURE_CY(143));

	itemarray[2].whereitem = BEE;
	itemarray[2].description = "로열젤리\n왕유라고도 부르는 이 물질을 먹은 여왕벌은 "
							"120만개의 알을 낳고 다른 벌보다 20배는 장수한다.\n"
							"(여왕 개미의 알 번식력 +15)";
	SetRect(&itemarray[2].descriptionrect, DESCRIPTION_X(58), DESCRIPTION_Y(209), DESCRIPTION_CX(58), DESCRIPTION_CY(209));
	itemarray[2].picture = DDLoadBitmap(lpdd, "art/item/item2.bmp", 0, 0);
	SetRect(&itemarray[2].picturerect, PICTURE_X(58), PICTURE_Y(209), PICTURE_CX(58), PICTURE_CY(209));

	itemarray[3].whereitem = FIELD_NORMAL;
	itemarray[3].description = "병뚜껑\n공원에서 쉽게 볼 수 있는 물체이다. 하지만 개미 조사팀은 아직도 이 물건이 어디에 "
						"쓰이는지 알아내고자 분주하다.";
	SetRect(&itemarray[3].descriptionrect, DESCRIPTION_X(58), DESCRIPTION_Y(276), DESCRIPTION_CX(58), DESCRIPTION_CY(276));
	itemarray[3].picture = DDLoadBitmap(lpdd, "art/item/item3.bmp", 0, 0);
	SetRect(&itemarray[3].picturerect, PICTURE_X(58), PICTURE_Y(276), PICTURE_CX(58), PICTURE_CY(276));

	itemarray[4].whereitem = SELLER;
	itemarray[4].description = "절대반지\n프로도라는 손가락이 잃어버린 엄청난 힘이 잠재되어 있는 반지이다. "
						"\n(전투력 상승,주위 종족과의 관계 악화)";
	SetRect(&itemarray[4].descriptionrect, DESCRIPTION_X(58), DESCRIPTION_Y(341), DESCRIPTION_CX(58), DESCRIPTION_CY(341));
	itemarray[4].picture = DDLoadBitmap(lpdd, "art/item/item4.bmp", 0, 0);
	SetRect(&itemarray[4].picturerect, PICTURE_X(58), PICTURE_Y(341), PICTURE_CX(58), PICTURE_CY(341));

	itemarray[5].whereitem = FINGER;
	itemarray[5].description = "로제타석\n손가락이 준 커다란 돌이다. 이것을 통해 "
						"그들과 대화를 할 수 있다.";
	SetRect(&itemarray[5].descriptionrect, DESCRIPTION_X(291), DESCRIPTION_Y(77), DESCRIPTION_CX(291), DESCRIPTION_CY(77));
	itemarray[5].picture = DDLoadBitmap(lpdd, "art/item/item5.bmp", 0, 0);
	SetRect(&itemarray[5].picturerect, PICTURE_X(291), PICTURE_Y(77), PICTURE_CX(291), PICTURE_CY(77));

	itemarray[6].whereitem = SELLER;
	itemarray[6].description = "수정구슬\n바라보고 있으면 빨려들어갈 것 같은 신비한 수정으로 만들어진 구슬이다. "
						"\n(세력 +20)";
	SetRect(&itemarray[6].descriptionrect, DESCRIPTION_X(291), DESCRIPTION_Y(143), DESCRIPTION_CX(291), DESCRIPTION_CY(143));
	itemarray[6].picture = DDLoadBitmap(lpdd, "art/item/item6.bmp", 0, 0);
	SetRect(&itemarray[6].picturerect, PICTURE_X(291), PICTURE_Y(143), PICTURE_CX(291), PICTURE_CY(143));

	itemarray[7].whereitem = GRASSHOPPER;
	itemarray[7].description = "어느 손가락의 사진\n메뚜기종족이 소중히 보관하던 그림이다. 그들은 "
						"이 손가락의 그림에서 어딘가 친근함을 느낀 모양이다.";
	SetRect(&itemarray[7].descriptionrect, DESCRIPTION_X(291), DESCRIPTION_Y(209), DESCRIPTION_CX(291), DESCRIPTION_CY(209));
	itemarray[7].picture = DDLoadBitmap(lpdd, "art/item/item7.bmp", 0, 0);
	SetRect(&itemarray[7].picturerect, PICTURE_X(291), PICTURE_Y(209), PICTURE_CX(291), PICTURE_CY(209));

	itemarray[8].whereitem = FIELD_NORMAL;
	itemarray[8].description = "빨대\n길쭉하게 생긴 굴이다. 일방통행이라 다른 쪽에서 개미가 들어오면 낭패이다."
						"\n(세력 +30)";
	SetRect(&itemarray[8].descriptionrect, DESCRIPTION_X(291), DESCRIPTION_Y(276), DESCRIPTION_CX(291), DESCRIPTION_CY(276));
	itemarray[8].picture = DDLoadBitmap(lpdd, "art/item/item8.bmp", 0, 0);
	SetRect(&itemarray[8].picturerect, PICTURE_X(291), PICTURE_Y(276), PICTURE_CX(291), PICTURE_CY(276));

	itemarray[9].whereitem = FIELD_NORMAL;
	itemarray[9].description = "수제 포크\n손가락의 무기로 알려진 포크. 다른 포크와는 다르게 장인의 "
						"정신이 느껴진다.\n(세력 +40)";
	SetRect(&itemarray[9].descriptionrect, DESCRIPTION_X(291), DESCRIPTION_Y(341), DESCRIPTION_CX(291), DESCRIPTION_CY(341));
	itemarray[9].picture = DDLoadBitmap(lpdd, "art/item/item9.bmp", 0, 0);
	SetRect(&itemarray[9].picturerect, PICTURE_X(291), PICTURE_Y(341), PICTURE_CX(291), PICTURE_CY(341));

	itemflag = 0;

	return 1;
}

int CItem::PrintItem()
{
	RECT dest_rect;

	if(SCREEN_STATE == SCREEN_ITEM)
	{
		for(int i=0; i<MAX_ITEM; i++)
		{
			if(itemarray[i].whereitem == PLAYER)
			{
				lpddsback->Blt(&itemarray[i].picturerect, itemarray[i].picture, NULL, DDBLT_WAIT, NULL);
				DDRAW_TEXT_RECT_ITEM(itemarray[i].description, itemarray[i].descriptionrect);
			}
		}
	}

	return 1;
}

int CItem::SetItem(int index, WHERE_ITEM whereitem)
{
	itemarray[index].whereitem = whereitem;

	return 1;
}

WHERE_ITEM CItem::GetItem(int index)
{
	return itemarray[index].whereitem;
}

int CItem::SearchItem()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	int temp_random;

	float temp_total;

	BOOL Find = FALSE;;

	temp_total = CPlayer::num_worker_search;

	if(objdialog_.labflag & LAB_2_DONE)
		temp_total *= 1.2;
	if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
		temp_total *= 1.1;

	temp_random = rand()%RAND_MAX;
	if(temp_random <= (int)temp_total)
	{
		temp_random = rand()%4;

		if(temp_random == 0)
		{
			if(itemflag & ITEM_3_RELEASE)
				if(itemarray[3].whereitem == FIELD_NORMAL)
					ShowFinedItem(3);
		}
		if(temp_random == 1)
		{
			if(itemflag & ITEM_1_RELEASE)
				if(itemarray[1].whereitem == FIELD_NORMAL)
					ShowFinedItem(1);
		}
		if(temp_random == 2)
		{
			if(itemflag & ITEM_8_RELEASE)
				if(itemarray[8].whereitem == FIELD_NORMAL)
					ShowFinedItem(8);
		}
		if(temp_random == 3)
		{
			if(itemflag & ITEM_9_RELEASE)
				if(itemarray[9].whereitem == FIELD_NORMAL)
					ShowFinedItem(9);
		}
	}

	return 1;
}

int CItem::ShowFinedItem(int item_index)
{
	if(hWndDlg_item)
		EndDialog( hWndDlg_item, TRUE );
	hWndDlg_item = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	if(item_index == 3)
	{
		itemarray[3].whereitem = PLAYER;
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n수색을 통해 '병뚜껑'을 발견했습니다.");
	}
	if(item_index == 1)
	{
		itemarray[1].whereitem = PLAYER;
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n수색을 통해 '젖꼭지'를 발견했습니다.");
	}
	if(item_index == 8)
	{
		itemarray[8].whereitem = PLAYER;
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n수색을 통해 '빨대'를 발견했습니다.");
	}
	if(item_index == 9)
	{
		itemarray[9].whereitem = PLAYER;
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n수색을 통해 '수제 포크'를 발견했습니다.");
	}
	
	ShowWindow( hWndDlg_item, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CItem::TakeItemFromSpe(int SPEARRAY_INDEX)
{
	if((SPEARRAY_INDEX == SPEARRAY_RED_ANT) || (SPEARRAY_INDEX == SPEARRAY_SNAIL))
		return 0;

	if(hWndDlg_item)
		EndDialog( hWndDlg_item, TRUE );
	hWndDlg_item = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
	{	
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n'메뚜기'종이 보관하던 '어느 손가락의 사진'을 발견했습니다.");
		itemarray[7].whereitem = PLAYER;
	}
	if(SPEARRAY_INDEX == SPEARRAY_SHORT_ANT)
	{
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n'난쟁이개미'종이 보관하던 '난쟁이개미 토템'을 발견했습니다.");
		itemarray[0].whereitem = PLAYER;
	}
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
	{
		SetDlgItemTextA(hWndDlg_item, IDC_NORMAL, "알림\n\n'꿀벌'종이 보관하던 '로열젤리'을 발견했습니다.");
		itemarray[2].whereitem = PLAYER;
	}

	ShowWindow( hWndDlg_item, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CItem::BuyItem(int index)
{
	// 절대반지를 사면 관계 악화
	if(index == 4)
	{
		itemarray[4].whereitem = PLAYER;
		for(int i=0; i<MAX_SPECIES; i++)
			diplomatic_.ChangeRelation(i, -4000);
	}
	if(index == 6)
		itemarray[6].whereitem = PLAYER;

	return 1;
}

int CItem::CheckItemTime()
{
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && (time_.GetMonth3() == 0+10) && (time_.GetDay() == 0*UNIT_PER_TICK))
		SET_BIT(itemflag, ITEM_3_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == SPRING) && (time_.GetMonth3() == 0+10) && (time_.GetDay() == 0*UNIT_PER_TICK))
		SET_BIT(itemflag, ITEM_1_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == FALL) && (time_.GetMonth3() == 45+10) && (time_.GetDay() == 0*UNIT_PER_TICK))
		SET_BIT(itemflag, ITEM_8_RELEASE);
	if((time_.GetYear() == 1) && (time_.GetSeason() == WINTER) && (time_.GetMonth3() == 0+10) && (time_.GetDay() == 0*UNIT_PER_TICK))
		SET_BIT(itemflag, ITEM_9_RELEASE);

	return 1;
}

INT_PTR CALLBACK CItem::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
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
					hWndDlg_item = NULL;
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
			hWndDlg_item = NULL;
            break;
    }

    return FALSE;
}

HWND CItem::GetHwnDia_Item()
{
	return hWndDlg_item;
}
int CItem::reload()
{
	itemarray[0].picture = DDLoadBitmap(lpdd, "art/item/item0.bmp", 0, 0);
	itemarray[1].picture = DDLoadBitmap(lpdd, "art/item/item1.bmp", 0, 0);
	itemarray[2].picture = DDLoadBitmap(lpdd, "art/item/item2.bmp", 0, 0);
	itemarray[3].picture = DDLoadBitmap(lpdd, "art/item/item3.bmp", 0, 0);
	itemarray[4].picture = DDLoadBitmap(lpdd, "art/item/item4.bmp", 0, 0);
	itemarray[5].picture = DDLoadBitmap(lpdd, "art/item/item5.bmp", 0, 0);
	itemarray[6].picture = DDLoadBitmap(lpdd, "art/item/item6.bmp", 0, 0);
	itemarray[7].picture = DDLoadBitmap(lpdd, "art/item/item7.bmp", 0, 0);
	itemarray[8].picture = DDLoadBitmap(lpdd, "art/item/item8.bmp", 0, 0);
	itemarray[9].picture = DDLoadBitmap(lpdd, "art/item/item9.bmp", 0, 0);

	return 1;
}
int CItem::Save()
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		WriteFile(hfile, &itemarray[i].description, sizeof(itemarray[i].description), &dwWritten, NULL);
		WriteFile(hfile, &itemarray[i].descriptionrect, sizeof(itemarray[i].descriptionrect), &dwWritten, NULL);
		WriteFile(hfile, &itemarray[i].picturerect, sizeof(itemarray[i].picturerect), &dwWritten, NULL);
		WriteFile(hfile, &itemarray[i].whereitem, sizeof(itemarray[i].whereitem), &dwWritten, NULL);
	}

	WriteFile(hfile, &itemflag, sizeof(itemflag), &dwWritten, NULL);

	return 1;
}
int CItem::Load()
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		ReadFile(hfile, &itemarray[i].description, sizeof(itemarray[i].description), &dwWritten, NULL);
		ReadFile(hfile, &itemarray[i].descriptionrect, sizeof(itemarray[i].descriptionrect), &dwWritten, NULL);
		ReadFile(hfile, &itemarray[i].picturerect, sizeof(itemarray[i].picturerect), &dwWritten, NULL);
		ReadFile(hfile, &itemarray[i].whereitem, sizeof(itemarray[i].whereitem), &dwWritten, NULL);
	}

	ReadFile(hfile, &itemflag, sizeof(itemflag), &dwWritten, NULL);

	return 1;
}
int CItem::Item_Shutdown()
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		if(itemarray[i].picture)
			itemarray[i].picture->Release();
	}

	return 1;
}
