#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

//�ð� ����ȭ ���� : ���α׷���ü���� �����ӿ� ���� ���� ��ü���� �ӵ��� �޶����� (updateȣ��Ǵ� ������� �޶���)

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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);
	// �ʴ� ī��Ʈ Ƚ��(������ 1õ������ ����)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// (������������ ī���� - ������������ ī����) / �� = > �����Ӹ��� �ɸ� �ð���
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; // ��Ȯ�� �����ϱ� ���� double������ ���

	// ���� ī��Ʈ���� ���簪���� ����
	m_llPrevCount = m_llCurCount;


#ifdef _DEBUG
	if (m_dDt > (1. / 60.))
		m_dDt = (1. / 60.);
#endif

}

void CTimeMgr::render()
{
	//m_dDt�� ���� = FPS(�ʴ� ī��Ʈ Ƚ��)
	//���� : �Ҿ����� => ���� ī��Ʈ �������� ���
	m_iCallCout++;
	m_dAcc += m_dDt; // DT����: �帥 �ð�
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCout;
		m_dAcc = 0.;
		m_iCallCout;

		// ���� ��ȯ
		wchar_t szBuffer[255];
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);
		// ���� Ÿ��Ʋâ���� ���
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}

}
