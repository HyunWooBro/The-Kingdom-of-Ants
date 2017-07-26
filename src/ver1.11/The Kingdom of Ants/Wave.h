// Wave.h: interface for the CWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVE_H__76D72001_6767_11D5_9834_00AA00D3EBF7__INCLUDED_)
#define AFX_WAVE_H__76D72001_6767_11D5_9834_00AA00D3EBF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#####################################################
// 용도 : 웨이브 파일의 모든 정보를 가져온다. 
// 연결관계 : CSound클래스에서 호출하여 사용한다.
//#####################################################
class CWave  
{
public:
    WAVEFORMATEX* wfx;// WAVEFORMATEX구조체의 포인터
    BYTE*         m_Data;// 파일의 실행되어질 데이타를 저장한다.
    UINT          m_dtSize;// 데이타의 크기


protected:
	//웨이브 파일을 오픈한다.
	HRESULT Open(char *FileName, HMMIO* phmmioIn, MMCKINFO* pckInRIFF );
	//멀티미디어의 입력과출력을 지원한다.
	HRESULT ReadMMIO( HMMIO hmmioIn, MMCKINFO* pckInRIFF);
	//데이타 청크를 읽어온다.
	HRESULT WaveDataLoad( HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF );
	//웨이브 파일로부터 웨이브데이터를 읽어옴 
	HRESULT Read( HMMIO hmmioIn, UINT cbRead, BYTE* pbDest);	

public:
    CWave();//생성자
    virtual ~CWave();//소멸자

	//메모리상으로 웨이브 파일을 읽어 온다. 
    HRESULT LoadWave(char *FileName );

};

#endif // !defined(AFX_WAVE_H__76D72001_6767_11D5_9834_00AA00D3EBF7__INCLUDED_)
