
#include "windows.h"
#include "CDataFile.h"
#include "GlobalDeclaration.h"
#include "CBattle.h"
#include "CBuilding.h"
#include "CDiplomatic.h"
#include "CDomestic.h"
#include "CEvent.h"
#include "CInfo.h"
#include "CItem.h"
#include "CObjDialog.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CScreen.h"
#include "CSpecies.h"
#include "CStory.h"
#include "CTime.h"

extern CBattle battle_;
extern CBuilding building_;
extern CDiplomatic diplomatic_;
extern CDomestic domestic_;
extern CEvent event_;
extern CInfo info_;
extern CItem item_;
extern CObjDialog objdialog_;
extern CObject object_;
extern CScreen screen_;
extern CStory story_;
extern CTime time_;

int CDataFile::DataFile_Init()
{

	return 1;
}

int CDataFile::Save()
{
	OPENFILENAME ofn;
	tag_Header header;
	char lpstrFile[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = main_window_handle;
	ofn.lpstrFilter = "SaveFile\0*.sav\0";
	ofn.lpstrDefExt = "sav";
	ofn.Flags = OFN_NOCHANGEDIR;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = lpstrFile;
	if(GetSaveFileName(&ofn) != NULL)
	{
		hfile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hfile == INVALID_HANDLE_VALUE)
		{
			MessageBox(main_window_handle, "에러", "알림", MB_OK);
			CloseHandle(hfile);
			return 0;
		}

		strcpy(header.desc, GAME_SAVETITLE);
        header.ver = GAME_VERSION;
		WriteFile(hfile, &header, sizeof(tag_Header), &dwWritten, NULL);
		
		SaveGlobal();

		battle_.Save();

		building_.Save();

		diplomatic_.Save();

		domestic_.Save();

		event_.Save();

		info_.Save();

		item_.Save();

		objdialog_.Save();

		object_.Save();

		CPlayer::Save();

		screen_.Save();

		CSpecies::Save();

		story_.Save();

		time_.Save();

		CloseHandle(hfile);

		MessageBox(main_window_handle, "저장을 완료했습니다.", "알림", MB_OK);
	}
	else
		return 0;

	return 1;
}

int CDataFile::SaveGlobal()
{
	WriteFile(hfile, &GAME_STATE, sizeof(GAME_STATE), &dwWritten, NULL);
	WriteFile(hfile, &CHAPTER, sizeof(CHAPTER), &dwWritten, NULL);
	WriteFile(hfile, &SCREEN_STATE, sizeof(SCREEN_STATE), &dwWritten, NULL);
	WriteFile(hfile, &MOUSE_STATE, sizeof(MOUSE_STATE), &dwWritten, NULL);
	WriteFile(hfile, &SCROLL_STATE, sizeof(SCROLL_STATE), &dwWritten, NULL);
	WriteFile(hfile, &LBUTTON_STATE, sizeof(LBUTTON_STATE), &dwWritten, NULL);
	WriteFile(hfile, &KEY_SPACE_STATE, sizeof(KEY_SPACE_STATE), &dwWritten, NULL);
	WriteFile(hfile, &KEY_S_STATE, sizeof(KEY_S_STATE), &dwWritten, NULL);
	WriteFile(hfile, &KEY_M_STATE, sizeof(KEY_M_STATE), &dwWritten, NULL);
	WriteFile(hfile, &KEY_I_STATE, sizeof(KEY_I_STATE), &dwWritten, NULL);
	WriteFile(hfile, &KEY_ESC_STATE, sizeof(KEY_ESC_STATE), &dwWritten, NULL);
	WriteFile(hfile, &LBUTTON_STATE2, sizeof(LBUTTON_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &KEY_I_STATE2, sizeof(KEY_I_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &KEY_M_STATE2, sizeof(KEY_M_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &KEY_S_STATE2, sizeof(KEY_S_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &KEY_SPACE_STATE2, sizeof(KEY_SPACE_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &KEY_ESC_STATE2, sizeof(KEY_ESC_STATE2), &dwWritten, NULL);
	WriteFile(hfile, &BATTLE_OUT_STATE, sizeof(BATTLE_OUT_STATE), &dwWritten, NULL);
	WriteFile(hfile, &BATTLE_IN_STATE, sizeof(BATTLE_IN_STATE), &dwWritten, NULL);
	WriteFile(hfile, &BUILDING_STATE, sizeof(BUILDING_STATE), &dwWritten, NULL);
	WriteFile(hfile, &FADE_STATE, sizeof(FADE_STATE), &dwWritten, NULL);
	WriteFile(hfile, &off_x, sizeof(off_x), &dwWritten, NULL);
	WriteFile(hfile, &off_y, sizeof(off_y), &dwWritten, NULL);

	return 1;
}

int CDataFile::Load()
{
	OPENFILENAME ofn;
	tag_Header header;
	char lpstrFile[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = main_window_handle;
	ofn.lpstrFilter = "SaveFile\0*.sav\0";
	ofn.lpstrDefExt = "sav";
	ofn.Flags = OFN_NOCHANGEDIR;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = lpstrFile;
	if(GetOpenFileName(&ofn) != NULL)
	{
		hfile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL,
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hfile == INVALID_HANDLE_VALUE)
		{
			MessageBox(main_window_handle, "에러", "알림", MB_OK);
			CloseHandle(hfile);
			return 0;
		}

		ReadFile(hfile, &header, sizeof(tag_Header), &dwWritten, NULL);
		
		if(strcmp(header.desc, GAME_SAVETITLE) != 0)
		{
			MessageBox(main_window_handle, "저장 파일이 아닙니다.", "알림", MB_OK);
			CloseHandle(hfile);
			return 0;
		}
		if(header.ver != GAME_VERSION)
		{
			sprintf(buffer, "저장 파일의 버젼은 %d인데, 게임의 버젼은 %d입니다.",
				header.ver, GAME_VERSION);
			MessageBox(main_window_handle, buffer, "알림", MB_OK);
			CloseHandle(hfile);
			return 0;
		}

		LoadGlobal();

		battle_.Load();

		building_.Load();

		diplomatic_.Load();

		domestic_.Load();

		event_.Load();

		info_.Load();

		item_.Load();

		objdialog_.Load();

		object_.Load();

		CPlayer::Load();

		screen_.Load();

		CSpecies::Load();

		story_.Load();

		time_.Load();

		CloseHandle(hfile);

		MessageBox(main_window_handle, "불러오기를 완료했습니다.", "알림", MB_OK);
	}
	else
		return 0;

	return 1;
}

int CDataFile::LoadGlobal()
{
	ReadFile(hfile, &GAME_STATE, sizeof(GAME_STATE), &dwWritten, NULL);
	ReadFile(hfile, &CHAPTER, sizeof(CHAPTER), &dwWritten, NULL);
	ReadFile(hfile, &SCREEN_STATE, sizeof(SCREEN_STATE), &dwWritten, NULL);
	ReadFile(hfile, &MOUSE_STATE, sizeof(MOUSE_STATE), &dwWritten, NULL);
	ReadFile(hfile, &SCROLL_STATE, sizeof(SCROLL_STATE), &dwWritten, NULL);
	ReadFile(hfile, &LBUTTON_STATE, sizeof(LBUTTON_STATE), &dwWritten, NULL);
	ReadFile(hfile, &KEY_SPACE_STATE, sizeof(KEY_SPACE_STATE), &dwWritten, NULL);
	ReadFile(hfile, &KEY_S_STATE, sizeof(KEY_S_STATE), &dwWritten, NULL);
	ReadFile(hfile, &KEY_M_STATE, sizeof(KEY_M_STATE), &dwWritten, NULL);
	ReadFile(hfile, &KEY_I_STATE, sizeof(KEY_I_STATE), &dwWritten, NULL);
	ReadFile(hfile, &KEY_ESC_STATE, sizeof(KEY_ESC_STATE), &dwWritten, NULL);
	ReadFile(hfile, &LBUTTON_STATE2, sizeof(LBUTTON_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &KEY_I_STATE2, sizeof(KEY_I_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &KEY_M_STATE2, sizeof(KEY_M_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &KEY_S_STATE2, sizeof(KEY_S_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &KEY_SPACE_STATE2, sizeof(KEY_SPACE_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &KEY_ESC_STATE2, sizeof(KEY_ESC_STATE2), &dwWritten, NULL);
	ReadFile(hfile, &BATTLE_OUT_STATE, sizeof(BATTLE_OUT_STATE), &dwWritten, NULL);
	ReadFile(hfile, &BATTLE_IN_STATE, sizeof(BATTLE_IN_STATE), &dwWritten, NULL);
	ReadFile(hfile, &BUILDING_STATE, sizeof(BUILDING_STATE), &dwWritten, NULL);
	ReadFile(hfile, &FADE_STATE, sizeof(FADE_STATE), &dwWritten, NULL);
	ReadFile(hfile, &off_x, sizeof(off_x), &dwWritten, NULL);
	ReadFile(hfile, &off_y, sizeof(off_y), &dwWritten, NULL);

	return 1;
}
int CDataFile::DataFile_Shutdown()
{

	return 1;
}
