/*
///////////////////////////////////////////

	CDomestic

	내정을 담당한다. 다이얼로그박스를 띄워 사용자의
	명령을 전달받는 것에서부터 실질적인 자원 관리,
	개미 수 증가 등까지 내정에 관해 총체적으로
	작업한다.

///////////////////////////////////////////
*/

#pragma once

#include <stdio.h> 
#include <ddraw.h>
#include <stdlib.h>
#include "t3dlib1.h"
#include "ddutil.h"
#include "GlobalDeclaration.h"

class CDomestic
{
	friend class CInfo;
	friend class CBattle;
	friend class CItem;
	friend class CDiplomatic;
	friend class CObjDialog;
	friend class CBuilding;
public:
	CDomestic() {}
	~CDomestic() {}

private:
	char buffer[10];
	struct _domestic
	{
		RECT domrect;
		POINT middlepoint;
		BOOL Disalbed;			// 변경한 후에 일정시간동안 사용하지 못함
		char *domtype;
		char describe_dom[100];
		int remaintime;
		int panel[4];
		int changeday;
		int changevalue;
	}domarray[MAX_DOM];

	int GetMaxPanel(int firstpanel, int secondpanel, int thirdpanel, 
					int firstcheck, int secondcheck, int thirdcheck);

	int GetMinPanel(int firstpanel, int secondpanel, int thirdpanel, 
					int firstcheck, int secondcheck, int thirdcheck);

	static HWND hWndDlg_dom;
	static INT_PTR CALLBACK DomWorkerDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK DomSoldierDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK DomQueenDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static INT_PTR CALLBACK GameoverDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static DWORD WINAPI ThreadGameover(LPVOID temp);
public:
	int Domestic_Init();

	int Resource_Init();
	int Resource_Final();
	int CheckPrintTime();
	int PrintDomMenu();
	int ShowDialog();
	int PrintResource();
	int ProduceResource();
	int ConsumeFood();	
	int CoputeAnts();			// 일꾼과 병정개미의 수를 사용자의 선택대로 나눈다.
	int hire();
	int ProduceAnts();
	int ComputeOther();
	int ChangeResource(int food, int timber, int mineral);
	int ChangeUnsatisfactory(int value);
	int UpgradeDom(int LAB_INDEX);
	int UpgradeMaxResource();
	int HelpAhpid();
	int ReturnFromBattle();
	int ComputeAttAnts(int num_soldier_attack, int num_hired_attack);
	int ComputeDefAnts(int num_soldier_defence, int num_hired_defence);
	
	static HWND GetHwnDialog_Dom();

	int Save();
	int Load();

	int Domestic_Shutdown();
};
