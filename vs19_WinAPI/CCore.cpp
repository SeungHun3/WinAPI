#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CObject.h"



CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC); // 싱글톤 객체로 데이터 영역의 메모리를 사용, 소멸자 호출되는시점 : 프로그램 종료
	DeleteDC(m_memDC);
	DeleteObject(m_hBit); // delete를 구분지어있는 이유는 정확히는 모름(메모리관련 예상) : 공식 문서에서 요구하는데로 틀 맞춤 
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 초기해상도 사용자가 모름
	// 해상도 직접 설정하여 윈도우 크기조정 , 타이틀창+ 메뉴바 포함된 모든 픽셀을 말함(윈도우 버전마다 다름)
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPED,true); // 윈도우크기를 내가 지정한 사이즈로 잡을 수 있게 크기정보를 먼저 얻음 // 현재 메뉴바가 있으니 감안해서 계산하기위해 true로 넣음 
	// 함수실행시 rt의 값이 바뀌어있음, 반환값: 함수 성공여부
	
	//=> 레지스터의 부담을 줄이기 위해 메모리가 큰 구조체의 경우 구조체주소를 받아 값만 바꿔주는 식의 형태를 많이 씀
	
	// 가로길이:	rt.right - rt.left;
	// 세로길이:	rt.bottom - rt.top;

	SetWindowPos(m_hwnd,nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top,0);//변경할 윈도우객체 ,...
	
	m_hDC = GetDC(m_hwnd); // 윈도우가 보유하고 있는 비트맵을 DC의 목적지로 삼겠다

	// 이중버퍼링 용도의 비트맵과 DC를 만든다
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // m_hDC의 m_ptResolution해상도로 비트맵 만들기
	m_memDC = CreateCompatibleDC(m_hDC); // m_hDC의 호환성있는 DC 만들기 => 사본 비트맵을 하나 만들었으니 사본을 타겟으로 하는 그림그려줄 DC가 필요해서 
	//현재 사본 비트맵과 사본 DC의 접점은 없는 상태

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // 사본 비트맵,DC접점 만들어줌 == m_memDC의 타겟설정: m_hBit
	//DC가 디폴트로 가지고 있는 타겟은 1pixel 의미없는 비트맵으로 Select를 하면 의미없는 해당 비트맵이 반환됨 
	DeleteObject(hOldBit);
	// 지움(m_memDC 생성시 디폴트로된 의미없는 비트맵)

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}



void CCore::progress()
{
	
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();


	CSceneMgr::GetInst()->update();
	//=========		//Update(); -> 씬 업데이트
	//Rendering		//
	//=========		//Render(); -> 씬 렌더
	//화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
