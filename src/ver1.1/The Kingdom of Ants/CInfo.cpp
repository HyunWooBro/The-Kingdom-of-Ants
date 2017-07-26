
#include <stdio.h>
#include "CInfo.h"
#include "CPlayer.h"
#include "CSpecies.h"
#include "CItem.h"
#include "CDomestic.h"
#include "CObjDialog.h"
#include "CBuilding.h"

extern CItem item_;
extern CBuilding building_;
extern CObjDialog objdialog_;
extern CDomestic domestic_;

int CInfo::Info_Init()
{	
	ZeroMemory(&stack_produce_food, sizeof(stack_produce_food));
	ZeroMemory(&stack_cost_food, sizeof(stack_cost_food));
	ZeroMemory(&stack_produce_timber, sizeof(stack_produce_timber));
	ZeroMemory(&stack_cost_timber, sizeof(stack_cost_timber));
	ZeroMemory(&stack_produce_mineral, sizeof(stack_produce_mineral));
	ZeroMemory(&stack_cost_mineral, sizeof(stack_cost_mineral));

	return 1;
}

int CInfo::PrintGmaeInfo()
{
	if(SCREEN_STATE == SCREEN_GAMEINFO)
	{
		PrintKingdomInfo();

		PrintResource();

		PrintBattle();

		PrintNumAnts();

		PrintSpecies();

		PrintOther();
	}

	return 1;
}

int CInfo::PrintKingdomInfo()
{
	DDRAW_TEXT_GAMEINFO("왕국", S1_R1, S_C1, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("세력", S1_R2, S_C1, RGB(255,255,255), TA_LEFT);
		sprintf(buffer, "%d", CPlayer::strength/NUM_CIPHER);
		DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1, RGB(255,255,255), TA_RIGHT);

		DDRAW_TEXT_GAMEINFO("영향력", S1_R2, S_C1+15*1, RGB(255,255,255), TA_LEFT);
		sprintf(buffer, "%d%%", CPlayer::occupation);
		DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*1, RGB(255,255,255), TA_RIGHT);

		DDRAW_TEXT_GAMEINFO("불만", S1_R2, S_C1+15*2, RGB(255,255,255), TA_LEFT);
		sprintf(buffer, "%.1f%%", GETPERCENT(CPlayer::unsatisfactory, MAX_UNSATISFACTORY));
		if((int)GETPERCENT(CPlayer::unsatisfactory, MAX_UNSATISFACTORY) >= 75)
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*2, RGB(255,0,0), TA_RIGHT);
		else if((int)GETPERCENT(CPlayer::unsatisfactory, MAX_UNSATISFACTORY) >= 50)
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*2, RGB(255,255,0), TA_RIGHT);
		else
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*2, RGB(255,255,255), TA_RIGHT);
	}

	return 1;
}
int CInfo::PrintResource()
{
	float temp_resource;

	DDRAW_TEXT_GAMEINFO("자원", S1_R1, S_C1+15*5, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("식량", S1_R2, S_C1+15*5, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("일일 생산량", S1_R2+10*1, S_C1+15*6, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_produce_food[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*6, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("일일 소비량", S1_R2+10*1, S_C1+15*7, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_cost_food[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*7, RGB(255,255,255), TA_RIGHT);
		}

		DDRAW_TEXT_GAMEINFO("목재", S1_R2, S_C1+15*8, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("일일 생산량", S1_R2+10*1, S_C1+15*9, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_produce_timber[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*9, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("일일 소비량", S1_R2+10*1, S_C1+15*10, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_cost_timber[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*10, RGB(255,255,255), TA_RIGHT);
		}

		DDRAW_TEXT_GAMEINFO("광석", S1_R2, S_C1+15*11, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("일일 생산량", S1_R2+10*1, S_C1+15*12, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_produce_mineral[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*12, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("일일 소비량", S1_R2+10*1, S_C1+15*13, RGB(255,255,255), TA_LEFT);
			temp_resource = 0;
			for(int i=0 ;i<UNIT_PER_DAY*UNIT_PER_TICK; i++)
				temp_resource += stack_cost_mineral[i];
			temp_resource /= NUM_CIPHER;
			sprintf(buffer, "%.1f", temp_resource);
			DDRAW_TEXT_GAMEINFO(buffer, S1_R3, S_C1+15*13, RGB(255,255,255), TA_RIGHT);
		}
	}
	return 1;
}
int CInfo::PrintBattle()
{
	char *temp_text;
	DWORD temp_color;
	int temp_power = 0;
	int temp_index;

	DDRAW_TEXT_GAMEINFO("전투", S1_R1, S_C1+15*16, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("원정", S1_R2, S_C1+15*16, RGB(255,255,255), TA_LEFT);
		temp_index = CSpecies::spe_attacked_index;
		if(CPlayer::remain_return_time > 0)
		{	
			temp_text = "귀환하는 중";
		}
		else
		{
			if(temp_index == -1)
				temp_text = "없음";
			else
				temp_text = CSpecies::speciesarray[temp_index].name;
		}
		DDRAW_TEXT_GAMEINFO(temp_text ,S1_R3, S_C1+15*16, RGB(255,255,255), TA_RIGHT);

		DDRAW_TEXT_GAMEINFO("남은 기간", S1_R2, S_C1+15*17, RGB(255,255,255), TA_LEFT);
		if(CPlayer::remain_reach_time > 0)
			sprintf(buffer, "%d일", CPlayer::remain_reach_time/UNIT_PER_DAY/UNIT_PER_TICK);
		else if(CPlayer::remain_return_time > 0)
			sprintf(buffer, "%d일", CPlayer::remain_return_time/UNIT_PER_DAY/UNIT_PER_TICK);
		else
			sprintf(buffer, "0일");
		DDRAW_TEXT_GAMEINFO(buffer ,S1_R3, S_C1+15*17, RGB(255,255,255), TA_RIGHT);

		DDRAW_TEXT_GAMEINFO("전투력", S1_R2, S_C1+15*18, RGB(255,255,255), TA_LEFT);
		// 고농축 개미산
		if(objdialog_.labflag & LAB_1_DONE)
			temp_power++;
		// 전투 훈련실
		if(building_.buildingarray[BUILDINGARRAY_TRAINING].bexist == TRUE)
			temp_power++;
		// 예술의 전당
		if(building_.buildingarray[BUILDINGARRAY_ART].bexist == TRUE)
			temp_power++;
		// 절대반지
		if(item_.GetItem(4) == PLAYER)
			temp_power++;
		if(temp_power == 0)
		{
			temp_text = "매우 약함";
			temp_color = RGB(255,0,0);
		}
		else if(temp_power == 1)
		{
			temp_text = "약함";
			temp_color = RGB(255,255,0);
		}
		else if(temp_power == 2)
		{
			temp_text = "보통";
			temp_color = RGB(255,255,255);
		}
		else if(temp_power == 3)
		{
			temp_text = "강함";
			temp_color = RGB(50,255,50);
		}
		else if(temp_power == 4)
		{
			temp_text = "매우 강함";
			temp_color = RGB(0,255,255);
		}
		DDRAW_TEXT_GAMEINFO(temp_text ,S1_R3, S_C1+15*18, temp_color, TA_RIGHT);
	}

	

	return 1;
}
int CInfo::PrintNumAnts()
{
	DDRAW_TEXT_GAMEINFO("개체수", S2_R1, S_C1, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("총 개체수", S2_R2, S_C1, RGB(0,0,255), TA_LEFT);
		sprintf(buffer, "%d", CPlayer::num_ants_total);
		DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1, RGB(255,255,255), TA_RIGHT);
		{
			DDRAW_TEXT_GAMEINFO("일꾼개미 수", S2_R2+10*1, S_C1+15*1, RGB(50,255,50), TA_LEFT);
			sprintf(buffer, "%d", CPlayer::num_worker_total);
			DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*1, RGB(255,255,255), TA_RIGHT);
			{
				DDRAW_TEXT_GAMEINFO("수색", S2_R2+10*2, S_C1+15*2, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_worker_search);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*2, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("건설", S2_R2+10*2, S_C1+15*3, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_worker_building);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*3, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("버섯재배", S2_R2+10*2, S_C1+15*4, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_worker_mushroom);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*4, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("진딧물사육", S2_R2+10*2, S_C1+15*5, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_worker_aphid);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*5, RGB(255,255,255), TA_RIGHT);
			}

			DDRAW_TEXT_GAMEINFO("병정개미 수", S2_R2+10*1, S_C1+15*6, RGB(50,255,50), TA_LEFT);
			sprintf(buffer, "%d", CPlayer::num_soldier_total);
			DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*6, RGB(255,255,255), TA_RIGHT);
			{
				DDRAW_TEXT_GAMEINFO("사냥", S2_R2+10*2, S_C1+15*7, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_soldier_hunt);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*7, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("주둔군", S2_R2+10*2, S_C1+15*8, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_soldier_defence);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*8, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("원정군", S2_R2+10*2, S_C1+15*9, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_soldier_attack);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*9, RGB(255,255,255), TA_RIGHT);
			}

			DDRAW_TEXT_GAMEINFO("용병 수", S2_R2+10*1, S_C1+15*10, RGB(50,255,50), TA_LEFT);
			sprintf(buffer, "%d", CPlayer::num_hired_total);
			DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*10, RGB(255,255,255), TA_RIGHT);
			{
				DDRAW_TEXT_GAMEINFO("주둔군", S2_R2+10*2, S_C1+15*11, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d",CPlayer::num_hired_defence);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*11, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("원정군", S2_R2+10*2, S_C1+15*12, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CPlayer::num_hired_attack);
				DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*12, RGB(255,255,255), TA_RIGHT);
			}
		}

		DDRAW_TEXT_GAMEINFO("알 분배", S2_R2, S_C1+15*13, RGB(0,0,255), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("일꾼개미 알", S2_R2+10*1, S_C1+15*14, RGB(255,255,255), TA_LEFT);
			sprintf(buffer, "%d", MAX_PANEL-domestic_.domarray[2].panel[0]);
			DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*14, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("병정개미 알", S2_R2+10*1, S_C1+15*15, RGB(255,255,255), TA_LEFT);
			sprintf(buffer, "%d", domestic_.domarray[2].panel[0]);
			DDRAW_TEXT_GAMEINFO(buffer, S2_R3, S_C1+15*15, RGB(255,255,255), TA_RIGHT);
		}
	}

	return 1;
}
int CInfo::PrintSpecies()
{
	DDRAW_TEXT_GAMEINFO("외교", S3_R1, S_C1, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("민달팽이", S3_R2, S_C1, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("세력", S3_R2+10*1, S_C1+15*1, RGB(255,255,255), TA_LEFT);
			sprintf(buffer, "%d", CSpecies::speciesarray[0].strength/NUM_CIPHER);
			DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*1, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("관계", S3_R2+10*1, S_C1+15*2, RGB(255,255,255), TA_LEFT);
			PrintRelationText(0, S3_R3, S_C1+15*2);
		}

		DDRAW_TEXT_GAMEINFO("메뚜기", S3_R2, S_C1+15*3, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("세력", S3_R2+10*1, S_C1+15*4, RGB(255,255,255), TA_LEFT);
			sprintf(buffer, "%d", CSpecies::speciesarray[1].strength/NUM_CIPHER);
			DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*4, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("관계", S3_R2+10*1, S_C1+15*5, RGB(255,255,255), TA_LEFT);
			PrintRelationText(1, S3_R3, S_C1+15*5);
		}

		DDRAW_TEXT_GAMEINFO("난쟁이개미", S3_R2, S_C1+15*6, RGB(50,255,50), TA_LEFT);
		{
			DDRAW_TEXT_GAMEINFO("세력", S3_R2+10*1, S_C1+15*7, RGB(255,255,255), TA_LEFT);
			sprintf(buffer, "%d", CSpecies::speciesarray[2].strength/NUM_CIPHER);
			DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*7, RGB(255,255,255), TA_RIGHT);

			DDRAW_TEXT_GAMEINFO("관계", S3_R2+10*1, S_C1+15*8, RGB(255,255,255), TA_LEFT);
			PrintRelationText(2, S3_R3, S_C1+15*8);
		}

		if(CSpecies::speciesarray[3].Disalbed == FALSE)
		{
			DDRAW_TEXT_GAMEINFO("꿀벌", S3_R2, S_C1+15*9, RGB(50,255,50), TA_LEFT);
			{
				DDRAW_TEXT_GAMEINFO("세력", S3_R2+10*1, S_C1+15*10, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CSpecies::speciesarray[3].strength/NUM_CIPHER);
				DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*10, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("관계", S3_R2+10*1, S_C1+15*11, RGB(255,255,255), TA_LEFT);
				PrintRelationText(3, S3_R3, S_C1+15*11);
			}
		}

		if(CSpecies::speciesarray[4].Disalbed == FALSE)
		{
			DDRAW_TEXT_GAMEINFO("불개미", S3_R2, S_C1+15*12, RGB(50,255,50), TA_LEFT);
			{
				DDRAW_TEXT_GAMEINFO("세력", S3_R2+10*1, S_C1+15*13, RGB(255,255,255), TA_LEFT);
				sprintf(buffer, "%d", CSpecies::speciesarray[4].strength/NUM_CIPHER);
				DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*13, RGB(255,255,255), TA_RIGHT);

				DDRAW_TEXT_GAMEINFO("관계", S3_R2+10*1, S_C1+15*14, RGB(255,255,255), TA_LEFT);
				PrintRelationText(4, S3_R3, S_C1+15*14);
			}
		}
	}

	return 1;
}

int CInfo::PrintOther()
{
	int temp_num = 0;

	DDRAW_TEXT_GAMEINFO("기타", S3_R1, S_C1+15*16, RGB(255,0,0), TA_LEFT);
	{
		DDRAW_TEXT_GAMEINFO("쳅터", S3_R2+10*1, S_C1+15*16, RGB(255,255,255), TA_LEFT);
		if(CHAPTER == CHAP_1)
			sprintf(buffer, "1장");
		if(CHAPTER == CHAP_2)
			sprintf(buffer, "2장");
		if(CHAPTER == CHAP_3)
			sprintf(buffer, "3장");
		if(CHAPTER == CHAP_4)
			sprintf(buffer, "4장");
		DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*16, RGB(255,255,255), TA_RIGHT);

		DDRAW_TEXT_GAMEINFO("아이템수집", S3_R2+10*1, S_C1+15*17, RGB(255,255,255), TA_LEFT);
		for(int i=0; i<MAX_ITEM; i++)
		{
			if(item_.GetItem(i) == PLAYER)
				temp_num++;
		}
		sprintf(buffer, "%d/%d", temp_num, MAX_ITEM);
		DDRAW_TEXT_GAMEINFO(buffer, S3_R3, S_C1+15*17, RGB(255,255,255), TA_RIGHT);

	}

	return 1;
}
int CInfo::ComputeResource(int resource_index, int value)
{
	if(resource_index == 0)
	{
		if(value >= 0)
			stack_produce_food[0] += value;
		else
			stack_cost_food[0] -= value;	
	}
	if(resource_index == 1)
	{
		if(value >= 0)
			stack_produce_timber[0] += value;
		else
			stack_cost_timber[0] -= value;	
	}
	if(resource_index == 2)
	{
		if(value >= 0)
			stack_produce_mineral[0] += value;
		else
			stack_cost_mineral[0] -= value;	
	}

	return value;
}
int CInfo::MoveStackMem()
{
	memmove(&stack_produce_food[1], &stack_produce_food[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	memmove(&stack_cost_food[1], &stack_cost_food[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	stack_produce_food[0] = 0;
	stack_cost_food[0] = 0;

	memmove(&stack_produce_timber[1], &stack_produce_timber[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	memmove(&stack_cost_timber[1], &stack_cost_timber[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	stack_produce_timber[0] = 0;
	stack_cost_timber[0] = 0;

	memmove(&stack_produce_mineral[1], &stack_produce_mineral[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	memmove(&stack_cost_mineral[1], &stack_cost_mineral[0], sizeof(int) * (UNIT_PER_DAY * UNIT_PER_TICK - 1));
	stack_produce_mineral[0] = 0;
	stack_cost_mineral[0] = 0;

	return 1;
}
int CInfo::PrintRelationText(int SPEARRAY_INDEX, int x, int y)
{
	char *temp_text;
	DWORD temp_color;

	if(CSpecies::speciesarray[SPEARRAY_INDEX].relation <= 10000)
	{
		temp_text = "험악";
		temp_color = RGB(255,0,0);
	}
	else if(CSpecies::speciesarray[SPEARRAY_INDEX].relation <= 20000)
	{
		temp_text = "불화";
		temp_color = RGB(255,255,0);
	}
	else if(CSpecies::speciesarray[SPEARRAY_INDEX].relation <= 30000)
	{
		temp_text = "중립";
		temp_color = RGB(255,255,255);
	}
	else if(CSpecies::speciesarray[SPEARRAY_INDEX].relation <= 40000)
	{
		temp_text = "호의";
		temp_color = RGB(50,255,50);
	}
	else if(CSpecies::speciesarray[SPEARRAY_INDEX].relation <= MAX_RELATION)
	{
		temp_text = "동맹";
		temp_color = RGB(0,255,255);
	}

	DDRAW_TEXT_GAMEINFO(temp_text , x, y, temp_color, TA_RIGHT);

	return 1;
}
int CInfo::Save()
{
	WriteFile(hfile, &stack_produce_food, sizeof(stack_produce_food), &dwWritten, NULL);
	WriteFile(hfile, &stack_cost_food, sizeof(stack_cost_food), &dwWritten, NULL);
	WriteFile(hfile, &stack_produce_timber, sizeof(stack_produce_timber), &dwWritten, NULL);
	WriteFile(hfile, &stack_cost_timber, sizeof(stack_cost_timber), &dwWritten, NULL);
	WriteFile(hfile, &stack_produce_mineral, sizeof(stack_produce_mineral), &dwWritten, NULL);
	WriteFile(hfile, &stack_cost_mineral, sizeof(stack_cost_mineral), &dwWritten, NULL);

	return 1;
}
int CInfo::Load()
{
	ReadFile(hfile, &stack_produce_food, sizeof(stack_produce_food), &dwWritten, NULL);
	ReadFile(hfile, &stack_cost_food, sizeof(stack_cost_food), &dwWritten, NULL);
	ReadFile(hfile, &stack_produce_timber, sizeof(stack_produce_timber), &dwWritten, NULL);
	ReadFile(hfile, &stack_cost_timber, sizeof(stack_cost_timber), &dwWritten, NULL);
	ReadFile(hfile, &stack_produce_mineral, sizeof(stack_produce_mineral), &dwWritten, NULL);
	ReadFile(hfile, &stack_cost_mineral, sizeof(stack_cost_mineral), &dwWritten, NULL);

	return 1;
}
int CInfo::Info_Shutdown()
{

	return 1;
}
