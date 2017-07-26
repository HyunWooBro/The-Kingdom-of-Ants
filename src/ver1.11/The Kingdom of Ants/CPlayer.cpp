
#include "CPlayer.h"

int CPlayer::occupation = 0;					
int CPlayer::strength = 0;					
int CPlayer::strength_time = 0;				
int CPlayer::strength_damege = 0;			
int CPlayer::unsatisfactory = 0;				

int CPlayer::num_ants_total = 0;				

int CPlayer::num_worker_total = 0;			
int CPlayer::num_worker_search = 0;			
int CPlayer::num_worker_building = 0;
int CPlayer::num_worker_mushroom = 0;
int CPlayer::num_worker_aphid = 0;

int CPlayer::num_soldier_total = 0;
int CPlayer::num_soldier_hunt = 0;
int CPlayer::num_soldier_defence = 0;
int CPlayer::num_soldier_attack = 0;

int CPlayer::num_hired_total = 0;
int CPlayer::num_hired_defence = 0;
int CPlayer::num_hired_attack = 0;

int CPlayer::search_produce_food = 0;
int CPlayer::hunt_produce_food = 0;
int CPlayer::mushroom_produce_food = 0;
int CPlayer::aphid_produce_food = 0;

int CPlayer::food = 0;
int CPlayer::foodgap = 0;					
int CPlayer::max_food = 0;

int CPlayer::timber = 0;
int CPlayer::timbergap = 0;					
int CPlayer::max_timber = 0;

int CPlayer::mineral = 0;
int CPlayer::mineralgap = 0;					
int CPlayer::max_mineral = 0;

int CPlayer::num_pro_food_per_day = 0;
int CPlayer::num_cos_food_per_day = 0;
int CPlayer::num_pro_timber_per_day = 0;
int CPlayer::num_cos_timber_per_day = 0;
int CPlayer::num_pro_mineral_per_day = 0;
int CPlayer::num_cos_mineral_per_day = 0;

int CPlayer::remain_reach_time = 0;
int CPlayer::remain_return_time = 0;
int CPlayer::strategy_att = 0;
int CPlayer::strategy_def = 0;

int CPlayer::Player_Init()
{
	num_worker_total = INIT_NUM_WORKER;
	num_soldier_total = INIT_NUM_SOLDIER;
	num_hired_total = 0;

	food = INIT_FOOD;
	timber = INIT_TIMBER;
	mineral = INIT_MINERAL;
	foodgap = 0;
	timbergap = 0;
	mineralgap = 0;
	max_food = INIT_MAX_FOOD;
	max_timber = INIT_MAX_TIMBER;
	max_mineral = INIT_MAX_MINERAL;

	int num_pro_food_per_day = 0;
	int num_cos_food_per_day = 0;
	int num_pro_timber_per_day = 0;
	int num_cos_timber_per_day = 0;
	int num_pro_mineral_per_day = 0;
	int num_cos_mineral_per_day = 0;

	strength = INIT_STRENGTH;
	strength_time = 0;
	strength_damege = 0;
	occupation = 0;
	unsatisfactory = INIT_UNSATISFACTORY;
	strength_time = 0;
	strength_damege = 0;

	search_produce_food = 0;
	hunt_produce_food = 0;
	aphid_produce_food = 0;
	mushroom_produce_food = 0;

	remain_reach_time = -1;
	remain_return_time = -1;
	strategy_att = -1;
	strategy_def = -1;

	return 1;
}

int CPlayer::Save()
{
	WriteFile(hfile, &occupation, sizeof(occupation), &dwWritten, NULL);
	WriteFile(hfile, &strength, sizeof(strength), &dwWritten, NULL);
	WriteFile(hfile, &strength_time, sizeof(strength_time), &dwWritten, NULL);
	WriteFile(hfile, &unsatisfactory, sizeof(unsatisfactory), &dwWritten, NULL);
	WriteFile(hfile, &num_ants_total, sizeof(num_ants_total), &dwWritten, NULL);
	WriteFile(hfile, &num_worker_total, sizeof(num_worker_total), &dwWritten, NULL);
	WriteFile(hfile, &num_worker_search, sizeof(num_worker_search), &dwWritten, NULL);
	WriteFile(hfile, &num_worker_building, sizeof(num_worker_building), &dwWritten, NULL);
	WriteFile(hfile, &num_worker_mushroom, sizeof(num_worker_mushroom), &dwWritten, NULL);
	WriteFile(hfile, &num_worker_aphid, sizeof(num_worker_aphid), &dwWritten, NULL);
	WriteFile(hfile, &num_soldier_total, sizeof(num_soldier_total), &dwWritten, NULL);
	WriteFile(hfile, &num_soldier_hunt, sizeof(num_soldier_hunt), &dwWritten, NULL);
	WriteFile(hfile, &num_soldier_defence, sizeof(num_soldier_defence), &dwWritten, NULL);
	WriteFile(hfile, &num_soldier_attack, sizeof(num_soldier_attack), &dwWritten, NULL);
	WriteFile(hfile, &num_hired_total, sizeof(num_hired_total), &dwWritten, NULL);
	WriteFile(hfile, &num_hired_defence, sizeof(num_hired_defence), &dwWritten, NULL);
	WriteFile(hfile, &num_hired_attack, sizeof(num_hired_attack), &dwWritten, NULL);
	WriteFile(hfile, &search_produce_food, sizeof(search_produce_food), &dwWritten, NULL);
	WriteFile(hfile, &hunt_produce_food, sizeof(hunt_produce_food), &dwWritten, NULL);
	WriteFile(hfile, &mushroom_produce_food, sizeof(mushroom_produce_food), &dwWritten, NULL);
	WriteFile(hfile, &aphid_produce_food, sizeof(aphid_produce_food), &dwWritten, NULL);
	WriteFile(hfile, &food, sizeof(food), &dwWritten, NULL);
	WriteFile(hfile, &foodgap, sizeof(foodgap), &dwWritten, NULL);
	WriteFile(hfile, &max_food, sizeof(max_food), &dwWritten, NULL);
	WriteFile(hfile, &timber, sizeof(timber), &dwWritten, NULL);
	WriteFile(hfile, &timbergap, sizeof(timbergap), &dwWritten, NULL);
	WriteFile(hfile, &max_timber, sizeof(max_timber), &dwWritten, NULL);
	WriteFile(hfile, &mineral, sizeof(mineral), &dwWritten, NULL);
	WriteFile(hfile, &mineralgap, sizeof(mineralgap), &dwWritten, NULL);
	WriteFile(hfile, &max_mineral, sizeof(max_mineral), &dwWritten, NULL);
	WriteFile(hfile, &remain_reach_time, sizeof(remain_reach_time), &dwWritten, NULL);
	WriteFile(hfile, &remain_return_time, sizeof(remain_return_time), &dwWritten, NULL);
	WriteFile(hfile, &strategy_att, sizeof(strategy_att), &dwWritten, NULL);
	WriteFile(hfile, &strategy_def, sizeof(strategy_def), &dwWritten, NULL);
	WriteFile(hfile, &strength_damege, sizeof(strength_damege), &dwWritten, NULL);

	return 1;
}
int CPlayer::Load()
{
	ReadFile(hfile, &occupation, sizeof(occupation), &dwWritten, NULL);
	ReadFile(hfile, &strength, sizeof(strength), &dwWritten, NULL);
	ReadFile(hfile, &strength_time, sizeof(strength_time), &dwWritten, NULL);
	ReadFile(hfile, &unsatisfactory, sizeof(unsatisfactory), &dwWritten, NULL);
	ReadFile(hfile, &num_ants_total, sizeof(num_ants_total), &dwWritten, NULL);
	ReadFile(hfile, &num_worker_total, sizeof(num_worker_total), &dwWritten, NULL);
	ReadFile(hfile, &num_worker_search, sizeof(num_worker_search), &dwWritten, NULL);
	ReadFile(hfile, &num_worker_building, sizeof(num_worker_building), &dwWritten, NULL);
	ReadFile(hfile, &num_worker_mushroom, sizeof(num_worker_mushroom), &dwWritten, NULL);
	ReadFile(hfile, &num_worker_aphid, sizeof(num_worker_aphid), &dwWritten, NULL);
	ReadFile(hfile, &num_soldier_total, sizeof(num_soldier_total), &dwWritten, NULL);
	ReadFile(hfile, &num_soldier_hunt, sizeof(num_soldier_hunt), &dwWritten, NULL);
	ReadFile(hfile, &num_soldier_defence, sizeof(num_soldier_defence), &dwWritten, NULL);
	ReadFile(hfile, &num_soldier_attack, sizeof(num_soldier_attack), &dwWritten, NULL);
	ReadFile(hfile, &num_hired_total, sizeof(num_hired_total), &dwWritten, NULL);
	ReadFile(hfile, &num_hired_defence, sizeof(num_hired_defence), &dwWritten, NULL);
	ReadFile(hfile, &num_hired_attack, sizeof(num_hired_attack), &dwWritten, NULL);
	ReadFile(hfile, &search_produce_food, sizeof(search_produce_food), &dwWritten, NULL);
	ReadFile(hfile, &hunt_produce_food, sizeof(hunt_produce_food), &dwWritten, NULL);
	ReadFile(hfile, &mushroom_produce_food, sizeof(mushroom_produce_food), &dwWritten, NULL);
	ReadFile(hfile, &aphid_produce_food, sizeof(aphid_produce_food), &dwWritten, NULL);
	ReadFile(hfile, &food, sizeof(food), &dwWritten, NULL);
	ReadFile(hfile, &foodgap, sizeof(foodgap), &dwWritten, NULL);
	ReadFile(hfile, &max_food, sizeof(max_food), &dwWritten, NULL);
	ReadFile(hfile, &timber, sizeof(timber), &dwWritten, NULL);
	ReadFile(hfile, &timbergap, sizeof(timbergap), &dwWritten, NULL);
	ReadFile(hfile, &max_timber, sizeof(max_timber), &dwWritten, NULL);
	ReadFile(hfile, &mineral, sizeof(mineral), &dwWritten, NULL);
	ReadFile(hfile, &mineralgap, sizeof(mineralgap), &dwWritten, NULL);
	ReadFile(hfile, &max_mineral, sizeof(max_mineral), &dwWritten, NULL);
	ReadFile(hfile, &remain_reach_time, sizeof(remain_reach_time), &dwWritten, NULL);
	ReadFile(hfile, &remain_return_time, sizeof(remain_return_time), &dwWritten, NULL);
	ReadFile(hfile, &strategy_att, sizeof(strategy_att), &dwWritten, NULL);
	ReadFile(hfile, &strategy_def, sizeof(strategy_def), &dwWritten, NULL);
	ReadFile(hfile, &strength_damege, sizeof(strength_damege), &dwWritten, NULL);

	return 1;
}

int CPlayer::Player_Shutdown()
{

	return 1;
}
