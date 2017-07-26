
#include <windows.h>
#include "CStory.h"
#include "CTime.h"
#include "CDebug.h"
#include "CObjDialog.h"
#include "CDomestic.h"
#include "CMainMenu.h"
#include "CBattle.h"
#include "CItem.h"
#include "CInterface.h"
#include "CObject.h"
#include "CBuilding.h"
#include "CDiplomatic.h"
#include "CScreen.h"
#include "CSpecies.h"
#include "resource.h"

HWND CStory::hWndDlg_story = NULL;

extern CDebug debug_;
extern CObject object_;
extern CScreen screen_;
extern CDomestic domestic_;
extern CInterface interface_;
extern CObjDialog objdialog_;
extern CMainMenu mainmenu_;
extern CDiplomatic diplomatic_;
extern CTime time_;
extern CBuilding building_;
extern CItem item_;

extern int ReturnScreenGamma(BOOL blong, int delay = 70);
extern int ChangeScreenGamma(int effect, BOOL blong, int delay = 70);
extern LPDIRECTDRAWSURFACE7 chapter1;
extern int CheckSpaceKey();
extern int CheckLButton();
extern int StopAllMusic();
extern BOOL g_bActive;

int CStory::Story_Init()
{
	chapter01 = DDLoadBitmap(lpdd, "art/story/chapter01.bmp", 0, 0);
	chapter01_1 = DDLoadBitmap(lpdd, "art/story/chapter01_1.bmp", 0, 0);
	chapter01_2 = DDLoadBitmap(lpdd, "art/story/chapter01_2.bmp", 0, 0);
	chapter02 = DDLoadBitmap(lpdd, "art/story/chapter02.bmp", 0, 0);
	chapter02_1 = DDLoadBitmap(lpdd, "art/story/chapter02_1.bmp", 0, 0);
	chapter02_2 = DDLoadBitmap(lpdd, "art/story/chapter02_2.bmp", 0, 0);
	chapter02_3 = DDLoadBitmap(lpdd, "art/story/chapter02_3.bmp", 0, 0);
	chapter03 = DDLoadBitmap(lpdd, "art/story/chapter03.bmp", 0, 0);
	chapter03_1 = DDLoadBitmap(lpdd, "art/story/chapter03_1.bmp", 0, 0);
	chapter04 = DDLoadBitmap(lpdd, "art/story/chapter04.bmp", 0, 0);
	chapter04_1 = DDLoadBitmap(lpdd, "art/story/chapter04_1.bmp", 0, 0);
	none = DDLoadBitmap(lpdd, "art/story/none.bmp", 0, 0);

	story.chap_1_intro[0] = "유모 개미\n\n\"문안인사 드립옵니다, 여왕님. "
							"저는 앞으로 여왕님의 시중을 들 유모개미입니다.\"";
	story.chap_1_intro[1] = "유모 개미\n\n\"아직 미숙한 여왕님을 위해 어떤 "
							"질문이라도 대답해 드리겠습니다.\"";
	story.chap_1_intro[2] = "참모 개미\n\n\"저 찬란한 태양보다 더 아름다운 분이시어. "
							"저는 여왕님에게 조언하는 임무를 맡은 참모개미 입니다.\"";
	story.chap_1_intro[3] = "참모 개미\n\n\"우리 왕국의 무한한 번영을 위해 이 한몸 바칠 것을 "
							"약속드립니다.\"";
	story.chap_1_intro[4] = "참모 개미\n\n\"아시다시피 우리 왕국은 탄생하지 얼마 안되어 힘이 "
							"미약합니다.\"";
	story.chap_1_intro[5] = "참모 개미\n\n\"다행하게도 이 겨울은 어떤 종족도 쉽게 움직이지 "
							"못하게 쎄찬 눈발을 내리고 있습니다.\"";
	story.chap_1_intro[6] = "참모 개미\n\n\"바로 이때 누구도 무시할 수 없는 힘을 비축해야 할 것입니다. "
							"미래를 대비해 가능한 많은 자원을 모으십시오.\"";

	story.chap_1_2_1[0] = "참모 개미\n\n\"우리쪽에 약간의 피해는 있었지만 '진딧물'들을 무사히 구출했습니다.\"";
	story.chap_1_2_1[1] = "참모 개미\n\n\" '진딧물'들은 안전한 우리 왕국의 굴에서 지내는 조건으로 "
						  "감로수를 공급하기로 하였습니다. 마침 비어있는 창고가 있어 그들의 거처로 정했습니다. "
						  "감로수를 원하시면 진딧물 축사에 일꾼 개미를 투입하십니오.\"";
	story.chap_1_2_1[2] = "참모 개미\n\n\"예견한대로 '메뚜기'종과의 관계가 악화되었습니다.\"";

	story.chap_1_2_2[0] = "참모 개미\n\n\"명목이 없습니다, 여왕이시어. 결국 '진딧물'들을 구해내지 못했습니다.\"";
	story.chap_1_2_2[1] = NULL;

	story.chap_1_3[0] = "참모 개미\n\n\"벌써 겨울의 반이 지났습니다, 여왕이시어.\"";
	story.chap_1_3[1] = "참모 개미\n\n\"그럴리야 없겠지만, 만약 겨울이 지나도록 우리의 힘이 "
						"기대에 미치지 못한다면 우리 왕국은 적의 먹이감이 될 뿐입니다.\"";

	story.chap_1_4[0] = "참모 개미\n\n\"미래를 대비해야 할 때입니다, 여왕이시어. "
						"아시겠지만 우리 왕국에는 자원을 저장할 장소가 많지 않습니다.\"";
	story.chap_1_4[1] = "참모 개미\n\n\"버리는 자원이 없도록 '자원 보관소'를 짓는 작업을 "
						"잊지 말아 주소서.\"";

	story.chap_1_5[0] = "참모 개미\n\n\"왕국의 눈부신 발전에 저의 가슴이 뛰는군요. 여왕이시어, "
						"참으로 길고 긴 겨울이었습니다만 왕국의 기반을 다지는 좋은 기회였습니다.\"";
	story.chap_1_5[1] = "참모 개미\n\n\"하지만 이것은 시작에 불과합니다. 신은 봄을 통해 모든 "
						"생물에게 생기를 주시지만, 한편으로는 피비린내 나는 삶의 장을 펼치시기 "
						"때문입니다.\"";

	story.chap_2_intro[0] = "참모 개미\n\n\"기분좋은 봄 날씨입니다, 여왕이시어. 이제, 왕국의 토대를 더욱 "
							"단단하게 다듬을 차례입니다.\"";
	story.chap_2_intro[1] = "참모 개미\n\n\" '화학 연구소'와 '전투 연습실'를 건설할 준비가 완료되었습니다. "
							"필요한 자재를 마련만 하면 언제든 시작할 수 있습니다.\"";

	story.chap_2_3[0] = "참모 개미\n\n\"몇몇의 일꾼 개미들이 버섯의 씨앗을 구해 왔습니다. 이것을 이용하면 "
						"식량 문제를 획기적으로 해결할 수 있습니다.\"";
	story.chap_2_3[1] = "참모 개미\n\n\"소량의 목재가 필요하겠지만 그정도는 감수해야 겠지요.\"";

	story.cahp_3_intro[0] = "참모 개미\n\n\"심기가 불편하시겠지만 좋은 소식도 있습니다. 오래전부터 "
						"사절단을 보낸 것을 기억하십니까? 그것의 효과가 서서히 나타나고 있습니다.\"";
	story.cahp_3_intro[1] = "참모 개미\n\n\"손가락의 과학기술을 이용한 새로운 연구과제를 수행할 수 "
						"있으며 기회가 된다면 보다 고차원적인 공간을 만들어 낼 수도 있을 것 같습니다.\"";
	story.cahp_3_intro[2] = "참모 개미\n\n\"여왕이시어, 우리의 힘으로 적들을 물리칠 수 있다면 가장 기쁜 상황이나, "
							"여의치 않을 때는 '용병'을 모집할 수도 있습니다.\"";
	story.cahp_3_intro[3] = "참모 개미\n\n\"그들은 일반적으로 강합니다. 하지만, 그들의 덩치만큼이나 많은 "
							"식량을 요구한다는 것을 기억해야 합니다.\"";

	story.chap_3_2[0] = "참모 개미\n\n\"떠돌이 개미들이 여왕폐하를 알현하고 싶어합니다.\"";
	story.chap_3_2[1] = "떠돌이 개미1\n\n\"여왕님을 뵙게되어 영광입니다. 다름아니라 작은 부탁이 "
						"있어 만나뵙고 싶었습니다.\"";
	story.chap_3_2[2] = "떠돌이 개미2\n\n\"저희는 손가락을 신으로 모시는 신도들입니다. "
						"만약 여유가 있으시다면 이곳에 작은 공간을 마련해 주실 수 있겠습니까?\"";
	story.chap_3_2[3] = "떠돌이 개미1\n\n\"여기 지하에 신이 존재한다는 소문을 들었습니다. "
						"그분과 교류가 있었다는 것까지도요. 그렇다면 종교에 관해서는 잘 아실거라 믿습니다.\"";
	story.chap_3_2[4] = "떠돌이 개미2\n\n\"저희는 이곳에 오래 머물 수 없습니다. 열흘동안 기다리겠으니 "
						"답변을 부탁드립니다.\"";
	story.chap_3_2[5] = "참모 개미\n\n\"사절단을 통해 우리 개미들이 종교라는 개념에 거부감을 받지 않는다는 것은 "
						"사실입니다.\"";
	story.chap_3_2[6] = "참모 개미\n\n\"하지만 신중히 선택할 문제입니다. 손가락을 믿는 개미들이 있는 지역들은 "
						"통치에 대한 불만으로 인해 해체위기에 처해있다고 합니다.\"";

	story.chap_3_3[0] = "참모 개미\n\n\"결국 행운의 여신이 우리에게 미소를 지어 주었습니다.\"";
	story.chap_3_3[1] = "참모 개미\n\n\"참으로 치열한 혈투였습니다만, 우리 왕국은 한 마음이 "
						"되어 적들을 물리쳤습니다.\"";
	story.chap_3_3[2] = "참모 개미\n\n\"이제 곧 겨울입니다. 안정과 휴식의 계절입니다. 지금의 "
						"고통과 절망이 어느정도는 아물겠지요.\"";

	story.chap_4_intro[0] = "참모 개미\n\n\"여왕이시어, 우리는 그동안 지하 손가락으로부터 많은 "
							"지식을 전수받아 왔습니다.\"";
	story.chap_4_intro[1] = "참모 개미\n\n\"선진 문물을 얻기 위해 땀흘린 개미들을 위해 이제는 "
							"결실을 낳을 차례입니다.\"";
	story.chap_4_intro[2] = "참모 개미\n\n\"여왕이시어, '예술의 전당'을 지어 우리 문명의 한 획을 "
							"그으소서. 이제 예술은 손가락만의 전유물이 아니라는 것을 보여주소서.\"";

	baphidroom = FALSE;

	countdown = -1;

	storyflag = 0;

	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;

	return 1;
}

int CStory::CheckStory()
{
	if(time_.GetYear() == 0)
	{
		if((time_.GetSeason() == WINTER) && (time_.GetMonth3() == 15) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_1_2_DONE))
			Chap_1_2();
		if((time_.GetSeason() == WINTER) && (time_.GetMonth3() == 45) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_1_3_DONE))
			Chap_1_3();
		if((time_.GetSeason() == WINTER) && (time_.GetMonth3() == 65) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_1_4_DONE))
			Chap_1_4();
		if((time_.GetSeason() == WINTER) && (time_.GetMonth3() == 89) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_1_5_DONE))
			Chap_1_5();
		if((time_.GetSeason() == SPRING) && (time_.GetMonth3() == 0) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_2_INTRO_DONE))
			Chap_2_Intro();
		if((time_.GetSeason() == SPRING) && (time_.GetMonth3() == 70) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_2_2_DONE))
			Chap_2_2();
		if((time_.GetSeason() == SPRING) && (time_.GetMonth3() == 80) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_2_3_DONE))
			Chap_2_3();
		if((time_.GetSeason() == SUMMER) && (time_.GetMonth3() == 10) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_2_4_DONE))
			Chap_2_4();
		if((time_.GetSeason() == SUMMER) && (time_.GetMonth3() == 45) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_3_INTRO_DONE))
			Chap_3_Intro();
		if((time_.GetSeason() == FALL) && (time_.GetMonth3() == 15) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_3_2_DONE))
			Chap_3_2();
		if((time_.GetSeason() == FALL) && (time_.GetMonth3() == 89) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_3_3_DONE))
			Chap_3_3();
	}
	if(time_.GetYear() == 1)
	{
		if((time_.GetSeason() == WINTER) && (time_.GetMonth3() == 0) && (time_.GetDay() == 0*UNIT_PER_TICK) && !(storyflag & CHAP_4_INTRO_DONE))
			Chap_4_Intro();
	}
	if(countdown > -1)
	{
		if(building_.building_under_construction
			== building_.buildingarray[BUILDINGARRAY_CHURCH].buildingtype)
			countdown = -1;
		countdown--;
		if(countdown == 0)
			building_.DisableBuilding(BUILDINGARRAY_CHURCH);

	}
	return 1;
}


int CStory::Chap_1_Intro()
{
	// 모든 다이얼로그 박스를 숨긴다.
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	Sleep(2000);
	DrawBitmap(&chapter01);
	ReturnScreenGamma(TRUE);
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 산속 깊은 곳 -\n벨로캉 왕국", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&chapter01_1);
	ReturnScreenGamma(TRUE);
	PrintScript(NULL, "'쩍'...... 암개미 1호와 그의 자매들이 탄생했다.", 1500);
	WaitSpace();
	PrintScript(NULL, "하늘 바다에 뜨거운 태양배가 나타나고\n 사라지기를 셀 수 없이 한 어느날", 2000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	PrintScript(NULL, "암개미 1호과 성체가 되어 비행 준비를 한다. 포근한 산들 바람이 분다. "
					"주위에는 먼저 비행했던 자매들의 비명이 들려오고.....", 3000);
	WaitSpace();
	Sleep(200);
	PrintScript(NULL, "드디어 암개미 1호가 결심을 한다.", 500);
	WaitSpace();
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&chapter01_2);
	ReturnScreenGamma(TRUE);
	PrintScript(NULL, "수없이 많은 위기를 극복하고 드디어 하나의 독립된 개미굴이 탄생했다. "
					"주위의 보이지 않는 곳에선 새로 지어진 개미굴을 주시하고 있는데....", 3000);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();
	SET_BIT(storyflag, CHAP_1_INTRO_DONE);
	DWORD ThreadID;
	hthread = CreateThread(NULL, 0, ThreadChapter_1_Intro, (LPVOID)this, 0, &ThreadID);

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	
	return 1;
}
DWORD WINAPI CStory::ThreadChapter_1_Intro(LPVOID temp)
{
	CStory *pThis = (CStory *)temp;

	CTime::ReleasePause();
	SCREEN_STATE = SCREEN_GAME;
	SCROLL_STATE = SCROLL_RUN;

	off_x = 0;
	off_y = 0;

	Sleep(500);

	mouse_x = 320;
	mouse_y = 475;

	Sleep(2000);

	CTime::SetPause();
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	pThis->ShowDialog(pThis->story.chap_1_intro, 7);

	hthread = NULL;

	return 0;
}

int CStory::Chap_1_2()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_STORY_APHID),
		main_window_handle,  (DLGPROC)AphidDlgProc );
	SendMessageA(hWndDlg_story, WM_GETPOINT, (WPARAM)0, (LPARAM)this);
	ShowWindow( hWndDlg_story, SW_SHOWNORMAL );

	WaitDialog();
	
	SET_BIT(storyflag, CHAP_1_2_DONE);

	return 1;
}
DWORD WINAPI CStory::ThreadChapter_1_2(LPVOID temp)
{
	CStory *pThis = (CStory *)temp;
	int temp_succes;

	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	
	temp_succes = domestic_.HelpAhpid();
	if(temp_succes == 1)
	{
		pThis->baphidroom = TRUE;
		object_.SetObName(OBJARRAY_BUILDING_WAREHOUSE, "진딧물 축사");
		// 진딧물 표시
		object_.ShowObjBob(OBJARRAY_AHPID);
	}
	Sleep(500);
	ReturnScreenGamma(TRUE);

	if(temp_succes == 1)
		pThis->ShowDialog(pThis->story.chap_1_2_1, 3);
	else
		pThis->ShowDialog(pThis->story.chap_1_2_2, 1);

	diplomatic_.ChangeRelation(SPEARRAY_GRASSHOPPER, -15000);

	hthread = NULL;

	return 0;
}

int CStory::Chap_1_3()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_1_3, 2);
	
	SET_BIT(storyflag, CHAP_1_3_DONE);

	return 1;;
}
int CStory::Chap_1_4()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_1_4, 2);
	
	SET_BIT(storyflag, CHAP_1_4_DONE);
	building_.ShowBuilding(BUILDINGARRAY_DEPOSITORY);

	return 1;
}
int CStory::Chap_1_5()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_1_5, 2);
	
	SET_BIT(storyflag, CHAP_1_5_DONE);

	return 1;
}
int CStory::Chap_2_Intro()
{
	// 모든 다이얼로그 박스를 숨긴다.
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	Sleep(2000);
	DrawBitmap(&chapter02);
	ReturnScreenGamma(TRUE);
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴 아래 깉은 곳", 1000);
	WaitSpace();
	PrintScript("조나탕", "이곳에 언제까지 머물 생각이야?", 500);
	WaitSpace();
	PrintScript("쥘리", "몇번씩이나 물어보는 거야?", 500);
	WaitSpace();
	PrintScript("다윗", "나도 지쳤어. 이 돌덩이 같은 기계를 가지고 도대체 무엇을 할 수 있지?", 1000);
	WaitSpace();
	PrintScript("쥘리", "어차피 이곳에 갇힌거나 마찬가지야. 여기서 영원히 빠져나갈 수 없다고 "
				"하더라도 난 이걸 밝혀 낼거야.", 1500);
	WaitSpace();
	PrintScript("조나탕", "식량도 거의 떨어져 간다고! 난 이 지긋지긋한 곳을 빠져나가는 길이나 찾아보겠어", 1000);
	WaitSpace();
	PrintScript("다윗", "쥘리, 너의 마음은 이해해. 하지만 그건 작동하지 않아. 어쩌면 처음부터 "
				"그랬을지도 모르지.", 1500);
	WaitSpace();
	PrintScript("쥘리", "너흰 몰라. 이 순간을 내가 얼마나 기다려 왔는지를...", 1000);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();

	// 챕터 2 초기화
	SET_BIT(storyflag, CHAP_2_INTRO_DONE);
	building_.ShowBuilding(BUILDINGARRAY_LAB);
	building_.ShowBuilding(BUILDINGARRAY_TRAINING);
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	diplomatic_.EnableSpecies(SPEARRAY_BEE);
	object_.EnableMapObj(OBJARRAY_MAP_BEE);
	CHAPTER = CHAP_2;
	for(int i=0; i<MAX_SPECIES; i++)
	{
		diplomatic_.SetAttempt_to_Attack(i, 8);
		diplomatic_.ChangeSpeStrength(i, 40*NUM_CIPHER);
	}
	
	
	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_2_intro, 2);

	return 1;
}
int CStory::Chap_2_2()
{
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴 하단", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&chapter02_1);
	ReturnScreenGamma(TRUE);
	PrintScript("일꾼 개미1", "이봐. 이 돌에서 이상한 냄새가 나는 것 같지 않나?", 1500);
	WaitSpace();
	PrintScript("일꾼 개미2", "자네도 느꼈나? 며칠 전까지만 해도 희미했는데 "
				"근래에 들어서 자주, 그리고 강하게 나는군", 2500);
	WaitSpace();
	Sleep(2000);
	PrintScript("참모 개미", "여왕이시어, 굴 하단에 있는 돌덩이에서 수상한 냄새가 난다는 "
				"일꾼 개미들의 보고가 급증하고 있습니다.", 2500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "그렇다면, 적당한 수의 개미들을 구성하여 돌을 파보도록 하게.", 1500);
	WaitSpace();
	PrintScript("참모 개미", "바로 시행하겠습니다.", 1000);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();
	SET_BIT(storyflag, CHAP_2_2_DONE);
	CTime::ReleasePause();
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	return 1;
}
int CStory::Chap_2_3()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_2_3, 2);
	
	SET_BIT(storyflag, CHAP_2_3_DONE);
	building_.ShowBuilding(BUILDINGARRAY_MUSHROOM);

	return 1;
}
int CStory::Chap_2_4()
{
	// 모든 다이얼로그 박스를 숨긴다.
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴 하단", 1000);
	WaitSpace();
	PrintScript("참모 개미", "방금 돌을 뚫는 작업을 마쳤습니다. 수색대를 조직하여 "
				"내려보냈으니 곧 연락이 올 것입니다.", 2000);
	WaitSpace();
	Sleep(2000);
	PrintScript("참모 개미", "내려갔던 개미들이 돌아왔습니다만.... "
				"헛 소리만 하고 있습니다.", 1500);
	WaitSpace();
	PrintScript("참모 개미", "그들 말로는 굴아래에서 손가락들을 보았다고 합니다. "
				"그리고 그들이 자신들에게 먹이를 주었다고 합니다.", 2500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "손가락?", 500);
	WaitSpace();
	PrintScript("참모 개미", "그렇습니다. 하지만 그들을 믿을 수가 없습니다. "
				"손가락이라니요. 다른 개미들을 구성하여 내려 보내겠습니다.", 2500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "아닐세. 내가 직접 내려가 보겠네.", 500);
	WaitSpace();
	PrintScript("참모 개미", "그건 너무 위험하지 않겠습니까?", 1000);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "괜찮네. 어서 내려갈 차비를 하지", 1000);
	WaitSpace();
	Sleep(2000);
	PrintScript("쥘리", "이것봐! 이번엔 여왕 개미 같은데.", 1000);
	WaitSpace();
	PrintScript("조나탕", "우리 따위를 보러 여왕까지 행차하셨나?", 1000);
	WaitSpace();
	PrintScript("쥘리", "우리한테는 이 '로제타석'을 사용해볼 수 있는 좋은 기회지. "
				"여왕 개미의 지능이라면 충분히 통할 수 있을 거야.", 2000);
	WaitSpace();
	Sleep(2000);
	PrintScript("쥘리", "여왕님, 내 말이 들리나요?", 500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "..............", 500);
	WaitSpace();
	PrintScript("쥘리", "안들리는 건가? 성공할 줄 알았는데....", 500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "..............", 500);
	WaitSpace();
	PrintScript("다윗", "여왕 개미가 더듬이를 흔들고 있어. 뭔가 말을 하고 "
				"있는게 틀림없어", 1500);
	WaitSpace();
	PrintScript("쥘리", "맞아. 그럼 기계를 증폭시켜 보자.", 500);
	WaitSpace();
	Sleep(2000);
	PrintScript("여왕 암개미 1호", "손가락들이여, 어떻게 된 일인지는 모르지만 당신들의 언어를 "
				"이해할 수 있는 것 같다.", 2000);
	WaitSpace();
	PrintScript("쥘리", "성공이야! 너도 들었지? 이 '로제타석'이 작동한다고!", 1000);
	WaitSpace();
	Sleep(2000);
	PrintScript("참모 개미", "여왕이시어, 그것은 불가능 합니다. 만약 이 사실이 "
				"밖으로 새어 나간다면 주위에 있는 모든 종족을 적으로 돌리는 꼴이됩니다.", 2500);
	WaitSpace();
	PrintScript("여왕 암개미 1호", "자네의 걱정을 이해 못하는 바는 아니나, 나에게도 "
				"생각이 있다네.", 2500);
	WaitSpace();
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	PrintScript(NULL, "- 어느 깊은 산 속 -\n벨로캉 왕국", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&chapter02_2);
	ReturnScreenGamma(TRUE);
	PrintScript("개미 103호", "저의 여정은 이것으로 끝을 맺게 됩니다.", 1000);
	WaitSpace();
	PrintScript("암개미 1호", "저 세상밖은 정말 신기한 일로 가득 하군요.", 1000);
	WaitSpace();
	PrintScript("개미 103호", "물론입니다. 아무튼 손가락과의 만남을 저는 평생토록 "
				"잊지 못할 겁니다. 그들의 문화, 과학, 사회는 정말 낭만으로 가득차 있습니다.", 3000);
	WaitSpace();
	PrintScript("개미 103호", "그들과 교류를 하는 것은 우리의 종족을 더욱 풍요럽고 "
				"행복하게 만들 것입니다.", 1500);
	WaitSpace();
	PrintScript("암개미 1호", "하지만 우리 대부분은 모르고 있지요. 마음의 문을 열지 않는 "
				"이상 더 이상의 발전은 없을 것입니다.", 2500);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript("여왕 암개미 1호", "내 결정은 단호하네. 돌아갈 준비를 하게나.", 1500);
	WaitSpace();
	Sleep(2000);
	PrintScript(NULL, "암개미 1호의 굴 아래에는 3명의 손가락들이 있었다.", 1000);
	WaitSpace();
	PrintScript(NULL, "암개미 1호는 그들이 식량이 부족하다는 이야기를 듣고 "
					"선뜻 자신들의 식량을 나누어 주기로 하였다.", 1500);
	WaitSpace();
	PrintScript(NULL, "한편 손가락의 선진 문물을 받아들인 좋은 기회로 생각하여 "
					"사절단을 손가락에게 정기적으로 보내기로 합의했다.", 2000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&chapter02_3);
	ReturnScreenGamma(TRUE);
	PrintScript(NULL, "손가락들은 '로제타석'이라 불리우는 커더란 돌을 암개미 1호에게 "
					"주었다. 이 돌을 가지고 그들과 대화를 할 수 있을 것이다.", 2500);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();
	item_.SetItem(5, PLAYER);
	object_.SetObName(OBJARRAY_BUILDING_STRANGE_STONE, "지하세계의 통로");
	screen_.ChangeStrangeStone();

	SET_BIT(storyflag, CHAP_2_4_DONE);
	CTime::ReleasePause();
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	return 1;
}
int CStory::Chap_3_Intro()
{
	// 모든 다이얼로그 박스를 숨긴다.
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	Sleep(2000);
	DrawBitmap(&chapter03);
	ReturnScreenGamma(TRUE);
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n불개미의 굴", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&chapter03_1);
	ReturnScreenGamma(TRUE);
	PrintScript(NULL, "쉬쉬하던 지하 손가락들의 대한 소문은 여기 불개미의 굴까지 "
					"오게 되었다.", 1500);
	WaitSpace();
	PrintScript(NULL, "불개미 뿐만 아니라 이 공원의 모든 공동체는 손가락을 그들의 최대의 "
					"적으로 삼고 있었다.", 1500);
	WaitSpace();
	PrintScript(NULL, "손가락들은 심심하면 그들의 동료를 잡아가거나 그들의 둥지에 불을 "
					"피우며 못 살게 군다고 생각했기 때문이다.", 1500);
	WaitSpace();
	PrintScript(NULL, "암개미 1호의 굴을 주시하던 불개미들은 손가락을 보호하고 있는 "
					"그들을 용서하지 않을 것이라 다짐한다.", 2000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴", 1000);
	WaitSpace();
	PrintScript("참모 개미", "첩자에 따르면 불개미를 포함, 많은 무리들이 지하 손가락에 "
				"관한 소문을 알고 있는 것 같이 보입니다.", 2500);
	WaitSpace();
	PrintScript("참모 개미", "빨리 대책을 세우지 않으면 안될 것 같습니다, 여왕이시어. ", 1000);
	WaitSpace();
	PrintScript("참모 개미", "세력을 더욱 키우고 많은 동맹국들을 만들어 적에 대항해야 할 것 "
				"입니다.", 1500);
	WaitSpace();
	PrintScript("참모 개미", "행운의 여신이 우리와 함께 하기를....", 1500);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();
	
	// 챕터 3 초기화
	SET_BIT(storyflag, CHAP_3_INTRO_DONE);
	building_.ShowBuilding(BUILDINGARRAY_HIRED_1);
	building_.ShowBuilding(BUILDINGARRAY_HIRED_2);
	objdialog_.UpgradeLab();
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	diplomatic_.EnableSpecies(SPEARRAY_RED_ANT);
	object_.EnableMapObj(OBJARRAY_MAP_RED_ANT);
	CHAPTER = CHAP_3;
	for(int i=0; i<MAX_SPECIES; i++)
	{
		diplomatic_.ChangeRelation(i, -10000);
		diplomatic_.SetAttempt_to_Attack(i, 20);
		diplomatic_.ChangeSpeStrength(i, 60*NUM_CIPHER);
	}

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.cahp_3_intro, 4);

	return 1;
}
int CStory::Chap_3_2()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_3_2, 7);
	
	SET_BIT(storyflag, CHAP_3_2_DONE);
	building_.ShowBuilding(BUILDINGARRAY_CHURCH);
	countdown = LENGTH_TIME_LEAVE;

	return 1;
}
int CStory::Chap_3_3()
{
	CTime::SetPause();

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_3_3, 3);
	
	SET_BIT(storyflag, CHAP_3_3_DONE);

	return 1;
}
int CStory::Chap_4_Intro()
{
	// 모든 다이얼로그 박스를 숨긴다.
	CTime::SetPause();
	MOUSE_STATE = MOUSE_HIDE;
	ShowCursor(FALSE);
	HideAllDialog();
	StopAllMusic();
	restore.surface = NULL;
	restore.script = NULL;
	restore.name = NULL;
	
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	Sleep(2000);
	DrawBitmap(&chapter04);
	ReturnScreenGamma(TRUE);
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	Sleep(2000);
	PrintScript(NULL, "- 어느 한적한 공원 -\n암개미 1호의 굴 근처 풀잎 위", 1000);
	WaitSpace();
	ChangeScreenGamma(SCREEN_DARKNESS, FALSE);
	DrawBitmap(&chapter04_1);
	ReturnScreenGamma(TRUE);
	Sleep(2000);
	PrintScript(NULL, "암개미 1호는 자신의 왕국 근처 풀잎위에 올라가 하늘을 "
					"바라본다.", 1000);
	WaitSpace();
	PrintScript(NULL, "암개미 1호의 왕국 탄생 1년.", 1000);
	WaitSpace();
	PrintScript(NULL, "어려운 시기를 극복하고 이제 모두의 안식처인 겨울이 돌아왔다.", 1000);
	WaitSpace();
	PrintScript(NULL, "암개미 1호는 손가락은 개미의 친구가 될 수 있다는"
					"생각을 변함없이 믿는다.", 1500);
	WaitSpace();
	Sleep(2000);
	ChangeScreenGamma(SCREEN_DARKNESS, TRUE);
	DrawBitmap(&none);
	ReturnScreenGamma(FALSE);
	PrintScript(NULL, "이제 암개미 1호와 그의 자식들, 그리고 손가락의 운명은\n 이제 당신의 손에 "
					"놓여있다.", 1500);
	WaitSpace();

	Sleep(1000);

	ShowAllDialog();

	// 챕터 4 초기화
	SET_BIT(storyflag, CHAP_4_INTRO_DONE);
	building_.ShowBuilding(BUILDINGARRAY_ART);
	MOUSE_STATE = MOUSE_SHOW;
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	CHAPTER = CHAP_4;
	for(int i=0; i<MAX_SPECIES; i++)
	{
		diplomatic_.SetAttempt_to_Attack(i, 15);
		diplomatic_.ChangeSpeStrength(i, 80*NUM_CIPHER);
	}

	if(hWndDlg_story)
		EndDialog( hWndDlg_story, TRUE );
	hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowDialog(story.chap_4_intro, 3);

	return 1;
}
int CStory::GetStoryFlag()
{
	return storyflag;
}
BOOL CStory::IsAphidRoomBuilt()
{
	return baphidroom;
}
int CStory::ShowDialog(char *firstpage[], int total)
{
	SendMessageA(hWndDlg_story, WM_GETPOINT, NULL, (LPARAM)firstpage);
	SendMessageA(hWndDlg_story, WM_GETPAGE, (WPARAM)0, (LPARAM)total);
	SetDlgItemTextA(hWndDlg_story, IDC_NORMAL, *firstpage);
	ShowWindow( hWndDlg_story, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CStory::Restore()
{
	MSG msg;
	HRESULT hRet;

	for(int i=0; i<4000; i++)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if(msg.message == WM_QUIT)
			   break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		hRet = lpdd->RestoreAllSurfaces();
		if (hRet == DD_OK)
			break;
		if(i == 3999)
			return ErrorMessage(main_window_handle, "restore 실패");
	}

	item_.reload();
	screen_.reload();
	interface_.reload();
	this->reload();
	mainmenu_.reload();
	
	return 1;
}
INT_PTR CALLBACK CStory::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static char **content;
	static int curpage;
	static int totalpage;

	switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
		case WM_GETPOINT:
			content = (char **)lParam;
			return TRUE;
		case WM_GETPAGE:
			curpage = (int)wParam;
			totalpage = (int)lParam;
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDOK:
				{
					if(curpage < totalpage-1)
					{
						curpage++;
						SetDlgItemTextA(hDlg, IDC_NORMAL, content[curpage]);
					}
					else
					{
						EndDialog( hDlg, TRUE );
						hDlg = NULL;
						hWndDlg_story = NULL;
						CTime::ReleasePause();
					}
				}
				break;
			}
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
			hWndDlg_story = NULL;
			break;
    }

    return FALSE;
}
INT_PTR CALLBACK CStory::AphidDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CStory* pThis; 

	static HWND hradio1;
	static HWND hradio2;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_STORY_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_STORY_RADIO2);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CStory *)lParam;

			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_story = NULL;

				if(SendMessage(hradio1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
				{
					CTime::ReleasePause();
					return TRUE;
				}

				DWORD ThreadID;
				hthread = CreateThread(NULL, 0, ThreadChapter_1_2, (LPVOID)pThis, 0, &ThreadID);

				if(hWndDlg_story)
					EndDialog( hWndDlg_story, TRUE );
				hWndDlg_story = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );

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
           hWndDlg_story = NULL;
            break;
    }

    return FALSE;
}

int CStory::PrintScript(char *name, char *script, int delay)
{
	HRESULT hRet;
	RECT rect_text = {100, 410, 550, 460};

	DDraw_Fill_Surface(lpddsback, RGB(13, 13, 13));
	restore.name = name;
	restore.script = script;

	if(name != NULL)
		sprintf(buffer,"%s : \"%s\"",name, script);
	else
		sprintf(buffer,"%s", script);
	DDraw_Text_Rect(buffer,
				&rect_text,
				15,
				lpddsback,
				RGB(255,255,255),
				DT_CENTER | DT_WORDBREAK,
				NULL,
				TRANSPARENT);
	
	hRet = lpddsprimary->Blt(&rect_text, lpddsback, &rect_text, DDBLT_WAIT, NULL);
	if((hRet == DDERR_SURFACELOST) && (g_bActive == TRUE))
		Restore();

	Sleep(delay);

	return 1;
}

int CStory::DrawBitmap(LPDIRECTDRAWSURFACE7 *psur)
{
	HRESULT hRet;

	// 현재 표시되는 surface를 가리키는 LPDIRECTDRAWSURFACE7의
	// 주소를 저장한다. 그러므로써 restore할 때 무엇을 가리키는
	// 지와는 상관없이 복구가 쉽다.
	restore.surface = psur;
	hRet = lpddsprimary->Blt(NULL, *psur, NULL, DDBLT_WAIT, NULL);
	if((hRet == DDERR_SURFACELOST) && (g_bActive == TRUE))
		Restore();

	return 1;
}

int CStory::WaitSpace()
{
	int show = 0;
	HRESULT hRet;
	RECT rect_text = {120, 460, 540, 480};
	RECT rect_clear = {100, 410, 550, 480};
	MSG msg;

	// restore시에 message 처리하는 부분에서 그림을 지우는
	// 문제가 있어 그 안에서 그려줄 수 있도록 하는 변수
	BOOL draw_restore = FALSE;

	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			if(draw_restore)
			{
				DrawBitmap(restore.surface);
				PrintScript(restore.name, restore.script, 0);
				draw_restore = FALSE;
			}

			// test if this is a quit
			if(msg.message == WM_QUIT)
			   break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
			
		} // end if
		// main game processing goes here

		show++;
		if(show >= 0 && show <= 500)
		{
			DDraw_Fill_Surface(lpddsback, RGB(13, 13, 13));
			
			sprintf(buffer,"%s", "Press Spacebar or Left Button");
			DDraw_Text_Rect(buffer,
						&rect_text,
						15,
						lpddsback,
						RGB(255,255,255),
						DT_CENTER | DT_WORDBREAK,
						NULL,
						TRANSPARENT);		
			
			hRet = lpddsprimary->Blt(&rect_text, lpddsback, &rect_text, DDBLT_WAIT, NULL);
		}
		if(show > 500)
		{
			DDraw_Fill_Surface(lpddsback, RGB(13, 13, 13));
			hRet = lpddsprimary->Blt(&rect_text, lpddsback, &rect_text, DDBLT_WAIT, NULL);
			if(show == 980)
				show = 10;
		}

		if(CheckSpaceKey() == KEY_DOWN && show >= 10)
		{
			DDraw_Fill_Surface(lpddsback, RGB(13, 13, 13));
			hRet = lpddsprimary->Blt(&rect_clear, lpddsback, &rect_clear, DDBLT_WAIT, NULL);
			break;
		}
		if(CheckLButton() == BUTTON_DOWN && show > 10)
		{
			DDraw_Fill_Surface(lpddsback, RGB(13, 13, 13));
			hRet = lpddsprimary->Blt(&rect_clear, lpddsback, &rect_clear, DDBLT_WAIT, NULL);
			break;
		}

		if((hRet == DDERR_SURFACELOST) && (g_bActive == TRUE))
		{
			draw_restore = TRUE;
			Restore();
		}
	} // end while

	Sleep(300);

	return 0;
}

HWND CStory::GetHwnDia_Story()
{
	return hWndDlg_story;
}
int CStory::reload()
{
	chapter01 = DDLoadBitmap(lpdd, "art/story/chapter01.bmp", 0, 0);
	chapter01_1 = DDLoadBitmap(lpdd, "art/story/chapter01_1.bmp", 0, 0);
	chapter01_2 = DDLoadBitmap(lpdd, "art/story/chapter01_2.bmp", 0, 0);
	chapter02 = DDLoadBitmap(lpdd, "art/story/chapter02.bmp", 0, 0);
	chapter02_1 = DDLoadBitmap(lpdd, "art/story/chapter02_1.bmp", 0, 0);
	chapter02_2 = DDLoadBitmap(lpdd, "art/story/chapter02_2.bmp", 0, 0);
	chapter02_3 = DDLoadBitmap(lpdd, "art/story/chapter02_3.bmp", 0, 0);
	chapter03 = DDLoadBitmap(lpdd, "art/story/chapter03.bmp", 0, 0);
	chapter03_1 = DDLoadBitmap(lpdd, "art/story/chapter03_1.bmp", 0, 0);
	chapter04 = DDLoadBitmap(lpdd, "art/story/chapter04.bmp", 0, 0);
	chapter04_1 = DDLoadBitmap(lpdd, "art/story/chapter04_1.bmp", 0, 0);
	none = DDLoadBitmap(lpdd, "art/story/none.bmp", 0, 0);

	return 1;
}
int CStory::Save()
{
	WriteFile(hfile, &baphidroom, sizeof(baphidroom), &dwWritten, NULL);
	WriteFile(hfile, &countdown, sizeof(countdown), &dwWritten, NULL);
	WriteFile(hfile, &storyflag, sizeof(storyflag), &dwWritten, NULL);

	return 1;
}
int CStory::Load()
{
	ReadFile(hfile, &baphidroom, sizeof(baphidroom), &dwWritten, NULL);
	ReadFile(hfile, &countdown, sizeof(countdown), &dwWritten, NULL);
	ReadFile(hfile, &storyflag, sizeof(storyflag), &dwWritten, NULL);
	if(storyflag & CHAP_2_4_DONE)
		object_.SetObName(OBJARRAY_BUILDING_STRANGE_STONE, "지하세계의 통로");

	return 1;
}
int CStory::Story_Shutdown()
{
	if(chapter01)
		chapter01->Release();
	if(chapter01_1)
		chapter01_1->Release();
	if(chapter01_2)
		chapter01_2->Release();
	if(chapter02)
		chapter02->Release();
	if(chapter02_1)
		chapter02_1->Release();
	if(chapter02_2)
		chapter02_2->Release();
	if(chapter02_3)
		chapter02_3->Release();
	if(chapter03)
		chapter03->Release();
	if(chapter03_1)
		chapter03_1->Release();
	if(chapter04)
		chapter04->Release();
	if(chapter04_1)
		chapter04_1->Release();
	if(none)
		none->Release();

	return 1;
}
