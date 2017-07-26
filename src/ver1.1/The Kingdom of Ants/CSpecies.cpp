
#include "CSpecies.h"

struct CSpecies::_species CSpecies::speciesarray[5];

int CSpecies::Selectedindex = 0;

int CSpecies::spe_attacked_index = 0;
int CSpecies::spe_attacking_index = 0;

int CSpecies::Species_Init()
{
	speciesarray[0].name = "민달팽이";
	SetRect(&speciesarray[0].sperect, 291, 241, 291+20, 241+20);
	speciesarray[0].state = SPECIES_STATE_NORMAL;
	speciesarray[0].blanguage = FALSE;
	speciesarray[0].Disalbed = FALSE;
	speciesarray[0].relation = 32000;
	speciesarray[0].initstrength = 50500;
	speciesarray[0].strength = speciesarray[0].initstrength;
	speciesarray[0].strength_time = 0;
	speciesarray[0].religion = 0;
	speciesarray[0].attempt_to_attck = 1;
	speciesarray[0].remain_reach_time = -1;
	speciesarray[0].remain_return_time = -1;
	speciesarray[0].power = POWER_SANIL;
	speciesarray[0].num_attack = 0;
	speciesarray[0].num_defence = 0;
	speciesarray[0].strength_damege = 0;

	speciesarray[1].name = "메뚜기";
	SetRect(&speciesarray[1].sperect, 159, 258, 159+20, 258+20);
	speciesarray[1].state = SPECIES_STATE_NORMAL;
	speciesarray[1].blanguage = FALSE;
	speciesarray[1].Disalbed = FALSE;
	speciesarray[1].relation =  27000;
	speciesarray[1].initstrength = 63300;
	speciesarray[1].strength = speciesarray[1].initstrength;
	speciesarray[1].strength_time = 0;
	speciesarray[1].religion = 0;
	speciesarray[1].attempt_to_attck = 1;
	speciesarray[1].remain_reach_time = -1;
	speciesarray[1].remain_return_time = -1;
	speciesarray[1].power = POWER_GRSSHOPPER;
	speciesarray[1].num_attack = 0;
	speciesarray[1].num_defence = 0;
	speciesarray[1].strength_damege = 0;

	speciesarray[2].name = "난쟁이개미";
	SetRect(&speciesarray[2].sperect, 379, 235, 379+20, 235+20);
	speciesarray[2].state = SPECIES_STATE_NORMAL;
	speciesarray[2].blanguage = TRUE;
	speciesarray[2].Disalbed = FALSE;
	speciesarray[2].relation = 22000;
	speciesarray[2].initstrength = 80100;
	speciesarray[2].strength = speciesarray[2].initstrength;
	speciesarray[2].strength_time = 0;
	speciesarray[2].religion = 0;
	speciesarray[2].attempt_to_attck = 1;
	speciesarray[2].remain_reach_time = -1;
	speciesarray[2].remain_return_time = -1;
	speciesarray[2].power = POWER_SHORT_ANT;
	speciesarray[2].num_attack = 0;
	speciesarray[2].num_defence = 0;
	speciesarray[2].strength_damege = 0;

	speciesarray[3].name = "꿀벌";
	SetRect(&speciesarray[3].sperect, 85, 246, 85+20, 246+20);
	speciesarray[3].state = SPECIES_STATE_NORMAL;
	speciesarray[3].blanguage = FALSE;
	speciesarray[3].Disalbed = TRUE;
	speciesarray[3].relation = 27000;
	speciesarray[3].initstrength = 102000;
	speciesarray[3].strength = speciesarray[3].initstrength;
	speciesarray[3].strength_time = 0;
	speciesarray[3].religion = 0;
	speciesarray[3].attempt_to_attck = 1;
	speciesarray[3].remain_reach_time = -1;
	speciesarray[3].remain_return_time = -1;
	speciesarray[3].power = POWER_BEE;
	speciesarray[3].num_attack = 0;
	speciesarray[3].num_defence = 0;
	speciesarray[3].strength_damege = 0;

	speciesarray[4].name = "불개미";
	SetRect(&speciesarray[4].sperect, 195, 288, 195+20, 288+20);
	speciesarray[4].state = SPECIES_STATE_NORMAL;
	speciesarray[4].blanguage = TRUE;
	speciesarray[4].Disalbed = TRUE;
	speciesarray[4].relation = 14000;
	speciesarray[4].initstrength = 130200;
	speciesarray[4].strength = speciesarray[4].initstrength;
	speciesarray[4].strength_time = 0;
	speciesarray[4].religion = 0;
	speciesarray[4].attempt_to_attck = 1;
	speciesarray[4].remain_reach_time = -1;
	speciesarray[4].remain_return_time = -1;
	speciesarray[4].power = POWER_RED_ANT;
	speciesarray[4].num_attack = 0;
	speciesarray[4].num_defence = 0;
	speciesarray[4].strength_damege = 0;

	Selectedindex = -1;

	spe_attacked_index = -1;
	spe_attacking_index = -1;

	return 1;
}

int CSpecies::Save()
{
	for(int i=0; i<MAX_SPECIES; i++)
		WriteFile(hfile, &speciesarray[i], sizeof(speciesarray[i]), &dwWritten, NULL);

	WriteFile(hfile, &Selectedindex, sizeof(Selectedindex), &dwWritten, NULL);
	WriteFile(hfile, &spe_attacked_index, sizeof(spe_attacked_index), &dwWritten, NULL);
	WriteFile(hfile, &spe_attacking_index, sizeof(spe_attacking_index), &dwWritten, NULL);

	return 1;
}
int CSpecies::Load()
{
	for(int i=0; i<MAX_SPECIES; i++)
		ReadFile(hfile, &speciesarray[i], sizeof(speciesarray[i]), &dwWritten, NULL);

	ReadFile(hfile, &Selectedindex, sizeof(Selectedindex), &dwWritten, NULL);
	ReadFile(hfile, &spe_attacked_index, sizeof(spe_attacked_index), &dwWritten, NULL);
	ReadFile(hfile, &spe_attacking_index, sizeof(spe_attacking_index), &dwWritten, NULL);

	return 1;
}
int CSpecies::Species_Shutdown()
{

	return 1;
}
