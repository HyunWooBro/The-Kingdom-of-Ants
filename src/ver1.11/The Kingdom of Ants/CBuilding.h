/*
///////////////////////////////////////////

	CBuilding

	오른쪽 인터페이스에 건물의 이름을 뿌려주고,
	다이얼로그 박스를 띄우며 scrren_game(개미 굴이 나오는 화면)
	에 방이	완성이 될때까지 관여한다. 공사가 시작하는 시점에서
	CObject class와 같이 그 방을 담당하며 방이 완성
	되면 인터페이스에 글자를 뿌려주는 것 이외에 건물에 관련된 
	모든 일을 CObject가 맡는다.

///////////////////////////////////////////
*/

#pragma once

#include <windows.h>
#include <ddraw.h>
#include <stdlib.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CBuilding
{
	friend class CScreen;
	friend class CInfo;
	friend class CBattle;
	friend class CStory;
	friend class CItem;
	friend class CDomestic;
	friend class CObjDialog;
	friend class CBattle;
public:
	CBuilding() {}
	~CBuilding() {}

private:
	char buffer[90];					// 출력용
	struct _building
	{
		char *buildingtype;				// 건물의 이름
		BOOL bexist;					// 건물이 지어졌는가
		BOOL bshow;						// 건물의 이름이 인터페이스에 나오는가
		BOOL Disabled;					// 건설 불가능으로 만든다; 
										// 용병양성소와 종교 회관이 해당된다.
		int remaintime;					// 완공까지의 남은 정도
		int inittime;					// 초기 완공까지의 시간
		POINT middlepoint;				// 인터페이스에서 이름을 출력할 위치의 중앙
		char *describe_building;		// 건물 설명
		int building_cost[3];			// 건물 비용
		RECT buildingrect;				// 인터페이스에서 건물 이름의 위치
	}buildingarray[MAX_BUILDING];

	char *building_under_construction;	// 현재 건설되고 있는 건물의 이름
	
	static HWND hWndDlg_building;
	static INT_PTR CALLBACK BuildingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK BuildingErrorDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static DWORD WINAPI ThreadBuilding(LPVOID temp);

public:
	int Building_Init();

	int PrintBuildingMenu();
	int ShowDialog();
	int CheckBuildingTime();
	int ShowBuilding(int BUILDINGARRAY_INDEX);
	int DisableBuilding(int BUILDINGARRAY_INDEX);

	static HWND GetHwnDia_Building();

	int Save();
	int Load();

	int Building_Shutdown();
};
