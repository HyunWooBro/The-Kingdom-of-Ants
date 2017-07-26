/*
///////////////////////////////////////////

	CBattle

	전투를 담당한다. 여기서 실질적인 AI가 
	사용된다. 컴퓨터가 여러가지 정보와 랜덤적인
	요소를 가지고 플레이어에게로 공격을 결정한다.

///////////////////////////////////////////
*/
#pragma once

#include <ddraw.h>
#include "t3dlib1.h"
#include "GlobalDeclaration.h"

class CBattle
{
public:
	CBattle() {}
	~CBattle() {}

private:
	char buffer[110];

	struct _battle
	{
		int num_food_get;						// 약탈한 식량
		int num_timber_get;						// 약탈한 목재
		int num_mineral_get;					// 약탈한 광석

		int num_food_lost;						// 약탈된 식량
		int num_timber_lost;					// 약탈된 목재
		int num_mineral_lost;					// 약탈된 광석

		int spe_init_num_att;					// 컴퓨터의 초기 공격 병력
		int spe_cur_num_att;					// 컴퓨터의 남은 공격 병력
		int spe_init_num_def;					// 컴퓨터의 초기 방어 병력
		int spe_cur_num_def;					// 컴퓨터의 남은 방어 병력
		
		int power_hired_att;					// 용병의 공격 파워
		int power_hired_def;					// 용병의 방어 파워

		int player_cur_num_soldier_att;
		int player_cur_num_hired_att;
		int player_cur_num_soldier_def;
		int player_cur_num_hired_def;

		int player_init_num_soldier_att;
		int player_init_num_hired_att;
		int player_init_num_soldier_def;
		int player_init_num_hired_def;

		int player_init_num_att;
		int player_cur_num_att;
		int player_init_num_def;
		int player_cur_num_def;

		int player_attack_time;					// 공격을 시작한 이래로 지나간 기간
		int player_defence_time;				// 방어를 시작한 이래로 지나간 기간

		BOOL player_join;						// 원정을 나갔던 병사들이 합류했는가
	}battle;

	BOB battle_dirt;
	BOB battle_dirt2;

	static HWND hWndDlg_battle;
	static INT_PTR CALLBACK BattleAttDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
	static INT_PTR CALLBACK BattleDefDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static HWND hWndDlg_battle_normal;
	static HWND hWndDlg_battle_result_att;
	static HWND hWndDlg_battle_result_def;
	static INT_PTR CALLBACK NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static INT_PTR CALLBACK GameoverDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

	static DWORD WINAPI ThreadGameover(LPVOID temp);

	static DWORD WINAPI ThreadBattle(LPVOID temp);

	int ShowAttResDialog(int SPEARRAY_INDEX);
	int ShowDefResDialog(int SPEARRAY_INDEX);
	int ShowNorDialog(char *buffer);

	int BattleOut_Init();
	int BattleIn_Init();

	int PlayerComeBackInit(int SPEARRAY_INDEX);
	int SpeGoBackInit(int SPEARRAY_INDEX);

	int ReturnFromBattle();
public:
	int Battle_Init(int flag = NULL);

	int PlayerDecideStr(int selectedindex);		// 플레이어가 공격 전략을 수립
	int SpeDecideAttack();						// 컴퓨터가 공격할지를 결정
	int CheckReachTime();						// 플레이어나 컴퓨터가 상대 서식처로 도달했는지 체크
	int CheckReturnTime();						// 플레이어나 컴퓨터가 되돌아 갔는지 체크
	
	int BattleOutside();
	int BattleInside();
	int PrintBattleInfo();
	int PrintBattleBreakOut();
	int PrintSpeCome();
	int PrintPlayerGo();
	int PrintPlayerCome();

	int DrawBattleDirt();

	static HWND GetHwnDia_Battle();
	static HWND GetHwnDia_Battle_Normal();
	static HWND GetHwnDia_Battle_Result_Att();
	static HWND GetHwnDia_Battle_Result_Def();

	int Save();
	int Load();

	int Battle_Shutdown();

};
