/*
///////////////////////////////////////////

	CItem

	아이템과 관련된 연산을 담당한다.

///////////////////////////////////////////
*/
#ifndef CITEM
#define CITEM

#include <ddraw.h>
#include "GlobalDeclaration.h"

class CItem
{
public:
	CItem() {}
	~CItem() {}

private:
	struct _item
	{
		WHERE_ITEM whereitem;
		LPDIRECTDRAWSURFACE7 picture;
		RECT picturerect;
		char *description;
		RECT descriptionrect;
	}itemarray[MAX_ITEM];

	int itemflag;

	static HWND hWndDlg_item;
	static INT_PTR CALLBACK NormalDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	int ShowFinedItem(int item_index);

public:
	int Item_Init();

	int PrintItem();
	int SearchItem();	
	int TakeItemFromSpe(int SPEARRAY_INDEX);	
	int BuyItem(int index);
	int SetItem(int index, WHERE_ITEM whereitem);
	WHERE_ITEM GetItem(int index);
	int CheckItemTime();

	static HWND GetHwnDia_Item();

	int reload();

	int Save();
	int Load();

	int Item_Shutdown();
	
};


#endif
