/*
///////////////////////////////////////////

	CObject

	이 게임에서 object의 정의는 screen상(interface를 제외)에서 
	사용자와 상호작용하는 모든 물체를 말한다. 개미, 방, 종족 등
	마우스를 올렸을 때 오른쪽 아래에 이름이 나오는 것
	을 말한다.
	COject의 역활이 너무 많아 CObjDialog class에서
	다이얼로그 박스를 띄우는 일을 분담시켰다.

///////////////////////////////////////////
*/

#ifndef COBJECT
#define COBJECT

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"
#include "CObjDialog.h"

class CObject
{
	friend class CBattle;
	friend class CDiplomatic;
	friend class CBuilding;
	friend class CObjDialog;
public:
	CObject() {}
	~CObject() {}

private:
	char buffer[80];

	struct _object
	{
		char *name;
		BOOL bshowname;
		RECT objrect;
		OBJSCREEN objscreen;
		BOOL bdialog;
		BOB bob;
		BOOL bshowbob;
		int dialogtype;
		int temp[5];
	}objarray[MAX_OBJECT], pobjarray;
	
	typedef struct WAYPOINT_TYP
	{
		int x,y;
	}WAYPOINT, *WAYPOINT_PTR;

	WAYPOINT path[NUM_WAYPOINTS]; 

	int CheckDistance(int x1, int y1, int x2, int y2);
	int SetAniDir(BOB *bob, int newway, int oldway);

public:
	int Obj_Init();

	int PrintObjName();
	int DrawObjBob();
	int MoveObjBob();
	int SetObName(int OBJARRAY_INDEX, char *name);
	int ShowDialog();
	int EnableBuildingObj(int OBJARRAY_INDEX);
	int ChangeObjTemp(int OBJARRAY_INDEX, int INDEX, int value);
	int ChangeObjBobFrame(int OBJARRAY_INDEX, int frame);
	int EnableMapObj(int OBJARRAY_INDEX);
	int ShowObjBob(int OBJARRAY_INDEX);
	int ShowWanderingAnts();

	int Save();
	int Load();

	int Obj_Shutdown();

};



#endif
