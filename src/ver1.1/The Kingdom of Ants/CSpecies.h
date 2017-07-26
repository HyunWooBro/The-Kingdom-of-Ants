/*
///////////////////////////////////////////

	CSpecies

	플레이어를 제외한 컴퓨터가 운용하는 
	종족에 대한 정보를 관리한다.

///////////////////////////////////////////
*/
#pragma once

#include "GlobalDeclaration.h"

class CSpecies
{
	friend class CInfo;
	friend class CEvent;
	friend class CBattle;
	friend class CDomestic;
	friend class CDiplomatic;
public:
	CSpecies() {}
	~CSpecies() {}

private:
	static struct _species				// 플레이어를 제외한 맵상의 종족
	{
		// 외교 관련(CDiplomatic에서 처리)
		char *name;						// 종족 이름
		RECT sperect;					// 맵에서의 영역
		BOOL Disalbed;					// 맵에 존재하는가
		BOOL blanguage;					// 플레이어와 의사소통할 수 있는가
		int state;						// 상태
		int initstrength;				// 초기 세력
		int strength;					// 세력
		int strength_time;				// 시간에 경과에 따른 누적 세력
		int relation;					// 플레이어와의 관계(0~50000)
		int religion;					// 교화된 정도(0~100)

		// 전쟁 관련(CBattle에서 처리)
		int remain_reach_time;
		int remain_return_time;
		int num_attack;
		int num_defence;
		int attempt_to_attck;			// 공격 성향; 이것과 관계가 함께 공격을 결정한다.
										// 스토리 진행에 따라 달라진다.(1~10)
		float power;
		int strategy_att;
		int strategy_def;
		int strength_damege;			// 피해에 따른 누적 세력
	}speciesarray[MAX_SPECIES];

	static int Selectedindex;

	static int spe_attacked_index;
	static int spe_attacking_index;

public:
	static int Species_Init();

	static int Save();
	static int Load();

	static int Species_Shutdown();
};




