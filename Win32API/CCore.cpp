#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC); // �̱��� ��ü�� ������ ������ �޸𸮸� ���, �Ҹ��� ȣ��Ǵ½��� : ���α׷� ����
	DeleteDC(m_memDC);
	DeleteObject(m_hBit); // delete�� ���������ִ� ������ ��Ȯ���� ��(�޸𸮰��� ����) : ���� �������� �䱸�ϴµ��� Ʋ ���� 

	//������ Pen �����
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ʱ��ػ� ����ڰ� ��
	// �ػ� ���� �����Ͽ� ������ ũ������ , Ÿ��Ʋâ+ �޴��� ���Ե� ��� �ȼ��� ����(������ �������� �ٸ�)
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, true); // ������ũ�⸦ ���� ������ ������� ���� �� �ְ� ũ�������� ���� ���� // ���� �޴��ٰ� ������ �����ؼ� ����ϱ����� true�� ���� 
	// �Լ������ rt�� ���� �ٲ������, ��ȯ��: �Լ� ��������

	//=> ���������� �δ��� ���̱� ���� �޸𸮰� ū ����ü�� ��� ����ü�ּҸ� �޾� ���� �ٲ��ִ� ���� ���¸� ���� ��

	// ���α���:	rt.right - rt.left;
	// ���α���:	rt.bottom - rt.top;

	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);//������ �����찴ü ,...

	m_hDC = GetDC(m_hwnd); // �����찡 �����ϰ� �ִ� ��Ʈ���� DC�� �������� ��ڴ�

	// ���߹��۸� �뵵�� ��Ʈ�ʰ� DC�� �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // m_hDC�� m_ptResolution�ػ󵵷� ��Ʈ�� �����
	m_memDC = CreateCompatibleDC(m_hDC); // m_hDC�� ȣȯ���ִ� DC ����� => �纻 ��Ʈ���� �ϳ� ��������� �纻�� Ÿ������ �ϴ� �׸��׷��� DC�� �ʿ��ؼ� 
	//���� �纻 ��Ʈ�ʰ� �纻 DC�� ������ ���� ����

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // �纻 ��Ʈ��,DC���� ������� == m_memDC�� Ÿ�ټ���: m_hBit
	//DC�� ����Ʈ�� ������ �ִ� Ÿ���� 1pixel �ǹ̾��� ��Ʈ������ Select�� �ϸ� �ǹ̾��� �ش� ��Ʈ���� ��ȯ�� 
	DeleteObject(hOldBit);
	// ����(m_memDC ������ ����Ʈ�ε� �ǹ̾��� ��Ʈ��)

	//���� ����ϴ� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
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
	CCollisionMgr::GetInst()->update();
	//=========		//Update(); -> �� ������Ʈ
	//Rendering		//
	//=========		//Render(); -> �� ����
	//ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	//CTimeMgr::GetInst()->render();
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //HOLLOW BRUSH�� ��������쿡�� �⺻������ �����ϱ⶧���� get���� �ٷ� �޾ƿ�

	//red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0,0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0,255,0));
}