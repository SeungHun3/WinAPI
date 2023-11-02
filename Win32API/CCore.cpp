#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CResMgr.h"
#include "CTexture.h"


CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC); // 싱글톤 객체로 데이터 영역의 메모리를 사용, 소멸자 호출되는시점 : 프로그램 종료
	
	//생성한 Pen 지우기
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 초기해상도 사용자가 모름
	// 해상도 직접 설정하여 윈도우 크기조정 , 타이틀창+ 메뉴바 포함된 모든 픽셀을 말함(윈도우 버전마다 다름)
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true); // 윈도우크기를 내가 지정한 사이즈로 잡을 수 있게 크기정보를 먼저 얻음 // 현재 메뉴바가 있으니 감안해서 계산하기위해 true로 넣음 
	// 함수실행시 rt의 값이 바뀌어있음, 반환값: 함수 성공여부

	//=> 레지스터의 부담을 줄이기 위해 메모리가 큰 구조체의 경우 구조체주소를 받아 값만 바꿔주는 식의 형태를 많이 씀

	// 가로길이:	rt.right - rt.left;
	// 세로길이:	rt.bottom - rt.top;

	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);//변경할 윈도우객체 ,...

	m_hDC = GetDC(m_hwnd); // 윈도우가 보유하고 있는 비트맵을 DC의 목적지로 삼겠다

	// 이중버퍼링 용도의 비트맵과 DC를 만든다 => 텍스쳐한장을 만든다
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	//자주 사용하는 펜 및 브러쉬 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();
	return S_OK;
}



void CCore::progress()
{

	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();
	
	// Scene Update
	CSceneMgr::GetInst()->update();
	
	// 충돌체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();


	//Rendering	
	//화면 Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	//이벤트 지연처리 후 다음프레임에 실행
	CEventMgr::GetInst()->update();
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //HOLLOW BRUSH의 경우윈도우에서 기본적으로 제공하기때문에 get으로 바로 받아옴

	//red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0,0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0,255,0));
}