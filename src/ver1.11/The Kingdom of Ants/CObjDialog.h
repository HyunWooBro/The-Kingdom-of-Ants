/*
///////////////////////////////////////////

	CObjDialog

	CObject class의 다이얼로그를 분담한다.
	자세한 사항은 CObject를 참고하라.

///////////////////////////////////////////
*/

#ifndef COBJDIALOG
#define COBJDIALOG

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CObjDialog
{
	friend class CInfo;
	friend class CBattle;
	friend class CItem;
	friend class CDomestic;
	friend class CObject;
	friend class CBuilding;
public:
	CObjDialog() {}
	~CObjDialog() {}

private:
	char buffer[180];

	struct _lab
	{
		char *name;
		int lab_cost[3];
		int remaintime;
		int inittime;
		char *describe_lab;
	}labarray[MAX_LAB];

	char *lab_on_subject;	// 현재 연구하고 있는 과제의 이름

	int selectedindex;

	int labflag;

	struct _library
	{
		char *page[5];
		int totalpage;
	}libraryarray[MAX_LIBRARY];

	int libraryflag;

	BOOL CheckedHired;

	struct _dialog
	{
		char *worker_dialog[4][3];
		char *soldier_dialog[4][3];
		char *queen_dialog;
		char *adviser_dialog[4];
		char *adviser_addition_dialog[4];
		char *nanny_dialog[3];
		char *scientist_dialog;
		char *mushroom_ant_dialog;
		char *church_ant_dialog;
		char *hired_1_dialog;
		char *hired_2_dialog;
		char *training_ant_dialog;
		char *art_ant_dialog;
		char *aphid_dialog;

		char *buildingqueen_dialog;
		char *strangestone_dialog[2];
		char *egg_dialog;
		char *warehouse_dialog[2];

		char *depository_dialog;
		char *mushroom_dialog;
		char *church_dialog;
		char *buildinghired_1_dialog;
		char *buildinghired_2_dialog;
		char *training_dilaog;
		char *art_dialog;

		char *seller_dialog[2];
	}dialog;

	static HWND hWndDlg_obj;
	static INT_PTR CALLBACK LabDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK LibraryDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK HiredDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK AdviserDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK NannyDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK SellerDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	
	static HWND hWndDlg_obj_additonal;
	static INT_PTR CALLBACK BookDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK ExpDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	int ShowExpDialog(int labindex);

	int ShowBookDialog(int bookindex);

	int ShowObjDialog_Under_Construction(int BUILDINGARRAY_INDEX);

public:
	int ObjDialog_Init();

	int ShowObjDialog_Worker();
	int ShowObjDialog_Soldier();
	int ShowObjDialog_Queen();
	int ShowObjDialog_Adviser();
	int ShowObjDialog_Nanny();
	int ShowObjDialog_Scientist();
	int ShowObjDialog_Mushroom_Ant();
	int ShowObjDialog_Church_Ant();
	int ShowObjDialog_Hired_1();
	int ShowObjDialog_Hired_2();
	int ShowObjDialog_Training_Ant();
	int ShowObjDialog_Art_Ant();
	int ShowObjDialog_Aphid();

	int ShowObjDialog_BuildingQueen();
	int ShowObjDialog_Egg();
	int ShowObjDialog_WareHouse();
	int ShowObjDialog_StrangeStone();

	int ShowObjDialog_Library();
	int ShowObjDialog_Depository();
	int ShowObjDialog_Lab();
	int ShowObjDialog_Training();
	int ShowObjDialog_Mushroom();
	int ShowObjDialog_BuildingHired_1();
	int ShowObjDialog_BuildingHired_2();
	int ShowObjDialog_Church();
	int ShowObjDialog_Art();

	int ShowObjDialog_Seller();

	int CheckLabTime();
	int CheckLibraryTime();

	int UpgradeLab();

	BOOL GetHiredCheck();

	static HWND GetHwnDia_Obj();
	static HWND GetHwnDia_Obj_Additonal();

	int Save();
	int Load();

	int ObjDialog_Shutdown();

};


#endif
