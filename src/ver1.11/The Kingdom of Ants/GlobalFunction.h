

#pragma once

#include "CDebug.h"
#include "CObjDialog.h"
#include "CDomestic.h"
#include "CBattle.h"
#include "CItem.h"
#include "CDiplomatic.h"
#include "CBuilding.h"
#include "CMainMenu.h"
#include "CEvent.h"

extern int mouse_x;
extern int mouse_y;
extern int GameOver();

extern CDebug debug_;
extern CMainMenu mainmenu_;

// 다이얼로그 박스의 내용이 정확히 나오도록 기다림
int WaitDialog()
{
	MSG msg;
	for(int i=0; i<35; i++)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			if(msg.message == WM_QUIT)
			   break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} // end if
	} 

	return 1;
}
// point_x와 point_y가 rect안에 있는지 확인
int CheckRect(RECT *rect, int point_x, int point_y, BOOL screen_only = FALSE)
{
	if(screen_only == FALSE)
	{
		if((rect->left <= point_x) && (rect->right >= point_x))
			if((rect->top <= point_y) && (rect->bottom >= point_y))
				return 1;
	}
	else
	{
		
		if(mouse_x < SCREEN_WIDTH-INTERFACE2_WIDTH)
			if(mouse_y > INTERFACE1_HEIGHT)
				if((rect->left <= point_x) && (rect->right >= point_x))
					if((rect->top <= point_y) && (rect->bottom >= point_y))
						return 1;
	}

	return 0;
}
// 원하는 형태와 크기로 글자를 출력한다.
int DDraw_Text(char *text, 
			   int x,
			   int y, 
			   int size, 
			   LPDIRECTDRAWSURFACE7 lpdds, 
			   COLORREF fcolor, 
			   int fmode, 
			   COLORREF bkcolor, 
			   int bkmode,
			   char *fonttype = "굴림")
{
	HDC hdc;

	if (FAILED(lpdds->GetDC(&hdc)))
	   return(0);

	SetTextColor(hdc,fcolor);

	SetTextAlign(hdc, fmode);

	SetBkColor(hdc, bkcolor);

	SetBkMode(hdc, bkmode);

	HFONT font;
	font = CreateFontA(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, fonttype);

	SelectObject(hdc, font);
	DeleteObject(font);

	if(fmode == TA_CENTER)
		y -= (size/2-1);
	TextOutA(hdc,x,y,text,strlen(text));

	lpdds->ReleaseDC(hdc);

	return 1;
}
// 원하는 형태와 크기로 사각형안에 글자를 출력한다.
int DDraw_Text_Rect(char *text, 
			   RECT *text_rect,
			   int size,
			   LPDIRECTDRAWSURFACE7 lpdds, 
			   COLORREF fcolor, 
			   int fmode, 
			   COLORREF bkcolor, 
			   int bkmode,
			   char *fonttype = "굴림")
{
	HDC hdc;

	if (FAILED(lpdds->GetDC(&hdc)))
	   return(0);

	SetTextColor(hdc,fcolor);

	SetBkColor(hdc, bkcolor);

	SetBkMode(hdc, bkmode);
	
	HFONT font;
	font = CreateFontA(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, fonttype);

	SelectObject(hdc, font);
	DeleteObject(font);

	DrawTextA(hdc, text, -1, text_rect, fmode);

	lpdds->ReleaseDC(hdc);

	return 1;
}
int HideAllDialog()
{
	if(CEvent::GetHwnDia_Event())
		ShowWindow(CEvent::GetHwnDia_Event(), SW_HIDE);
	if(CEvent::GetHwnDia_Event_Dialog())
		ShowWindow(CEvent::GetHwnDia_Event_Dialog(), SW_HIDE);
	if(CEvent::GetHwnDia_Event_Normal())
		ShowWindow(CEvent::GetHwnDia_Event_Normal(), SW_HIDE);
	if(CBattle::GetHwnDia_Battle())
		ShowWindow(CBattle::GetHwnDia_Battle(), SW_HIDE);
	if(CBattle::GetHwnDia_Battle_Normal())
		ShowWindow(CBattle::GetHwnDia_Battle_Normal(), SW_HIDE);
	if(CBattle::GetHwnDia_Battle_Result_Att())
		ShowWindow(CBattle::GetHwnDia_Battle_Result_Att(), SW_HIDE);
	if(CBattle::GetHwnDia_Battle_Result_Def())
		ShowWindow(CBattle::GetHwnDia_Battle_Result_Def(), SW_HIDE);
	if(CBuilding::GetHwnDia_Building())
		ShowWindow(CBuilding::GetHwnDia_Building(), SW_HIDE);
	if(CDiplomatic::GetHwnDia_Dip())
		ShowWindow(CDiplomatic::GetHwnDia_Dip(), SW_HIDE);
	if(CDiplomatic::GetHwnDia_Dip_Error())
		ShowWindow(CDiplomatic::GetHwnDia_Dip_Error(), SW_HIDE);
	if(CDomestic::GetHwnDialog_Dom())
		ShowWindow(CDomestic::GetHwnDialog_Dom(), SW_HIDE);
	if(CItem::GetHwnDia_Item())
		ShowWindow(CItem::GetHwnDia_Item(), SW_HIDE);
	if(CObjDialog::GetHwnDia_Obj())
		ShowWindow(CObjDialog::GetHwnDia_Obj(), SW_HIDE);
	if(CObjDialog::GetHwnDia_Obj_Additonal())
		ShowWindow(CObjDialog::GetHwnDia_Obj_Additonal(), SW_HIDE);

	return 1;
}
int ShowAllDialog()
{
	if(CEvent::GetHwnDia_Event())
		ShowWindow(CEvent::GetHwnDia_Event(), SW_SHOWNORMAL);
	if(CEvent::GetHwnDia_Event_Dialog())
		ShowWindow(CEvent::GetHwnDia_Event_Dialog(), SW_SHOWNORMAL);
	if(CEvent::GetHwnDia_Event_Normal())
		ShowWindow(CEvent::GetHwnDia_Event_Normal(), SW_SHOWNORMAL);
	if(CBattle::GetHwnDia_Battle())
		ShowWindow(CBattle::GetHwnDia_Battle(), SW_SHOWNORMAL);
	if(CBattle::GetHwnDia_Battle_Normal())
		ShowWindow(CBattle::GetHwnDia_Battle_Normal(), SW_SHOWNORMAL);
	if(CBattle::GetHwnDia_Battle_Result_Att())
		ShowWindow(CBattle::GetHwnDia_Battle_Result_Att(), SW_SHOWNORMAL);
	if(CBattle::GetHwnDia_Battle_Result_Def())
		ShowWindow(CBattle::GetHwnDia_Battle_Result_Def(), SW_SHOWNORMAL);
	if(CBuilding::GetHwnDia_Building())
		ShowWindow(CBuilding::GetHwnDia_Building(), SW_SHOWNORMAL);
	if(CDiplomatic::GetHwnDia_Dip())
		ShowWindow(CDiplomatic::GetHwnDia_Dip(), SW_SHOWNORMAL);
	if(CDiplomatic::GetHwnDia_Dip_Error())
		ShowWindow(CDiplomatic::GetHwnDia_Dip_Error(), SW_SHOWNORMAL);
	if(CDomestic::GetHwnDialog_Dom())
		ShowWindow(CDomestic::GetHwnDialog_Dom(), SW_SHOWNORMAL);
	if(CItem::GetHwnDia_Item())
		ShowWindow(CItem::GetHwnDia_Item(), SW_SHOWNORMAL);
	if(CObjDialog::GetHwnDia_Obj())
		ShowWindow(CObjDialog::GetHwnDia_Obj(), SW_SHOWNORMAL);
	if(CObjDialog::GetHwnDia_Obj_Additonal())
		ShowWindow(CObjDialog::GetHwnDia_Obj_Additonal(), SW_SHOWNORMAL);

	WaitDialog();

	return 1;
}
int CloseAllDialog(int flag = 0)
{
	if(CEvent::GetHwnDia_Event())
		EndDialog(CEvent::GetHwnDia_Event(), TRUE );
	if(CEvent::GetHwnDia_Event_Dialog())
		EndDialog(CEvent::GetHwnDia_Event_Dialog(), TRUE );
	if(CEvent::GetHwnDia_Event_Normal())
		EndDialog(CEvent::GetHwnDia_Event_Normal(), TRUE );
	if(flag != EXCEPT_BATTLE)
	{
		if(CBattle::GetHwnDia_Battle())
			EndDialog(CBattle::GetHwnDia_Battle(), TRUE );
		if(CBattle::GetHwnDia_Battle_Normal())
			EndDialog(CBattle::GetHwnDia_Battle_Normal(), TRUE );
		if(CBattle::GetHwnDia_Battle_Result_Att())
			EndDialog(CBattle::GetHwnDia_Battle(), TRUE );
		if(CBattle::GetHwnDia_Battle_Result_Def())
			EndDialog(CBattle::GetHwnDia_Battle_Result_Def(), TRUE );
	}
	if(CBuilding::GetHwnDia_Building())
		EndDialog(CBuilding::GetHwnDia_Building(), TRUE );
	if(CDiplomatic::GetHwnDia_Dip())
		EndDialog(CDiplomatic::GetHwnDia_Dip(), TRUE );
	if(CDiplomatic::GetHwnDia_Dip_Error())
		EndDialog(CDiplomatic::GetHwnDia_Dip_Error(), TRUE );
	if(CDomestic::GetHwnDialog_Dom())
		EndDialog(CDomestic::GetHwnDialog_Dom(), TRUE );
	if(CItem::GetHwnDia_Item())
		EndDialog(CItem::GetHwnDia_Item(), TRUE );
	if(CObjDialog::GetHwnDia_Obj())
		EndDialog(CObjDialog::GetHwnDia_Obj(), TRUE );
	if(CObjDialog::GetHwnDia_Obj_Additonal())
		EndDialog(CObjDialog::GetHwnDia_Obj_Additonal(), TRUE );

	return 1;
}
int Select_State_Rand(int state1, int prob1,            
					  int state2, int prob2,    
					  int state3, int prob3,    
					  int state4, int prob4,    
					  int state5, int prob5,
				      int state6, int prob6)
{
// this function simply selects one of state1...state6 based on the probability
// of each state, if probi is 0 then the state is not considered

int index     = 0,   // looping variable
    curr_elem = 0,   // tracks next entry to place in table
    state_prob[100]; // used to hold generated probability look up

// build probability table
for (index = 0; index < prob1; index++)
    state_prob[curr_elem++] = state1;

for (index = 0; index < prob2; index++)
    state_prob[curr_elem++] = state2;

for (index = 0; index < prob3; index++)
    state_prob[curr_elem++] = state3;

for (index = 0; index < prob4; index++)
    state_prob[curr_elem++] = state4;

for (index = 0; index < prob5; index++)
    state_prob[curr_elem++] = state5;

for (index = 0; index < prob6; index++)
    state_prob[curr_elem++] = state6;

// now select a state
return(state_prob[rand()%100]);

} // end Select_State_Rand

BOOL ErrorMessage(HWND hwnd , char *str)
{
    MessageBox( hwnd, str, "연산실패", MB_OK );//메시지를 출력 할 메시지 박스  
    DestroyWindow( hwnd );//윈도우를 소멸시킨다.
    return FALSE;
}
