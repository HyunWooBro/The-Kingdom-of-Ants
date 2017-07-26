
#include <stdio.h> 
#include <ddraw.h>
#include "t3dlib1.h"
#include "CDebug.h"
#include "GlobalDeclaration.h"

CDebug::CDebug()
{
	for(int i=0; i<MAX_DINFO; i++)
	{
		dinfoarray[i].title = NULL;
	}
}

int CDebug::GetValue(const char *title ,int *v1, int *v2, LPDIRECTDRAWSURFACE7 sur, int index,int flag)
{
	if((index > MAX_DINFO) || (index < 1))
		return 0;

	if(v1 == NULL)
		return 0;

	dinfoarray[index-1].text_height = index;
	dinfoarray[index-1].title = title;
	dinfoarray[index-1].v1 = v1;
	dinfoarray[index-1].sur = sur;
	if(flag != ONLY_V1)
	{
		if(v2 == NULL)
			return 0;
		dinfoarray[index-1].v2 = v2;
	}
	else
		dinfoarray[index-1].v2 = (int *)ONLY_V1;
		
	return 1;
}

int CDebug::PrintDbInfo()
{
	for(int i=0; i<MAX_DINFO; i++)
	{
		if(dinfoarray[i].title != NULL)
		{
			const char *ttitle = dinfoarray[i].title;
			int *tv1 = dinfoarray[i].v1;
			int *tv2 = dinfoarray[i].v2;
			int theight = dinfoarray[i].text_height;
			LPDIRECTDRAWSURFACE7 tsur = dinfoarray[i].sur;
			
			if(dinfoarray[i].v2 == (int *)ONLY_V1)
			{
				if(tv1 == NULL)
					return 0;
				sprintf(buffer, "%s %d", ttitle, *tv1);
			}
			else
			{
				if((tv1 == NULL) || (tv2 == NULL))
					return 0;
				sprintf(buffer, "%s (%d, %d)", ttitle, *tv1, *tv2);
			}
			DDraw_Text(buffer, 
						8,
						SCREEN_HEIGHT - 16*theight,
						NULL,
						tsur,
						RGB(255,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT,
						"System");
		}
	}

	if((temp_sur != NULL) && (temp_char != NULL))
	{
		sprintf(buffer, "%s : %s", temp_title, temp_char);
		DDraw_Text(buffer, 
						8,
						SCREEN_HEIGHT - 16*26,
						NULL,
						temp_sur,
						RGB(255,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT,
						"System");
	}

	return 1;
}
