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
	ReleaseDC(m_hwnd, m_hDC); // �̱��� ��ü�� ������ ������ �޸𸮸� ���, �Ҹ��� ȣ��Ǵ½��� : ���α׷� ����
	DeleteDC(m_memDC);
	DeleteObject(m_hBit); // delete�� ���������ִ� ������ ��Ȯ���� ��(�޸𸮰��� ����) : ���� �������� �䱸�ϴµ��� Ʋ ���� 
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ʱ��ػ� ����ڰ� ��
	// �ػ� ���� �����Ͽ� ������ ũ������ , Ÿ��Ʋâ+ �޴��� ���Ե� ��� �ȼ��� ����(������ �������� �ٸ�)
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPED,true); // ������ũ�⸦ ���� ������ ������� ���� �� �ְ� ũ�������� ���� ���� // ���� �޴��ٰ� ������ �����ؼ� ����ϱ����� true�� ���� 
	// �Լ������ rt�� ���� �ٲ������, ��ȯ��: �Լ� ��������
	
	//=> ���������� �δ��� ���̱� ���� �޸𸮰� ū ����ü�� ��� ����ü�ּҸ� �޾� ���� �ٲ��ִ� ���� ���¸� ���� ��
	
	// ���α���:	rt.right - rt.left;
	// ���α���:	rt.bottom - rt.top;

	SetWindowPos(m_hwnd,nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top,0);//������ �����찴ü ,...
	
	m_hDC = GetDC(m_hwnd); // �����찡 �����ϰ� �ִ� ��Ʈ���� DC�� �������� ��ڴ�

	// ���߹��۸� �뵵�� ��Ʈ�ʰ� DC�� �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // m_hDC�� m_ptResolution�ػ󵵷� ��Ʈ�� �����
	m_memDC = CreateCompatibleDC(m_hDC); // m_hDC�� ȣȯ���ִ� DC ����� => �纻 ��Ʈ���� �ϳ� ��������� �纻�� Ÿ������ �ϴ� �׸��׷��� DC�� �ʿ��ؼ� 
	//���� �纻 ��Ʈ�ʰ� �纻 DC�� ������ ���� ����

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // �纻 ��Ʈ��,DC���� ������� == m_memDC�� Ÿ�ټ���: m_hBit
	//DC�� ����Ʈ�� ������ �ִ� Ÿ���� 1pixel �ǹ̾��� ��Ʈ������ Select�� �ϸ� �ǹ̾��� �ش� ��Ʈ���� ��ȯ�� 
	DeleteObject(hOldBit);
	// ����(m_memDC ������ ����Ʈ�ε� �ǹ̾��� ��Ʈ��)

	// Manager �ʱ�ȭ
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
	//=========		//Update(); -> �� ������Ʈ
	//Rendering		//
	//=========		//Render(); -> �� ����
	//ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}
