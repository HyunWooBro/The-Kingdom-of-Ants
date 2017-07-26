/*
///////////////////////////////////////////

	CInfo

	다른 클래스에서 자료를 읽어와서 
	scrren_gameinfo(게임정보)에서 
	그것들을 뿌려주기만 한다.

///////////////////////////////////////////
*/

#pragma once

#include "GlobalDeclaration.h"

class CInfo
{
public:
	CInfo() {}
	~CInfo() {}

private:
	char buffer[100];

	int stack_produce_food[UNIT_PER_DAY * UNIT_PER_TICK];
	int stack_cost_food[UNIT_PER_DAY * UNIT_PER_TICK];
	int stack_produce_timber[UNIT_PER_DAY * UNIT_PER_TICK];
	int stack_cost_timber[UNIT_PER_DAY * UNIT_PER_TICK];
	int stack_produce_mineral[UNIT_PER_DAY * UNIT_PER_TICK];
	int stack_cost_mineral[UNIT_PER_DAY * UNIT_PER_TICK];

	int PrintKingdomInfo();
	int PrintResource();
	int PrintBattle();
	int PrintNumAnts();
	int PrintSpecies();
	int PrintOther();

	int PrintRelationText(int SPEARRAY_INDEX, int x, int y); 

public:
	int Info_Init();

	int PrintGmaeInfo();
	int ComputeResource(int resource_index, int value);
	int MoveStackMem();

	int Save();
	int Load();

	int Info_Shutdown();
};

