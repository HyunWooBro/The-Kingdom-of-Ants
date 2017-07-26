/*
/////////////////////////////////////////////////////////////

	CEvent

	event에 대한 정의는 주 스토리와는 별개로 주기적으로
	일어나는 사건을 말한다.

/////////////////////////////////////////////////////////////
*/

#ifndef CEVENT
#define CEVENT

#include "GlobalDeclaration.h"

class CEvent
{
	friend class CDiplomatic;
public:
	CEvent() {}
	~CEvent() {}

private:
	char buffer[200];
	struct _event
	{
		BOOL Exist;
		EVENT_TYPE eventtype;
		int remaintime;
		int temp[2];
	}eventarray[MAX_EVENT];

	static HWND hWndDlg_event;
	static INT_PTR CALLBACK EveFightDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static HWND hWndDlg_event_dialog;
	static HWND hWndDlg_event_normal;
	static INT_PTR CALLBACK NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static DWORD WINAPI ThreadEventFight(LPVOID temp);

	int EventSeller();
	int EventFight();
	int EventDialog();
public:
	int Event_Init();

	int CheckEvent();
	int SetEvent(int EVENTARRAY_INDEX);

	static HWND GetHwnDia_Event();
	static HWND GetHwnDia_Event_Dialog();
	static HWND GetHwnDia_Event_Normal();

	int Save();
	int Load();

	int Event_Shutdown();
};


#endif
