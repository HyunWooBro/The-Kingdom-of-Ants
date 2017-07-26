
#include <windows.h>   // include important windows stuff
#include <stdio.h>
#include "CObjDialog.h"
#include "GlobalDeclaration.h"
#include "CObject.h"
#include "CBuilding.h"
#include "CDomestic.h"
#include "CEvent.h"
#include "CDiplomatic.h"
#include "CStory.h"
#include "CTime.h"
#include "CItem.h"
#include "CPlayer.h"
#include "resource.h"
#include "CDebug.h"

extern CDebug debug_;
extern CEvent event_;
extern CItem item_;
extern CObject object_;
extern CTime time_;
extern CBuilding building_;
extern CStory story_;
extern CDomestic domestic_;
extern CDiplomatic diplomatic_;

HWND CObjDialog::hWndDlg_obj = NULL;
HWND CObjDialog::hWndDlg_obj_additonal = NULL;

int CObjDialog::ObjDialog_Init()
{
	dialog.worker_dialog[0][0] = "일꾼 개미\n\n\"왕국의 발전하는 모습에 정말 뿌듯하군요.\"";
	dialog.worker_dialog[0][1] = "일꾼 개미\n\n\"열심히 일하자.\"";
	dialog.worker_dialog[0][2] = "일꾼 개미\n\n\"수색하는 길에 여러 생명체들이 겨울잠에서 깨어나는 "
								"것을 보았습니다. 물론 그중에는 우리의 천적도 있었지만요.\"";

	dialog.worker_dialog[1][0] = "일꾼 개미\n\n\"여름은 수확의 계절입니다. 기회를 놓치지 마십시오.\"";
	dialog.worker_dialog[1][1] = "일꾼 개미\n\n\"열심히 일하자.\"";
	dialog.worker_dialog[1][2] = "일꾼 개미\n\n\"여름에 수색과 사냥을 하는 것은 정말 위험합니다. "
								"왜냐하면 우리의 천적들이 활발하게 활동하는 계절이기 때문입니다. "
								"하지만 동시에 기회의 계절이기도 합니다.\"";

	dialog.worker_dialog[2][0] = "일꾼 개미\n\n\"겨울이 다가옵니다. 겨울을 지낼 식량은 충분한지요?\"";
	dialog.worker_dialog[2][1] = "일꾼 개미\n\n\"열심히 일하자.\"";
	dialog.worker_dialog[2][2] = "일꾼 개미\n\n\"가을에는 왠지 모르게 쓸쓸해 집니다.\"";

	dialog.worker_dialog[3][0] = "일꾼 개미\n\n\"겨울에는 먹이감을 찾기가 쉽지 않습니다.\"";
	dialog.worker_dialog[3][1] = "일꾼 개미\n\n\"열심히 일하자.\"";
	dialog.worker_dialog[3][2] = "일꾼 개미\n\n\"게으른 귀뚜라미는 지금쯤 굶고 있을 겁니다.\"";

	dialog.soldier_dialog[0][0] = "병정 개미\n\n\"전투가 없어서 몸이 근질거렸는데 이제 몸을 풀 기회가 올까?\"";
	dialog.soldier_dialog[0][1] = "병정 개미\n\n\"잔꾀를 부리는 일꾼 개미가 꼭 있단 말이야. 혼내줘야지.\"";
	dialog.soldier_dialog[0][2] = "병정 개미\n\n\"저희는 저희보다 몇 배나 큰 생명체와 싸워 이겨본 적이 많습니다.\"";

	dialog.soldier_dialog[1][0] = "병정 개미\n\n\"여름에는 전투의 발생 빈도가 높습니다. 공격의 패널티가 거의 "
								"없기 때문이죠.\"";
	dialog.soldier_dialog[1][1] = "병정 개미\n\n\"잔꾀를 부리는 일꾼 개미가 꼭 있단 말이야. 혼내줘야지.\"";
	dialog.soldier_dialog[1][2] = "병정 개미\n\n\"민달팽이는 크기만 컸지 전투력은 형평없습니다.\"";

	dialog.soldier_dialog[2][0] = "병정 개미\n\n\"겨울을 대비하기 위해 사냥에 신경을 써야 합니다.\"";
	dialog.soldier_dialog[2][1] = "병정 개미\n\n\"잔꾀를 부리는 일꾼 개미가 꼭 있단 말이야. 혼내줘야지.\"";
	dialog.soldier_dialog[2][2] = "병정 개미\n\n\"오래전에 꿀벌에 쏘인적이 있었는데 며칠을 기절했다가 "
								"구사일생으로 동료에 의해 깨어났습니다.\"";

	dialog.soldier_dialog[3][0] = "병정 개미\n\n\"저도 가끔은 도서관에서 책을 봅니다.\"";
	dialog.soldier_dialog[3][1] = "병정 개미\n\n\"잔꾀를 부리는 일꾼 개미가 꼭 있단 말이야. 혼내줘야지.\"";
	dialog.soldier_dialog[3][2] = "병정 개미\n\n\"불개미들은 정말 무서운 종족입니다. 사납기로 소문이 자자하죠.\"";

	dialog.adviser_dialog[0] = "참모 개미\n\n\"우선 일꾼 개미는 현재 2가지의 일을 할 수 있습니다. "
						"수색을 통해 자원을 찾아내며 가끔 아이템을 얻기도 합니다. 건설은 굴을 확장할 때 "
						"필요합니다. 병정 개미는 먹이감을 사냥할 수 있고 전투를 준비 하기도 합니다.\"";
	dialog.adviser_dialog[1] = "참모 개미\n\n\"각각의 비율에 따라 개미들에게 작업을 부여하게 됩니다. 예를 들어 "
						"굴을 빨리 확장하고 싶으면 건설에 많은 일꾼 개미를 투입하면 됩니다. 주의할 것은 "
						"전투는 전투 태세인 병정 개미만이 할 수 있다는 것입니다.\"";
	dialog.adviser_dialog[2] = "참모 개미\n\n\"전쟁에는 많은 요소들이 포함되어 있습니다. 계절, 개체수, "
						"공격 전략과 방어 전략, 기타 전쟁에 영향을 주는 많은 요소들이 있습니다. "
						"자세한 내용은 도서관을 참조하시기 바랍니다.\"";
	dialog.adviser_dialog[3] = "참모 개미\n\n\"정보 창을 주위 깊게 보십시오. 그곳에는 모든 정보가 일목요연하게 "
						"정리되어 있습니다. 왕국 통치에 관한 더욱 자세한 내용을 알기 위해서는 도서관에 "
						"가보셔야 합니다. 도서관이 있다면 말입니다.\"";

	dialog.adviser_addition_dialog[0] = "참모 개미\n\n\"우리의 세력은 주위 종족에 비해 매우 약합니다. "
						"하지만 겨울에는 공격에 많은 패널티가 있기 때문에 쉽게 공격하지는 않을 "
						"것입니다. 따라서 내실 기여에만 집중하시면 될 것입니다.\"";
	dialog.adviser_addition_dialog[1] = "참모 개미\n\n\"겨울이 지났습니다. 이 사실은 기쁘면서도 한편으로는 걱정을 "
						"불러 일으킵니다. 적의 공격이 발생할 가능성이 높다는 것입니다. 따라서 병정 개미의 "
						"적정 수를 전투 태세로 하심이 좋을 듯 싶습니다.\"";
	dialog.adviser_addition_dialog[2] = "참모 개미\n\n\"말할 필요도 없이 방어에 총력을 기울여야 합니다. "
						"여유가 있다면 연구소에서 전투에 관한 과제를 연구하는 것도 좋은 방법입니다. "
						"동맹 세력을 많이 두는 것도 큰 도움이 될 것입니다.\"";
	dialog.adviser_addition_dialog[3] = "참모 개미\n\n\"이제는 여왕폐하께서 결정해 보십시오. 꿈꾸던 목표가 "
						"무엇입니까? 목표가 정해지면 왕국의 개미들은 그것을 실현 시키기 위해 취선을 "
						"다할 것입니다.\"";

	dialog.nanny_dialog[0] = "유모 개미\n\n\"모든 자원을 고루 얻고 굴을 확장하며 내실에 기여하실 건가요? "
						"아니면 사냥을 통해 식량을 쌓아가며 전투를 준비하실 생각이십니까? 여왕폐하의 의중에 "
						"따라 적절히 알을 분배하시면 됩니다.\"";
	dialog.nanny_dialog[1] = "유모 개미\n\n\"현재 여왕폐하께서는 이틀에 최대 약 30개의 알을 생산하실 수 있으십니다. "
						"하지만 한계를 뛰어넘을 방법이 없는 것은 아닙니다. 꿀벌의 로열젤리가 있으면 "
						"생산할 수 있는 알의 개수를 증가시킬 수 있다 합니다.\"";
	dialog.nanny_dialog[2] = "유모 개미\n\n\"현재 여왕폐하께서는 이틀에 최대 약 45개의 알을 생산하실 수 있으십니다.\"";

	dialog.queen_dialog = "여왕 암개미 1호\n\n오늘도 여왕 암개미 1호는 왕국의 미래를 걱정하고 있습니다.";

	dialog.scientist_dialog = "과학자 개미\n\n\"이곳은 관계자외 출입... 앗! 여왕님. 연구에 집중한 나머지 몰라뵈어 사죄드립니다.\"";

	dialog.training_ant_dialog = "병정 개미\n\n\"먼저 적의 공격을 여유럽게 피하며 개미산으로 카운터를 "
						"날린다라....\"";

	dialog.mushroom_ant_dialog = "버섯재배 개미\n\n\"버섯이 무럭무럭 자라고 있습니다. 보통의 식물이라면 "
						"햇빛을 필요로 하지만 버섯은 잎과 엽록체가 없어 광합성을 하지 못하고 "
						"다른 기주체에 기생을 합니다.\"";

	dialog.hired_1_dialog = "장수풍데이\n\n\"안녕하시오. 아늑한 거처를 만들어 주어 감사의 말을 전하오. "
						"우리가 식량을 너무 축내는건 아닌지 걱정스럽군요.\"";
	
	dialog.hired_2_dialog = "사슴벌레\n\n\"너무 무료한 일상이군. 한건이 크게 터져줘야 하는데 말이야.\"";

	dialog.church_ant_dialog = "신도 개미\n\n\"손가락을 아십니까? 그분은 전지전능하신 분이십니다. "
						"우리 개미들을 만들었고 다른 모든 만물을 창조하신 분이라는 겁니다. 손가락을 믿고 "
						"구원을 받으십시오.\"";

	dialog.art_ant_dialog = "일꾼 개미\n\n\"이 작품은 원근감을 살려 각 개미들을 배치하고 배경의 "
						"묘사가 뛰어나군\"";

	dialog.aphid_dialog = "진딧물\n\n\"꾸꾸.. 꾸엑\"";



	dialog.seller_dialog[0] = "절대반지\n프로도라는 손가락이 잃어버린 엄청난 힘이 잠재되어 있는 반지이다. "
						"\n(전투력 상승,주위 종족과의 관계 악화)";
	dialog.seller_dialog[1] = "수정구슬\n바라보고 있으면 빨려들어갈 것 같은 신비한 수정으로 만들어진 구슬이다. "
						"\n(세력 +20)";




	dialog.strangestone_dialog[0] = "수상한 돌덩이\n\n이 돌은 반대편 통로를 막고 있는 것처럼 보입니다.";
	dialog.strangestone_dialog[1] = "지하세계의 통로\n\n수상한 냄새가 나던 돌을 파내자 손가락에게 향하는 "
								"통로가 나타났습니다. 여왕 암개미 1호는 손가락의 과학,종교,문화 등의 선진 "
								"문명을 받아들이기 위해 손가락에게 사절단을 보내기로 결정했습니다.";

	dialog.buildingqueen_dialog = "여왕 개미의 방\n\n벨로캉 왕국에서 독립하고 새 왕국을 새운 암개미 1호의 거처입니다.";

	dialog.egg_dialog = "영아실\n\n갓 태어난 어린 애벌레를 보호하기 위해 습도와 온도가 알맞게 조절된 방입니다.";

	dialog.warehouse_dialog[0] = "비어있는 창고\n\n비어있는 창고입니다. 유용하게 사용할 수 있을 것 같습니다.";
	dialog.warehouse_dialog[1] = "진딧물 축사\n\n진딧물을 기르는 곳입니다. 진딧물을 보호하며 그들에게 식물 잎을 "
							"주면 그들은 개미가 좋아하는 감로수를 배설해 냅니다. 또한 그들은 기분이 좋으면 "
							"평소보다 수십배의 감로수를 더 만들어 냅니다.";
							
	dialog.depository_dialog = "자원 보관소\n\n식량, 목재, 광석을 각각 12000, 3000, 1500까지 보관합니다.";

	dialog.training_dilaog = "전투 연습실\n\n병정 개미들이 진정한 용사로 거듭나기 위해 수련을 "
							"하는 곳입니다.";

	dialog.mushroom_dialog = "버섯 재배소\n\n참나무에 여러종의 버섯을 기릅니다. 버섯에는 영양소가 많이 "
							"들어 있어 개미에게 매우 유익합니다. 단, 버섯을 기르기 위해서는 소량의 "
							"목재가 소비됩니다.";

	dialog.buildinghired_1_dialog = "용병양성소-장수풍뎅이\n\n방어에 능숙한 종입니다. 보통은 그들끼리 평화롭게 "
						  "모여있지만 위험한 분위기가 감지되면 재빨리 전투태세에 돌입합니다."; 

	dialog.buildinghired_2_dialog = "용병양성소-사슴벌레\n\n공격에 능숙한 종입니다. 그들이 굴을 지나갈 때면 "
						  "겁많은 개미들은 보이지 않는 그늘진 곳에 몸을 숨깁니다.";

	dialog.church_dialog = "종교 회관\n\n손가락을 신으로 모시는 -그들에 따르면- 성스러운 곳입니다. "
						"이들은 손가락을 따르고 구원을 받으라는 등의 알수없는 말들을 중얼거립니다.";

	dialog.art_dialog = "예술의 전당\n\n이곳에서 개미들은 자신의 끼를 마음껏 발산할 수 있습니다. "
					"개미들은 자신의 일을 끝낸 후에 이곳에 들러 예술의 세계에 빠져듭니다.";

	labarray[0].name = "고농축 개미산";
	labarray[0].remaintime = LAB_TIME(7);
	labarray[0].inittime = labarray[0].remaintime;
	labarray[0].lab_cost[0] = 300;
	labarray[0].lab_cost[1] = 70;
	labarray[0].lab_cost[2] = 90;
	labarray[0].describe_lab = "고농축 개미산\n\n병정 개미들의 기본적인 생화학 무기인 "
							"개미산의 부식력은 뛰어났으나 적들의 두려움을 살 정도는 아니었다. "
							"하지만 개미 문명의 발달과 함께 가공할 부식성을 지닌 산을 병정 개미의 "
							"산주머니에 주입하는 기술이 개발되었다. 이것에 제대로 적중된다면 피부는 "
							"물론 주요 내장을 모조리 삼켜버릴 것이다.";

	labarray[1].name = "영양 교환의 개선";
	labarray[1].remaintime = LAB_TIME(7);
	labarray[1].inittime = labarray[1].remaintime;
	labarray[1].lab_cost[0] = 350;
	labarray[1].lab_cost[1] = 0;
	labarray[1].lab_cost[2] = 70;
	labarray[1].describe_lab = "영양 교환의 개선\n\n개미들의 영양 교환은 굶주린 동족을 살리기 "
							"위해 시작되었다. 개미들의 개체수가 증가하고 더 많은 먹이감이 필요하자 "
							"더 넓고 먼 지역으로 수색의 범위를 넓힐 필요가 생겼다. 자연스럽게 영양 "
							"교환의 효율을 개선해 수색과 사냥의 효율을 증대시킬 방법을 연구하기 "
							"시작했다.";

	labarray[2].name = "건설의 혁신";
	labarray[2].remaintime = LAB_TIME(10);
	labarray[2].inittime = labarray[2].remaintime;
	labarray[2].lab_cost[0] = 170;
	labarray[2].lab_cost[1] = 210;
	labarray[2].lab_cost[2] = 75;
	labarray[2].describe_lab = "건설의 혁신\n\n개미굴은 매우 이상적인 구조를 갖고 있다. "
							"일반적으로 수직으로 건설되며 다량의 햇빛과 수분 섭취에 양호하다. "
							"또한 배수가 잘되어 홍수가 나도 크게 문제가 없다. 그러나 그런 굴을 "
							"만들기 위해서는 많은 노력과 시간이 필요했다. 많은 고민 끝에 건설 기간을 "
							"획기적으로 줄일 수 있는 공법이 발견되었다.";

	labarray[3].name = "언어 - 민달팽이";
	labarray[3].remaintime = LAB_TIME(7);
	labarray[3].inittime = labarray[3].remaintime;
	labarray[3].lab_cost[0] = 210;
	labarray[3].lab_cost[1] = 80;
	labarray[3].lab_cost[2] = 45;
	labarray[3].describe_lab = "언어 - 민달팽이\n\n껍데기가 없는 달팽이이다. 몸길이 4∼5cm, "
							"몸너비 약 1cm이다. 껍데기는 퇴화해 없어지고 연한 갈색의 외투막이 "
							"등을 감싸고 있다. 민달팽이의 언어를 습득하면 민달팽이와 높은 수준의 "
							"외교가 가능해지며 관계가 조금 개선된다.";

	labarray[4].name = "언어 - 꿀벌";
	labarray[4].remaintime = LAB_TIME(7);
	labarray[4].inittime = labarray[4].remaintime;
	labarray[4].lab_cost[0] = 220;
	labarray[4].lab_cost[1] = 95;
	labarray[4].lab_cost[2] = 40;
	labarray[4].describe_lab = "언어 - 꿀벌\n\n꿀벌은 계급사회를 형성하여 생활하는데, "
							"일벌이 먹이가 있는 곳을 팔(8)자모양의 춤으로 알려주어서 공유할만큼 "
							"공동체의식이 강하다. 여왕벌이 알을 낳아서 애벌레가 부화하면 일벌은 "
							"여왕벌이 될 벌에게만 로열제리를 먹여서 다음 대를 준비한다. 꿀벌의 "
							"언어를 습득하면 꿀벌과 높은 수준의 외교가 가능해지며 관계가 조금 개선 "
							"된다.";

	labarray[5].name = "언어 - 메뚜기";
	labarray[5].remaintime = LAB_TIME(7);
	labarray[5].inittime = labarray[5].remaintime;
	labarray[5].lab_cost[0] = 210;
	labarray[5].lab_cost[1] = 90;
	labarray[5].lab_cost[2] = 50;
	labarray[5].describe_lab = "언어 - 메뚜기\n\n날씨가 건조해서 번식률이 높아지면 집단으로 "
							"먹을 것을 찾아다닌다. 반대로 날이 습하면 알이 부패하기 때문에 "
							"번식률이 낮아진다. 메뚜기의 언어를 습득하면 메뚜기와 높은 수준의 "
							"외교가 가능해지며 관계가 조금 개선된다.";

	labarray[6].name = "융통성";
	labarray[6].remaintime = LAB_TIME(10);
	labarray[6].inittime = labarray[6].remaintime;
	labarray[6].lab_cost[0] = 270;
	labarray[6].lab_cost[1] = 110;
	labarray[6].lab_cost[2] = 85;
	labarray[6].describe_lab = "융통성\n\n개미들의 사회는 동적인 듯이 보이지만 정적인 면도 "
							"있다. 각자 맡은 역할을 고집하여 불균형이 발생하더라도 효과적으로 "
							"분배가 이루어지지 못했다. 많은 노력끝에 역할 분배를 효율적으로 할 수 "
							"있는 방법이 발견되었다. 이것을 연구하면 일꾼, 병정, 여왕의 변경 "
							"허용치를 한단계 더 조정할 수 있다.";

	labarray[7].name = "적응력";
	labarray[7].remaintime = LAB_TIME(10);
	labarray[7].inittime = labarray[7].remaintime;
	labarray[7].lab_cost[0] = 300;
	labarray[7].lab_cost[1] = 160;
	labarray[7].lab_cost[2] = 70;
	labarray[7].describe_lab = "적응력\n\n본래 개미는 적응력이 뛰어난 축에 속한다. 하지만 그것은 "
							"주위 환경에는 맞을지는 몰라도 내부적으로는 그렇지 못하다. 자신의 역할에 "
							"적응할 시간이 어느정도 필요했던 것이다. 결국 적응력을 높이기 위한 "
							"연구가 필요해졌다. 이것을 연구하면 일꾼, 병정, 여왕의 작업을 변경한 후 "
							"기존보다 하루 일찍 조정할 수 있다.";

	labarray[8].name = "광산의 개발";
	labarray[8].remaintime = LAB_TIME(15);
	labarray[8].inittime = labarray[8].remaintime;
	labarray[8].lab_cost[0] = 350;
	labarray[8].lab_cost[1] = 400;
	labarray[8].lab_cost[2] = 0;
	labarray[8].describe_lab = "광산의 개발\n\n손가락에게서 배운, 어떻게 보면 가장 실용적인 과제라 "
							"할 수 있다. 손가락의 그것처럼 코끼리가 들어갈 만한 거대한 크기는 "
							"아니지만 안정적으로 광석을 얻을 수 있다는 점은 큰 매력이 아닐 수 없다.";

	labarray[9].name = "불을 이용한 방어법";
	labarray[9].remaintime = LAB_TIME(15);
	labarray[9].inittime = labarray[9].remaintime;
	labarray[9].lab_cost[0] = 230;
	labarray[9].lab_cost[1] = 300;
	labarray[9].lab_cost[2] = 200;
	labarray[9].describe_lab = "불을 이용한 방어법\n\n불은 손가락을 제외한 모든 생명체에게 접근해서는 "
							"안되는 무시무시한 존재이다. 그들은 프로메테우스가 손가락에게 불을 준 사실은 "
							"역사상 가장 비극적인 일이라 생각했다. 여왕 암개미 1호 역시 고향 벨로캉 왕국이 "
							"한때 손가락의 불에 의해 파괴된 사실을 알고 있다. 하지만 그녀는 불이야말로 방어의 "
							"최적임을 부인하지는 못한다. 단, 불은 굴과 자원에 피해를 줄 수 있다.";

	labarray[10].name = "긍정적 사고";
	labarray[10].remaintime = LAB_TIME(10);
	labarray[10].inittime = labarray[10].remaintime;
	labarray[10].lab_cost[0] = 400;
	labarray[10].lab_cost[1] = 0;
	labarray[10].lab_cost[2] = 140;
	labarray[10].describe_lab = "긍정적 사고\n\n오래되록 감정은 손가락의 고유한 성질이라고 여겨왔다. "
							"근래에 들어 이 생각은 바뀌어 왔지만 기본적인 감정밖에는 나타낼 수 없다는 "
							"한계가 있다는 생각은 변함이 없었다. 한편 지하 손가락과의 교류에서 나타난 "
							"가장 큰 변화는 개미들이 손가락의 복잡한 사고를 모방하기 시작했다는 것이다. "
							"이 현상을 이용해 불만을 줄이는 감정을 연구하자는 생각에 이르렀다.";

	labarray[11].name = "언어 - 장수풍뎅이";
	labarray[11].remaintime = LAB_TIME(10);
	labarray[11].inittime = labarray[11].remaintime;
	labarray[11].lab_cost[0] = 350;
	labarray[11].lab_cost[1] = 100;
	labarray[11].lab_cost[2] = 70;
	labarray[11].describe_lab = "언어 - 장수풍뎅이\n\n수컷의 머리에는 긴 뿔이 나있고 가슴등판에도 뿔이 있다. "
							"다리와 몸통이 굵어 힘이 세며 길이는 30~90mm로 다양하다. 많은 종족들은 장수풍뎅이를 "
							"용병으로 원하지만 그들의 언어는 배우기 어려워서 실제로 고용하는 이들은 그리 많지 "
							"않다.";

	labarray[12].name = "언어 - 사슴벌레";
	labarray[12].remaintime = LAB_TIME(10);
	labarray[12].inittime = labarray[12].remaintime;
	labarray[12].lab_cost[0] = 350;
	labarray[12].lab_cost[1] = 85;
	labarray[12].lab_cost[2] = 75;
	labarray[12].describe_lab = "언어 - 사슴벌레\n\n몸 빛깔은 황갈색이나 흑갈색을 띠며, 암컷이 더 진하고 "
							"등딱지날개에 매우 가는 황금색 잔털로 덮여 있다. 머리 뒤쪽은 코끼리의 귀처럼 넓으며, "
							"큰턱은 굵고 강하며 아래쪽을 향해 있다. 다루기는 조금 까다로운 편이며 공격적인 "
							"성향이 강해 조심할 필요성이 있다.";

	labflag = 0;

	lab_on_subject = NULL;

	CheckedHired = FALSE;

	libraryarray[0].totalpage = 2;
	libraryarray[0].page[0] = "상대적이고 절대적인 지식의 백과사전\n\n"
							"영양 교환\n\n"
							"인간이 개미에게서 모방한 것이 무엇인지를 묻는 사람이 가끔 있다. 그럴 때 "
							"내가 가장 먼저 예로 드는 것은 입맞춤이다. 흔히 말하기를, 입맞춤은 기원전 "
							"3백 년경 로마 인들이 생각해 냈다고 한다. 그러나 따지고 보면 그것은 개미들의 "
							"영양 교환을 모방한 것에 지나지 않는다."
							"\n\n"
							"page 1 of 2";
	libraryarray[0].page[1] = "상대적이고 절대적인 지식의 백과사전\n\n"
							"영양 교환은 고결한 관용의 행위다. 개미들의 뱃속에는 사회위라는 제 2의 위가 있다. "
							"그 위에서는 먹이가 소화되지 않고 갈무리될 뿐이다. 그 먹이는 구걸하는 개미를 위한 "
							"것이다. 그러면 영양 교환은 어떻게 이루어지는가? 굶주린 개미가 다른 개미를 찾아가 "
							"영양 교환을 요구하기만 하면 된다. 그러면 요구를 받은 개미는 자기 입을 구걸한 개미의 "
							"입에 갖다 대고, 사회위에 갈무리된 먹이를 되올려 준다.\n"
							"(by 에드몽 웰즈)"
							"\n\n"
							"page 2 of 2";

	libraryarray[1].totalpage = 5;
	libraryarray[1].page[0] = "꼭 읽어야 하는 왕국 매뉴얼\n\n"
						"한 왕국을 다스리는 여왕이 알아야 하는 것들은 다음과 같다. "
						"\n첫째, 계절에 따라 계획을 세워라. 다른 종족도 마찬가지지만 "
						"개미의 세계에서도 계절의 변화는 거스를 수 없는 숙명과도 같다. "
						"겨울에는 수색과 사냥의 효율이 극도로 떨어진다. 따라서 다른 방책을 "
						"세워야 할 것이다. 반대로 여름은 모든 활동이 정점에 있는 시기이다. "
						"\n\n"
						"page 1 of 5";
	libraryarray[1].page[1] = "꼭 읽어야 하는 왕국 매뉴얼\n\n"
						"봄과 가을은 비슷한 계절이다. 전자는 추위에서 따뜻함으로, "
						"후자는 따뜻함에서 추위로 변하는 것이지만 말이다. 이 두 계절은 "
						"여름보다는 활동이 적다. "
						"\n둘째, 작업을 효과적으로 분배하라. 건설을 하지도 않는데 건설을 "
						"담당하는 일꾼 개미들이 많다면 어떻게 될 것인가? 이 부분은 중요하지만 "
						"시작하면 끝이 없을 것 같아 한 가지만 소개하겠다."
						"\n\n"
						"page 2 of 5";
	libraryarray[1].page[2] = "꼭 읽어야 하는 왕국 매뉴얼\n\n"
						"병정 개미는 전투 태세인 상태에서만 전투를 치를 수 있다는 "
						"사실은 꽤 중요하다. 왜냐하면 많은 병정 개미를 보유하면서 "
						"대부분이 사냥을 하다가 공격을 당하면 뒷일은 뻔하기 때문이다. "
						"\n세번째는 개미들의 불만을 잘 다스리는 것이다. 그들은 타고난 "
						"왕국의 일꾼으로써 자신의 역할에 대한 불만은 나타나지 않는다. "
						"하지만 식량이 떨어졌거나 전투에서 농성을 하여 모든 개미들을 "
						"공포에 떨개하면 불만이 급속도로 올라갈 것이다."
						"\n\n"
						"page 3 of 5";
	libraryarray[1].page[3] = "꼭 읽어야 하는 왕국 매뉴얼\n\n"
						"불만이 폭발하면 그 왕국은 그걸로 끝이다. 따라서 모든 방법을 "
						"동원해서라도 불만을 줄여라."
						"\n네번째, 세력에 대한 것이다. 왕국의 개체수는 세력에 비례해서 증가한다. "
						"알을 더 생산할 수 있는 상황이어도 세력이 적다면 알을 낳지 않는것은 "
						"태초부터 내려온 방식이다. 즉, 세력을 확장하지 않고서는 개체수를 "
						"늘릴 수 없다."
						"\n세력은 굴의 확장, 연구과제 수행, 세력을 증가시키는 아이템 등을 "
						"통해 증가된다. 또한 식량이 충분하다면 세력은 자연히 증가한다. "
						"\n\n"
						"page 4 of 5";
	libraryarray[1].page[4] = "꼭 읽어야 하는 왕국 매뉴얼\n\n"
						"심지어 소유하는 자원의 양 자체도 세력 평가에 포함된다. 반면 "
						"불만은 세력의 확장을 저지시킨다. "
						"\n마지막으로 몇 가지 알아두어야 할 것을 적는다. 사냥과 수색은 "
						"위험한 작업이다. 천적에게 잡아 먹히거나 전투 중에 죽을 수도 있다. "
						"정보창에 나오는 자원 생산량과 소비량에는 주기적으로 발생하는 사건만 "
						"포함된다. 예를들어 조공 같은 경우는 역시 주기적으로 보내는 것이므로 포함된다. "
						"\n\n"
						"page 5 of 5";

	libraryarray[2].totalpage = 1;
	libraryarray[2].page[0] = "개미 연방\n\n"
						"개미 연방에 가입한 개미의 종류는 그 수를 헤아리기 어려울 "
						"정도로 많다. 서기 1608년을 기준으로 약 13506종이 가입을 한 "
						"상태이다. 미가입한 종류까지 합하면 15000종을 넘기는 것으로 "
						"보인다. 개미 연방에 가입한 많은 개미들에 대한 보고서를 보면 "
						"각자의 형태는 다양하다는 것을 알 수 있다. 하지만 흥미로운 점은 "
						"개미 공동체의 언어는 거의 유사하여 통역이 필요없다는 것이다."
						"이 사실은 수 많은 개미 종들은 한 때는 같은 종족에서 출발하지 "
						"않았나를 말하고자 하는게 아닐까 싶다."; 

	libraryarray[3].totalpage = 2;
	libraryarray[3].page[0] = "진기한 물건들의 행방\n\n"
						"만약 아이템 수집에 관심이 많다면 이 책을 든 그대는 "
						"축복을 받았음이 틀림없다. 나는 일평생을 아이템 소재 파악에 "
						"보냈다. 이제 나의 지식을 대중과 공유할까 한다. "
						"알다시피 몇 개의 아이템은 어느 누구도 찾지 못한 곳에 숨겨져 "
						"있다. 아니면 앞에 두고도 찾지 못했거나. 어쨌든 그 수는 약 4개 "
						"정도로 파악된다."
						"\n\n"
						"page 1 of 2";
	libraryarray[3].page[1] = "진기한 물건들의 행방\n\n"
						"알려진 바로는 난쟁이개미종족은 선조때부터 내려온 유물을 "
						"가지고 있다고 한다. 메뚜기종족은 우연히 어느 손가락의 그림을 "
						"발견 했는데 그것을 보자마자 그들의 보물 1호가 되었다는 일화로 유명하다. "
						"꿀벌의 로열젤리는 누구나 탐내는 것이지만 꿀벌의 거센 공격을 감수하면서 그것을 "
						"구할 자가 있을지 궁금하다."
						"\n\n"
						"page 2 of 2";

	libraryarray[4].totalpage = 4;
	libraryarray[4].page[0] = "전쟁의 미학\n\n"
						"전쟁은 예술이다. 충격이다. 숭고한 존재이다. 제3자의 입장에서는 "
						"전쟁은 한낮 흥미로운 광경에 지나지 않는다. 그렇다면 이제 전쟁의 "
						"미를 완성시켜보자. 전쟁의 시작은 전략의 수립이다. 공격 전략과 "
						"방어 전략으로 나눌 수 있겠는데, 공격 전략은 자원 약탈, 일반 공격, "
						"정복으로 나눌 수 있다. 자원 약탈은 문자 그대로 자원 약탈의 목적으로 "
						"병사를 파견하는 것이다. "
						"\n\n"
						"page 1 of 4";
	libraryarray[4].page[1] = "전쟁의 미학\n\n"
						"물론 자원 약탈이 목적이므로 전투를 효과적으로 대처하지 못하는 단점은 "
						"있다. 병력의 1/3을 잃거나 반나절이 조금 넘으면 후퇴를 시작한다. 일반 공격은 "
						"공격을 위주로 하되 자원 약탈을 병행한다. 병력의 1/2를 잃거나 하루가 조금 "
						"후퇴를 시작한다. 마지막으로 정복은 가장 효과적으로 전투를 수행할 수 있는 "
						"전략이다. 그들의 목표는 상대의 항복이므로 후퇴란 있을 수 없다."
						"\n\n"
						"page 2 of 4";
	libraryarray[4].page[2] = "전쟁의 미학\n\n"
						"방어 전략에는 농성과 요격이 있다. 농성은 방어가 효과적이지만 굴에 "
						"간접적인 타격이 있을 수 있고 자원 약탈의 위험이 있다. 또한 전쟁으로 "
						"인한 공포에 의해 불만이 쌓일 수 있다. 요격은 농성보다는 덜 효과적이나 "
						"농성의 약점이 요격에서는 강점이 된다. 이쯤에서 각 전략의 상성을 살펴보자. "
						"모든 전략에 상성이 있는 것은 아니지만 몇 가지의 경우에는 존재한다. "
						"공격 전략으로 자원 약탈을 했을 때 상대가 요격을 한다면 상대에게 감사의 "
						"편지를 써보자."
						"\n\n"
						"page 3 of 4";
	libraryarray[4].page[3] = "전쟁의 미학\n\n"
						"적이 요격을 하는 틈을 타서 자원 약탈을 손쉽게 할 수 있기 때문이다. 반대로 "
						"농성을 하고 있다면 불가능한 것은 아니나 자원 약탈이 어렵게 된다. 전략은 "
						"이쯤에서 멈추기로 하고 다음은 몇 가지의 요소를 더 살펴보자. 공격자의 입장에서 "
						"공격에 패널티가 적은 계절은 여름이다. 그 다음은 봄과 가을이며, 마지막은 겨울이다. "
						"말할 필요도 없이 병사의 양은 중요하다. 그러나 각 개체마다 전투력이 다르다는 "
						"사실을 명심하기 바란다."
						"\n\n"
						"page 4 of 4";

	libraryarray[5].totalpage = 4;
	libraryarray[5].page[0] = "상대적이고 절대적인 지식의 백과사전2\n\n"
						"연대 의식\n\n"
						"연대 의식은 기쁨이 아닌 고통에서 생긴다. 누구나 즐거운 일을 함께한 사람보다 "
						"고통의 순간을 함께 나눈 사람에게 더 친근함을 느낀다. 불행한 시기에 사람들은 "
						"연대 의식을 느끼며 단결하지만, 행복한 시기엔 분열한다. 왜 그럴까? 힘을 합해 "
						"승리하는 순간, 각자 자기 공적에 비해 보상이 부족하다고 느끼기 때문이다. "
						"\n\n"
						"page 1 of 4";
	libraryarray[5].page[1] = "상대적이고 절대적인 지식의 백과사전2\n\n"
						"저마다 자기가 공동의 성공에 기여한 유일한 공로자라고 생각한다. 그리고 서서히 "
						"소외감에 빠진다."
						"친한 사람들을 갈라놓는 가장 좋은 방법은 그들에게 공동의 성공을 안겨 주는 "
						"것이다. 얼마나 많은 가족이 상속을 둘러싸고 사이가 벌어지는가? 성공을 한 "
						"다음의 로큰롤 그룹이 함께 남아 있는 경우가 얼마나 되는가? 얼마나 많은 정치 "
						"단체들이 권력을 잡은 후 분열하는가?\n"
						"\n\n"
						"page 2 of 4";
	libraryarray[5].page[2] = "상대적이고 절대적인 지식의 백과사전2\n\n"
						"벗들과의 우정을 간직하려면, 자기들이 성공한 일에 대해 이야기하기보다는 "
						"자기들이 실망한 일, 실패한 일을 자꾸 들먹이는 쪽이 낫다."
						"어원적으로 보면, 공감(sympathie)이란 말은 '함께 고통을 겪다'라는 뜻의 "
						"그리스 어(soun pathein)에서 유래한다. 마찬가지로 동정(compassion)이란 "
						"말 또한 '함께 고통을 겪다'라는 뜻의 라틴 어(cum patior)에서 나온 것이다. "
						"\n\n"
						"page 3 of 4";
	libraryarray[5].page[3] = "상대적이고 절대적인 지식의 백과사전2\n\n"
						"대부분의 종교에서 순교자들을 기리는 일에 정성을 다하는 것도 그런 것과 "
						"관계가 있다. 저마다 상상 속에서나마 골고다의 언덕이나 선구자들의 고난을 "
						"겪게 함으로써, 공동체의 끈끈한 연대를 유지하려는 것이다.\n"
						"(by 에드몽 웰즈)"
						"\n\n"
						"page 4 of 4";

	libraryarray[6].totalpage = 2;
	libraryarray[6].page[0] = "개미 사회에 대한 고찰\n\n"
						"개미 사회의 신분 제도는 간단하다. 여왕, 공주, 수개미, 일개미, 병정 개미로 "
						"구성된다. 자신의 왕국에서 공주로 태어난 예비 여왕은 일개미와 비교되는 "
						"장신의 매끈한 몸체를 가졌다. 혼례를 올리기 전까지의 공주개미는 수개미들과 "
						"격리된채 혼례의 날짜만을 기다린다. 결혼비행을 알리는 페르몬이 분산되면 "
						"수많은 공주 개미과 수개미가 하늘로 날아 조우하게 된다. 결혼비행 도중에 "
						"많은 개미들이 천적에게 죽임을 당한다."
						"\n\n"
						"page 1 of 2";
	libraryarray[6].page[1] = "개미 사회에 대한 고찰\n\n"
						"결혼에 성공한 공주개미는 새로운 왕국을 건설하기 위한 영토를 물색하게 된다. "
						"많은 수의 공주개미는 이시기에 죽음을 맞이한다. 종류에 따라서 신왕국 건설의 "
						"형태가 달라질 때가 있는데 결혼비행 후 다른 종류의 왕국에 잠입해 여왕만을 "
						"노려 암살한 후 그 왕국을 송두리째 삼켜버리는 경우도 있다."
						"\n\n"
						"page 2 of 2";

	libraryarray[7].totalpage = 1;
	libraryarray[7].page[0] = "상대적이고 절대적인 지식의 백과사전3\n\n"
						"십이 초 동안\n\n"
						"당신이 다음 몇 줄의 글을 읽는 십이 초 동안,\n"
						" - 40명의 사람과 7억 마리의 개미가 지구 위에 태어나고 있다.\n"
						" - 30명의 사람과 5억 마리의 개미가 지구 위에서 죽어 가고 있다.\n"
						"(by 에드몽 웰즈)";

	libraryarray[8].totalpage = 1;
	libraryarray[8].page[0] = "너희가 예술을 아느냐\n\n"
						"예술이란 무엇인가? 이 질문에 대답할 수 있는 자는 아마 "
						"없을 것이다. 대부분이 처음 듣기 때문이다. 하지만 손가락은 "
						"이것의 강력한 이점을 잘 알고 있다. 그들은 예술을 통해 "
						"불만을 승화시킨다. 또한 많은 활동에 있어 긍정적인 영향을 "
						"주는 것으로 밝혀 졌다. 무슨 얘기를 하는 지 모를 수 있다. "
						"하지만 나는 보았다. 나는 개미 역사상 최초로 인간과 교류한 "
						"개미 103호다.";
		
		
	return 1;
}

int CObjDialog::ObjDialog_Shutdown()
{

	return 1;
}

int CObjDialog::ShowObjDialog_Worker()
{
	int temp = rand()%3;
	
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );


	if(time_.GetSeason() == SPRING)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[0][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[0][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[0][2]);
	}
	else if(time_.GetSeason() == SUMMER)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[1][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[1][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[1][2]);
	}
	else if(time_.GetSeason() == FALL)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[2][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[2][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[2][2]);
	}
	else if(time_.GetSeason() == WINTER)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[3][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[3][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.worker_dialog[3][2]);
	}

	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );
	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_Soldier()
{
	int temp = rand()%3;
	
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );

	if(time_.GetSeason() == SPRING)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[0][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[0][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[0][2]);
	}
	else if(time_.GetSeason() == SUMMER)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[1][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[1][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[1][2]);
	}
	else if(time_.GetSeason() == FALL)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[2][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[2][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[2][2]);
	}
	else if(time_.GetSeason() == WINTER)
	{
		if(temp == 0)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[3][0]);
		else if(temp == 1)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[3][1]);
		else if(temp == 2)
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.soldier_dialog[3][2]);
	}

	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );
	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Adviser()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_ADVISER),
		main_window_handle,  (DLGPROC)AdviserDlgProc );
	SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.queen_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Nanny()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NANNY),
		main_window_handle,  (DLGPROC)NannyDlgProc );
	SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.queen_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Queen()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.queen_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Scientist()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.scientist_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Mushroom_Ant()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.mushroom_ant_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Church_Ant()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.church_ant_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Hired_1()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.hired_1_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Hired_2()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.hired_2_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Training_Ant()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.training_ant_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Art_Ant()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.art_ant_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_Aphid()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.aphid_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::ShowObjDialog_StrangeStone()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	if(story_.GetStoryFlag() & CHAP_2_4_DONE)
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.strangestone_dialog[1]);
	else
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.strangestone_dialog[0]);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_BuildingQueen()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.buildingqueen_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_Egg()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.egg_dialog);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_WareHouse()
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	if(story_.IsAphidRoomBuilt() == FALSE)
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.warehouse_dialog[0]);
	else
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.warehouse_dialog[1]);

	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_Under_Construction(int BUILDINGARRAY_INDEX)
{
	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
		main_window_handle,  (DLGPROC)NormalDlgProc );
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );


	if(CPlayer::num_worker_building != 0)
		sprintf(buffer, "%s\n\n진척도 : %.1f%%\n\n남은 예상 공사기간 : %d일", 
			building_.buildingarray[BUILDINGARRAY_INDEX].buildingtype,
			(building_.buildingarray[BUILDINGARRAY_INDEX].inittime-building_.buildingarray[BUILDINGARRAY_INDEX].remaintime)
				*100.0/building_.buildingarray[BUILDINGARRAY_INDEX].inittime,
			building_.buildingarray[BUILDINGARRAY_INDEX].remaintime/CPlayer::num_worker_building/UNIT_PER_TICK/UNIT_PER_DAY);
	else
		sprintf(buffer, "%s\n\n진척도 : %.1f%%\n\n남은 예상 공사기간 : %s일",
			building_.buildingarray[BUILDINGARRAY_INDEX].buildingtype,
			(building_.buildingarray[BUILDINGARRAY_INDEX].inittime-building_.buildingarray[BUILDINGARRAY_INDEX].remaintime)
				*100.0/building_.buildingarray[BUILDINGARRAY_INDEX].inittime,
			"'경고'건설을 담당하는 일꾼 개미들이 없어서 더 이상 진행할 수 없습니다.");

	SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, buffer);

	WaitDialog();

	return 1;
}

int CObjDialog::ShowObjDialog_Library()
{
	if(object_.objarray[OBJARRAY_BUILDING_LIBARAY].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_LIBARAY);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_LIBARAY),
			main_window_handle,  (DLGPROC)LibraryDlgProc );
		SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}

int CObjDialog::ShowObjDialog_Depository()
{
	if(object_.objarray[OBJARRAY_BUILDING_DEPOSITORY].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_DEPOSITORY);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
			main_window_handle,  (DLGPROC)NormalDlgProc );
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.depository_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_Lab()
{
	if(object_.objarray[OBJARRAY_BUILDING_LAB].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_LAB);
	else
	{
		if(lab_on_subject == NULL)
		{
			if(hWndDlg_obj)
				EndDialog( hWndDlg_obj, TRUE );
			if(labflag & LAB_UPGRADED)
				hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_LAB),
					main_window_handle,  (DLGPROC)LabDlgProc );
			else
				hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_LAB_INIT),
					main_window_handle,  (DLGPROC)LabDlgProc );
			SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
			ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

			WaitDialog();
		}
		else
		{
			if(hWndDlg_obj)
				EndDialog( hWndDlg_obj, TRUE );
			hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
				main_window_handle,  (DLGPROC)NormalDlgProc );
			ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );


			sprintf(buffer, "연구과제 : %s\n\n진척도 : %.1f%%\n\n남은 연구기간 : %d", 
				labarray[selectedindex].name,
				(labarray[selectedindex].inittime-labarray[selectedindex].remaintime)
					*100.0/labarray[selectedindex].inittime,
					labarray[selectedindex].remaintime/UNIT_PER_TICK/UNIT_PER_DAY);

			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, buffer);

			WaitDialog();
		}
	}
	return 1;
}
int CObjDialog::ShowObjDialog_Training()
{
	if(object_.objarray[OBJARRAY_BUILDING_TRAINING].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_TRAINING);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
			main_window_handle,  (DLGPROC)NormalDlgProc );
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.training_dilaog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_Mushroom()
{
	if(object_.objarray[OBJARRAY_BUILDING_MUSHROOM].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_MUSHROOM);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
			main_window_handle,  (DLGPROC)NormalDlgProc );
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.mushroom_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_BuildingHired_1()
{
	if(object_.objarray[OBJARRAY_BUILDING_HIRED_1].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_HIRED_1);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_HIRED),
			main_window_handle,  (DLGPROC)HiredDlgProc );
		SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
		SetDlgItemTextA(hWndDlg_obj, IDC_STATIC_HIRED, dialog.buildinghired_1_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_BuildingHired_2()
{
	if(object_.objarray[OBJARRAY_BUILDING_HIRED_2].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_HIRED_2);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_HIRED),
			main_window_handle,  (DLGPROC)HiredDlgProc );
		SendMessage(hWndDlg_obj, WM_GETPOINT, NULL, (LPARAM)this);
		SetDlgItemTextA(hWndDlg_obj, IDC_STATIC_HIRED, dialog.buildinghired_2_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_Church()
{
	if(object_.objarray[OBJARRAY_BUILDING_CHURCH].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_CHURCH);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
			main_window_handle,  (DLGPROC)NormalDlgProc );
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.church_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_Art()
{
	if(object_.objarray[OBJARRAY_BUILDING_ART].temp[BULIDING_INT_STATE] == BUILDING_UNDER_CONSTRUCTION)
		ShowObjDialog_Under_Construction(BUILDINGARRAY_ART);
	else
	{
		if(hWndDlg_obj)
			EndDialog( hWndDlg_obj, TRUE );
		hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
			main_window_handle,  (DLGPROC)NormalDlgProc );
		SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, dialog.art_dialog);
		ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

		WaitDialog();
	}

	return 1;
}
int CObjDialog::ShowObjDialog_Seller()
{
	if(object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_DIALOG] == 0)
	{
		if(item_.GetItem(4) == PLAYER)
		{
			if(hWndDlg_obj)
				EndDialog(hWndDlg_obj, TRUE );
			hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
				main_window_handle,  (DLGPROC)NormalDlgProc );
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "상인 무당벌레\n\n\"지금은 팔 아이템이 없습니다. 다음에 뵙지요.\"");
			ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

			WaitDialog();

			return 0;
		}
	}
	else
	{
		if(item_.GetItem(6) == PLAYER)
		{
			if(hWndDlg_obj)
				EndDialog(hWndDlg_obj, TRUE );
			hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
				main_window_handle,  (DLGPROC)NormalDlgProc );
			SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "상인 무당벌레\n\n\"지금은 팔 아이템이 없습니다. 다음에 뵙지요.\"");
			ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

			WaitDialog();

			return 0;
		}
	}

	CTime::SetPause(PAUSE_SELLER);

	if(hWndDlg_obj)
		EndDialog( hWndDlg_obj, TRUE );
	hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_EVENT_SELLER),
		main_window_handle,  (DLGPROC)SellerDlgProc );
	if(object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_DIALOG] == 0)
		SetDlgItemTextA(hWndDlg_obj, IDC_STATIC_ITEM, dialog.seller_dialog[0]);
	if(object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_DIALOG] == 1)
		SetDlgItemTextA(hWndDlg_obj, IDC_STATIC_ITEM, dialog.seller_dialog[1]);
	sprintf(buffer, "가격\n식량 : %d, 목재 : %d, 광석 : %d",
		object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_FOOD],
		object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_TIMBER],
		object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_MINERAL]);
	SetDlgItemTextA(hWndDlg_obj, IDC_STATIC_ITEM_COST, buffer);
	ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

	WaitDialog();

	return 1;

}
int CObjDialog::ShowExpDialog(int labindex)
{
	if(hWndDlg_obj_additonal)
		EndDialog( hWndDlg_obj_additonal, TRUE );
	hWndDlg_obj_additonal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_EXP),
		main_window_handle,  (DLGPROC)ExpDlgProc );
	SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_EXP, labarray[labindex].describe_lab);
	sprintf(buffer,
			"필요 자원\n식량 : %d, 목재 : %d, 광석 : %d",
			labarray[labindex].lab_cost[0],
			labarray[labindex].lab_cost[1],
			labarray[labindex].lab_cost[2]);
	SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_COST, buffer);
	sprintf(buffer, "연구 기간 : %d일", labarray[labindex].inittime/UNIT_PER_TICK/UNIT_PER_DAY);
	SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_PERIOD, buffer);
	ShowWindow( hWndDlg_obj_additonal, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::CheckLabTime()
{
	if(BATTLE_IN_STATE == BATTLE_IN_BREAK)
		return 0;

	for(int i=0; i<MAX_LAB; i++)
	{
		if(lab_on_subject == labarray[i].name)
		{
			labarray[i].remaintime -= 1;
			if(labarray[i].remaintime < 0)
			{
				if(labarray[i].name == "고농축 개미산")
					SET_BIT(labflag, LAB_1_DONE);
				if(labarray[i].name == "영양 교환의 개선")
					SET_BIT(labflag, LAB_2_DONE);
				if(labarray[i].name == "건설의 혁신")
					SET_BIT(labflag, LAB_3_DONE);
				if(labarray[i].name == "언어 - 민달팽이")
				{
					SET_BIT(labflag, LAB_4_DONE);
					diplomatic_.LearnLanguage(SPEARRAY_SNAIL);
					diplomatic_.ChangeRelation(SPEARRAY_SNAIL, 2000);
				}
				if(labarray[i].name == "언어 - 꿀벌")
				{
					SET_BIT(labflag, LAB_5_DONE);
					diplomatic_.LearnLanguage(SPEARRAY_BEE);
					diplomatic_.ChangeRelation(SPEARRAY_BEE, 2000);
				}
				if(labarray[i].name == "언어 - 메뚜기")
				{
					SET_BIT(labflag, LAB_6_DONE);
					diplomatic_.LearnLanguage(SPEARRAY_GRASSHOPPER);
					diplomatic_.ChangeRelation(SPEARRAY_GRASSHOPPER, 2000);
				}
				if(labarray[i].name == "융통성")
				{
					SET_BIT(labflag, LAB_7_DONE);
					domestic_.UpgradeDom(LAB_7_DONE);
				}
				if(labarray[i].name == "적응력")
				{
					SET_BIT(labflag, LAB_8_DONE);
					domestic_.UpgradeDom(LAB_9_DONE);
				}
				if(labarray[i].name == "광산의 개발")
					SET_BIT(labflag, LAB_9_DONE);
				if(labarray[i].name == "불을 이용한 방어법")
					SET_BIT(labflag, LAB_10_DONE);
				if(labarray[i].name == "긍정적 사고")
					SET_BIT(labflag, LAB_11_DONE);
				if(labarray[i].name == "언어 - 장수풍뎅이")
					SET_BIT(labflag, LAB_12_DONE);
				if(labarray[i].name == "언어 - 사슴벌레")
					SET_BIT(labflag, LAB_13_DONE);

				if(hWndDlg_obj_additonal)
					EndDialog(hWndDlg_obj, TRUE );
				hWndDlg_obj_additonal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				SetDlgItemTextA(hWndDlg_obj_additonal, IDC_NORMAL, "알림\n\n연구과제가 완료되었습니다.");
				ShowWindow(hWndDlg_obj_additonal, SW_SHOWNORMAL );

				WaitDialog();

				lab_on_subject = NULL;
			}
		}
	}

	return 1;
}
int CObjDialog::ShowBookDialog(int bookindex)
{
	if(hWndDlg_obj_additonal)
		EndDialog( hWndDlg_obj_additonal, TRUE );
	hWndDlg_obj_additonal = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_BUILDING_BOOK),
		main_window_handle,  (DLGPROC)BookDlgProc );
	SendMessageA(hWndDlg_obj_additonal, WM_GETPOINT, NULL, (LPARAM)&libraryarray[bookindex]);
	SendMessageA(hWndDlg_obj_additonal, WM_GETPAGE, (WPARAM)0, libraryarray[bookindex].totalpage);
	SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_BOOK,libraryarray[bookindex].page[0]);
	ShowWindow( hWndDlg_obj_additonal, SW_SHOWNORMAL );

	WaitDialog();

	return 1;
}
int CObjDialog::CheckLibraryTime()
{
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 25) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_3_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 34) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_4_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 39) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_5_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 42) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_6_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 48) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_7_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 62) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_8_RELEASE);
	if((time_.GetYear() == 0) && (time_.GetSeason() == WINTER) && 
		(time_.GetMonth3() == 69) && time_.GetDay() == 0*UNIT_PER_TICK)
		SET_BIT(libraryflag, BOOK_9_RELEASE);

	return 1;
}
int CObjDialog::UpgradeLab()
{
	SET_BIT(labflag, LAB_UPGRADED); 
	return 1;
}
BOOL CObjDialog::GetHiredCheck()
{
	return CheckedHired;
}
HWND CObjDialog::GetHwnDia_Obj()
{
	return hWndDlg_obj;
}
HWND CObjDialog::GetHwnDia_Obj_Additonal()
{
	return hWndDlg_obj_additonal;
}
INT_PTR CALLBACK CObjDialog::LabDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	static HWND hradio1;
	static HWND hradio2;
	static HWND hradio3;
	static HWND hradio4;
	static HWND hradio5;
	static HWND hradio6;
	static HWND hradio7;
	static HWND hradio8;
	static HWND hradio9;
	static HWND hradio10;
	static HWND hradio11;
	static HWND hradio12;
	static HWND hradio13;

	int Checked = FALSE;
	static int selectedindex;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_LIB_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_LIB_RADIO2);
			hradio3 = GetDlgItem(hDlg, IDC_LIB_RADIO3);
			hradio4 = GetDlgItem(hDlg, IDC_LIB_RADIO4);
			hradio5 = GetDlgItem(hDlg, IDC_LIB_RADIO5);
			hradio6 = GetDlgItem(hDlg, IDC_LIB_RADIO6);
			hradio7 = GetDlgItem(hDlg, IDC_LIB_RADIO7);
			hradio8 = GetDlgItem(hDlg, IDC_LIB_RADIO8);
			hradio9 = GetDlgItem(hDlg, IDC_LIB_RADIO9);
			hradio10 = GetDlgItem(hDlg, IDC_LIB_RADIO10);
			hradio11 = GetDlgItem(hDlg, IDC_LIB_RADIO11);
			hradio12 = GetDlgItem(hDlg, IDC_LIB_RADIO12);
			hradio13 = GetDlgItem(hDlg, IDC_LIB_RADIO13);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			selectedindex = -1;
			debug_.GetValue("index", &selectedindex, 0, lpddsback, 16, ONLY_V1);
			if(pThis->labflag & LAB_1_DONE)
				EnableWindow(hradio1, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);
					selectedindex = 0;
				}
			}
			if(pThis->labflag & LAB_2_DONE)
				EnableWindow(hradio2, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio2, BM_SETCHECK, TRUE, NULL);
					selectedindex = 1;
				}
			}
			if(pThis->labflag & LAB_3_DONE)
				EnableWindow(hradio3, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio3, BM_SETCHECK, TRUE, NULL);
					selectedindex = 2;
				}
			}
			if(pThis->labflag & LAB_4_DONE)
				EnableWindow(hradio4, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio4, BM_SETCHECK, TRUE, NULL);
					selectedindex = 3;
				}
			}
			if(pThis->labflag & LAB_5_DONE)
				EnableWindow(hradio5, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio5, BM_SETCHECK, TRUE, NULL);
					selectedindex = 4;
				}

			}
			if(pThis->labflag & LAB_6_DONE)
				EnableWindow(hradio6, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio6, BM_SETCHECK, TRUE, NULL);
					selectedindex = 5;
				}
			}
			if(pThis->labflag & LAB_7_DONE)
				EnableWindow(hradio7, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio7, BM_SETCHECK, TRUE, NULL);
					selectedindex = 6;
				}
			}
			if(pThis->labflag & LAB_8_DONE)
				EnableWindow(hradio8, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio8, BM_SETCHECK, TRUE, NULL);
					selectedindex = 7;
				}
			}
			if(pThis->labflag & LAB_9_DONE)
				EnableWindow(hradio9, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio9, BM_SETCHECK, TRUE, NULL);
					selectedindex = 8;
				}
			}
			if(pThis->labflag & LAB_10_DONE)
				EnableWindow(hradio10, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio10, BM_SETCHECK, TRUE, NULL);
					selectedindex = 9;
				}
			}
			if(pThis->labflag & LAB_11_DONE)
				EnableWindow(hradio11, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio11, BM_SETCHECK, TRUE, NULL);
					selectedindex = 10;
				}
			}
			if(pThis->labflag & LAB_12_DONE)
				EnableWindow(hradio12, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio12, BM_SETCHECK, TRUE, NULL);
					selectedindex = 11;
				}
			}
			if(pThis->labflag & LAB_13_DONE)
				EnableWindow(hradio13, FALSE);
			else
			{
				if(!Checked)
				{
					Checked = TRUE;
					SendMessage(hradio13, BM_SETCHECK, TRUE, NULL);
					selectedindex = 12;
				}
			}

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDC_LIB_BUTTON1:
				pThis->ShowExpDialog(0);
				return TRUE;
			case IDC_LIB_BUTTON2:
				pThis->ShowExpDialog(1);
				return TRUE;
			case IDC_LIB_BUTTON3:
				pThis->ShowExpDialog(2);
				return TRUE;
			case IDC_LIB_BUTTON4:
				pThis->ShowExpDialog(3);
				return TRUE;
			case IDC_LIB_BUTTON5:
				pThis->ShowExpDialog(4);
				return TRUE;
			case IDC_LIB_BUTTON6:
				pThis->ShowExpDialog(5);
				return TRUE;
			case IDC_LIB_BUTTON7:
				pThis->ShowExpDialog(6);
				return TRUE;
			case IDC_LIB_BUTTON8:
				pThis->ShowExpDialog(7);
				return TRUE;
			case IDC_LIB_BUTTON9:
				pThis->ShowExpDialog(8);
				return TRUE;
			case IDC_LIB_BUTTON10:
				pThis->ShowExpDialog(9);
				return TRUE;
			case IDC_LIB_BUTTON11:
				pThis->ShowExpDialog(10);
				return TRUE;
			case IDC_LIB_BUTTON12:
				pThis->ShowExpDialog(11);
				return TRUE;
			case IDC_LIB_BUTTON13:
				pThis->ShowExpDialog(12);
				return TRUE;
			case IDC_LIB_RADIO1:
				selectedindex = 0;
				return TRUE;
			case IDC_LIB_RADIO2:
				selectedindex = 1;
				return TRUE;
			case IDC_LIB_RADIO3:
				selectedindex = 2;
				return TRUE;
			case IDC_LIB_RADIO4:
				selectedindex = 3;
				return TRUE;
			case IDC_LIB_RADIO5:
				selectedindex = 4;
				return TRUE;
			case IDC_LIB_RADIO6:
				selectedindex = 5;
				return TRUE;
			case IDC_LIB_RADIO7:
				selectedindex = 6;
				return TRUE;
			case IDC_LIB_RADIO8:
				selectedindex = 7;
				return TRUE;
			case IDC_LIB_RADIO9:
				selectedindex = 8;
				return TRUE;
			case IDC_LIB_RADIO10:
				selectedindex = 9;
				return TRUE;
			case IDC_LIB_RADIO11:
				selectedindex = 10;
				return TRUE;
			case IDC_LIB_RADIO12:
				selectedindex = 11;
				return TRUE;
			case IDC_LIB_RADIO13:
				selectedindex = 12;
				return TRUE;
			case IDCANCEL:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;
				return TRUE;
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;

				if(selectedindex == -1)
					return TRUE;

				if((pThis->labarray[selectedindex].lab_cost[0] > CPlayer::food/NUM_CIPHER)
						|| (pThis->labarray[selectedindex].lab_cost[1] > CPlayer::timber/NUM_CIPHER)
						|| (pThis->labarray[selectedindex].lab_cost[2] > CPlayer::mineral/NUM_CIPHER))
				{
					if(hWndDlg_obj)
						EndDialog(hWndDlg_obj, TRUE );
					hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "경고\n\n자원이 부족합니다.");
					ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

					WaitDialog();
					return TRUE;
				}

				domestic_.ChangeResource(-pThis->labarray[selectedindex].lab_cost[0]*NUM_CIPHER,
									 -pThis->labarray[selectedindex].lab_cost[1]*NUM_CIPHER,
									 -pThis->labarray[selectedindex].lab_cost[2]*NUM_CIPHER);

				if(hWndDlg_obj)
					EndDialog(hWndDlg_obj, TRUE );
				hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "알림\n\n연구과제를 시작합니다. 연구가 완료되기 전까지는 "
														"연구과제를 변경할 수 없습니다.");
				ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

				WaitDialog();

				pThis->selectedindex = selectedindex;
				pThis->lab_on_subject = pThis->labarray[selectedindex].name;

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
           hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::LibraryDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	static HWND hbutton1;
	static HWND hbutton2;
	static HWND hbutton3;
	static HWND hbutton4;
	static HWND hbutton5;
	static HWND hbutton6;
	static HWND hbutton7;
	static HWND hbutton8;
	static HWND hbutton9;

	switch (msg)
    {
        case WM_INITDIALOG:
			hbutton1 = GetDlgItem(hDlg, IDC_LAB_BUTTON1);
			hbutton2 = GetDlgItem(hDlg, IDC_LAB_BUTTON2);
			hbutton3 = GetDlgItem(hDlg, IDC_LAB_BUTTON3);
			hbutton4 = GetDlgItem(hDlg, IDC_LAB_BUTTON4);
			hbutton5 = GetDlgItem(hDlg, IDC_LAB_BUTTON5);
			hbutton6 = GetDlgItem(hDlg, IDC_LAB_BUTTON6);
			hbutton7 = GetDlgItem(hDlg, IDC_LAB_BUTTON7);
			hbutton8 = GetDlgItem(hDlg, IDC_LAB_BUTTON8);
			hbutton9 = GetDlgItem(hDlg, IDC_LAB_BUTTON9);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			if(pThis->libraryflag & BOOK_3_RELEASE)
				EnableWindow(hbutton3, TRUE);
			if(pThis->libraryflag & BOOK_4_RELEASE)
				EnableWindow(hbutton4, TRUE);
			if(pThis->libraryflag & BOOK_5_RELEASE)
				EnableWindow(hbutton5, TRUE);
			if(pThis->libraryflag & BOOK_6_RELEASE)
				EnableWindow(hbutton6, TRUE);
			if(pThis->libraryflag & BOOK_7_RELEASE)
				EnableWindow(hbutton7, TRUE);
			if(pThis->libraryflag & BOOK_8_RELEASE)
				EnableWindow(hbutton8, TRUE);
			if(pThis->libraryflag & BOOK_9_RELEASE)
				EnableWindow(hbutton9, TRUE);

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDC_LAB_BUTTON1:
				pThis->ShowBookDialog(0);
				return TRUE;
			case IDC_LAB_BUTTON2:
				pThis->ShowBookDialog(1);
				return TRUE;
			case IDC_LAB_BUTTON3:
				pThis->ShowBookDialog(2);
				return TRUE;
			case IDC_LAB_BUTTON4:
				pThis->ShowBookDialog(3);
				return TRUE;
			case IDC_LAB_BUTTON5:
				pThis->ShowBookDialog(4);
				return TRUE;
			case IDC_LAB_BUTTON6:
				pThis->ShowBookDialog(5);
				return TRUE;
			case IDC_LAB_BUTTON7:
				pThis->ShowBookDialog(6);
				return TRUE;
			case IDC_LAB_BUTTON8:
				pThis->ShowBookDialog(7);
				return TRUE;
			case IDC_LAB_BUTTON9:
				pThis->ShowBookDialog(8);
				return TRUE;
			case IDCANCEL:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;

                return TRUE;
            }
            break;

        case WM_MOVE:
			{
				RECT dest_rect = {0, 0, 640, 480};
				lpddsprimary->Blt(&dest_rect,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             &dest_rect,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
           hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::BookDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static _library *plibrary;
	static int curpage;
	static int totalpage;

	switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
		case WM_GETPOINT:
			plibrary = (_library *)lParam;
			debug_.GetValue("curpage, totalpage : ", &curpage, &totalpage, lpddsback, 8, NULL);
			return TRUE;
		case WM_GETPAGE:
			curpage = (int)wParam;
			totalpage = (int)lParam;
			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDNEXT:
				if(curpage < totalpage-1)
				{
					curpage++;
					SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_BOOK, plibrary->page[curpage]);
				}
				return TRUE;
            case IDPREVIEW:
				if(curpage > 0)
				{
					curpage--;
					SetDlgItemTextA(hWndDlg_obj_additonal, IDC_STATIC_BOOK, plibrary->page[curpage]);
				}
				return TRUE;
            case IDCANCEL:
                EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj_additonal = NULL;
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
			hWndDlg_obj_additonal = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::ExpDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj_additonal = NULL;
                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				RECT dest_rect = {0, 0, 640, 480};
				lpddsprimary->Blt(&dest_rect,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             &dest_rect,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_obj_additonal = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::NormalDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                case IDOK:
                    EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj = NULL;
					hWndDlg_obj_additonal = NULL;
                    return TRUE;
            }
            break;

        case WM_MOVE:
			{
				RECT dest_rect = {0, 0, 640, 480};
				lpddsprimary->Blt(&dest_rect,  // pointer to dest RECT
                             lpddsback,   // pointer to source surface
                             &dest_rect,// pointer to source RECT
                             DDBLT_WAIT,  // control flags
                             NULL);     // pointer to DDBLTFX holding info
			}
            break;

        case WM_DESTROY:
			hWndDlg_obj = NULL;
			hWndDlg_obj_additonal = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::HiredDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	static HWND hcheck1;

	switch (msg)
    {
        case WM_INITDIALOG:
			hcheck1 = GetDlgItem(hDlg, IDC_HIRED_CHECK1);
            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			if(pThis->CheckedHired == TRUE)
				SendMessage(hcheck1, BM_SETCHECK, TRUE, 0);
			else
				SendMessage(hcheck1, BM_SETCHECK, FALSE, 0);

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj = NULL;
					return TRUE;
                case IDOK:
					if(SendMessage(hcheck1, BM_GETCHECK, 0, 0) == BST_CHECKED)
						pThis->CheckedHired = TRUE;
					else
						pThis->CheckedHired = FALSE;
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj = NULL;

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
			hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::AdviserDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	static HWND hradio1;
	static HWND hradio2;
	static HWND hradio3;
	static HWND hradio4;
	static HWND hradio5;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_ADVISER_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_ADVISER_RADIO2);
			hradio3 = GetDlgItem(hDlg, IDC_ADVISER_RADIO3);
			hradio4 = GetDlgItem(hDlg, IDC_ADVISER_RADIO4);
			hradio5 = GetDlgItem(hDlg, IDC_ADVISER_RADIO5);

			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDCANCEL:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;
				return TRUE;
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;

				if(hWndDlg_obj)
					EndDialog( hWndDlg_obj, TRUE );
				hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				
				if(SendMessage(hradio1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_dialog[0]);
				if(SendMessage(hradio2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_dialog[1]);
				if(SendMessage(hradio3, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_dialog[2]);
				if(SendMessage(hradio4, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_dialog[3]);
				if(SendMessage(hradio5, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
				{
					if(CHAPTER == CHAP_1)
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_addition_dialog[0]);
					if(CHAPTER == CHAP_2)
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_addition_dialog[1]);
					if(CHAPTER == CHAP_3)
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_addition_dialog[2]);
					if(CHAPTER == CHAP_4)
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.adviser_addition_dialog[3]);
				}

				ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

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
			hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::NannyDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	static HWND hradio1;
	static HWND hradio2;

	switch (msg)
    {
        case WM_INITDIALOG:
			hradio1 = GetDlgItem(hDlg, IDC_NANNY_RADIO1);
			hradio2 = GetDlgItem(hDlg, IDC_NANNY_RADIO2);

			SendMessage(hradio1, BM_SETCHECK, TRUE, NULL);

            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
			case IDCANCEL:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;
				return TRUE;
            case IDOK:
				EndDialog( hDlg, TRUE );
				hDlg = NULL;
				hWndDlg_obj = NULL;

				if(hWndDlg_obj)
					EndDialog( hWndDlg_obj, TRUE );
				hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
					main_window_handle,  (DLGPROC)NormalDlgProc );
				
				if(SendMessage(hradio1, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.nanny_dialog[0]);
				if(SendMessage(hradio2, BM_GETCHECK, NULL, NULL) == BST_CHECKED)
				{
					if(item_.GetItem(2) != PLAYER)
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.nanny_dialog[1]);
					else
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, pThis->dialog.nanny_dialog[2]);
				}

				ShowWindow( hWndDlg_obj, SW_SHOWNORMAL );

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
			hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
INT_PTR CALLBACK CObjDialog::SellerDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static CObjDialog* pThis; 

	int temp_cost_food;
	int temp_cost_timber;
	int temp_cost_mineral;

	switch (msg)
    {
        case WM_INITDIALOG:
            return TRUE;
		case WM_GETPOINT:
			pThis = (CObjDialog *)lParam;

			return TRUE;
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj = NULL;

					CTime::ReleasePause(PAUSE_SELLER);

					return TRUE;
                case IDOK:
					EndDialog( hDlg, TRUE );
					hDlg = NULL;
					hWndDlg_obj = NULL;

					CTime::ReleasePause(PAUSE_SELLER);

					temp_cost_food = object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_FOOD];
					temp_cost_timber = object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_TIMBER];
					temp_cost_mineral = object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_COST_MINERAL];

					if((temp_cost_food > CPlayer::food/NUM_CIPHER)
						|| (temp_cost_timber > CPlayer::timber/NUM_CIPHER)
						|| (temp_cost_mineral > CPlayer::mineral/NUM_CIPHER))
					{
						if(hWndDlg_obj)
							EndDialog(hWndDlg_obj, TRUE );
						hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
							main_window_handle,  (DLGPROC)NormalDlgProc );
						SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "상인 무당벌레\n\n\"어허.. 자원이 부족하시군요. 죄송하지만 할부는 "
													"안됩니다.\"");
						ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

						WaitDialog();
						return TRUE;
					}

					domestic_.ChangeResource(-temp_cost_food*NUM_CIPHER,
											 -temp_cost_timber*NUM_CIPHER,
											 -temp_cost_mineral*NUM_CIPHER);

					if(hWndDlg_obj)
						EndDialog(hWndDlg_obj, TRUE );
					hWndDlg_obj = CreateDialog( main_instance, MAKEINTRESOURCE(IDD_NORMAL),
						main_window_handle,  (DLGPROC)NormalDlgProc );
					SetDlgItemTextA(hWndDlg_obj, IDC_NORMAL, "상인 무당벌레\n\n\"이용해 주셔서 감사합니다.\"");
					ShowWindow(hWndDlg_obj, SW_SHOWNORMAL );

					WaitDialog();

					if(object_.objarray[OBJARRAY_SELLER].temp[BOB_INT_SELLER_DIALOG] == 0)
						item_.BuyItem(4);
					else
						item_.BuyItem(6);

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
			hWndDlg_obj = NULL;
            break;
    }

    return FALSE;
}
int CObjDialog::Save()
{
	for(int i=0; i<MAX_LAB; i++)
		WriteFile(hfile, &labarray[i], sizeof(labarray[i]), &dwWritten, NULL);

	WriteFile(hfile, &lab_on_subject, sizeof(lab_on_subject), &dwWritten, NULL);
	WriteFile(hfile, &selectedindex, sizeof(selectedindex), &dwWritten, NULL);
	WriteFile(hfile, &labflag, sizeof(labflag), &dwWritten, NULL);
	WriteFile(hfile, &libraryflag, sizeof(libraryflag), &dwWritten, NULL);
	WriteFile(hfile, &CheckedHired, sizeof(CheckedHired), &dwWritten, NULL);

	return 1;
}
int CObjDialog::Load()
{
	for(int i=0; i<MAX_LAB; i++)
		ReadFile(hfile, &labarray[i], sizeof(labarray[i]), &dwWritten, NULL);

	ReadFile(hfile, &lab_on_subject, sizeof(lab_on_subject), &dwWritten, NULL);
	ReadFile(hfile, &selectedindex, sizeof(selectedindex), &dwWritten, NULL);
	ReadFile(hfile, &labflag, sizeof(labflag), &dwWritten, NULL);
	ReadFile(hfile, &libraryflag, sizeof(libraryflag), &dwWritten, NULL);
	ReadFile(hfile, &CheckedHired, sizeof(CheckedHired), &dwWritten, NULL);

	return 1;
}
