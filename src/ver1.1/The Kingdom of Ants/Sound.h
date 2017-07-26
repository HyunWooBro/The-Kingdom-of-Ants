// Sound.h: interface for the CSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__50DD1963_66A2_11D5_9834_00AA00D3EBF7__INCLUDED_)
#define AFX_SOUND_H__50DD1963_66A2_11D5_9834_00AA00D3EBF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dsound.h>
#include "Wave.h"

#define NOLOOPING (FALSE)//음이 반복되지 않게 한다.
#define LOOPING (TRUE)//음이 반복 되도록 한다.

//#####################################################
// 용도 : 다이렉트 사운드의 모든 자원을 사용할 수 있게 한다.
// 연결관계 : CWave클래스를 읽어와서 사용하고 WinMain에서  
//            사운드를 초기화하고 플래이 할때 사용된다.
//#####################################################
class CSound
{
public:
	
    LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;// 다이렉트 사운드 버퍼
    BOOL    m_bPlaying;// 플래이가 되고 있는 생태
	BOOL fadeout;
	
public:
    CSound();
    virtual ~CSound();	

	void ReadyBufferFromWaveFile(char *filename);//웨이브 파일을 읽어와 버퍼에 담는다. 
	HRESULT LockenWaveFile( CWave* );//버퍼에 직접적으로 접근한다.    
    HRESULT Play( BOOL Loop = NOLOOPING );//플래이하기
    HRESULT Stop();//정지하기    
	int SetSoundVolume(float fvalue);
};

HRESULT CreateDirectSound( HWND hWnd);//다이렉트 사운드의 생성
HRESULT DestroyDirectSound(void);//다이렉트 사운드 객체를 소멸.

#endif // !defined(AFX_SOUND_H__50DD1963_66A2_11D5_9834_00AA00D3EBF7__INCLUDED_)
