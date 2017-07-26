/*
///////////////////////////////////////////

	CDebug

	개발 중 디버그 용으로 사용

///////////////////////////////////////////
*/
#ifndef CDEBUG
#define CDEBUG

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CDebug
{
public:
	CDebug(); 
	~CDebug() {}
private:
	char buffer[80];			// 변수 출력에 사용
	struct _debuginfo
	{
		const char *title;
		int *v1;
		int *v2;
		LPDIRECTDRAWSURFACE7 sur;
		int text_height;
	}dinfoarray[MAX_DINFO];

	const char *temp_title;
	const char *temp_char;
	LPDIRECTDRAWSURFACE7 temp_sur;
public:
	// 변수(int) 입력
	// index는 1 ~ 20까지만
	int GetValue(const char *title ,int *v1, int *v2, LPDIRECTDRAWSURFACE7 sur, int index,int flag);	
	// 변수(char) 입력
	// 한 문자열만 가능
	int GetValue(const char *title ,char *c1, LPDIRECTDRAWSURFACE7 sur)
	{
		temp_char = c1;
		temp_title = title;
		temp_sur = sur;

		return 1;
	}
		// 디버그 정보 화면에 출력
	int PrintDbInfo();
};


#endif
