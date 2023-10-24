#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"


CObject g_obj;


CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC); // 싱글톤 객체로 데이터 영역의 메모리를 사용, 소멸자 호출되는시점 : 프로그램 종료

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
	
	m_hDC = GetDC(m_hwnd);

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();


	// 오브젝트 초기화 : 해상도 / 2 =>화면중앙
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2) ));
	g_obj.SetScale(Vec2(100, 100));


	return S_OK;
}



void CCore::progress()
{
	//static int callcount = 0;
	//++callcount;
	//static int iPrevCount = GetTickCount();
	//
	//int iCurCount = GetTickCount();
	//
	//if (iCurCount - iPrevCount > 1000) // 1초 차이가 났을때 
	//{
	//	iPrevCount = iCurCount; // 중단점걸어 호출카운팅했을때 callcount = 13만번 => 1초에 13만번 호출
	//	callcount = 0;
	//}


	// Manager Update
	CTimeMgr::GetInst()->update();

	Update();
	
	Render();

}

//물체들의 변경점(좌표 등..) 체크할 함수
void CCore::Update()
{
	//비동기: 포커싱 되어있지 않아도 함수 호출됨
	//동기화에 대한 문제 생각하며 설계필요
	
	//GetAsyncKeyState(VK_LEFT); // 키가 눌렸는지 => 키의 상태값 비트 조합 후 반환
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 비트연산: 키가 눌렸는지 확인
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}
	g_obj.SetPos(vPos);
}

void CCore::Render()
{
	// 그리기
	// 오브젝트 하나하나마다 그리고 있는 과정을 보여주는게 아닌 모두 다 그렸을때 보여주는화면으로 바꿔줘야함

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_hDC, int(vPos.x - vScale.x /2.f)
				   , int(vPos.y - vScale.y / 2.f)
				   , int(vPos.x + vScale.x / 2.f)
				   , int(vPos.y + vScale.y / 2.f));

}

