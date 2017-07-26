
#include <ddraw.h>
#include "CInterface.h"

int CInterface::Interface_Init()
{
	sur_horinterface = DDLoadBitmap(lpdd, "art/interface/horinterface.bmp", 0, 0);
	if(sur_horinterface == NULL)
		ErrorMessage(main_window_handle, "fff");
	sur_verinterface = DDLoadBitmap(lpdd, "art/interface/verinterface.bmp", 0, 0);

	return 1;
}


int CInterface::DrawInterface()
{
	RECT dest_rect = {0, 0, INTERFACE1_WIDTH, INTERFACE1_HEIGHT};
	RECT dest_rect2 = {SCREEN_WIDTH-INTERFACE2_WIDTH, INTERFACE1_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	lpddsback->Blt(&dest_rect, sur_horinterface, NULL, DDBLT_WAIT, NULL);
	lpddsback->Blt(&dest_rect2, sur_verinterface, NULL, DDBLT_WAIT, NULL);

	return 1;
}

int CInterface::reload()
{
	sur_horinterface = DDLoadBitmap(lpdd, "art/interface/horinterface.bmp", 0, 0);
	sur_verinterface = DDLoadBitmap(lpdd, "art/interface/verinterface.bmp", 0, 0);

	return 1;
}

int CInterface::Interface_Shutdown()
{
	if(sur_verinterface)
		sur_verinterface->Release();
	if(sur_horinterface)
		sur_horinterface->Release();

	return 1;
}
