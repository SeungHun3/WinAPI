#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

//시간 동기화 이유 : 프로그램자체적인 프레임에 따라 게임 자체적인 속도가 달라진다 (update호출되는 절대양이 달라짐)

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDt(0.)
	, m_dAcc(0.)
	, m_iCallCout(0)
{

}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);
	// 초당 카운트 횟수(디버깅시 1천만으로 나옴)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// (이전프레임의 카운팅 - 현재프레임의 카운팅) / 빈도 = > 프레임마다 걸린 시간값
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // 정확히 측정하기 위해 double형으로 사용

	// 이전 카운트값을 현재값으로 갱신
	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG
	if (m_dDt > (1. / 60.))
		m_dDt = (1. / 60.);
#endif

}

void CTimeMgr::render()
{
	//m_dDt의 역수 = FPS(초당 카운트 횟수)
	//단점 : 불안정함 => 직접 카운트 증가시켜 계산
	m_iCallCout++;
	m_dAcc += m_dDt; // DT누적: 흐른 시간
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCout;
		m_dAcc = 0.;
		m_iCallCout;

		// 숫자 변환
		wchar_t szBuffer[255];
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);
		// 정보 타이틀창으로 출력
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}

}
