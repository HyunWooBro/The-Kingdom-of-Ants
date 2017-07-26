//#####################################################
// Wave.cpp: implementation of the CWave class.
//
//#####################################################

#include <windows.h>
#include "Wave.h"

//////////////////////////////////////////////////////////////////////
// 생성자 / 소멸자
//////////////////////////////////////////////////////////////////////

//#####################################################
// Name: CWave()
// Desc: 생성자
//#####################################################
CWave::CWave()
{
    m_Data = NULL;
    wfx   = NULL;
	m_dtSize = 0;
}

//#####################################################
// Name: ~CWave()
// Desc: 소멸자
//#####################################################
CWave::~CWave()
{
    if( m_Data )
	{
		delete [] m_Data; 
		m_Data = NULL;
	}

    if( wfx )   
	{
		delete wfx;   
		wfx   = NULL;
	}
}

//#####################################################
// Name: LoadWave()
// Desc: 메모리 속으로 웨이브 파일을 로드 한다. 
//#####################################################
HRESULT CWave::LoadWave(char *Filename )
{    
    HMMIO    hmmioIn;        
    MMCKINFO ckInRiff;
    MMCKINFO ckIn;		
	
    if( FAILED( Open( Filename, &hmmioIn, &ckInRiff ) ) )
        return E_FAIL;

    if( SUCCEEDED( WaveDataLoad( &hmmioIn, &ckIn, &ckInRiff ) ) )
    {
        //ckIn.cksize의 사이즈 만큼의 메모리를 할당한다  
        if( ( m_Data = new BYTE[ckIn.cksize] ) )
        {
            if( SUCCEEDED( Read( hmmioIn, ckIn.cksize, m_Data) ) )
            {
                mmioClose( hmmioIn, 0 );
                return S_OK;
            }
        }
    }	

    mmioClose( hmmioIn, 0 );
    delete wfx;
    wfx = NULL;

    return E_FAIL;	
}

//#####################################################
// Name: Open()
// Desc: 웨이브파일을 읽어온다.
//#####################################################
HRESULT CWave::Open( char *FileName, HMMIO* phmmioIn, MMCKINFO* pckInRIFF )
{
    HRESULT hr;
    HMMIO   hmmioIn = NULL;	
		
    if( NULL == ( hmmioIn = mmioOpen( (char*)(const char*)FileName, NULL, MMIO_ALLOCBUF|MMIO_READ ) ) )
        return E_FAIL;

    if( FAILED( hr = ReadMMIO( hmmioIn, pckInRIFF) ) )
    {
        mmioClose( hmmioIn, 0 );
        return E_FAIL;
    }	

    *phmmioIn = hmmioIn;

    return S_OK;
}

//#####################################################
// Name: ReadMMIO()
// Desc: 멀티미디어의 입출력을 지원하는 곳으로
//       웨이브파일을 오픈할 때 사용된다.
//#####################################################
HRESULT CWave::ReadMMIO( HMMIO hmmioIn, MMCKINFO* pckInRIFF)
{
    MMCKINFO        ckIn;           // chunk의 정보
    PCMWAVEFORMAT   pcmWaveFormat;  // PCM종류의 웨이브 포멧 

    wfx = NULL;

	pckInRIFF->fccType = mmioFOURCC('W', 'A', 'V', 'E');	
	if( ( 0 != mmioDescend( hmmioIn, pckInRIFF, NULL, MMIO_FINDRIFF ) ) )
        return E_FAIL;

    // 'fmt ' chunk을 위한 준비
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');	
	if( 0 != mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK) )
        return E_FAIL;	

    // <pcmWaveFormat>안에 'fmt ' chunk를 읽는다..	
    if( mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat) )
        return E_FAIL;

    // waveformatex에 미모리할당.
    wfx = new WAVEFORMATEX;

    // pcm structure로 부터 waveformatex structure를 복사한다.
    memcpy( wfx, &pcmWaveFormat, sizeof(pcmWaveFormat) );
    wfx->cbSize = 0;
	
	mmioAscend(hmmioIn, &ckIn, 0);

    return S_OK;
}

//#####################################################
// Name: WaveDataLoad()
// Desc: 웨이브데이타를 로드하기위해서 'data' chunk를 
//       찾는다.
//#####################################################
HRESULT CWave::WaveDataLoad( HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF )
{
    // 데이타의 정확위치를 찾는다.
    if( -1 == mmioSeek( *phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC),
                        SEEK_SET ) )
        return E_FAIL;
	
	// 'data' chunk를 찾는다.
    pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');	
    if( 0 != mmioDescend( *phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK ) )
        return E_FAIL;

    return S_OK;
}

//#####################################################
// Name: Read()
// Desc: 웨이브데이타를 읽는다. 'data' chunk가 출되기 전에 
//       이 함수가 호출되어야 한다.
//          hmmioIn      - mmio의 헨들.
//          cbRead       - read를 위한 변수.   
//          pbDest       - 출력 바이트의 정의  
//#####################################################
HRESULT CWave::Read( HMMIO hmmioIn, UINT cbRead, BYTE* pbDest)
{	
	mmioRead(hmmioIn, (LPSTR)pbDest, cbRead);
	m_dtSize = cbRead;
    return S_OK;
}
