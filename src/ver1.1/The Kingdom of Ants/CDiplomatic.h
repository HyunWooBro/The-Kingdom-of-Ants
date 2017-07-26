/*
///////////////////////////////////////////

	CDiplomatic

	외교를 담당한다. 컴퓨터 종족의 연산에서부터
	컴퓨터 종족과의 외교까지 플레이어 이외의 종
	족과 관련된 일을 한다.

///////////////////////////////////////////
*/

#include <windows.h>
#include <ddraw.h>
#include <stdlib.h>
#include "t3dlib1.h"
#include "ddutil.h"
#include "GlobalDeclaration.h"

#pragma once

class CDiplomatic
{
	friend class CBattle;
	friend class CDomestic;
public:
	CDiplomatic() {}
	~CDiplomatic() {}

private:
	char buffer[20];

	struct _diplomatic				// 외교 패널
	{
		RECT diprect;
		BOOL Disalbed;
		POINT middlepoint;
		BOOL bshow;
		char *diptype;
	}diparray[MAX_DIP];

	static HWND hWndDlg_dip;
	static INT_PTR CALLBACK DipAttackDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK DipSupportDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK DipPropagationDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static HWND hWndDlg_dip_normal;
	static INT_PTR CALLBACK NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	int ChangeRelation(int food, int timber, int mineral);
	int ChangeReligion();
	int CheckPropagation();
public:
	int Diplomatic_Init();

	int PrintMapinfo();
	int PrintDipMenu();			// 외교 다이얼로그를 띄운다.(공격, 증정 등)
	int SelectSpecies();
	int ShowDialog();
	int ComputeSpecies();		// 컴퓨터 종족의 정보에 대한 필요한 연산을 한다.
	int GetPresent();			// 정복한 적으로부터 공물을 받는다.
	int ChangeRelation(int SPEARRAY_INDEX, int value);
	int ChangeSpeState(int SPEARRAY_INDEX, int STATE);
	int ChangeSpeStrength(int SPEARRAY_INDEX, int value);
	int LearnLanguage(int SPEARRAY_INDEX);
	int EnablePropagation();
	int EnableSpecies(int SPEARRAY_INDEX);
	int SetAttempt_to_Attack(int SPEARRAY_INDEX, int value);
	int EnableDipAtt();
	BOOL PickUpSpe(int *spe1_index, int *spe2_index);
	
	static HWND GetHwnDia_Dip();
	static HWND GetHwnDia_Dip_Error();

	int Save();
	int Load();

	int Diplomatic_Shutdown();

};
