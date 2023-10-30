#pragma once

// getTickCount = �������� �ʰ� ȣ��Ƚ�� 1�� 13������ ƽ 1000���� �ʹ� ���� => QueryPerformanceCounter �Լ����
// // FPS
// 1�����Ӵ� �ð�: Delta Time

class CTimeMgr
{
	SINGLE(CTimeMgr)

private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDt;	   // �����Ӱ��� �ð���
	double m_dAcc;     // 1�ʴ� DT ������
	UINT m_iCallCout;  // �ʴ� ȣ�� Ƚ��üũ
	UINT m_iFPS;	   // �ʴ� ȣ�� Ƚ��

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDt; }
	float GetfDT() { return (float)m_dDt; }

};

