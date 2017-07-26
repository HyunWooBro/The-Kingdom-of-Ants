/*
///////////////////////////////////////////

	CPlayer

	플레이어와 관계된 모든 정보를 관리한다.

///////////////////////////////////////////
*/
#pragma once

#include "GlobalDeclaration.h"

class CPlayer
{
	friend class CEvent;
	friend class CInfo;
	friend class CObject;
	friend class CDiplomatic;
	friend class CBattle;
	friend class CObjDialog;
	friend class CBuilding;
	friend class CDomestic;
	friend class CItem;
public:
	CPlayer() {}
	~CPlayer() {}

private:
	// 내정 관련(CDomestic에서 처리)
	static int occupation;					// 공원 장악력
	static int strength;					// 세력
	static int strength_time;				// 시간의 경과에 따른 누적 세력
	static int unsatisfactory;				// 불만

	static int num_ants_total;				// 총 개미 수

	static int num_worker_total;			// 총 일꾼 개미 수
	static int num_worker_search;			//
	static int num_worker_building;
	static int num_worker_mushroom;
	static int num_worker_aphid;

	static int num_soldier_total;
	static int num_soldier_hunt;
	static int num_soldier_defence;
	static int num_soldier_attack;

	static int num_hired_total;
	static int num_hired_defence;
	static int num_hired_attack;

	static int search_produce_food;
	static int hunt_produce_food;
	static int mushroom_produce_food;
	static int aphid_produce_food;

	static int food;
	static int foodgap;						// 바로 전과 자원을 비교하여 손해인지 체크
	static int max_food;

	static int timber;
	static int timbergap;					// 바로 전과 자원을 비교하여 손해인지 체크
	static int max_timber;

	static int mineral;
	static int mineralgap;					// 바로 전과 자원을 비교하여 손해인지 체크
	static int max_mineral;

	static int num_pro_food_per_day;
	static int num_cos_food_per_day;
	static int num_pro_timber_per_day;
	static int num_cos_timber_per_day;
	static int num_pro_mineral_per_day;
	static int num_cos_mineral_per_day;

	// 전쟁 관련(CBattle에서 처리)
	static int remain_reach_time;
	static int remain_return_time;
	static int strategy_att;
	static int strategy_def;
	static int strength_damege;				// 피해에 따른 누적 세력

public:
	static int Player_Init();

	static int Save();
	static int Load();

	static int Player_Shutdown();

};
