#pragma once

// getTickCount = 정밀하지 않고 호출횟수 1초 13만번에 틱 1000번은 너무 적다 => QueryPerformanceCounter 함수사용
// // FPS
// 1프레임당 시간: Delta Time

class CTimeMgr
{
	SINGLE(CTimeMgr)

private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDt;	   // 프레임간의 시간값
	double m_dAcc;     // 1초당 DT 누적값
	UINT m_iCallCout;  // 초당 호출 횟수체크
	UINT m_iFPS;	   // 초당 호출 횟수

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDt; }
	float GetfDT() { return (float)m_dDt; }

};

