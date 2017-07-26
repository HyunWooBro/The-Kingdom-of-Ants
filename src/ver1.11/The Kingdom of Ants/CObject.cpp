
#include <stdio.h> 
#include "CObject.h"
#include "CobjDialog.h"
#include "CPlayer.h"
#include "CDebug.h"
#include "CTime.h"
#include "GlobalDeclaration.h"

extern CDebug debug_;
extern CObjDialog objdialog_;

int CObject::Obj_Init()
{
	int temp_path_array[NUM_WAYPOINTS][2] = {
	{317,230},
	{328,263},
	{343,322},
	{337,365},
	{307,410},
	{351,447},
	{399,437},
	{440,412},
	{486,454},
	{522,470},
	{554,444},
	{587,423},
	{626,409},
	{664,373},
	{686,325},
	{665,278}};

	for(int i=0; i<NUM_WAYPOINTS; i++)
	{
		path[i].x = temp_path_array[i][0];
		path[i].y = temp_path_array[i][1];
	}
	
	for(int i=0; i<MAX_OBJECT; i++)
		ZeroMemory(&objarray[i], sizeof(objarray[i]));

	Create_BOB(&objarray[0].bob,0,0, 24,24, 2, BOB_ATTR_MULTI_FRAME | BOB_ATTR_VISIBLE, DDSCAPS_SYSTEMMEMORY);

	

	BITMAP_FILE snail;
	ZeroMemory(&snail, sizeof(BITMAP_FILE));
	Load_Bitmap_File(&snail, "art/etc/ANTIMG8.bmp");

	for(int index=0; index < 2; index++)
		Load_Frame_BOB(&objarray[0].bob, &snail, index, index, 2, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&snail);

	for (int index=1; index<6; index++)
		Clone_BOB(&objarray[0].bob, &objarray[index].bob);

	objarray[0].name = "민달팽이 서식처";
	objarray[0].bshowname = TRUE;
	objarray[0].objscreen = OBJSCREEN_MAP;
	objarray[0].bdialog = FALSE;
	SetRect(&objarray[0].objrect, 291, 241, 291+20, 241+20);
	objarray[0].bshowbob = TRUE;
	objarray[0].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[0].bob.x = 291;
	objarray[0].bob.y = 241;
	objarray[0].bob.curr_frame = 0;

	objarray[1].name = "메뚜기 서식처";
	objarray[1].bshowname = TRUE;
	objarray[1].objscreen = OBJSCREEN_MAP;
	objarray[1].bdialog = FALSE;
	SetRect(&objarray[1].objrect, 159, 258, 159+20, 258+20);
	objarray[1].bshowbob = TRUE;
	objarray[1].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[1].bob.x = 159;
	objarray[1].bob.y = 258;
	objarray[1].bob.curr_frame = 0;

	objarray[2].name = "난쟁이개미 굴";
	objarray[2].bshowname = TRUE;
	objarray[2].objscreen = OBJSCREEN_MAP;
	objarray[2].bdialog = FALSE;
	SetRect(&objarray[2].objrect, 379, 235, 379+20, 235+20);
	objarray[2].bshowbob = TRUE;
	objarray[2].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[2].bob.x = 379;
	objarray[2].bob.y = 235;
	objarray[2].bob.curr_frame = 0;

	objarray[3].name = "꿀벌 집";
	objarray[3].bshowname = FALSE;
	objarray[3].objscreen = OBJSCREEN_MAP;
	objarray[3].bdialog = FALSE;
	SetRect(&objarray[3].objrect, 85, 246, 85+20, 246+20);
	objarray[3].bshowbob = FALSE;
	objarray[3].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[3].bob.x = 85;
	objarray[3].bob.y = 246;
	objarray[3].bob.curr_frame = 0;

	objarray[4].name = "불개미 굴";
	objarray[4].bshowname = FALSE;
	objarray[4].objscreen = OBJSCREEN_MAP;
	objarray[4].bdialog = FALSE;
	SetRect(&objarray[4].objrect, 195, 288, 195+20, 288+20);
	objarray[4].bshowbob = FALSE;
	objarray[4].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[4].bob.x = 195;
	objarray[4].bob.y = 288;
	objarray[4].bob.curr_frame = 0;

	objarray[5].name = "암개미 1호의 굴";
	objarray[5].bshowname = TRUE;
	objarray[5].objscreen = OBJSCREEN_MAP;
	objarray[5].bdialog = FALSE;
	SetRect(&objarray[5].objrect, 305, 174, 305+20, 174+25);
	objarray[5].bshowbob = TRUE;
	objarray[5].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;

	objarray[5].bob.x = 305;
	objarray[5].bob.y = 174;
	objarray[5].bob.curr_frame = 0;

	objarray[6].name = "수상한 돌덩이";
	objarray[6].bshowname = TRUE;
	objarray[6].objscreen = OBJSCREEN_GAME;
	objarray[6].bdialog = TRUE;
	objarray[6].dialogtype = STRANGE_STONE_DIALOG;
	SetRect(&objarray[6].objrect, 710, 636, 781, 672);
	objarray[6].bshowbob = FALSE;

	objarray[7].name = "비어있는 창고";
	objarray[7].bshowname = TRUE;
	objarray[7].objscreen = OBJSCREEN_GAME;
	objarray[7].bdialog = TRUE;
	objarray[7].bshowbob = FALSE;
	objarray[7].dialogtype = BUILDING_WAREHOUSE_DIALOG;
	SetRect(&objarray[7].objrect, 730, 367, 806, 426);

	objarray[8].name = "여왕 개미의 방";
	objarray[8].bshowname = TRUE;
	objarray[8].objscreen = OBJSCREEN_GAME;
	objarray[8].bdialog = TRUE;
	objarray[8].bshowbob = FALSE;
	objarray[8].dialogtype = BUILDING_QUEEN_DIALOG;
	SetRect(&objarray[8].objrect, 255, 471, 356, 542);

	objarray[9].name = "영아실";
	objarray[9].bshowname = TRUE;
	objarray[9].objscreen = OBJSCREEN_GAME;
	objarray[9].bdialog = TRUE;
	objarray[9].bshowbob = FALSE;
	objarray[9].dialogtype = BUILDING_EGG_DIALOG;
	SetRect(&objarray[9].objrect, 415, 535, 483, 586);

	objarray[10].name = "도서관";
	objarray[10].bshowname = FALSE;
	objarray[10].objscreen = OBJSCREEN_GAME;
	objarray[10].bdialog = FALSE;
	objarray[10].bshowbob = FALSE;
	objarray[10].dialogtype = BUILDING_LIBRARY_DIALOG;
	objarray[10].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[10].objrect, 630, 531, 726, 590);

	objarray[11].name = "자원 보관소";
	objarray[11].bshowname = FALSE;
	objarray[11].objscreen = OBJSCREEN_GAME;
	objarray[11].bdialog = FALSE;
	objarray[11].bshowbob = FALSE;
	objarray[11].dialogtype = BUILDING_DEPOSITORY_DIALOG;
	objarray[11].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[11].objrect, 361, 349, 447, 401);

	objarray[12].name = "화학 연구소";
	objarray[12].bshowname = FALSE;
	objarray[12].objscreen = OBJSCREEN_GAME;
	objarray[12].bdialog = FALSE;
	objarray[12].bshowbob = FALSE;
	objarray[12].dialogtype = BUILDING_LAB_DIALOG;
	objarray[12].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[12].objrect, 196, 374, 294, 438);

	objarray[13].name = "전투 연습실";
	objarray[13].bshowname = FALSE;
	objarray[13].objscreen = OBJSCREEN_GAME;
	objarray[13].bdialog = FALSE;
	objarray[13].bshowbob = FALSE;
	objarray[13].dialogtype = BUILDING_TRAINING_DIALOG;
	objarray[13].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[13].objrect, 360, 269, 452, 332);

	objarray[14].name = "버섯 재배실";
	objarray[14].bshowname = FALSE;
	objarray[14].objscreen = OBJSCREEN_GAME;
	objarray[14].bdialog = FALSE;
	objarray[14].bshowbob = FALSE;
	objarray[14].dialogtype = BUILDING_MUSHROOM_DIALOG;
	objarray[14].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[14].objrect, 750, 569, 832, 626);

	objarray[15].name = "용병양성소-장수풍뎅이";
	objarray[15].bshowname = FALSE;
	objarray[15].objscreen = OBJSCREEN_GAME;
	objarray[15].bdialog = FALSE;
	objarray[15].bshowbob = FALSE;
	objarray[15].dialogtype = BUILDING_HIRED_1_DIALOG;
	objarray[15].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[15].objrect, 557, 317, 655, 385);

	objarray[16].name = "용병양성소-사슴벌레";
	objarray[16].bshowname = FALSE;
	objarray[16].objscreen = OBJSCREEN_GAME;
	objarray[16].bdialog = FALSE;
	objarray[16].bshowbob = FALSE;
	objarray[16].dialogtype = BUILDING_HIRED_2_DIALOG;
	objarray[16].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[16].objrect, 557, 317, 655, 385);

	objarray[17].name = "종교 회관";
	objarray[17].bshowname = FALSE;
	objarray[17].objscreen = OBJSCREEN_GAME;
	objarray[17].bdialog = FALSE;
	objarray[17].bshowbob = FALSE;
	objarray[17].dialogtype = BUILDING_CHURCH_DIALOG;
	objarray[17].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[17].objrect, 732, 455, 815, 525);

	objarray[18].name = "예술의 전당";
	objarray[18].bshowname = FALSE;
	objarray[18].objscreen = OBJSCREEN_GAME;
	objarray[18].bdialog = FALSE;
	objarray[18].bshowbob = FALSE;
	objarray[18].dialogtype = BUILDING_ART_DIALOG;
	objarray[18].temp[BULIDING_INT_STATE] = BUILDING_UNDER_CONSTRUCTION;
	SetRect(&objarray[18].objrect, 205, 244, 314, 321);


	objarray[19].name = "일꾼 개미";
	objarray[19].bshowname = FALSE;
	objarray[19].objscreen = OBJSCREEN_GAME;
	objarray[19].bdialog = FALSE;
	objarray[19].bshowbob = FALSE;
	objarray[19].dialogtype = WORKER_DIALOG;
	objarray[19].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[19].bob.varsI[ANT_INT_CUR_WAYPOINT] = 1;
	objarray[19].bob.varsI[ANT_INT_OLD_WAYPOINT] = 0;
	objarray[19].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[19].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;

	Create_BOB(&objarray[19].bob,317,230, 24,24, 9, BOB_ATTR_MULTI_ANIM | BOB_ATTR_VISIBLE, DDSCAPS_SYSTEMMEMORY);

	BITMAP_FILE ant;
	ZeroMemory(&ant, sizeof(BITMAP_FILE));
	Load_Bitmap_File(&ant, "art/insect/곤충들.bmp");

	// load the ants in 
	for (int index=0; index < 9; index++)
		Load_Frame_BOB(&objarray[19].bob, &ant, index, index, 0, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&ant);

	// set the animations
	int ant_anim_up[3]    = {0,1,-1};
	int ant_anim_right[3] = {2,3,-1};
	int ant_anim_down[3]  = {4,5,-1};
	int ant_anim_left[3]  = {6,7,-1};
	int ant_anim_dead[2]  = {8,-1};

	Load_Animation_BOB(&objarray[19].bob,0,2, ant_anim_up);
	Load_Animation_BOB(&objarray[19].bob,1,2, ant_anim_right);
	Load_Animation_BOB(&objarray[19].bob,2,2, ant_anim_down);
	Load_Animation_BOB(&objarray[19].bob,3,2, ant_anim_left);
	Load_Animation_BOB(&objarray[19].bob,4,2, ant_anim_dead);

	Set_Anim_Speed_BOB(&objarray[19].bob,8);
	Set_Animation_BOB(&objarray[19].bob, ANT_ANIM_DOWN);
	objarray[19].bob.anim_state = ANT_ANIM_DOWN;
	objarray[19].bob.curr_frame = 4;

	objarray[20].name = "일꾼 개미";
	objarray[20].bshowname = FALSE;
	objarray[20].objscreen = OBJSCREEN_GAME;
	objarray[20].bdialog = FALSE;
	objarray[20].bshowbob = FALSE;
	objarray[20].dialogtype = WORKER_DIALOG;
	objarray[20].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[20].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[20].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[20].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[20].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;

	Clone_BOB(&objarray[19].bob, &objarray[20].bob);

	objarray[21].name = "일꾼 개미";
	objarray[21].bshowname = FALSE;
	objarray[21].objscreen = OBJSCREEN_GAME;
	objarray[21].bdialog = FALSE;
	objarray[21].bshowbob = FALSE;
	objarray[21].dialogtype = WORKER_DIALOG;
	objarray[21].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[21].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[21].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[21].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[21].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[19].bob, &objarray[21].bob);

	objarray[22].name = "일꾼 개미";
	objarray[22].bshowname = FALSE;
	objarray[22].objscreen = OBJSCREEN_GAME;
	objarray[22].bdialog = FALSE;
	objarray[22].bshowbob = FALSE;
	objarray[22].dialogtype = WORKER_DIALOG;
	objarray[22].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[22].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[22].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[22].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[22].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[19].bob, &objarray[22].bob);

	objarray[23].name = "일꾼 개미";
	objarray[23].bshowname = FALSE;
	objarray[23].objscreen = OBJSCREEN_GAME;
	objarray[23].bdialog = FALSE;
	objarray[23].bshowbob = FALSE;
	objarray[23].dialogtype = WORKER_DIALOG;
	objarray[23].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[23].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[23].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[23].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[23].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[19].bob, &objarray[23].bob);

	objarray[24].name = "병정 개미";
	objarray[24].bshowname = FALSE;
	objarray[24].objscreen = OBJSCREEN_GAME;
	objarray[24].bdialog = FALSE;
	objarray[24].bshowbob = FALSE;
	objarray[24].dialogtype = SOLDIER_DIALOG;
	objarray[24].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[24].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[24].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[24].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[24].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;

	Create_BOB(&objarray[24].bob,317,230, 24,24, 9, BOB_ATTR_MULTI_ANIM | BOB_ATTR_VISIBLE, DDSCAPS_SYSTEMMEMORY);

	ZeroMemory(&ant, sizeof(BITMAP_FILE));
	Load_Bitmap_File(&ant, "art/insect/곤충들.bmp");

	// load the ants in 
	for (int index=0; index < 9; index++)
		Load_Frame_BOB(&objarray[24].bob, &ant, index, index, 1, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&ant);

	Load_Animation_BOB(&objarray[24].bob,0,2, ant_anim_up);
	Load_Animation_BOB(&objarray[24].bob,1,2, ant_anim_right);
	Load_Animation_BOB(&objarray[24].bob,2,2, ant_anim_down);
	Load_Animation_BOB(&objarray[24].bob,3,2, ant_anim_left);
	Load_Animation_BOB(&objarray[24].bob,4,2, ant_anim_dead);

	Set_Anim_Speed_BOB(&objarray[24].bob,8);
	Set_Animation_BOB(&objarray[24].bob, ANT_ANIM_DOWN);
	objarray[24].bob.anim_state = ANT_ANIM_DOWN;
	objarray[24].bob.curr_frame = 4;

	objarray[25].name = "병정 개미";
	objarray[25].bshowname = FALSE;
	objarray[25].objscreen = OBJSCREEN_GAME;
	objarray[25].bdialog = FALSE;
	objarray[25].bshowbob = FALSE;
	objarray[25].dialogtype = SOLDIER_DIALOG;
	objarray[25].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[25].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[25].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[25].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[25].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[24].bob, &objarray[25].bob);

	objarray[26].name = "병정 개미";
	objarray[26].bshowname = FALSE;
	objarray[26].objscreen = OBJSCREEN_GAME;
	objarray[26].bdialog = FALSE;
	objarray[26].bshowbob = FALSE;
	objarray[26].dialogtype = SOLDIER_DIALOG;
	objarray[26].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[26].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[26].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[26].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[26].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[24].bob, &objarray[26].bob);

	objarray[27].name = "병정 개미";
	objarray[27].bshowname = FALSE;
	objarray[27].objscreen = OBJSCREEN_GAME;
	objarray[27].bdialog = FALSE;
	objarray[27].bshowbob = FALSE;
	objarray[27].dialogtype = SOLDIER_DIALOG;
	objarray[27].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[27].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[27].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[27].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[27].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[24].bob, &objarray[27].bob);

	objarray[28].name = "병정 개미";
	objarray[28].bshowname = FALSE;
	objarray[28].objscreen = OBJSCREEN_GAME;
	objarray[28].bdialog = FALSE;
	objarray[28].bshowbob = FALSE;
	objarray[28].dialogtype = SOLDIER_DIALOG;
	objarray[28].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[28].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[28].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[28].bob.varsI[ANT_INT_RESTING] = 0;
	objarray[28].temp[BOB_INT_MOVE] = BOB_MOVE_NORMAL;
  
	Clone_BOB(&objarray[24].bob, &objarray[28].bob);

	objarray[29].name = "여왕 암개미 1호";
	objarray[29].bshowname = TRUE;
	objarray[29].objscreen = OBJSCREEN_GAME;
	objarray[29].bdialog = TRUE;
	objarray[29].dialogtype = QUEEN_DIALOG;
	objarray[29].bshowbob = TRUE;
	objarray[29].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[29].objrect, 255, 495, 255+50, 495+25);

	Load_Bitmap_File(&ant, "art/insect/queen.bmp");
	Create_BOB(&objarray[29].bob,255,495,50,25,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[29].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[30].name = "참모 개미";
	objarray[30].bshowname = TRUE;
	objarray[30].objscreen = OBJSCREEN_GAME;
	objarray[30].bdialog = TRUE;
	objarray[30].dialogtype = ADVISER_DIALOG;
	objarray[30].bshowbob = TRUE;
	objarray[30].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[30].objrect, 310, 510, 310+32, 510+20);

	Load_Bitmap_File(&ant, "art/insect/ant2_left.bmp");
	Create_BOB(&objarray[30].bob,310,510,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[30].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[31].name = "유모 개미";
	objarray[31].bshowname = TRUE;
	objarray[31].objscreen = OBJSCREEN_GAME;
	objarray[31].bdialog = TRUE;
	objarray[31].dialogtype = NANNY_DIALOG;
	objarray[31].bshowbob = TRUE;
	objarray[31].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[31].objrect, 440, 555, 440+32, 555+20);

	Load_Bitmap_File(&ant, "art/insect/ant_left.bmp");
	Create_BOB(&objarray[31].bob,440,555,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[31].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[32].name = "과학자 개미";
	objarray[32].bshowname = FALSE;
	objarray[32].objscreen = OBJSCREEN_GAME;
	objarray[32].bdialog = FALSE;
	objarray[32].dialogtype = SCIENTIST_DIALOG;
	objarray[32].bshowbob = FALSE;
	objarray[32].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[32].objrect, 255, 410, 255+32, 410+20);

	Load_Bitmap_File(&ant, "art/insect/ant_left.bmp");
	Create_BOB(&objarray[32].bob,255,410,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[32].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[33].name = "버섯재배 개미";
	objarray[33].bshowname = FALSE;
	objarray[33].objscreen = OBJSCREEN_GAME;
	objarray[33].bdialog = FALSE;
	objarray[33].dialogtype = MUSHROOM_ANT_DIALOG;
	objarray[33].bshowbob = FALSE;
	objarray[33].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[33].objrect, 760, 598, 760+32, 598+20);

	Load_Bitmap_File(&ant, "art/insect/ant_right.bmp");
	Create_BOB(&objarray[33].bob,760,598,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[33].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[34].name = "신도 개미";
	objarray[34].bshowname = FALSE;
	objarray[34].objscreen = OBJSCREEN_GAME;
	objarray[34].bdialog = FALSE;
	objarray[34].dialogtype = CHURCH_ANT_DIALOG;
	objarray[34].bshowbob = FALSE;
	objarray[34].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[34].objrect, 751, 497, 751+32, 497+20);

	Load_Bitmap_File(&ant, "art/insect/ant_left.bmp");
	Create_BOB(&objarray[34].bob,751,497,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[34].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[35].name = "장수풍뎅이";
	objarray[35].bshowname = FALSE;
	objarray[35].objscreen = OBJSCREEN_GAME;
	objarray[35].bdialog = FALSE;
	objarray[35].dialogtype = HIRED_1_DIALOG;
	objarray[35].bshowbob = FALSE;
	objarray[35].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[35].objrect, 584, 334, 584+44, 334+46);

	Load_Bitmap_File(&ant, "art/insect/장수풍뎅이.bmp");
	Create_BOB(&objarray[35].bob,584,334,44,46,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[35].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[36].name = "사슴벌레";
	objarray[36].bshowname = FALSE;
	objarray[36].objscreen = OBJSCREEN_GAME;
	objarray[36].bdialog = FALSE;
	objarray[36].dialogtype = HIRED_2_DIALOG;
	objarray[36].bshowbob = FALSE;
	objarray[36].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[36].objrect, 584, 344, 584+32, 344+32);

	Load_Bitmap_File(&ant, "art/insect/사슴벌레.bmp");
	Create_BOB(&objarray[36].bob,584,344,32,32,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[36].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[37].name = "병정 개미";
	objarray[37].bshowname = FALSE;
	objarray[37].objscreen = OBJSCREEN_GAME;
	objarray[37].bdialog = FALSE;
	objarray[37].dialogtype = TRAINING_ANT_DIALOG;
	objarray[37].bshowbob = FALSE;
	objarray[37].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[37].objrect, 388, 295, 388+32, 295+20);

	Load_Bitmap_File(&ant, "art/insect/ant2_right.bmp");
	Create_BOB(&objarray[37].bob,388,295,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[37].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[38].name = "일꾼 개미";
	objarray[38].bshowname = FALSE;
	objarray[38].objscreen = OBJSCREEN_GAME;
	objarray[38].bdialog = FALSE;
	objarray[38].dialogtype = ART_ANT_DIALOG;
	objarray[38].bshowbob = FALSE;
	objarray[38].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[38].objrect, 220, 284, 220+32, 284+20);

	Load_Bitmap_File(&ant, "art/insect/ant_right.bmp");
	Create_BOB(&objarray[38].bob,220,284,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[38].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[39].name = "일꾼 개미";
	objarray[39].bshowname = FALSE;
	objarray[39].objscreen = OBJSCREEN_GAME;
	objarray[39].bdialog = FALSE;
	objarray[39].dialogtype = ART_ANT_DIALOG;
	objarray[39].bshowbob = FALSE;
	objarray[39].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[39].objrect, 269, 274, 269+32, 274+20);

	Load_Bitmap_File(&ant, "art/insect/ant_left.bmp");
	Create_BOB(&objarray[39].bob,269,274,32,20,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[39].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[40].name = "진딧물";
	objarray[40].bshowname = FALSE;
	objarray[40].objscreen = OBJSCREEN_GAME;
	objarray[40].bdialog = FALSE;
	objarray[40].dialogtype = APHID_DIALOG;
	objarray[40].bshowbob = FALSE;
	objarray[40].temp[BOB_INT_MOVE] = BOB_NOT_MOVE;
	SetRect(&objarray[40].objrect, 753, 400, 753+36, 400+24);

	Load_Bitmap_File(&ant, "art/insect/aphid.bmp");
	Create_BOB(&objarray[40].bob,753,400,36,24,1,
			   BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME,DDSCAPS_SYSTEMMEMORY);    
	Load_Frame_BOB(&objarray[40].bob,&ant,0,0,0,BITMAP_EXTRACT_MODE_ABS);
	Unload_Bitmap_File(&ant);

	objarray[41].name = "상인 무당벌레";
	objarray[41].bshowname = FALSE;
	objarray[41].objscreen = OBJSCREEN_GAME;
	objarray[41].bdialog = FALSE;
	objarray[41].dialogtype = EVENT_SELLER_DIALOG;
	objarray[41].bshowbob = FALSE;
	objarray[41].temp[BOB_INT_MOVE] = BOB_MOVE_SELLER;

	Load_Bitmap_File(&ant, "art/insect/무당벌레.bmp");
	Create_BOB(&objarray[41].bob,865,170,46,19,2,
			   BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_SYSTEMMEMORY);    

	// load the ants in 
	for (int index=0; index < 2; index++)
		Load_Frame_BOB(&objarray[41].bob, &ant, index, index, 0, BITMAP_EXTRACT_MODE_CELL);

	Unload_Bitmap_File(&ant);

	int seller_anim_left[3]    = {0,1,-1};

	Load_Animation_BOB(&objarray[41].bob,0,2, seller_anim_left);

	Set_Anim_Speed_BOB(&objarray[41].bob,8);
	Set_Animation_BOB(&objarray[41].bob, SELLER_ANIM_LEFT);
	objarray[41].bob.curr_frame = 0;




	/*objarray[20].dialogtype = WORKER_DIALOG;
	objarray[20].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	objarray[20].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	objarray[20].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	objarray[20].bob.varsI[ANT_INT_RESTING] = 0;*/


	//objarray[20].name = "일꾼 개미";
	//objarray[20].bshowname = TRUE;
	//objarray[20].objscreen = OBJSCREEN_GAME;
	//objarray[20].bdialog = TRUE;
	//objarray[20].bshowbob = TRUE;
	//objarray[20].dialogtype = WORKER_DIALOG;
	//objarray[20].bob.varsI[ANT_INT_CUR_STATE] = ANT_GORIGHT;
	//objarray[20].bob.varsI[ANT_INT_CUR_WAYPOINT] = 0;
	//objarray[20].bob.varsI[ANT_INT_OLD_WAYPOINT] = 1;
	//objarray[20].bob.varsI[ANT_INT_RESTING] = 0;

	//// clone the ants
	////for (index=1; index < NUM_ANTS; index++)
	////	Clone_BOB(&ants[0], &ants[index]);
	//Clone_BOB(&objarray[19].bob, &objarray[20].bob);



	return 1;
}

int CObject::Obj_Shutdown()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if(objarray[i].bob.state == BOB_STATE_ALIVE)
			Destroy_BOB(&objarray[i].bob);
	}

	return 1;
}

int CObject::MoveObjBob()
{
	if(GAME_STATE != GAME_RUN)
		return 0;

	for(int i=0; i<MAX_OBJECT; i++)
	{		
		// object가 보이고
		if(objarray[i].bshowbob == TRUE)
		{
			// 개미굴에서 돌아다니는 개미라면
			if(objarray[i].temp[BOB_INT_MOVE] == BOB_MOVE_NORMAL)
			{
				int temp = objarray[i].bob.varsI[ANT_INT_CUR_STATE];
				// 개미굴을 따라 입력된 point로 개미가 다가갔는지 확인
				if(CheckDistance(path[objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]].x,
								path[objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]].y,
								objarray[i].bob.x,
								objarray[i].bob.y))
				{
					objarray[i].bob.varsI[ANT_INT_OLD_WAYPOINT] = objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT];
					// 개미가 왼쪽으로 이동중이었으면
					if(objarray[i].bob.varsI[ANT_INT_CUR_STATE] == ANT_GOLEFT)
					{
						// 왼쪽 80%, 오른쪽 5%, 휴식 15%로 다음 행동을 결정
						temp = Select_State_Rand(ANT_GOLEFT, 80,
										  ANT_GORIGHT, 5,
										  ANT_RESTING, 15,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0);
						if(temp == ANT_GOLEFT)
						{
							if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == 0)
							{
								temp = ANT_GORIGHT;

								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
							}
							else
							{
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
							}
						}
						else if(temp == ANT_GORIGHT)
						{
							if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == NUM_WAYPOINTS-1)
							{
								temp = ANT_GOLEFT;
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
							}
							else
							{
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
							}
						}
						else if(temp == ANT_RESTING)
						{	
							objarray[i].bob.varsI[ANT_INT_RESTING] = 60 + rand()%50;

						}


					}
					// 개미가 오른쪽으로 이동중이었으면
					if(objarray[i].bob.varsI[ANT_INT_CUR_STATE] == ANT_GORIGHT)
					{
						// 왼쪽 5%, 오른쪽 80%, 휴식 15%로 다음 행동을 결정
						temp = Select_State_Rand(ANT_GOLEFT, 5,
										  ANT_GORIGHT, 80,
										  ANT_RESTING, 15,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0);
						if(temp == ANT_GOLEFT)
						{
							if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == 0)
							{
								temp = ANT_GORIGHT;
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
							}
							else
							{
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
							}
						}
						else if(temp == ANT_GORIGHT)
						{
							if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == NUM_WAYPOINTS-1)
							{
								temp = ANT_GOLEFT;
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
							}
							else
							{
								objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
							}
						}
						else if(temp == ANT_RESTING)
						{
							objarray[i].bob.varsI[ANT_INT_RESTING] = 60 + rand()%50;
						}
					}
					// 개미가 휴식중이었으면
					if(objarray[i].bob.varsI[ANT_INT_CUR_STATE] == ANT_RESTING)
					{
						// fps마다 휴식 변수의 값을 1씩 뺀다
						objarray[i].bob.varsI[ANT_INT_RESTING]--;
						if(objarray[i].bob.anim_state == ANT_ANIM_DOWN)
							Set_Animation_BOB(&objarray[i].bob, ANT_ANIM_DOWN);
						if(objarray[i].bob.anim_state == ANT_ANIM_UP)
							Set_Animation_BOB(&objarray[i].bob, ANT_ANIM_UP);
						if(objarray[i].bob.anim_state == ANT_ANIM_RIGHT)
							Set_Animation_BOB(&objarray[i].bob, ANT_ANIM_RIGHT);
						if(objarray[i].bob.anim_state == ANT_ANIM_LEFT)
							Set_Animation_BOB(&objarray[i].bob, ANT_ANIM_LEFT);
						// 휴식이 끝나면
						if(objarray[i].bob.varsI[ANT_INT_RESTING] <= 0)
						{
							// 왼쪽 50%, 오른쪽 50%로 다음 행동을 결정
							temp = Select_State_Rand(ANT_GOLEFT, 50,
										  ANT_GORIGHT, 50,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0,
										  ANT_RESTING, 0);
							if(temp == ANT_GOLEFT)
							{
								if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == 0)
								{
									temp = ANT_GORIGHT;
									objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
								}
								else
								{
									objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
								}
							}
							else if(temp == ANT_GORIGHT)
							{
								if(objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT] == NUM_WAYPOINTS-1)
								{
									temp = ANT_GOLEFT;
									objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]--;
								}
								else
								{
									objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]++;
								}
							}
							
						}

					}

					objarray[i].bob.varsI[ANT_INT_CUR_STATE] = temp;
					SetAniDir(&objarray[i].bob, objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT], objarray[i].bob.varsI[ANT_INT_OLD_WAYPOINT]);
				}

				
				// 다음 목적지까지 vector를 구한다.
				int wx = (path[objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]].x - objarray[i].bob.x);
				int wy = (path[objarray[i].bob.varsI[ANT_INT_CUR_WAYPOINT]].y - objarray[i].bob.y);
				
				//// for normalizing wx, wy
				int length = Fast_Distance_2D(wx,wy);

				if(length == 0)
					length = 1;

				// normal vector 구하기(정확히는 normal vector의 크기 2배)
				wx*=2;
				wy*=2;
				wx/=length;
				wy/=length;

				// 휴식이 아니면 vector만큼 이동
				if(objarray[1].bob.varsI[ANT_INT_CUR_STATE] != ANT_RESTING)
				{
					objarray[i].bob.x += wx;
					objarray[i].bob.y += wy;
				}

				SetRect(&objarray[i].objrect, 
					objarray[i].bob.x, 
					objarray[i].bob.y,
					objarray[i].bob.x + objarray[i].bob.width,
					objarray[i].bob.y + objarray[i].bob.height);
			}
			// 상인일 경우 이동 경로
			if(objarray[i].temp[BOB_INT_MOVE] == BOB_MOVE_SELLER)
			{
				objarray[i].bob.x -= 1;

				if(objarray[i].bob.x == 837)
					objarray[i].bob.y += 2;
				if(objarray[i].bob.x == 784)
					objarray[i].bob.y -= 2;
				if(objarray[i].bob.x == 765)
					objarray[i].bob.y -= 3;
				if(objarray[i].bob.x == 603)
					objarray[i].bob.y -= 2;
				if(objarray[i].bob.x == 498)
					objarray[i].bob.y += 3;
				if(objarray[i].bob.x == 400)
					objarray[i].bob.y += 1;
				if(objarray[i].bob.x == 359)
					objarray[i].bob.y += 2;
				if(objarray[i].bob.x == 315)
					objarray[i].bob.y += 2;
				if(objarray[i].bob.x == 291)
					objarray[i].bob.y += 2;
				if(objarray[i].bob.x == 267)
					objarray[i].bob.y += 2;
				if(objarray[i].bob.x == 220)
					objarray[i].bob.y -= 1;
				if(objarray[i].bob.x == 214)
					objarray[i].bob.y -= 2;

				if(objarray[i].bob.x <= 87)
				{
					objarray[i].bob.x = 865;
					objarray[i].bob.y = 170;
					objarray[i].bshowbob = FALSE;
					objarray[i].bdialog = FALSE;
					objarray[i].bshowname = FALSE;
				}
	
				SetRect(&objarray[i].objrect, 
					objarray[i].bob.x, 
					objarray[i].bob.y,
					objarray[i].bob.x + objarray[i].bob.width,
					objarray[i].bob.y + objarray[i].bob.height);
			}
		}
	}

	return 1;
}

int CObject::CheckDistance(int x1, int y1, int x2, int y2)
{
	int temp_x = x1 - x2;
	int temp_y = y1 - y2;
	temp_x = abs(temp_x);
	temp_y = abs(temp_y);

	if((temp_x <= 6) && (temp_y <= 6))
		return 1;
	

	return 0;
}

int CObject::SetAniDir(BOB *bob, int newway, int oldway)
{
	if(oldway == 0)
		if(newway == 1)
			bob->anim_state = ANT_ANIM_DOWN;

	if(oldway == 1)
	{
		if(newway == 0)
			bob->anim_state = ANT_ANIM_UP;
		if(newway == 2)
			bob->anim_state = ANT_ANIM_DOWN;
	}
	if(oldway == 2)
	{
		if(newway == 1)
			bob->anim_state = ANT_ANIM_UP;
		if(newway == 3)
			bob->anim_state = ANT_ANIM_DOWN;
	}
	if(oldway == 3)
	{
		if(newway == 2)
			bob->anim_state = ANT_ANIM_UP;
		if(newway == 4)
			bob->anim_state = ANT_ANIM_DOWN;
	}
	if(oldway == 4)
	{
		if(newway == 3)
			bob->anim_state = ANT_ANIM_UP;
		if(newway == 5)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 5)
	{
		if(newway == 4)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 6)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 6)
	{
		if(newway == 5)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 7)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 7)
	{
		if(newway == 6)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 8)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 8)
	{
		if(newway == 7)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 9)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 9)
	{
		if(newway == 8)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 10)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 10)
	{
		if(newway == 9)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 11)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 11)
	{
		if(newway == 10)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 12)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 12)
	{
		if(newway == 11)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 13)
			bob->anim_state = ANT_ANIM_RIGHT;
	}
	if(oldway == 13)
	{
		if(newway == 12)
			bob->anim_state = ANT_ANIM_LEFT;
		if(newway == 14)
			bob->anim_state = ANT_ANIM_UP;
	}
	if(oldway == 14)
	{
		if(newway == 13)
			bob->anim_state = ANT_ANIM_DOWN;
		if(newway == 15)
			bob->anim_state = ANT_ANIM_UP;
	}
	if(oldway == 15)
	{
		if(newway == 14)
			bob->anim_state = ANT_ANIM_DOWN;
	}

	Set_Animation_BOB(bob, bob->anim_state);
	Animate_BOB(bob);

	return 1;
}
int CObject::DrawObjBob()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if(objarray[i].bshowbob == TRUE)
		{
			if((objarray[i].objscreen == OBJSCREEN_GAME) && (SCREEN_STATE == SCREEN_GAME))
			{
				int temp_x = objarray[i].bob.x;
				int temp_y = objarray[i].bob.y;
				objarray[i].bob.x -= off_x;
				objarray[i].bob.y -= off_y;
				Draw_BOB(&objarray[i].bob, lpddsback);
				objarray[i].bob.x = temp_x;
				objarray[i].bob.y = temp_y;

				if(GAME_STATE == GAME_RUN)
					Animate_BOB(&objarray[i].bob);
			}
			if((objarray[i].objscreen == OBJSCREEN_MAP) && (SCREEN_STATE == SCREEN_MAP))
			{
				Draw_BOB(&objarray[i].bob, lpddsback);
			}
		}
	}
	
	return 1;
}
int CObject::PrintObjName()
{
	for(int i=MAX_OBJECT-1; i>=0; i--)
	{
		if(objarray[i].bshowname == TRUE)
		{
			if((objarray[i].objscreen == OBJSCREEN_GAME) && (SCREEN_STATE == SCREEN_GAME))
			{
				if(CheckRect(&objarray[i].objrect, mouse_off_x, mouse_off_y))
				{
					DDraw_Text(objarray[i].name,
							OBJ_NAME_X,
							OBJ_NAME_Y,
							17,
							lpddsback,
							RGB(0,0,255),
							TA_CENTER,
							RGB(255,255,255),
							OPAQUE);
					return 1;
				}
			}
			if((objarray[i].objscreen == OBJSCREEN_MAP) && (SCREEN_STATE == SCREEN_MAP))
			{	
				if(CheckRect(&objarray[i].objrect, mouse_x, mouse_y))
				{
					DDraw_Text(objarray[i].name,
							OBJ_NAME_X,
							OBJ_NAME_Y,
							17,
							lpddsback,
							RGB(0,0,255),
							TA_CENTER,
							RGB(255,255,255),
							OPAQUE);
					return 1;
				}
			}
		}
	}

	return 1;
}
int CObject::ShowDialog()
{
	for(int i=MAX_OBJECT-1; i>=0; i--)
	{
		if(objarray[i].bdialog == TRUE)
		{
			if((objarray[i].objscreen == OBJSCREEN_GAME) && (SCREEN_STATE == SCREEN_GAME))
			{
				if(CheckRect(&objarray[i].objrect, mouse_off_x, mouse_off_y, TRUE))
				{
					// 상인에서 강제 정지를 했으면 일단 해제한다.
					if(CTime::GetPauseCheck(PAUSE_SELLER) == TRUE)
						CTime::ReleasePause(PAUSE_SELLER);

					if(objarray[i].dialogtype == STRANGE_STONE_DIALOG)
						objdialog_.ShowObjDialog_StrangeStone();
					if(objarray[i].dialogtype == BUILDING_WAREHOUSE_DIALOG)
						objdialog_.ShowObjDialog_WareHouse();
					if(objarray[i].dialogtype == BUILDING_QUEEN_DIALOG)
						objdialog_.ShowObjDialog_BuildingQueen();
					if(objarray[i].dialogtype == BUILDING_EGG_DIALOG)
						objdialog_.ShowObjDialog_Egg();
					if(objarray[i].dialogtype == BUILDING_LIBRARY_DIALOG)
						objdialog_.ShowObjDialog_Library();
					if(objarray[i].dialogtype == BUILDING_DEPOSITORY_DIALOG)
						objdialog_.ShowObjDialog_Depository();
					if(objarray[i].dialogtype == BUILDING_LAB_DIALOG)
						objdialog_.ShowObjDialog_Lab();
					if(objarray[i].dialogtype == BUILDING_TRAINING_DIALOG)
						objdialog_.ShowObjDialog_Training();
					if(objarray[i].dialogtype == BUILDING_MUSHROOM_DIALOG)
						objdialog_.ShowObjDialog_Mushroom();
					if(objarray[i].dialogtype == BUILDING_HIRED_1_DIALOG)
						objdialog_.ShowObjDialog_BuildingHired_1();
					if(objarray[i].dialogtype == BUILDING_HIRED_2_DIALOG)
						objdialog_.ShowObjDialog_BuildingHired_2();
					if(objarray[i].dialogtype == BUILDING_CHURCH_DIALOG)
						objdialog_.ShowObjDialog_Church();
					if(objarray[i].dialogtype == BUILDING_ART_DIALOG)
						objdialog_.ShowObjDialog_Art();

					if(objarray[i].dialogtype == WORKER_DIALOG)
						objdialog_.ShowObjDialog_Worker();
					if(objarray[i].dialogtype == SOLDIER_DIALOG)
						objdialog_.ShowObjDialog_Soldier();
					if(objarray[i].dialogtype == QUEEN_DIALOG)
						objdialog_.ShowObjDialog_Queen();
					if(objarray[i].dialogtype == ADVISER_DIALOG)
						objdialog_.ShowObjDialog_Adviser();
					if(objarray[i].dialogtype == NANNY_DIALOG)
						objdialog_.ShowObjDialog_Nanny();
					if(objarray[i].dialogtype == SCIENTIST_DIALOG)
						objdialog_.ShowObjDialog_Scientist();
					if(objarray[i].dialogtype == MUSHROOM_ANT_DIALOG)
						objdialog_.ShowObjDialog_Mushroom_Ant();
					if(objarray[i].dialogtype == CHURCH_ANT_DIALOG)
						objdialog_.ShowObjDialog_Church_Ant();
					if(objarray[i].dialogtype == HIRED_1_DIALOG)
						objdialog_.ShowObjDialog_Hired_1();
					if(objarray[i].dialogtype == HIRED_2_DIALOG)
						objdialog_.ShowObjDialog_Hired_2();
					if(objarray[i].dialogtype == TRAINING_ANT_DIALOG)
						objdialog_.ShowObjDialog_Training_Ant();
					if(objarray[i].dialogtype == ART_ANT_DIALOG)
						objdialog_.ShowObjDialog_Art_Ant();
					if(objarray[i].dialogtype == APHID_DIALOG)
						objdialog_.ShowObjDialog_Aphid();

					if(objarray[i].dialogtype == EVENT_SELLER_DIALOG)
						objdialog_.ShowObjDialog_Seller();

					return 1;
				}
			}
		}
	}

	return 0;
}
int CObject::EnableBuildingObj(int OBJARRAY_INDEX)
{
	objarray[OBJARRAY_INDEX].bdialog = TRUE;
	objarray[OBJARRAY_INDEX].bshowname = TRUE;

	return 1;
}
int CObject::ChangeObjTemp(int OBJARRAY_INDEX, int INDEX, int value)
{
	objarray[OBJARRAY_INDEX].temp[INDEX] = value;

	return 1;
}
int CObject::ChangeObjBobFrame(int OBJARRAY_INDEX, int frame)
{
	objarray[OBJARRAY_INDEX].bob.curr_frame = frame;

	return 1;
}
int CObject::SetObName(int OBJARRAY_INDEX, char *name)
{
	objarray[OBJARRAY_INDEX].name = name;

	return 1;
}
int CObject::EnableMapObj(int OBJARRAY_INDEX)
{
	objarray[OBJARRAY_INDEX].bshowbob = TRUE;
	objarray[OBJARRAY_INDEX].bshowname = TRUE;

	return 1;
}
int CObject::ShowObjBob(int OBJARRAY_INDEX)
{
	objarray[OBJARRAY_INDEX].bshowbob = TRUE;
	objarray[OBJARRAY_INDEX].bshowname = TRUE;
	objarray[OBJARRAY_INDEX].bdialog = TRUE;

	return 1;
}
int CObject::ShowWanderingAnts()
{
	objarray[OBJARRAY_WORKER_ANT_1].bshowbob = FALSE;
	objarray[OBJARRAY_WORKER_ANT_1].bdialog = FALSE;
	objarray[OBJARRAY_WORKER_ANT_1].bshowname = FALSE;
	objarray[OBJARRAY_WORKER_ANT_2].bshowbob = FALSE;
	objarray[OBJARRAY_WORKER_ANT_2].bdialog = FALSE;
	objarray[OBJARRAY_WORKER_ANT_2].bshowname = FALSE;
	objarray[OBJARRAY_WORKER_ANT_3].bshowbob = FALSE;
	objarray[OBJARRAY_WORKER_ANT_3].bdialog = FALSE;
	objarray[OBJARRAY_WORKER_ANT_3].bshowname = FALSE;
	objarray[OBJARRAY_WORKER_ANT_4].bshowbob = FALSE;
	objarray[OBJARRAY_WORKER_ANT_4].bdialog = FALSE;
	objarray[OBJARRAY_WORKER_ANT_4].bshowname = FALSE;
	objarray[OBJARRAY_WORKER_ANT_5].bshowbob = FALSE;
	objarray[OBJARRAY_WORKER_ANT_5].bdialog = FALSE;
	objarray[OBJARRAY_WORKER_ANT_5].bshowname = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_1].bshowbob = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_1].bdialog = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_1].bshowname = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_2].bshowbob = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_2].bdialog = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_2].bshowname = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_3].bshowbob = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_3].bdialog = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_3].bshowname = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_4].bshowbob = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_4].bdialog = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_4].bshowname = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_5].bshowbob = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_5].bdialog = FALSE;
	objarray[OBJARRAY_SOLDIER_ANT_5].bshowname = FALSE;

	if(CPlayer::num_worker_total >= 50)
	{
		objarray[OBJARRAY_WORKER_ANT_1].bshowbob = TRUE;
		objarray[OBJARRAY_WORKER_ANT_1].bdialog = TRUE;
		objarray[OBJARRAY_WORKER_ANT_1].bshowname = TRUE;
	}
	if(CPlayer::num_worker_total >= 120)
	{
		objarray[OBJARRAY_WORKER_ANT_2].bshowbob = TRUE;
		objarray[OBJARRAY_WORKER_ANT_2].bdialog = TRUE;
		objarray[OBJARRAY_WORKER_ANT_2].bshowname = TRUE;
	}
	if(CPlayer::num_worker_total >= 190)
	{
		objarray[OBJARRAY_WORKER_ANT_3].bshowbob = TRUE;
		objarray[OBJARRAY_WORKER_ANT_3].bdialog = TRUE;
		objarray[OBJARRAY_WORKER_ANT_3].bshowname = TRUE;
	}
	if(CPlayer::num_worker_total >= 260)
	{
		objarray[OBJARRAY_WORKER_ANT_4].bshowbob = TRUE;
		objarray[OBJARRAY_WORKER_ANT_4].bdialog = TRUE;
		objarray[OBJARRAY_WORKER_ANT_4].bshowname = TRUE;
	}
	if(CPlayer::num_worker_total >= 320)
	{
		objarray[OBJARRAY_WORKER_ANT_5].bshowbob = TRUE;
		objarray[OBJARRAY_WORKER_ANT_5].bdialog = TRUE;
		objarray[OBJARRAY_WORKER_ANT_5].bshowname = TRUE;
	}

	if(CPlayer::num_soldier_total >= 50)
	{
		objarray[OBJARRAY_SOLDIER_ANT_1].bshowbob = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_1].bdialog = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_1].bshowname = TRUE;
	}
	if(CPlayer::num_soldier_total >= 120)
	{
		objarray[OBJARRAY_SOLDIER_ANT_2].bshowbob = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_2].bdialog = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_2].bshowname = TRUE;
	}
	if(CPlayer::num_soldier_total >= 190)
	{
		objarray[OBJARRAY_SOLDIER_ANT_3].bshowbob = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_3].bdialog = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_3].bshowname = TRUE;
	}
	if(CPlayer::num_soldier_total >= 260)
	{
		objarray[OBJARRAY_SOLDIER_ANT_4].bshowbob = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_4].bdialog = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_4].bshowname = TRUE;
	}
	if(CPlayer::num_soldier_total >= 320)
	{
		objarray[OBJARRAY_SOLDIER_ANT_5].bshowbob = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_5].bdialog = TRUE;
		objarray[OBJARRAY_SOLDIER_ANT_5].bshowname = TRUE;
	}

	return 1;
}
int CObject::Save()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		WriteFile(hfile, &objarray[i].bshowname, sizeof(objarray[i].bshowname), &dwWritten, NULL);
		WriteFile(hfile, &objarray[i].objrect, sizeof(objarray[i].objrect), &dwWritten, NULL);
		WriteFile(hfile, &objarray[i].bdialog, sizeof(objarray[i].bdialog), &dwWritten, NULL);
		WriteFile(hfile, &objarray[i].bob, sizeof(int)*18+sizeof(float), &dwWritten, NULL);
		WriteFile(hfile, &objarray[i].bshowbob, sizeof(objarray[i].bshowbob), &dwWritten, NULL);
		WriteFile(hfile, &objarray[i].dialogtype, sizeof(objarray[i].dialogtype), &dwWritten, NULL);
		for(int j=0; j<5; j++)
			WriteFile(hfile, &objarray[i].temp[j], sizeof(objarray[i].temp[j]), &dwWritten, NULL);
	}

	return 1;
}
int CObject::Load()
{
	//for(int i=0; i<MAX_OBJECT; i++)
	//	ReadFile(hfile, &objarray[i], sizeof(objarray[i]), &dwWritten, NULL);
	for(int i=0; i<MAX_OBJECT; i++)
	{
		ReadFile(hfile, &objarray[i].bshowname, sizeof(objarray[i].bshowname), &dwWritten, NULL);
		ReadFile(hfile, &objarray[i].objrect, sizeof(objarray[i].objrect), &dwWritten, NULL);
		ReadFile(hfile, &objarray[i].bdialog, sizeof(objarray[i].bdialog), &dwWritten, NULL);
		ReadFile(hfile, &objarray[i].bob, sizeof(int)*18+sizeof(float), &dwWritten, NULL);
		ReadFile(hfile, &objarray[i].bshowbob, sizeof(objarray[i].bshowbob), &dwWritten, NULL);
		ReadFile(hfile, &objarray[i].dialogtype, sizeof(objarray[i].dialogtype), &dwWritten, NULL);
		for(int j=0; j<5; j++)
			ReadFile(hfile, &objarray[i].temp[j], sizeof(objarray[i].temp[j]), &dwWritten, NULL);
	}

	return 1;
}
