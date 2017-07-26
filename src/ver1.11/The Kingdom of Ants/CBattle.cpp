
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
		Load_Bitmap_File(&dirt, "art/etc/전투연기.bmp");
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
							sprintf(buffer,"개체수 : (아군)%d vs (적군)%d", 
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
								sprintf(buffer,"공격 타입 :   자원약탈");
							if(CPlayer::strategy_att == 1)
								sprintf(buffer,"공격 타입 :     일반");
							if(CPlayer::strategy_att == 2)
								sprintf(buffer,"공격 타입 :     정복");
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
								sprintf(buffer,"방어 타입 :       농성");
							if(CSpecies::speciesarray[temp_index].strategy_def == 1)
								sprintf(buffer,"방어 타입 :	      요격");
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
				sprintf(buffer,"개체수 : (아군)%d vs (적군)%d", 
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
					sprintf(buffer,"공격 타입 :   자원약탈");
				if(CSpecies::speciesarray[temp_index].strategy_att == 1)
					sprintf(buffer,"공격 타입 :       일반");
				if(CSpecies::speciesarray[temp_index].strategy_att == 2)
					sprintf(buffer,"공격 타입 :       정복");
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
					sprintf(buffer,"방어 타입 :       농성");
				if(CPlayer::strategy_def == 1)
					sprintf(buffer,"방어 타입 :       요격");
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
		sprintf(buffer, "참모 개미\n\n\" '민달팽이'종을 공격하려 합니다. 어떤 공격 전략을 사용하시겠습니까?\"");
	if(selectedindex == SPEARRAY_GRASSHOPPER)
		sprintf(buffer, "참모 개미\n\n\" '메뚜기'종을 공격하려 합니다. 어떤 공격 전략을 사용하시겠습니까?\"");
	if(selectedindex == SPEARRAY_SHORT_ANT)
		sprintf(buffer, "참모 개미\n\n\" '난쟁이개미'종을 공격하려 합니다. 어떤 공격 전략을 사용하시겠습니까?\"");
	if(selectedindex == SPEARRAY_BEE)
		sprintf(buffer, "참모 개미\n\n\" '꿀벌'종을 공격하려 합니다. 어떤 공격 전략을 사용하시겠습니까?\"");
	if(selectedindex == SPEARRAY_RED_ANT)
		sprintf(buffer, "참모 개미\n\n\" '불개미'종을 공격하려 합니다. 어떤 공격 전략을 사용하시겠습니까?\"");
	SetDlgItemTextA(hWndDlg_battle, IDC_STATIC_BATTLE, buffer);
	ShowWindow(hWndDlg_battle, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CBattle::SpeDecideAttack()
{
	// 쳅터 1에서 겨울의 1/2이 지나야 공격해온다.
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

	// 어떤 종족도 플레이어를 공격하지 않았다면
	if(CSpecies::spe_attacking_index == -1)
	{
		for(int i=0; i<MAX_SPECIES; i++)
		{
			temp_attatck = 0;		// 공격을 결정하기 위한 변수

			// 지금 전쟁중이면 플레이어를 공격하지 않는다.
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_BATTLE)
				continue;

			// 플레이어에게 종속되어 있다면 공격하지 않는다.
			if(CSpecies::speciesarray[i].state == SPECIES_STATE_OCCUPIED)
				continue;

			// 관계와 세력차이에 따른
			if(CSpecies::speciesarray[i].Disalbed == FALSE)
			{
				// 동맹이면 공격 안함
				if(CSpecies::speciesarray[i].relation > 40000)
					continue;

				// 관계에 따른
				temp_relation = CSpecies::speciesarray[i].relation;
				temp_attatck -= (temp_relation/100 - 250)/2;

				// 세력 차이에 따른
				temp_strength = CPlayer::strength - CSpecies::speciesarray[i].strength;
				temp_attatck -= temp_strength/500;
			}
			else
				continue;

			// 계절에 따른
			if(time_.GetSeason() == SPRING)
				temp_attatck += 70;
			if(time_.GetSeason() == SUMMER)
				temp_attatck += 90;
			if(time_.GetSeason() == FALL)
				temp_attatck += 70;
			if(time_.GetSeason() == WINTER)
				temp_attatck += 30;

			// 플레이어의 주둔군에 따른
			temp_attatck -= CPlayer::num_soldier_defence/10;
			temp_attatck -= CPlayer::num_hired_defence/3;

			// 플레이어의 공격에 따른
			if(CSpecies::spe_attacked_index == i)
			{
				temp_attatck -= (CPlayer::num_soldier_attack/3
							 + CPlayer::num_hired_attack);
			}
			
			// 전체적 공격 성향에 따른
			temp_attatck *= CSpecies::speciesarray[i].attempt_to_attck;

			// 결정
			if(temp_attatck > 0)
			{
				temp_random = (rand()%RAND_MAX)*10;
				// temp_attack이 temp_random보다 커야 실제로 공격 결정
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

					// 관계 악화
					if(CSpecies::speciesarray[i].strategy_att == 0)
						diplomatic_.ChangeRelation(i, -5000);
					if(CSpecies::speciesarray[i].strategy_att == 1)
						diplomatic_.ChangeRelation(i, -7000);
					if(CSpecies::speciesarray[i].strategy_att == 2)
						diplomatic_.ChangeRelation(i, -9000);

					// 공격할 개체 수
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
						// 초반에는 공격하는 수에 제한을 둔다.
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

	// 전투연기의 위치를 잡는다.
	battle_dirt2.x = object_.objarray[temp_index].objrect.left;
	battle_dirt2.y = object_.objarray[temp_index].objrect.top;

	// 전략 ///////////////////////////////////////////
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

	// 확률대로 전투나 자원약탈이 발생한다. 
	temp_rand = 1 +rand()%10;
	if(temp_rand <= temp_pro_attack)
	{
		//************* 전투 *************//

		// 보너스에 따른 ///////////////////////////////////////////////////
		temp_attack += temp_attack_bonus;
		temp_defence += temp_defence_bonus;

		// 계절 패널티에 따른 //////////////////////////////////////////////
		if(time_.GetSeason() == SPRING)
			temp_attack -= 0.2;
		if(time_.GetSeason() == SUMMER)
			temp_attack -= 0.1;
		if(time_.GetSeason() == FALL)
			temp_attack -= 0.2;
		if(time_.GetSeason() == WINTER)
			temp_attack -= 0.4;

		// 수에 따른 ////////////////////////////////////////////////////////
		temp_attack *= battle.player_cur_num_att/NUM_CIPHER;
		temp_defence *= battle.spe_cur_num_def/NUM_CIPHER;

		// 파워에 따른 //////////////////////////////////////////////////////
		temp_attack *= (((float)battle.player_cur_num_soldier_att/battle.player_cur_num_att*POWER_SOLDIER_ANT)
			+ ((float)battle.player_cur_num_hired_att/battle.player_cur_num_att*battle.power_hired_att));
		temp_defence *= CSpecies::speciesarray[temp_index].power;

		// 기타 /////////////////////////////////////////////////////////////
		if(objdialog_.labflag & LAB_1_DONE)
			temp_attack += ((float)battle.player_cur_num_soldier_att/NUM_CIPHER*DEMAGE_UPGRADE_LAB);

		if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
			temp_attack += ((float)battle.player_cur_num_soldier_att/NUM_CIPHER*DEMAGE_UPGRADE_TRAINING);

		if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
			temp_attack *= 1.1;

		if(item_.GetItem(4) == PLAYER)
			temp_attack *= 1.1;

		// 운에 따른 ////////////////////////////////////////////////////////
		temp_attack *= (1.0 - rand()%5/10.0 + 0.2);
		temp_defence *= (1.0 - rand()%5/10.0 + 0.2);

		// 전투 결과 ///////////////////////////////////////////////////
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

		// 컴퓨터의 피해만큼 세력을 줄인다.
		if(temp_str_def == 0)
			CSpecies::speciesarray[temp_index].strength_damege += temp_attack*1.9;
		else
			CSpecies::speciesarray[temp_index].strength_damege += temp_attack*1.2;
	}
	else
	{
		//************ 자원약탈 ************//

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

	//********** 결과(승리, 후퇴 등) ***********//

	battle.player_attack_time++;
	debug_.GetValue("time", &battle.player_attack_time, 0, lpddsback, 12, ONLY_V1);
	if(temp_str_att == 0)
	{
		if((battle.player_attack_time == 40)
			|| (GETPERCENT(battle.player_cur_num_att, battle.player_init_num_att) <= 66))
		{
			PlayerComeBackInit(temp_index);
			diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_NORMAL);

			sprintf(buffer, "참모 개미\n\n\"원정을 나갔던 아군이 귀환을 시작했습니다.\"");
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

			sprintf(buffer, "참모 개미\n\n\"원정을 나갔던 아군이 귀환을 시작했습니다.\"");
			ShowNorDialog(buffer);

			WaitDialog();
		}
	}

	// 플레이어의 병사 전멸
	if(battle.player_cur_num_att <= 0)
	{
		BATTLE_OUT_STATE = BATTLE_OUT_NO;

		sprintf(buffer, "참모 개미\n\n\"원정을 나갔던 아군이 전멸했습니다.\"");
		ShowNorDialog(buffer);

		diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_NORMAL);

		CPlayer::remain_return_time = 0;
		CSpecies::spe_attacked_index = -1;
		diplomatic_.EnableDipAtt();
	}

	// 점령
	if(battle.spe_cur_num_def <= 0)
	{
		// 아이템 확인 창을 먼저 뛰우고 다음 내용을 그 위에 뛰운다.
		item_.TakeItemFromSpe(temp_index);

		PlayerComeBackInit(temp_index);
		// 종족 상태을 '종속'으로 바꾼다. 1일마다 조공을 바친다.
		diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_OCCUPIED);

		// 정복당한 종족의 세력을 반으로
		diplomatic_.ChangeSpeStrength(temp_index, -CSpecies::speciesarray[temp_index].strength/2);

		sprintf(buffer, "참모 개미\n\n\"기뻐하십시오, 여왕이시어. 원정을 나갔던 우리의 병사가 승전보를 "
						"알려왔습니다. 앞으로 그들은 우리에게 조공을 보내오게 될 것입니다.\"");
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

	// 전략 ///////////////////////////////////////////
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

	// 확률대로 전투나 자원약탈이 발생한다. 
	temp_rand = 1 +rand()%10;
	if(temp_rand <= temp_pro_attack)
	{
		//************* 전투 *************//

		// 보너스에 따른 ///////////////////////////////////////////////////
		temp_attack += temp_attack_bonus;
		temp_defence += temp_defence_bonus;

		// 계절 패널티에 따른 //////////////////////////////////////////////
		if(time_.GetSeason() == SPRING)
			temp_attack -= 0.2;
		if(time_.GetSeason() == SUMMER)
			temp_attack -= 0.1;
		if(time_.GetSeason() == FALL)
			temp_attack -= 0.2;
		if(time_.GetSeason() == WINTER)
			temp_attack -= 0.4;

		// 수에 따른 ////////////////////////////////////////////////////////
		temp_defence *= battle.player_cur_num_def/NUM_CIPHER;
		temp_attack *= battle.spe_cur_num_att/NUM_CIPHER;

		// 파워에 따른 //////////////////////////////////////////////////////
		temp_defence *= (((float)battle.player_cur_num_soldier_def/battle.player_cur_num_def*POWER_SOLDIER_ANT)
			+ ((float)battle.player_cur_num_hired_def/battle.player_cur_num_def*battle.power_hired_def));
		temp_attack *= CSpecies::speciesarray[temp_index].power;

		// 기타 /////////////////////////////////////////////////////////////

		// 고농축 개미산
		if(objdialog_.labflag & LAB_1_DONE)
			temp_defence += ((float)battle.player_cur_num_soldier_def/NUM_CIPHER*DEMAGE_UPGRADE_LAB);

		// 전투 훈련실
		if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
			temp_defence += ((float)battle.player_cur_num_soldier_def/NUM_CIPHER*DEMAGE_UPGRADE_TRAINING);

		// 예술의 전당
		if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
			temp_defence *= 1.1;

		// 절대반지
		if(item_.GetItem(4) == PLAYER)
			temp_defence *= 1.1;
		
		// 불을 이용
		if(objdialog_.labflag & LAB_10_DONE)
		{
			temp_defence *= 1.2;
			domestic_.ChangeResource(-rand()%30,
									 -rand()%70,
									 -rand()%15);
			CPlayer::strength_damege += rand()%15;

		}

		// 운에 따른 ////////////////////////////////////////////////////////
		temp_attack *= (1.0 - rand()%5/10.0 + 0.2);
		temp_defence *= (1.0 - rand()%5/10.0 + 0.2);

		// 전투 결과 ///////////////////////////////////////////////////
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

		// 컴퓨터의 피해만큼 세력을 줄인다.
		CSpecies::speciesarray[temp_index].strength_damege += temp_defence*1.5;

		// 농성을 하면 서식처에 피해를 입고 개체들의 불만이 쌓인다.
		if(temp_str_def == 0)
		{
			CPlayer::strength_damege += temp_attack/3;
			domestic_.ChangeUnsatisfactory(temp_attack*4);
		}
	}
	else
	{
		//************ 자원약탈 ************//

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

	//********** 결과(승리, 후퇴 등) ***********//

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

	// 플레이어의 병사 전멸
	if(battle.player_cur_num_def <= 0)
	{
		CloseAllDialog();

		CTime::SetPause();

		if(hWndDlg_gameover)
			EndDialog(hWndDlg_gameover, TRUE );
		hWndDlg_gameover = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_GAMEOVER),
			main_window_handle,  (DLGPROC)GameoverDlgProc );
		SetDlgItemTextA(hWndDlg_gameover, IDC_STATIC_GAMEOVER, 
			"알림\n\n전투 가능한 병사들이 전멸했습니다. "
			"칩입자들은 왕국을 완전히 파괴했습니다.  암개미 1호의 "
			"왕국은 역사의 뒤안길로 사라졌습니다.");
		ShowWindow(hWndDlg_gameover, SW_SHOWNORMAL );

		WaitDialog();

		return 0;
	}

	// 컴퓨터의 병사 전멸
	if(battle.spe_cur_num_att <= 0)
	{
		SpeGoBackInit(temp_index);

		ShowDefResDialog(temp_index);

		sprintf(buffer, "참모 개미\n\n\"아군이 적군을 섬멸했습니다. 다음은 이번 전투의 보고서입니다.\"");
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
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "지역 : 민달팽이 서식처");
	if(SPEARRAY_INDEX == SPEARRAY_GRASSHOPPER)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "지역 : 메뚜기 서식처");
	if(SPEARRAY_INDEX == SPEARRAY_SHORT_ANT)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "지역 : 난쟁이개미 굴");
	if(SPEARRAY_INDEX == SPEARRAY_BEE)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "지역 : 꿀벌 집");
	if(SPEARRAY_INDEX == SPEARRAY_RED_ANT)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLACE, "지역 : 불개미 굴");
	if(CPlayer::strategy_att == 0)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "공격 전략 : 자원 약탈");
	if(CPlayer::strategy_att == 1)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "공격 전략 : 일반");
	if(CPlayer::strategy_att == 2)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_ATT, "공격 전략 : 정복");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_def == 0)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_DEF, "방어 전략 : 농성");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_def == 1)
		SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_STR_DEF, "방어 전략 : 요격");
	sprintf(buffer, "아군 피해 : 사망 %d",
		(battle.player_init_num_att - battle.player_cur_num_att) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_PLAYER_DEM, buffer);
	sprintf(buffer, "적군 피해 : 사망 %d",
		(battle.spe_init_num_def - battle.spe_cur_num_def) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_SPE_DEM, buffer);
	sprintf(buffer, "자원 약탈\n\n식량 : %d\n목재 : %d\n광석 : %d",
		battle.num_food_get/NUM_CIPHER,
		battle.num_timber_get/NUM_CIPHER,
		battle.num_mineral_get/NUM_CIPHER);
	SetDlgItemTextA(hWndDlg_battle_result_att, IDC_STATIC_RESOURCE, buffer);
	SendMessage(hWndDlg_battle_result_att, WM_GETINFO, NULL, (LPARAM)hWndDlg_battle_result_att);
	ShowWindow( hWndDlg_battle_result_att, SW_SHOWNORMAL );

	WaitDialog();

	sprintf(buffer, "참모 개미\n\n\"이번 전투의 보고서입니다.\"");
	ShowNorDialog(buffer);

	return 1;
}
int CBattle::ShowDefResDialog(int SPEARRAY_INDEX)
{
	if(hWndDlg_battle_result_def)
		EndDialog( hWndDlg_battle_result_def, TRUE );
	hWndDlg_battle_result_def = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_RESULT),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_PLACE, "지역 : 암개미 1호의 굴");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 0)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "공격 전략 : 자원 약탈");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 1)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "공격 전략 : 일반");
	if(CSpecies::speciesarray[SPEARRAY_INDEX].strategy_att == 2)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_ATT, "공격 전략 : 정복");
	if(CPlayer::strategy_def == 0)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_DEF, "방어 전략 : 농성");
	if(CPlayer::strategy_def == 1)
		SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_STR_DEF, "방어 전략 : 요격");
	if(battle.player_join == TRUE)
	{
		sprintf(buffer, "아군 피해 : 사망 %d",
		(battle.player_init_num_def - battle.player_cur_num_def + battle.player_cur_num_att) 
			/ NUM_CIPHER);	
		battle.player_join = FALSE;
	}
	else
		sprintf(buffer, "아군 피해 : 사망 %d",
		(battle.player_init_num_def - battle.player_cur_num_def) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_PLAYER_DEM, buffer);
	sprintf(buffer, "적군 피해 : 사망 %d",
		(battle.spe_init_num_att - battle.spe_cur_num_att) / NUM_CIPHER);	
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_SPE_DEM, buffer);
	sprintf(buffer, "자원 피해\n\n식량 : %d\n목재 : %d\n광석 : %d",
		battle.num_food_lost/NUM_CIPHER,
		battle.num_timber_lost/NUM_CIPHER,
		battle.num_mineral_lost/NUM_CIPHER);
	SetDlgItemTextA(hWndDlg_battle_result_def, IDC_STATIC_RESOURCE, buffer);
	SendMessage(hWndDlg_battle_result_def, WM_GETINFO, NULL, (LPARAM)hWndDlg_battle_result_def);
	ShowWindow( hWndDlg_battle_result_def, SW_SHOWNORMAL );

	WaitDialog();

	sprintf(buffer, "참모 개미\n\n\"적군이 후퇴하기 시작했습니다. 다음은 이번 전투의 보고서입니다.\"");
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

				sprintf(buffer, "참모 개미\n\n\"원정을 나갔던 아군이 전투에 돌입했습니다.\"");
				ShowNorDialog(buffer);

				WaitDialog();

				// 전투 시작
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

				sprintf(buffer, "참모 개미\n\n\" '%s'종의 병사가 접근중입니다. 약 %d일 후에 도착할 "
								"것으로 보입니다.\"",
						CSpecies::speciesarray[temp_index].name,
						CSpecies::speciesarray[temp_index].remain_reach_time/UNIT_PER_TICK/UNIT_PER_DAY);
				ShowNorDialog(buffer);

				WaitDialog();
			}
			if(CSpecies::speciesarray[temp_index].remain_reach_time == 0)
			{
				BattleIn_Init();

				// 모든 창 닫기
				CloseAllDialog(EXCEPT_BATTLE);
				
				CTime::SetPause();

				// 방어 전략 수립
				if(hWndDlg_battle)
					EndDialog(hWndDlg_battle, TRUE );
				hWndDlg_battle = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BATTLE_DEFENCE),
					main_window_handle,  (DLGPROC)BattleDefDlgProc );
				SendMessage(hWndDlg_battle, WM_GETINFO, 0, (LPARAM)temp_index);
				SendMessage(hWndDlg_battle, WM_GETPOINT, 0, (LPARAM)this);
				if(temp_index == SPEARRAY_SNAIL)
					sprintf(buffer, "참모 개미\n\n\" '민달팽이'종이 우리 왕국을 공격해오고 있습니다. 어떤 방어 전략을 사용하시겠습니까?\"");
				if(temp_index == SPEARRAY_GRASSHOPPER)
					sprintf(buffer, "참모 개미\n\n\" '메뚜기'종이 우리 왕국을 공격해오고 있습니다. 어떤 방어 전략을 사용하시겠습니까?\"");
				if(temp_index == SPEARRAY_SHORT_ANT)
					sprintf(buffer, "참모 개미\n\n\" '난쟁이개미'종이 우리 왕국을 공격해오고 있습니다. 어떤 방어 전략을 사용하시겠습니까?\"");
				if(temp_index == SPEARRAY_BEE)
					sprintf(buffer, "참모 개미\n\n\" '꿀벌'종이 우리 왕국을 공격해오고 있습니다. 어떤 방어 전략을 사용하시겠습니까?\"");
				if(temp_index == SPEARRAY_RED_ANT)
					sprintf(buffer, "참모 개미\n\n\" '불개미'종이 우리 왕국을 공격해오고 있습니다. 어떤 방어 전략을 사용하시겠습니까?\"");
				SetDlgItemTextA(hWndDlg_battle, IDC_STATIC_BATTLE, buffer);
				ShowWindow(hWndDlg_battle, SW_SHOWNORMAL );

				WaitDialog();

				// 전투 준비
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

				// 원정군 해산
				domestic_.ReturnFromBattle();

				// 귀환했는데 암개미 1호의 굴에서 전투중이라면 합류
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
				// 귀환한 컴퓨터의 병력 해산
				CSpecies::speciesarray[temp_index].num_attack = 0;

				CSpecies::spe_attacking_index = -1;
			}
		}
	}

	return 1;
}
int CBattle::ReturnFromBattle()
{
	// 암개미 1호 궁에서 일어나는 전투에 추가
	battle.player_cur_num_def += battle.player_cur_num_att;
	battle.player_join = TRUE;

	sprintf(buffer, "참모 개미\n\n\"원정을 나갔던 아군이 합류했습니다. 다음은 이번 전투의 보고서입니다.\"");
	ShowNorDialog(buffer);

	return 1;
}
int CBattle::BattleOut_Init()
{
	int temp_rand;
	int temp_index;

	// 전투 준비
	temp_index = CSpecies::spe_attacked_index;

	// 약탈자원 초기화
	battle.num_food_get = 0;
	battle.num_timber_get = 0;
	battle.num_mineral_get = 0;

	// 컴퓨터의 수비군을 정한다.
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

	// 전투 상태로
	diplomatic_.ChangeSpeState(temp_index, SPECIES_STATE_BATTLE);

	// 전투 시간 초기화
	battle.player_attack_time = 0;

	// 군사수 초기화
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

	// 용병의 종류에 따른 파워를 초기화한다.
	if(building_.buildingarray[BUILDINGARRAY_HIRED_1].bexist == TRUE)
		battle.power_hired_att = POWER_HIRED_1_ATT;
	if(building_.buildingarray[BUILDINGARRAY_HIRED_2].bexist == TRUE)
		battle.power_hired_att = POWER_HIRED_2_ATT;

	// 컴퓨터의 방어 전략을 정한다.
	if((CPlayer::strength-CSpecies::speciesarray[temp_index].strength) > 0)
	{
		// 플레이어의 세력이 더 강하면 농성의 비율이 높아진다.
		temp_rand = rand()%5;
		if(temp_rand <= 2)
			CSpecies::speciesarray[temp_index].strategy_def = 0;
		else
			CSpecies::speciesarray[temp_index].strategy_def = 1;
	}
	else
	{
		// 그렇지 않다면 확률은 반반이다.
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

	// 전투 준비
	temp_index = CSpecies::spe_attacking_index;

	// 약탈자원 초기화
	battle.num_food_lost = 0;
	battle.num_timber_lost = 0;
	battle.num_mineral_lost = 0;

	// 전투 시간 초기화
	battle.player_defence_time = 0;

	// 군사수 초기화
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

	// 용병의 종류에 따른 파워를 초기화한다.
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
		sprintf(buffer,"전쟁 발발중");
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
		sprintf(buffer,"적군이 접근중");
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
		sprintf(buffer,"아군이 진격중");
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
		sprintf(buffer,"아군이 귀환중");
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
	
	// 마무리와 초기화할 시간동안
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

				// 해당 종족과의 관계 악화
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
				SetDlgItemTextA(hWndDlg_battle_normal, IDC_NORMAL, "참모 개미\n\n\"아군이 준비를 마치고 진격을 시작합니다.\"");
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

				// 전투 시작
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
					// 그냥 닫느다.
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
