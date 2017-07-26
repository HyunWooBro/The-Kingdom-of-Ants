/*
///////////////////////////////////////////

	CInterface

	UI(상당, 오른쪽)를 단순히 그려주기만 한다.

///////////////////////////////////////////
*/

#ifndef CINTERFACE
#define CINTERFACE

#include "t3dlib1.h"
#include "ddutil.h"
#include "GlobalDeclaration.h"

class CInterface
{
public:
	CInterface() {}
	~CInterface() {}

private:
	LPDIRECTDRAWSURFACE7 sur_horinterface;
	LPDIRECTDRAWSURFACE7 sur_verinterface;

public:
	int Interface_Init();
	int DrawInterface();
	int Interface_Shutdown();

	int reload();

};


#endif
