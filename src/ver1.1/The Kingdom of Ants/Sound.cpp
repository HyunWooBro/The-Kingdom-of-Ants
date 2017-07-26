//#####################################################
// Sound.cpp: implementation of the CWave1fileLoad class.
//
//#####################################################

#include <windows.h>
#include "Sound.h"
#include <math.h>

#define DSVOLUME_TO_DB(volume) (-2000 * log10(1.0f / volume))

LPDIRECTSOUND8 lpDirectSoundOBJ;//다이렉트 사운드8의 객체를 생성한다. 

//#####################################################
// 이름: CreateDirectSound()
// 정의 : 다이렉트 사운드의 오브젝트를 생성한다. 
//#####################################################
HRESULT CreateDirectSound(HWND hWnd)
{
	//다이렉트 사운드8의 오브젝트를 생성
	if( FAILED( DirectSoundCreate8( NULL, &lpDirectSoundOBJ, NULL ) ) )
        return E_FAIL;

	//협력 수준의 설정
    if( FAILED( lpDirectSoundOBJ->SetCooperativeLevel( hWnd, DSSCL_NORMAL) ) )
        return E_FAIL;

    return S_OK;
}

//#####################################################
// 이름: DestroyDirectSound()
// 정의: 다이렉트 사운드의 소멸
//#####################################################
HRESULT DestroyDirectSound(void)
{
	//생성한 객체를 소멸한다.
    if( NULL != lpDirectSoundOBJ )
	{
		lpDirectSoundOBJ->Release();
		lpDirectSoundOBJ = NULL;
	}

	return S_OK;
}

//#####################################################
// 이름: CSound()
// 정의: 생성자
//#####################################################
CSound::CSound()
{
    lpDirectSoundBuffer = NULL;//버퍼의 초기값을 NULL로 한다.
    m_bPlaying = FALSE;//플래이가 되지않은 상태를 말한다.
	fadeout = FALSE;
}

//#####################################################
// 이름: ~CSound()
// 정의: 소멸자
//#####################################################
CSound::~CSound()
{
    if( lpDirectSoundBuffer )      
	{
		lpDirectSoundBuffer->Release();//사용된 버퍼를 소멸한다.      
		lpDirectSoundBuffer = NULL;//버퍼의 값으로 다시 NULL을 넣는다.  
	}
}

//#####################################################
// 이름 : ReadyBufferFromWaveFile
// 정의 : 웨이브(.wav)화일을 읽어들여와 DirectSound 버퍼를 생성한다.
//#####################################################
void CSound::ReadyBufferFromWaveFile(char *filename)
{
	CWave *waveFileSound = new CWave();//CWave클래스 객체의 메모리 할당.

	// 웨이브 파일 로드하기
    if( waveFileSound->LoadWave( filename ) != S_OK)
		return ;
	  
    // 사운드버퍼를 읽어온 사운드로 구성한다.
    LockenWaveFile( waveFileSound );

	delete waveFileSound;//할당된 메모리를 반환한다. 
}

//#####################################################
// 이름 : LockenWaveFile()
// 정의 : Lock과 Unlock를 통한 데이터를 직접적으로 쓰는 작업을 한다.
//#####################################################
HRESULT CSound::LockenWaveFile( CWave* pWave )
{
    // Set up the direct sound buffer. 
    DSBUFFERDESC dsbd;
    ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );
    dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_STATIC | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = pWave->m_dtSize;
    dsbd.lpwfxFormat   = pWave->wfx;
 
	//사운드 버퍼의 생성
    if( FAILED( lpDirectSoundOBJ->CreateSoundBuffer( &dsbd, &lpDirectSoundBuffer, NULL ) ) )
        return E_FAIL;

    //메모리를 카피할 변수로 사용
    VOID* pbData  = NULL;
    VOID* pbData2 = NULL;
    DWORD dwLength;
    DWORD dwLength2;

	//메모리로 접근을 허용한다.
    if( FAILED( lpDirectSoundBuffer->Lock( 0, dsbd.dwBufferBytes, &pbData, &dwLength, 
                              &pbData2, &dwLength2, 0L ) ) )
    {
        lpDirectSoundBuffer->Release();
        lpDirectSoundBuffer = NULL;
        return E_FAIL;
    }

	//웨이브데이타를 버퍼로 복사한다.
    memcpy( pbData, pWave->m_Data, dsbd.dwBufferBytes );

    //메모리로의 접근을 해제한다. 
    lpDirectSoundBuffer->Unlock( pbData, dsbd.dwBufferBytes, NULL, 0 );
    pbData = NULL;

    return S_OK;
}

//#####################################################
// 이름: Play()
// 정의: 음악을 플래이 한다.
//#####################################################
HRESULT CSound::Play( BOOL Loop )
{
	//버퍼가 비어 있으면 실행하지 않는다.
    if( NULL == lpDirectSoundBuffer )
        return E_FAIL;

	//버퍼에 들어있는 음악을 연주 한다.
	if( FAILED( lpDirectSoundBuffer->Play( 0, 0, (Loop) ? LOOPING : NOLOOPING ) ) )
		return E_FAIL;
	
    m_bPlaying = TRUE;
    return S_OK;
}

//#####################################################
// 이름 : Stop()
// 정의 : 연주 중인 음악을 정지한다.
//#####################################################
HRESULT CSound::Stop()
{
	//버퍼가 비어있으면 종료한다.
    if( lpDirectSoundBuffer == NULL )
        return E_FAIL;
    //플래이 중이 아니면 종료한다. 
    if( m_bPlaying == FALSE )
        return S_OK;

    //프래이를 정지한다.
    lpDirectSoundBuffer->Stop();
    //위치를 처음위치로 가지고 간다.
	lpDirectSoundBuffer->SetCurrentPosition( 0L );
    m_bPlaying = FALSE;

    return S_OK;
}

int CSound::SetSoundVolume(float fvalue)
{
	if(fvalue == 0L)
	{
		if(lpDirectSoundBuffer->SetVolume(DSBVOLUME_MIN)!=DS_OK)
		return 0;
	}
	else
	{
		if(lpDirectSoundBuffer->SetVolume(DSVOLUME_TO_DB(fvalue))!=DS_OK)
		return 0;
	}

	return 1;
}



