癤?
#include "CBattle.h"
#include "CDomestic.h"
#include "CDiplomatic.h"
#include "CTime.h"
#include "CPlayer.h"
#include "CSpecies.h"
#include "CDebug.h"
#include "CBuilding.h"
#include "CObject.h"
#include "CItem.h"
#include "CObjDialog.h"
#include "CBuilding.h"
#include "resource.h"

extern CDebug debug_;
extern CTime time_;
extern CBuilding building_;
extern CDiplomatic diplomatic_;
extern CObjDialog objdialog_;
extern CBuilding building_;
extern CObject object_;
extern CDomestic domestic_;
extern CItem item_;

extern int ReturnScreenGamma(BOOL blong, int delay = 70);
extern int ChangeScreenGamma(int effect, BOOL blong, int delay = 70);

HWND CBattle::hWndDlg_battle = NULL;
HWND CBattle::hWndDlg_battle_normal = NULL;
HWND CBattle::hWndDlg_battle_result_att = NULL;
HWND CBattle::hWndDlg_battle_result_def = NULL;

int CBattle::Battle_Init(int flag)
{
	battle.num_food_get = 0;
	battle.num_timber_get = 0;
	battle.num_mineral_get = 0;

	battle.num_food_lost = 0;
	battle.num_timber_lost = 0;
	battle.num_mineral_lost = 0;

	battle.spe_init_num_att = 0;
	battle.spe_cur_num_att = 0;
	battle.spe_init_num_def = 0;
	battle.spe_cur_num_def = 0;
	
	battle.power_hired_att = 0;
	battle.power_hired_def = 0;

	battle.player_cur_num_soldier_att = 0;
	battle.player_cur_num_hired_att = 0;
	battle.player_cur_num_soldier_def = 0;
	battle.player_cur_num_hired_def = 0;

	battle.player_init_num_soldier_att = 0;
	battle.player_init_num_hired_att = 0;
	battle.player_init_num_soldier_def = 0;
	battle.player_init_num_hired_def = 0;

	battle.player_init_num_att = 0;
	battle.player_cur_num_att = 0;
	battle.player_init_num_def = 0;
	battle.player_cur_num_def = 0;

	battle.player_attack_time = 0;
	battle.player_defence_time = 0;

	battle.player_join = FALSE;


	if(flag == NULL)
	{
		BITMAP_FILE dirt;
		
		ZeroMemory(&dirt, sizeof(BITMAP_FILE));
		Load_Bitmap_File(&dirt, "art/etc/?꾪닾?곌린.bmp");
		Create_BOB(&battle_dirt,
			object_.objarray[OBJARRAY_MAP_PLAYER].objrect.left,
			object_.objarray[OBJARRAY_MAP_PLAYER].objrect.top
			,30,23,3,
			BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_SYSTEMMEMORY);    
		// load the ants in 
		for (int index=0; index < 3; index++)
			Load_Frame_BOB(&battle_dirt, &dirt, index, index, 0, BITMAP_EXTRACT_MODE_CELL);

		Unload_Bitmap_File(&dirt);

		int battle_dirt_anim[4]    = {0,1,2,-1};

		Load_Animation_BOB(&battle_dirt,0,3, battle_dirt_anim);

		Set_Anim_Speed_BOB(&battle_dirt,7);
		Set_Animation_BOB(&battle_dirt, BATTLE_DIRT_ANIM);
		battle_dirt.curr_frame = 0;
		
		Clone_BOB(&battle_dirt, &battle_dirt2);
	}

	return 1;
}
int CBattle::PrintBattleInfo()
{
	int temp_index;

	temp_index = CSpecies::spe_attacked_index;

	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(BATTLE_OUT_STATE == BATTLE_OUT_BREAK)
		{
			for(int i=0; i<MAX_SPECIES; i++)
			{
				if(CheckRect(&CSpecies::speciesarray[i].sperect, mouse_x, mouse_y))
				{
					if(CSpecies::speciesarray[i].Disalbed == FALSE)
					{
						if(CSpecies::speciesarray[i].state == SPECIES_STATE_BATTLE)
						{
							sprintf(buffer,"媛쒖껜??: (?꾧뎔)%d vs (?곴뎔)%d", 
								battle.player_cur_num_att/NUM_CIPHER,
								battle.spe_cur_num_def/NUM_CIPHER);
							DDraw_Text(buffer, 
									PRINT_BATTLE_X,
									PRINT_BATTLE_Y,
									NULL,
									lpddsback,
									RGB(0,0,0),
									TA_LEFT,
									NULL,
									TRANSPARENT,
									"System");
							if(CPlayer::strategy_att == 0)
								sprintf(buffer,"怨듦꺽 ???:   ?먯썝?쏀깉");
							if(CPlayer::strategy_att == 1)
								sprintf(buffer,"怨듦꺽 ???:     ?쇰컲");
							if(CPlayer::strategy_att == 2)
								sprintf(buffer,"怨듦꺽 ???:     ?뺣났");
							DDraw_Text(buffer, 
									PRINT_BATTLE_STRATT_X,
									PRINT_BATTLE_STRATT_Y,
									NULL,
									lpddsback,
									RGB(0,0,0),
									TA_LEFT,
									NULL,
									TRANSPARENT,
									"System");
							if(CSpecies::speciesarray[temp_index].strategy_def == 0)
								sprintf(buffer,"諛⑹뼱 ???:       ?띿꽦");
							if(CSpecies::speciesarray[temp_index].strategy_def == 1)
								sprintf(buffer,"諛⑹뼱 ???:	      ?붽꺽");
							DDraw_Text(buffer, 
									PRINT_BATTLE_STRDEF_X,
									PRINT_BATTLE_STRDEF_Y,
									NULL,
									lpddsback,
									RGB(0,0,0),
									TA_LEFT,
									NULL,
									TRANSPARENT,
									"System");
						}
					}
				}
			}
		}
	}

	temp_index = CSpecies::spe_attacking_index;

	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		{
			if(CheckRect(&object_.objarray[OBJARRAY_MAP_PLAYER].objrect, mouse_x, mouse_y))
			{
				sprintf(buffer,"媛쒖껜??: (?꾧뎔)%d vs (?곴뎔)%d", 
					battle.player_cur_num_def/NUM_CIPHER,
					battle.spe_cur_num_att/NUM_CIPHER);
				DDraw_Text(buffer, 
						PRINT_BATTLE_X,
						PRINT_BATTLE_Y,
						NULL,
						lpddsback,
						RGB(0,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT,
						"System");
				if(CSpecies::speciesarray[temp_index].strategy_att == 0)
					sprintf(buffer,"怨듦꺽 ???:   ?먯썝?쏀깉");
				if(CSpecies::speciesarray[temp_index].strategy_att == 1)
					sprintf(buffer,"怨듦꺽 ???:       ?쇰컲");
				if(CSpecies::speciesarray[temp_index].strategy_att == 2)
					sprintf(buffer,"怨듦꺽 ???:       ?뺣났");
				DDraw_Text(buffer, 
						PRINT_BATTLE_STRATT_X,
						PRINT_BATTLE_STRATT_Y,
						NULL,
						lpddsback,
						RGB(0,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT,
						"System");
				if(CPlayer::strategy_def == 0)
					sprintf(buffer,"諛⑹뼱 ???:       ?띿꽦");
				if(CPlayer::strategy_def == 1)
					sprintf(buffer,"諛⑹뼱 ???:       ?붽꺽");
				DDraw_Text(buffer, 
						PRINT_BATTLE_STRDEF_X,
						PRINT_BATTLE_STRDEF_Y,
						NULL,
						lpddsback,
						RGB(0,0,0),
						TA_LEFT,
						NULL,
						TRANSPARENT,
						"System");
			}
		}
	}

	return 1;
}
int CBattle::PlayerDecideStr(int selectedindex)
{
	CTime::SetPause();

	if(hWndDlg_battle)
		EndDialog(hWndDlg_battle, TRUE );
	hWndDlg_battle = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_ATTACK),
		main_window_handle,  (DLGPROC)BattleAttDlgProc );
	SendMessage(hWndDlg_battle, WM_GETINFO, 0, (LPARAM)selectedindex);
	SendMessage(hWndDlg_battle, WM_GETPOINT, 0, (LPARAM)this);
	if(selectedindex == SPEARRAY_SNAIL)
		sprintf(buffer, "李몃え 媛쒕?\n\n\" '誘쇰떖?쎌씠'醫낆쓣 怨듦꺽?섎젮 ?⑸땲?? ?대뼡 怨듦꺽 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
	if(selectedindex == SPEARRAY_GRASSHOPPER)
		sprintf(buffer, "李몃え 媛쒕?\n\n\" '硫붾슌湲?醫낆쓣 怨듦꺽?섎젮 ?⑸땲?? ?대뼡 怨듦꺽 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
	if(selectedindex == SPEARRAY_SHORT_ANT)
		sprintf(buffer, "李몃え 媛쒕?\n\n\" '?쒖웳?닿컻誘?醫낆쓣 怨듦꺽?섎젮 ?⑸땲?? ?대뼡 怨듦꺽 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
	if(selectedindex == SPEARRAY_BEE)
		sprintf(buffer, "李몃え 媛쒕?\n\n\" '轅踰?醫낆쓣 怨듦꺽?섎젮 ?⑸땲?? ?대뼡 怨듦꺽 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
	if(selectedindex == SPEARRAY_RED_ANT)
		sprintf(buffer, "李몃え 媛쒕?\n\n\" '遺덇컻誘?醫낆쓣 怨듦꺽?섎젮 ?⑸땲?? ?대뼡 怨듦꺽 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
	SetDlgItemTextA(hWndDlg_battle, IDC_STATIC_BATTLE, buffer);
	ShowWindow(hWndDlg_battle, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CBattle::SpeDecideAttack()
{
	// 爾낇꽣 1?먯꽌 寃⑥슱??1/2??吏?섏빞 怨듦꺽?댁삩??
	if((time_.GetYear()==0) && (time_.GetMonth3() <= 50))
		return 0;

	int temp_attatck;

	int temp_relation;
	int temp_strength;

	int temp_random;

	debug_.GetValue("attacked_time, attacking_time",
				&CPlayer::remain_reach_time,
				&CSpecies::speciesarray[CSpecies::spe_attacking_index].remain_reach_time,
				lpddsback,
				15,
				NULL);

	// ?대뼡 醫낆”???뚮젅?댁뼱瑜?怨듦꺽?섏? ?딆븯?ㅻ㈃
	if(CSpecies::spe_attacking_index == -1)
	{
		for(int i=0; i<MAX_SPECIES; i++)
		{
			temp_attatck = 0;		// 怨듦꺽??寃곗젙?섍린 ?꾪븳 蹂??

			// 吏湲??꾩웳以묒씠硫??뚮젅?댁뼱瑜?怨듦꺽?섏? ?딅뒗??
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_BATTLE)
				continue;

			// ?뚮젅?댁뼱?먭쾶 醫낆냽?섏뼱 ?덈떎硫?怨듦꺽?섏? ?딅뒗??
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_OCCUPIED)
				continue;

			// 愿怨꾩? ?몃젰李⑥씠???곕Ⅸ
			if(CSpecies::speciesarray[i].Disalbed == FALSE)
			{
				// ?숇㏏?대㈃ 怨듦꺽 ?덊븿
				if(CSpecies::speciesarray[i].relation > 40000)
					continue;

				// 愿怨꾩뿉 ?곕Ⅸ
				temp_relation = CSpecies::speciesarray[i].relation;
				temp_attatck -= (temp_relation/100 - 250)/2;

				// ?몃젰 李⑥씠???곕Ⅸ
				temp_strength = CPlayer::strength - CSpecies::speciesarray[i].strength;
				temp_attatck -= temp_strength/500;
			}
			else
				continue;

			// 怨꾩젅???곕Ⅸ
			if(time_.GetSeason() == SPRING)
				temp_attatck += 70;
			if(time_.GetSeason() == SUMMER)
				temp_attatck += 90;
			if(time_.GetSeason() == FALL)
				temp_attatck += 70;
			if(time_.GetSeason() == WINTER)
				temp_attatck += 30;

			// ?뚮젅?댁뼱??二쇰몦援곗뿉 ?곕Ⅸ
			temp_attatck -= CPlayer::num_soldier_defence/10;
			temp_attatck -= CPlayer::num_hired_defence/3;

			// ?뚮젅?댁뼱??怨듦꺽???곕Ⅸ
			if(CSpecies::spe_attacked_index == i)
			{
				temp_attatck -= (CPlayer::num_soldier_attack/3
							 + CPlayer::num_hired_attack);
			}
			
			// ?꾩껜??怨듦꺽 ?깊뼢???곕Ⅸ
			temp_attatck *= CSpecies::speciesarray[i].attempt_to_attck;

			// 寃곗젙
			if(temp_attatck > 0)
			{
				temp_random = (rand()%RAND_MAX)*10;
				// temp_attack??temp_random蹂대떎 而ㅼ빞 ?ㅼ젣濡?怨듦꺽 寃곗젙
				if(temp_random <= temp_attatck)
				{
					temp_random = rand()%10;
					if(temp_random <= 4)
						CSpecies::speciesarray[i].strategy_att = 0;
					else if(temp_random <= 7)
						CSpecies::speciesarray[i].strategy_att = 1;
					else if(temp_random <= 9)
						CSpecies::speciesarray[i].strategy_att = 2;

					CSpecies::spe_attacking_index = i;
					if(i == SPEARRAY_SNAIL)
						CSpecies::speciesarray[i].remain_reach_time 
							= LENGTH_TIME_FROM_SNAIL;
					if(i == SPEARRAY_GRASSHOPPER)
						CSpecies::speciesarray[i].remain_reach_time 
							= LENGTH_TIME_FROM_GRASSHOPPER;
					if(i == SPEARRAY_SHORT_ANT)
						CSpecies::speciesarray[i].remain_reach_time 
							= LENGTH_TIME_FROM_SHORT_ANT;
					if(i == SPEARRAY_BEE)
						CSpecies::speciesarray[i].remain_reach_time 
							= LENGTH_TIME_FROM_BEE;
					if(i == SPEARRAY_RED_ANT)
						CSpecies::speciesarray[i].remain_reach_time 
							= LENGTH_TIME_FROM_RED_ANT;

					// 愿怨??낇솕
					if(CSpecies::speciesarray[i].strategy_att == 0)
						diplomatic_.ChangeRelation(i, -5000);
					if(CSpecies::speciesarray[i].strategy_att == 1)
						diplomatic_.ChangeRelation(i, -7000);
					if(CSpecies::speciesarray[i].strategy_att == 2)
						diplomatic_.ChangeRelation(i, -9000);

					// 怨듦꺽??媛쒖껜 ??
					if(CSpecies::speciesarray[i].strategy_att == 0)
						CSpecies::speciesarray[i].num_attack
							= CSpecies::speciesarray[i].strength/NUM_CIPHER/11.5;
					if(CSpecies::speciesarray[i].strategy_att == 1)
						CSpecies::speciesarray[i].num_attack
							= CSpecies::speciesarray[i].strength/NUM_CIPHER/8.5;
					if(CSpecies::speciesarray[i].strategy_att == 2)
						CSpecies::speciesarray[i].num_attack
							= CSpecies::speciesarray[i].strength/NUM_CIPHER/6.5;
					if(time_.GetYear() == 0)
					{
						// 珥덈컲?먮뒗 怨듦꺽?섎뒗 ?섏뿉 ?쒗븳???붾떎.
						if(time_.GetSeason() == WINTER)
							CSpecies::speciesarray[i].num_attack /= 2;
						if(time_.GetSeason() == SPRING)
							CSpecies::speciesarray[i].num_attack /= 1.5;
					}
				}
			}
		}
	}

	return 1;
}

int CBattle::BattleOutside()
{
	if(BATTLE_OUT_STATE != BATTLE_OUT_BREAK)
		return 0;

	int temp_index;

	int temp_rand;

	int temp_str_def;
	int temp_str_att;
	
	int temp_pro_attack;
	int temp_pro_resource;

	float temp_attack_bonus = 1;
	float temp_defence_bonus = 1;

	float temp_attack = 0;
	float temp_defence = 0;

	temp_index = CSpecies::spe_attacked_index;
	temp_str_att = CPlayer::strategy_att;
	temp_str_def = CSpecies::speciesarray[temp_index].strategy_def;

	// ?꾪닾?곌린???꾩튂瑜??〓뒗??
	battle_dirt2.x = object_.objarray[temp_index].objrect.left;
	battle_dirt2.y = object_.objarray[temp_index].objrect.top;

	// ?꾨왂 ///////////////////////////////////////////
	if(temp_str_att == 0)
	{
		if(temp_str_def == 0)
		{
			temp_pro_attack = 6;
			temp_pro_resource = 4;
		}
		else
		{
			temp_pro_attack = 2;
			temp_pro_resource = 8;
		}
	}
	if(temp_str_att == 1)
	{
		temp_attack_bonus += 0.1;
		if(temp_str_def == 0)
		{
			temp_pro_attack = 7;
			temp_pro_resource = 3;
		}
		else
		{
			temp_pro_attack = 10;
			temp_pro_resource = 0;
		}
	}
	if(temp_str_att == 2)
	{
		temp_attack_bonus += 0.2;
		temp_pro_attack = 10;
		temp_pro_resource = 0;
	}

	if(temp_str_def == 0)
	{
		temp_attack_bonus -= 0.3;
		temp_defence_bonus += 0.2;
	}
	if(temp_str_def == 1)
	{
		temp_attack_bonus -= 0.1;
		temp_defence_bonus += 0.1;
	}

	// ?뺣쪧?濡??꾪닾???먯썝?쏀깉??諛쒖깮?쒕떎. 
	temp_rand = 1 +rand()%10;
	if(temp_rand <= temp_pro_attack)
	{
		//************* ?꾪닾 *************//

		// 蹂대꼫?ㅼ뿉 ?곕Ⅸ ///////////////////////////////////////////////////
		temp_attack += temp_attack_bonus;
		temp_defence += temp_defence_bonus;

		// 怨꾩젅 ?⑤꼸?곗뿉 ?곕Ⅸ //////////////////////////////////////////////
		if(time_.GetSeason() == SPRING)
			temp_attack -= 0.2;
		if(time_.GetSeason() == SUMMER)
			temp_attack -= 0.1;
		if(time_.GetSeason() == FALL)
			temp_attack -= 0.2;
		if(time_.GetSeason() == WINTER)
			temp_attack -= 0.4;

		// ?섏뿉 ?곕Ⅸ ////////////////////////////////////////////////////////
		temp_attack *= battle.player_cur_num_att/NUM_CIPHER;
		temp_defence *= battle.spe_cur_num_def/NUM_CIPHER;

		// ?뚯썙???곕Ⅸ //////////////////////////////////////////////////////
		temp_attack *= (((float)battle.player_cur_num_soldier_att/battle.player_cur_num_att*POWER_SOLDIER_ANT)
			+ ((float)battle.player_cur_num_hired_att/battle.player_cur_num_att*battle.power_hired_att));
		temp_defence *= CSpecies::speciesarray[temp_index].power;

		// 湲고? /////////////////////////////////////////////////////////////
		if(objdialog_.labflag & LAB_1_DONE)
			temp_attack += ((float)battle.player_cur_num_soldier_att/NUM_CIPHER*DEMAGE_UPGRADE_LAB);

		if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
			temp_attack += ((float)battle.player_cur_num_soldier_att/NUM_CIPHER*DEMAGE_UPGRADE_TRAINING);

		if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
			temp_attack *= 1.1;

		if(item_.GetItem(4) == PLAYER)
			temp_attack *= 1.1;

		// ?댁뿉 ?곕Ⅸ ////////////////////////////////////////////////////////
		temp_attack *= (1.0 - rand()%5/10.0 + 0.2);
		temp_defence *= (1.0 - rand()%5/10.0 + 0.2);

		// ?꾪닾 寃곌낵 ///////////////////////////////////////////////////
		battle.player_cur_num_att -= (temp_defence*1.5);
		if(battle.player_cur_num_att < 0)
			battle.player_cur_num_att = 0;
		battle.spe_cur_num_def -= (temp_attack*1.5);
		if(battle.spe_cur_num_def < 0)
			battle.spe_cur_num_def = 0;

		battle.player_cur_num_soldier_att
			= (float)battle.player_init_num_soldier_att*battle.player_cur_num_att
				/battle.player_init_num_att;
		battle.player_cur_num_hired_att
			= battle.player_cur_num_att - battle.player_cur_num_soldier_att;

		domestic_.ComputeAttAnts(battle.player_cur_num_soldier_att/NUM_CIPHER,
			battle.player_cur_num_hired_att/NUM_CIPHER);

		// 而댄벂?곗쓽 ?쇳빐留뚰겮 ?몃젰??以꾩씤??
		if(temp_str_def == 0)
			CSpecies::speciesarray[temp_index].strength_damege += temp_attack*1.4;
		else
			CSpecies::speciesarray[temp_index].strength_damege += temp_attack;
	}
	else
	{
		//************ ?먯썝?쏀깉 ************//

		int temp_num_food_get;
		int temp_num_timber_get;
		int temp_num_mineral_get;

		temp_num_food_get = (rand()%7 * battle.player_cur_num_att/NUM_CIPHER);
		temp_num_timber_get = (rand()%7 * battle.player_cur_num_att/NUM_CIPHER/2.5);
		temp_num_mineral_get = (rand()%7 * battle.player_cur_num_att/NUM_CIPHER/5);

		battle.num_food_get += temp_num_food_get;
		battle.num_timber_get += temp_num_timber_get;
		battle.num_mineral_get += temp_num_mineral_get;
		CSpecies::speciesarray[temp_index].strength_damege 
			+= (temp_num_food_get + temp_num_timber_get + temp_num_mineral_get)/4;
	}

	//********** 寃곌낵(?밸━, ?꾪눜 ?? ***********//

	battle.player_attack_time++;
	debug_.GetValue("time", &battle.player_attack_time, 0, lpddsback, 12, ONLY_V1);
	if(temp_str_att == 0)
	{
		if((battle.player_attack_time == 40)
			|| (GETPERCENT(battle.player_cur_num_att, battle.player_init_num_att) <= 66))
		{
			PlayerComeBackInit(temp_index);
			diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_NORMAL);

			sprintf(buffer, "李몃え 媛쒕?\n\n\"?먯젙???섍컮???꾧뎔??洹?섏쓣 ?쒖옉?덉뒿?덈떎.\"");
			ShowNorDialog(buffer);

			WaitDialog();
		}
	}
	if(temp_str_att == 1)
	{
		if((battle.player_attack_time == 90)
			|| (GETPERCENT(battle.player_cur_num_att, battle.player_init_num_att) <= 50))
		{
			PlayerComeBackInit(temp_index);
			diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_NORMAL);

			sprintf(buffer, "李몃え 媛쒕?\n\n\"?먯젙???섍컮???꾧뎔??洹?섏쓣 ?쒖옉?덉뒿?덈떎.\"");
			ShowNorDialog(buffer);

			WaitDialog();
		}
	}

	// ?뚮젅?댁뼱??蹂묒궗 ?꾨㈇
	if(battle.player_cur_num_att <= 0)
	{
		BATTLE_OUT_STATE = BATTLE_OUT_NO;

		sprintf(buffer, "李몃え 媛쒕?\n\n\"?먯젙???섍컮???꾧뎔???꾨㈇?덉뒿?덈떎.\"");
		ShowNorDialog(buffer);

		diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_NORMAL);

		CPlayer::remain_return_time = 0;
		CSpecies::spe_attacked_index = -1;
		diplomatic_.EnableDipAtt();
	}

	// ?먮졊
	if(battle.spe_cur_num_def <= 0)
	{
		// ?꾩씠???뺤씤 李쎌쓣 癒쇱? ?곗슦怨??ㅼ쓬 ?댁슜??洹??꾩뿉 ?곗슫??
		item_.TakeItemFromSpe(temp_index);

		PlayerComeBackInit(temp_index);
		// 醫낆” ?곹깭??'醫낆냽'?쇰줈 諛붽씔?? 1?쇰쭏??議곌났??諛붿튇??
		diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_OCCUPIED);

		// ?뺣났?뱁븳 醫낆”???몃젰??諛섏쑝濡?
		diplomatic_.ChangeSpeStrength(temp_index, -CSpecies::speciesarray[temp_index].strength/2);

		sprintf(buffer, "李몃え 媛쒕?\n\n\"湲곕퍙?섏떗?쒖삤, ?ъ솗?댁떆?? ?먯젙???섍컮???곕━??蹂묒궗媛 ?뱀쟾蹂대? "
						"?뚮젮?붿뒿?덈떎. ?욎쑝濡?洹몃뱾? ?곕━?먭쾶 議곌났??蹂대궡?ㅺ쾶 ??寃껋엯?덈떎.\"");
		ShowNorDialog(buffer);

		if(battle.num_food_get < 7000)
			battle.num_food_get = 6000 + rand()%1000;
		if(battle.num_timber_get < 21000)
			battle.num_timber_get = 18000 + rand()%3000;
		if(battle.num_mineral_get < 3500)
			battle.num_mineral_get = 3000 + rand()%500;
	}

	return 1;
}

int CBattle::BattleInside()
{
	if(BATTLE_IN_STATE != BATTLE_IN_BREAK)
		return 0;

	int temp_index;

	int temp_rand;

	int temp_str_def;
	int temp_str_att;
	
	int temp_pro_attack;
	int temp_pro_resource;

	float temp_attack_bonus = 1;
	float temp_defence_bonus = 1;

	float temp_attack = 0;
	float temp_defence = 0;

	temp_index = CSpecies::spe_attacking_index;
	temp_str_def = CPlayer::strategy_def;
	temp_str_att = CSpecies::speciesarray[temp_index].strategy_att;

	// ?꾨왂 ///////////////////////////////////////////
	if(temp_str_att == 0)
	{
		if(temp_str_def == 0)
		{
			temp_pro_attack = 6;
			temp_pro_resource = 4;
		}
		else
		{
			temp_pro_attack = 2;
			temp_pro_resource = 8;
		}
	}
	if(temp_str_att == 1)
	{
		temp_attack_bonus += 0.1;
		if(temp_str_def == 0)
		{
			temp_pro_attack = 7;
			temp_pro_resource = 3;
		}
		else
		{
			temp_pro_attack = 10;
			temp_pro_resource = 0;
		}
	}
	if(temp_str_att == 2)
	{
		temp_attack_bonus += 0.2;
		temp_pro_attack = 10;
		temp_pro_resource = 0;
	}

	if(temp_str_def == 0)
	{
		temp_attack_bonus -= 0.3;
		temp_defence_bonus += 0.2;
	}
	if(temp_str_def == 1)
	{
		temp_attack_bonus -= 0.1;
		temp_defence_bonus += 0.1;
	}

	// ?뺣쪧?濡??꾪닾???먯썝?쏀깉??諛쒖깮?쒕떎. 
	temp_rand = 1 +rand()%10;
	if(temp_rand <= temp_pro_attack)
	{
		//************* ?꾪닾 *************//

		// 蹂대꼫?ㅼ뿉 ?곕Ⅸ ///////////////////////////////////////////////////
		temp_attack += temp_attack_bonus;
		temp_defence += temp_defence_bonus;

		// 怨꾩젅 ?⑤꼸?곗뿉 ?곕Ⅸ //////////////////////////////////////////////
		if(time_.GetSeason() == SPRING)
			temp_attack -= 0.2;
		if(time_.GetSeason() == SUMMER)
			temp_attack -= 0.1;
		if(time_.GetSeason() == FALL)
			temp_attack -= 0.2;
		if(time_.GetSeason() == WINTER)
			temp_attack -= 0.4;

		// ?섏뿉 ?곕Ⅸ ////////////////////////////////////////////////////////
		temp_defence *= battle.player_cur_num_def/NUM_CIPHER;
		temp_attack *= battle.spe_cur_num_att/NUM_CIPHER;

		// ?뚯썙???곕Ⅸ //////////////////////////////////////////////////////
		temp_defence *= (((float)battle.player_cur_num_soldier_def/battle.player_cur_num_def*POWER_SOLDIER_ANT)
			+ ((float)battle.player_cur_num_hired_def/battle.player_cur_num_def*battle.power_hired_def));
		temp_attack *= CSpecies::speciesarray[temp_index].power;

		// 湲고? /////////////////////////////////////////////////////////////

		// 怨좊냽異?媛쒕???
		if(objdialog_.labflag & LAB_1_DONE)
			temp_defence += ((float)battle.player_cur_num_soldier_def/NUM_CIPHER*DEMAGE_UPGRADE_LAB);

		// ?꾪닾 ?덈젴??
		if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
			temp_defence += ((float)battle.player_cur_num_soldier_def/NUM_CIPHER*DEMAGE_UPGRADE_TRAINING);

		// ?덉닠???꾨떦
		if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
			temp_defence *= 1.1;

		// ?덈?諛섏?
		if(item_.GetItem(4) == PLAYER)
			temp_defence *= 1.1;
		
		// 遺덉쓣 ?댁슜
		if(objdialog_.labflag & LAB_10_DONE)
		{
			temp_defence *= 1.2;
			domestic_.ChangeResource(-rand()%30,
									 -rand()%70,
									 -rand()%15);
			CPlayer::strength_damege += rand()%15;

		}

		// ?댁뿉 ?곕Ⅸ ////////////////////////////////////////////////////////
		temp_attack *= (1.0 - rand()%5/10.0 + 0.2);
		temp_defence *= (1.0 - rand()%5/10.0 + 0.2);

		// ?꾪닾 寃곌낵 ///////////////////////////////////////////////////
		battle.player_cur_num_def -= (temp_attack*1.5);
		if(battle.player_cur_num_def < 0)
			battle.player_cur_num_def = 0;
		battle.spe_cur_num_att -= (temp_defence*1.5);
		if(battle.spe_cur_num_att < 0)
			battle.spe_cur_num_att = 0;

		battle.player_cur_num_soldier_def
			= (float)battle.player_init_num_soldier_def*battle.player_cur_num_def
				/battle.player_init_num_def;
		battle.player_cur_num_hired_def
			= battle.player_cur_num_def - battle.player_cur_num_soldier_def;

		domestic_.ComputeDefAnts(battle.player_cur_num_soldier_def/NUM_CIPHER,
			battle.player_cur_num_hired_def/NUM_CIPHER);

		// 而댄벂?곗쓽 ?쇳빐留뚰겮 ?몃젰??以꾩씤??
		CSpecies::speciesarray[temp_index].strength_damege += temp_defence;

		// ?띿꽦???섎㈃ ?쒖떇泥섏뿉 ?쇳빐瑜??낃퀬 媛쒖껜?ㅼ쓽 遺덈쭔???볦씤??
		if(temp_str_def == 0)
		{
			CPlayer::strength_damege += temp_attack/3;
			domestic_.ChangeUnsatisfactory(temp_attack*4);
		}
	}
	else
	{
		//************ ?먯썝?쏀깉 ************//

		int temp_num_food_lost;
		int temp_num_timber_lost;
		int temp_num_mineral_lost;

		temp_num_food_lost = (rand()%7 * battle.spe_cur_num_att/NUM_CIPHER);
		temp_num_timber_lost = (rand()%7 * battle.spe_cur_num_att/NUM_CIPHER/2.5);
		temp_num_mineral_lost = (rand()%7 * battle.spe_cur_num_att/NUM_CIPHER/5);

		battle.num_food_lost += temp_num_food_lost;
		battle.num_timber_lost += temp_num_timber_lost;
		battle.num_mineral_lost += temp_num_mineral_lost;
		CPlayer::strength_damege
			+= (temp_num_food_lost + temp_num_timber_lost + temp_num_mineral_lost)/4;

		domestic_.ChangeResource(-temp_num_food_lost,
								 -temp_num_timber_lost,
								 -temp_num_mineral_lost);
	}

	//********** 寃곌낵(?밸━, ?꾪눜 ?? ***********//

	battle.player_defence_time++;
	//debug_.GetValue("time", &battle.player_defence_time, 0, lpddsback, 12, ONLY_V1);
	if(temp_str_att == 0)
	{
		if((battle.player_defence_time == 40)
			|| (GETPERCENT(battle.spe_cur_num_att, battle.spe_init_num_att) <= 66))
		{
			SpeGoBackInit(temp_index);

			ShowDefResDialog(temp_index);
		}
	}
	if(temp_str_att == 1)
	{
		if((battle.player_defence_time == 90)
			|| (GETPERCENT(battle.spe_cur_num_att, battle.spe_init_num_att) <= 50))
		{
			SpeGoBackInit(temp_index);

			ShowDefResDialog(temp_index);
		}
	}

	// ?뚮젅?댁뼱??蹂묒궗 ?꾨㈇
	if(battle.player_cur_num_def <= 0)
	{
		CloseAllDialog();

		CTime::SetPause();

		if(hWndDlg_gameover)
			EndDialog(hWndDlg_gameover, TRUE );
		hWndDlg_gameover = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_GAMEOVER),
			main_window_handle,  (DLGPROC)GameoverDlgProc );
		SetDlgItemTextA(hWndDlg_gameover, IDC_STATIC_GAMEOVER, 
			"?뚮┝\n\n?꾪닾 媛?ν븳 蹂묒궗?ㅼ씠 ?꾨㈇?덉뒿?덈떎. "
			"移⑹엯?먮뱾? ?뺢뎅???꾩쟾???뚭눼?덉뒿?덈떎.  ?붽컻誘?1?몄쓽 "
			"?뺢뎅? ??궗???ㅼ븞湲몃줈 ?щ씪議뚯뒿?덈떎.");
		ShowWindow(hWndDlg_gameover, SW_SHOWNORMAL );

		WaitDialog();

		return 0;
	}

	// 而댄벂?곗쓽 蹂묒궗 ?꾨㈇
	if(battle.spe_cur_num_att <= 0)
	{
		SpeGoBackInit(temp_index);

		ShowDefResDialog(temp_index);

		sprintf(buffer, "李몃え 媛쒕?\n\n\"?꾧뎔???곴뎔???щ㈇?덉뒿?덈떎. ?ㅼ쓬? ?대쾲 ?꾪닾??蹂닿퀬?쒖엯?덈떎.\"");
		ShowNorDialog(buffer);

		CSpecies::spe_attacking_index = -1;
	}

	return 1;
}
int CBattle::PlayerComeBackInit(int SPEARRAY_INDEX)
{
	BATTLE_OUT_STATE = BATTLE_OUT_NO;
	if(SPEARRAY_INDEX == SPEARRAY_SNAIL)
		CPlayer::remain_return_time = LENGTH_TIME_FROM_SNAIL/2;
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
		CPlayer::remain_return_time = LENGTH_TIME_FROM_GRASSHOPPER/2;
	if(SPEARRAY_INDEX == SPEARRAY_SHORT_ANT)
		CPlayer::remain_return_time = LENGTH_TIME_FROM_SHORT_ANT/2;
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
		CPlayer::remain_return_time = LENGTH_TIME_FROM_BEE/2;
	if(SPEARRAY_INDEX == SPEARRAY_RED_ANT)
		CPlayer::remain_return_time = LENGTH_TIME_FROM_RED_ANT/2;

	return 1;
}
int CBattle::SpeGoBackInit(int SPEARRAY_INDEX)
{
	BATTLE_IN_STATE = BATTLE_IN_NO;
	if(SPEARRAY_INDEX == SPEARRAY_SNAIL)
		CSpecies::speciesarray[SPEARRAY_INDEX].remain_return_time = LENGTH_TIME_FROM_SNAIL/2;
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
		CSpecies::speciesarray[SPEARRAY_INDEX].remain_return_time = LENGTH_TIME_FROM_GRASSHOPPER/2;
	if(SPEARRAY_INDEX == SPEARRAY_SHORT_ANT)
		CSpecies::speciesarray[SPEARRAY_INDEX].remain_return_time = LENGTH_TIME_FROM_SHORT_ANT/2;
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
		CSpecies::speciesarray[SPEARRAY_INDEX].remain_return_time = LENGTH_TIME_FROM_BEE/2;
	if(SPEARRAY_INDEX == SPEARRAY_RED_ANT)
		CSpecies::speciesarray[SPEARRAY_INDEX].remain_return_time = LENGTH_TIME_FROM_RED_ANT/2;

	return 1;
}
int CBattle::ShowAttResDialog(int SPEARRAY_INDEX)
{
	if(hWndDlg_battle_result_att)
		EndDialog( hWndDlg_battle_result_att, TRUE );
	hWndDlg_battle_result_att = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_RESULT),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	if(SPEARRAY_INDEX == SPEARRAY_SNAIL)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "吏??: 誘쇰떖?쎌씠 ?쒖떇泥?);
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "吏??: 硫붾슌湲??쒖떇泥?);
	if(SPEARRAY_INDEX == SPEARRAY_SHORT_ANT)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "吏??: ?쒖웳?닿컻誘?援?);
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "吏??: 轅踰?吏?);
	if(SPEARRAY_INDEX == SPEARRAY_RED_ANT)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "吏??: 遺덇컻誘?援?);
	if(CPlayer::strategy_att == 0)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?먯썝 ?쏀깉");
	if(CPlayer::strategy_att == 1)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?쇰컲");
	if(CPlayer::strategy_att == 2)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?뺣났");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_def == 0)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_DEF, "諛⑹뼱 ?꾨왂 : ?띿꽦");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_def == 1)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_DEF, "諛⑹뼱 ?꾨왂 : ?붽꺽");
	sprintf(buffer, "?꾧뎔 ?쇳빐 : ?щ쭩 %d",
		(battle.player_init_num_att - battle.player_cur_num_att) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLAYER_DEM, buffer);
	sprintf(buffer, "?곴뎔 ?쇳빐 : ?щ쭩 %d",
		(battle.spe_init_num_def - battle.spe_cur_num_def) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_SPE_DEM, buffer);
	sprintf(buffer, "?먯썝 ?쏀깉\n\n?앸웾 : %d\n紐⑹옱 : %d\n愿묒꽍 : %d",
		battle.num_food_get/NUM_CIPHER,
		battle.num_timber_get/NUM_CIPHER,
		battle.num_mineral_get/NUM_CIPHER);
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_RESOURCE, buffer);
	SendMessage(hWndDlg_battle_result_att, WM_GETINFO, NULL, (LPARAM)hWndDlg_battle_result_att);
	ShowWindow( hWndDlg_battle_result_att, SW_SHOWNORMAL );

	WaitDialog();

	sprintf(buffer, "李몃え 媛쒕?\n\n\"?대쾲 ?꾪닾??蹂닿퀬?쒖엯?덈떎.\"");
	ShowNorDialog(buffer);

	return 1;
}
int CBattle::ShowDefResDialog(int SPEARRAY_INDEX)
{
	if(hWndDlg_battle_result_def)
		EndDialog( hWndDlg_battle_result_def, TRUE );
	hWndDlg_battle_result_def = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_RESULT),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_PLACE, "吏??: ?붽컻誘?1?몄쓽 援?);
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 0)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?먯썝 ?쏀깉");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 1)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?쇰컲");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 2)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "怨듦꺽 ?꾨왂 : ?뺣났");
	if(CPlayer::strategy_def == 0)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_DEF, "諛⑹뼱 ?꾨왂 : ?띿꽦");
	if(CPlayer::strategy_def == 1)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_DEF, "諛⑹뼱 ?꾨왂 : ?붽꺽");
	if(battle.player_join == TRUE)
	{
		sprintf(buffer, "?꾧뎔 ?쇳빐 : ?щ쭩 %d",
		(battle.player_init_num_def - battle.player_cur_num_def + battle.player_cur_num_att) 
			/ NUM_CIPHER);	
		battle.player_join = FALSE;
	}
	else
		sprintf(buffer, "?꾧뎔 ?쇳빐 : ?щ쭩 %d",
		(battle.player_init_num_def - battle.player_cur_num_def) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_PLAYER_DEM, buffer);
	sprintf(buffer, "?곴뎔 ?쇳빐 : ?щ쭩 %d",
		(battle.spe_init_num_att - battle.spe_cur_num_att) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_SPE_DEM, buffer);
	sprintf(buffer, "?먯썝 ?쇳빐\n\n?앸웾 : %d\n紐⑹옱 : %d\n愿묒꽍 : %d",
		battle.num_food_lost/NUM_CIPHER,
		battle.num_timber_lost/NUM_CIPHER,
		battle.num_mineral_lost/NUM_CIPHER);
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_RESOURCE, buffer);
	SendMessage(hWndDlg_battle_result_def, WM_GETINFO, NULL, (LPARAM)hWndDlg_battle_result_def);
	ShowWindow( hWndDlg_battle_result_def, SW_SHOWNORMAL );

	WaitDialog();

	sprintf(buffer, "李몃え 媛쒕?\n\n\"?곴뎔???꾪눜?섍린 ?쒖옉?덉뒿?덈떎. ?ㅼ쓬? ?대쾲 ?꾪닾??蹂닿퀬?쒖엯?덈떎.\"");
	ShowNorDialog(buffer);

	return 1;
}
int CBattle::ShowNorDialog(char *buffer)
{
	if(hWndDlg_battle_normal)
		EndDialog( hWndDlg_battle_normal, TRUE );
	hWndDlg_battle_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_battle_normal, IDC_NORMAL, buffer);
	ShowWindow( hWndDlg_battle_normal, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CBattle::CheckReachTime()
{
	int temp_index;

	temp_index = CSpecies::spe_attacked_index;

	if(temp_index != -1)
	{
		if(CPlayer::remain_reach_time > -1)
		{
			CPlayer::remain_reach_time--;
			if(CPlayer::remain_reach_time == 0)
			{
				BattleOut_Init();

				sprintf(buffer, "李몃え 媛쒕?\n\n\"?먯젙???섍컮???꾧뎔???꾪닾???뚯엯?덉뒿?덈떎.\"");
				ShowNorDialog(buffer);

				WaitDialog();

				// ?꾪닾 ?쒖옉
				BATTLE_OUT_STATE = BATTLE_OUT_BREAK;

			}
		}
	}

	temp_index = CSpecies::spe_attacking_index;

	if(temp_index != -1)
	{
		if(CSpecies::speciesarray[temp_index].remain_reach_time > -1)
		{
			CSpecies::speciesarray[temp_index].remain_reach_time--;
			if((CSpecies::speciesarray[temp_index].remain_reach_time == 4*UNIT_PER_TICK*UNIT_PER_DAY)
				|| (CSpecies::speciesarray[temp_index].remain_reach_time == 2*UNIT_PER_TICK*UNIT_PER_DAY))
			{
				//BattleOut_Init();

				sprintf(buffer, "李몃え 媛쒕?\n\n\" '%s'醫낆쓽 蹂묒궗媛 ?묎렐以묒엯?덈떎. ??%d???꾩뿉 ?꾩갑??"
								"寃껋쑝濡?蹂댁엯?덈떎.\"",
						CSpecies::speciesarray[temp_index].name,
						CSpecies::speciesarray[temp_index].remain_reach_time/UNIT_PER_TICK/UNIT_PER_DAY);
				ShowNorDialog(buffer);

				WaitDialog();
			}
			if(CSpecies::speciesarray[temp_index].remain_reach_time == 0)
			{
				BattleIn_Init();

				// 紐⑤뱺 李??リ린
				CloseAllDialog(EXCEPT_BATTLE);
				
				CTime::SetPause();

				// 諛⑹뼱 ?꾨왂 ?섎┰
				if(hWndDlg_battle)
					EndDialog(hWndDlg_battle, TRUE );
				hWndDlg_battle = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_DEFENCE),
					main_window_handle,  (DLGPROC)BattleDefDlgProc );
				SendMessage(hWndDlg_battle, WM_GETINFO, 0, (LPARAM)temp_index);
				SendMessage(hWndDlg_battle, WM_GETPOINT, 0, (LPARAM)this);
				if(temp_index == SPEARRAY_SNAIL)
					sprintf(buffer, "李몃え 媛쒕?\n\n\" '誘쇰떖?쎌씠'醫낆씠 ?곕━ ?뺢뎅??怨듦꺽?댁삤怨??덉뒿?덈떎. ?대뼡 諛⑹뼱 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
				if(temp_index == SPEARRAY_GRASSHOPPER)
					sprintf(buffer, "李몃え 媛쒕?\n\n\" '硫붾슌湲?醫낆씠 ?곕━ ?뺢뎅??怨듦꺽?댁삤怨??덉뒿?덈떎. ?대뼡 諛⑹뼱 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
				if(temp_index == SPEARRAY_SHORT_ANT)
					sprintf(buffer, "李몃え 媛쒕?\n\n\" '?쒖웳?닿컻誘?醫낆씠 ?곕━ ?뺢뎅??怨듦꺽?댁삤怨??덉뒿?덈떎. ?대뼡 諛⑹뼱 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
				if(temp_index == SPEARRAY_BEE)
					sprintf(buffer, "李몃え 媛쒕?\n\n\" '轅踰?醫낆씠 ?곕━ ?뺢뎅??怨듦꺽?댁삤怨??덉뒿?덈떎. ?대뼡 諛⑹뼱 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
				if(temp_index == SPEARRAY_RED_ANT)
					sprintf(buffer, "李몃え 媛쒕?\n\n\" '遺덇컻誘?醫낆씠 ?곕━ ?뺢뎅??怨듦꺽?댁삤怨??덉뒿?덈떎. ?대뼡 諛⑹뼱 ?꾨왂???ъ슜?섏떆寃좎뒿?덇퉴?\"");
				SetDlgItemTextA(hWndDlg_battle, IDC_STATIC_BATTLE, buffer);
				ShowWindow(hWndDlg_battle, SW_SHOWNORMAL );

				WaitDialog();

				// ?꾪닾 以鍮?
				BATTLE_IN_STATE = BATTLE_IN_INIT;
			}
		}
	}

	return 1;
}

int CBattle::CheckReturnTime()
{
	int temp_index;

	temp_index = CSpecies::spe_attacked_index;

	//if(temp_index != -1)
	{
		if(CPlayer::remain_return_time > -1)
		{
			CPlayer::remain_return_time--;
			if(CPlayer::remain_return_time == 0)
			{
				CSpecies::spe_attacked_index = -1;
				diplomatic_.EnableDipAtt();

				domestic_.ChangeResource(battle.num_food_get,
										battle.num_timber_get,
										battle.num_mineral_get);

				ShowAttResDialog(temp_index);

				// ?먯젙援??댁궛
				domestic_.ReturnFromBattle();

				// 洹?섑뻽?붾뜲 ?붽컻誘?1?몄쓽 援댁뿉???꾪닾以묒씠?쇰㈃ ?⑸쪟
				if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
					this->ReturnFromBattle();
			}
		}
	}

	temp_index = CSpecies::spe_attacking_index;

	if(temp_index != -1)
	{
		if(CSpecies::speciesarray[temp_index].remain_return_time > -1)
		{
			CSpecies::speciesarray[temp_index].remain_return_time--;
			if(CSpecies::speciesarray[temp_index].remain_return_time == 0)
			{
				// 洹?섑븳 而댄벂?곗쓽 蹂묐젰 ?댁궛
				CSpecies::speciesarray[temp_index].num_attack = 0;

				CSpecies::spe_attacking_index = -1;
			}
		}
	}

	return 1;
}
int CBattle::ReturnFromBattle()
{
	// ?붽컻誘?1??沅곸뿉???쇱뼱?섎뒗 ?꾪닾??異붽?
	battle.player_cur_num_def += battle.player_cur_num_att;
	battle.player_join = TRUE;

	sprintf(buffer, "李몃え 媛쒕?\n\n\"?먯젙???섍컮???꾧뎔???⑸쪟?덉뒿?덈떎. ?ㅼ쓬? ?대쾲 ?꾪닾??蹂닿퀬?쒖엯?덈떎.\"");
	ShowNorDialog(buffer);

	return 1;
}
int CBattle::BattleOut_Init()
{
	int temp_rand;
	int temp_index;

	// ?꾪닾 以鍮?
	temp_index = CSpecies::spe_attacked_index;

	// ?쏀깉?먯썝 珥덇린??
	battle.num_food_get = 0;
	battle.num_timber_get = 0;
	battle.num_mineral_get = 0;

	// 而댄벂?곗쓽 ?섎퉬援곗쓣 ?뺥븳??
	temp_rand = rand()%3;
	if(temp_rand == 0)
		CSpecies::speciesarray[temp_index].num_defence
			= CSpecies::speciesarray[temp_index].strength/NUM_CIPHER/3
				- CSpecies::speciesarray[temp_index].num_attack;
	else if(temp_rand == 1)
		CSpecies::speciesarray[temp_index].num_defence
			= CSpecies::speciesarray[temp_index].strength/NUM_CIPHER/3.5
				- CSpecies::speciesarray[temp_index].num_attack;
	else
		CSpecies::speciesarray[temp_index].num_defence
			= CSpecies::speciesarray[temp_index].strength/NUM_CIPHER/4
				- CSpecies::speciesarray[temp_index].num_attack;

	// ?꾪닾 ?곹깭濡?
	diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_BATTLE);

	// ?꾪닾 ?쒓컙 珥덇린??
	battle.player_attack_time = 0;

	// 援곗궗??珥덇린??
	battle.player_init_num_soldier_att
		= CPlayer::num_soldier_attack * NUM_CIPHER;
	battle.player_cur_num_soldier_att = battle.player_init_num_soldier_att;
	battle.player_init_num_hired_att
		= CPlayer::num_hired_attack * NUM_CIPHER;
	battle.player_cur_num_hired_att = battle.player_init_num_hired_att;
	battle.player_init_num_att 
		= (CPlayer::num_soldier_attack+CPlayer::num_hired_attack)
			* NUM_CIPHER;
	battle.player_cur_num_att = battle.player_init_num_att ;
	battle.spe_init_num_def
		= CSpecies::speciesarray[temp_index].num_defence
			* NUM_CIPHER;
	battle.spe_cur_num_def = battle.spe_init_num_def;

	// ?⑸퀝??醫낅쪟???곕Ⅸ ?뚯썙瑜?珥덇린?뷀븳??
	if(building_.buildingarray[BUILDINGARRAY_HIRED_1].bexist == TRUE)
		battle.power_hired_att = POWER_HIRED_1_ATT;
	if(building_.buildingarray[BUILDINGARRAY_HIRED_2].bexist == TRUE)
		battle.power_hired_att = POWER_HIRED_2_ATT;

	// 而댄벂?곗쓽 諛⑹뼱 ?꾨왂???뺥븳??
	if((CPlayer::strength-CSpecies::speciesarray[temp_index].strength) > 0)
	{
		// ?뚮젅?댁뼱???몃젰????媛뺥븯硫??띿꽦??鍮꾩쑉???믪븘吏꾨떎.
		temp_rand = rand()%5;
		if(temp_rand <= 2)
			CSpecies::speciesarray[temp_index].strategy_def = 0;
		else
			CSpecies::speciesarray[temp_index].strategy_def = 1;
	}
	else
	{
		// 洹몃젃吏 ?딅떎硫??뺣쪧? 諛섎컲?대떎.
		temp_rand = rand()%2;
		if(temp_rand == 0)
			CSpecies::speciesarray[temp_index].strategy_def = 0;
		else
			CSpecies::speciesarray[temp_index].strategy_def = 1;
	}

	

	return 1;
}
int CBattle::BattleIn_Init()
{
	int temp_index;

	// ?꾪닾 以鍮?
	temp_index = CSpecies::spe_attacking_index;

	// ?쏀깉?먯썝 珥덇린??
	battle.num_food_lost = 0;
	battle.num_timber_lost = 0;
	battle.num_mineral_lost = 0;

	// ?꾪닾 ?쒓컙 珥덇린??
	battle.player_defence_time = 0;

	// 援곗궗??珥덇린??
	battle.player_init_num_soldier_def
		= CPlayer::num_soldier_defence * NUM_CIPHER;
	battle.player_cur_num_soldier_def = battle.player_init_num_soldier_def;
	battle.player_init_num_hired_def
		= CPlayer::num_hired_defence * NUM_CIPHER;
	battle.player_cur_num_hired_def = battle.player_init_num_hired_def;
	battle.player_init_num_def
		= (CPlayer::num_soldier_defence+CPlayer::num_hired_defence)
			* NUM_CIPHER;
	battle.player_cur_num_def = battle.player_init_num_def;
	battle.spe_init_num_att
		= CSpecies::speciesarray[temp_index].num_attack
			* NUM_CIPHER;
	battle.spe_cur_num_att = battle.spe_init_num_att;

	// ?⑸퀝??醫낅쪟???곕Ⅸ ?뚯썙瑜?珥덇린?뷀븳??
	if(building_.buildingarray[BUILDINGARRAY_HIRED_1].bexist == TRUE)
		battle.power_hired_def = POWER_HIRED_1_DEF;
	if(building_.buildingarray[BUILDINGARRAY_HIRED_2].bexist == TRUE)
		battle.power_hired_def = POWER_HIRED_2_DEF;

	return 1;
}
int CBattle::PrintBattleBreakOut()
{
	if((BATTLE_OUT_STATE != BATTLE_OUT_BREAK) && (BATTLE_IN_STATE != BATTLE_IN_BREAK))
		return 0;

	static int show = 0;
	show++;
	if(show >= 0 && show <= 30)
	{
		sprintf(buffer,"?꾩웳 諛쒕컻以?);
		DDraw_Text(buffer, 
					PRINT_BATTLE_BREAK_OUT_X,
					PRINT_BATTLE_BREAK_OUT_Y,
					15,
					lpddsback,
					RGB(255,0,0),
					TA_RIGHT,
					RGB(255,255,255),
					OPAQUE);
	}
	if(show >= 60)
		show = 0;

	return 1;
}
int CBattle::PrintSpeCome()
{
	int temp_index = CSpecies::spe_attacking_index;
	if(temp_index == -1)
		return 0;

	debug_.GetValue("attacking_index, reaming time", &CSpecies::spe_attacking_index, &CSpecies::speciesarray[temp_index].remain_reach_time, lpddsback, 5, NULL);

	if((CSpecies::speciesarray[temp_index].remain_reach_time <= 0) 
		|| (CSpecies::speciesarray[temp_index].remain_reach_time 
			> 4*UNIT_PER_TICK*UNIT_PER_DAY))
		return 0;

	static int show = 0;
	show++;
	if(show >= 0 && show <= 30)
	{
		sprintf(buffer,"?곴뎔???묎렐以?);
		DDraw_Text(buffer, 
					PRINT_SPE_COME_X,
					PRINT_SPE_COME_Y,
					15,
					lpddsback,
					RGB(255,0,0),
					TA_RIGHT,
					RGB(255,255,255),
					OPAQUE);
	}
	if(show >= 60)
		show = 0;

	return 1;
}

int CBattle::PrintPlayerGo()
{
	if(CPlayer::remain_reach_time <= 0)
		return 0;

	static int show = 0;
	show++;
	if(show >= 0 && show <= 30)
	{
		sprintf(buffer,"?꾧뎔??吏꾧꺽以?);
		DDraw_Text(buffer, 
					PRINT_PLAYER_GO_X,
					PRINT_PLAYER_GO_Y,
					15,
					lpddsback,
					RGB(255,0,0),
					TA_RIGHT,
					RGB(255,255,255),
					OPAQUE);
	}
	if(show >= 60)
		show = 0;

	return 1;
}

int CBattle::PrintPlayerCome()
{
	if(CPlayer::remain_return_time <= 0)
		return 0;

	static int show = 0;
	show++;
	if(show >= 0 && show <= 30)
	{
		sprintf(buffer,"?꾧뎔??洹?섏쨷");
		DDraw_Text(buffer, 
					PRINT_PLAYER_COME_X,
					PRINT_PLAYER_COME_Y,
					15,
					lpddsback,
					RGB(255,0,0),
					TA_RIGHT,
					RGB(255,255,255),
					OPAQUE);
	}
	if(show >= 60)
		show = 0;

	return 1;
}

int CBattle::DrawBattleDirt()
{
	if(SCREEN_STATE == SCREEN_MAP)
	{
		if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		{
			Draw_BOB(&battle_dirt, lpddsback);
			if(GAME_STATE == GAME_RUN)
				Animate_BOB(&battle_dirt);
		}

		if(BATTLE_OUT_STATE == BATTLE_OUT_BREAK)
		{
			Draw_BOB(&battle_dirt2, lpddsback);
			if(GAME_STATE == GAME_RUN)
				Animate_BOB(&battle_dirt2);
		}
	}

	return 1;
}
DWORD WINAPI CBattle::ThreadBattle(LPVOID temp)
{
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);

	SCREEN_STATE = SCREEN_MAP;
	
	Sleep(500);

	CTime::ReleasePause();

	ReturnScreenGamma(TRUE);

	hthread = NULL;

	return 1;
}
DWORD WINAPI CBattle::ThreadGameover(LPVOID temp)
{
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE, 100);
	
	window_closed = 1;
	GAME_STATE = GAME_OVER;
	CTime::ReleasePause();
	
	// 留덈Т由ъ? 珥덇린?뷀븷 ?쒓컙?숈븞
	Sleep(2500);

	ReturnScreenGamma(FALSE);

	return 1;
}
INT_PTR CALLBACK CBattle::BattleAttDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CBattle* pThis; 

	static HWND hradio1;
	static HWND hradio2;
	static HWND hradio3;

	static int selectedindex;
	static int selectedradio;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_BATTLE_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_BATTLE_RADIO2);
			hradio3 = GetDlgItem(hDlg, IDC_BATTLE_RADIO3);
	
            return TRUE;
		case WM_GETPOINT:
			pThis = (CBattle *)lParam;

			return TRUE;
		case WM_GETINFO:
			selectedindex = (int)lParam;

			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);
			selectedradio = 0;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDC_BATTLE_RADIO1:
				selectedradio = 0;
				return TRUE;
			case IDC_BATTLE_RADIO2:
				selectedradio = 1;
				return TRUE;
			case IDC_BATTLE_RADIO3:
				selectedradio = 2;
				return TRUE;
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_battle = NULL;

				CTime::ReleasePause();

				CSpecies::spe_attacked_index = selectedindex;
				if(selectedindex == SPEARRAY_SNAIL)
					CPlayer::remain_reach_time = LENGTH_TIME_FROM_SNAIL;
				if(selectedindex == SPEARRAY_GRASSHOPPER)
					CPlayer::remain_reach_time = LENGTH_TIME_FROM_GRASSHOPPER;
				if(selectedindex == SPEARRAY_SHORT_ANT)
					CPlayer::remain_reach_time = LENGTH_TIME_FROM_SHORT_ANT;
				if(selectedindex == SPEARRAY_BEE)
					CPlayer::remain_reach_time = LENGTH_TIME_FROM_BEE;
				if(selectedindex == SPEARRAY_RED_ANT)
					CPlayer::remain_reach_time = LENGTH_TIME_FROM_RED_ANT;
				CPlayer::strategy_att = selectedradio;

				// ?대떦 醫낆”怨쇱쓽 愿怨??낇솕
				if(selectedradio == 0)
					diplomatic_.ChangeRelation(selectedindex, -10000);
				if(selectedradio == 1)
					diplomatic_.ChangeRelation(selectedindex, -20000);
				if(selectedradio == 2)
					diplomatic_.ChangeRelation(selectedindex, -30000);

				if(hWndDlg_battle_normal)
					EndDialog( hWndDlg_battle_normal, TRUE );
				hWndDlg_battle_normal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				SetDlgItemTextA(hWndDlg_battle_normal, IDC_NORMAL, "李몃え 媛쒕?\n\n\"?꾧뎔??以鍮꾨? 留덉튂怨?吏꾧꺽???쒖옉?⑸땲??\"");
				ShowWindow( hWndDlg_battle_normal, SW_SHOWNORMAL );

				WaitDialog();

                return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
            hWndDlg_battle = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CBattle::BattleDefDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CBattle* pThis; 

	static HWND hradio1;
	static HWND hradio2;

	static int spe_attacking_index;
	static int selectedradio;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_BATTLE_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_BATTLE_RADIO2);
	
            return TRUE;
		case WM_GETPOINT:
			pThis = (CBattle *)lParam;

			return TRUE;
		case WM_GETINFO:
			spe_attacking_index = (int)lParam;
			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);
			selectedradio = 0;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDC_BATTLE_RADIO1:
				selectedradio = 0;
				return TRUE;
			case IDC_BATTLE_RADIO2:
				selectedradio = 1;
				return TRUE;
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_battle = NULL;

				CPlayer::strategy_def = selectedradio;

				// ?꾪닾 ?쒖옉
				BATTLE_IN_STATE = BATTLE_IN_BREAK;

				DWORD ThreadID;
				hthread = CreateThread(NULL, 0,ThreadBattle, (LPVOID)NULL, 0, &ThreadID);

                return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;
        case WM_DESTROY:
            hWndDlg_battle = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CBattle::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static HWND temp_hDlg = NULL;

	switch (msg)
    {
        case WM_INITDIALOG:
            {
            }
            return TRUE;
		case WM_GETINFO:
			temp_hDlg = (HWND)lParam;
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_battle_normal = NULL;
					//if(temp_hDlg)
					//	temp_hDlg = NULL;
					// 洹몃깷 ?ル뒓??
					if(hWndDlg_battle_result_att)
						hWndDlg_battle_result_att = NULL;
					if(hWndDlg_battle_result_def)
						hWndDlg_battle_result_def = NULL;
                    return TRUE;
            }
            break;
        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;
        case WM_DESTROY:
			hWndDlg_battle = NULL;
            break;
    }

    return FALSE;
}

INT_PTR CALLBACK CBattle::GameoverDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
    {
        case WM_INITDIALOG:
            {
            }
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;

					hWndDlg_gameover = NULL;

					DWORD ThreadID;
					hthread = CreateThread(NULL, 0,ThreadGameover, NULL, 0, &ThreadID);

                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				lpddsprimary->Blt(NULL,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             NULL,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_gameover = NULL;
            break;
    }

    return FALSE;
}
HWND CBattle::GetHwnDia_Battle()
{
	return hWndDlg_battle;
}
HWND CBattle::GetHwnDia_Battle_Normal()
{
	return hWndDlg_battle_normal;
}
HWND CBattle::GetHwnDia_Battle_Result_Att()
{
	return hWndDlg_battle_result_att;
}
HWND CBattle::GetHwnDia_Battle_Result_Def()
{
	return hWndDlg_battle_result_def;
}
int CBattle::Save()
{
	WriteFile(hfile, &battle, sizeof(battle), &dwWritten, NULL);

	return 1;
}
int CBattle::Load()
{
	ReadFile(hfile, &battle, sizeof(battle), &dwWritten, NULL);

	return 1;
}
int CBattle::Battle_Shutdown()
{

	return 1;
}
