#include "pch.h"
#include "CCore.h"

#include "resource.h"

#include "SelectGDI.h"
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
	ReleaseDC(m_hwnd, m_hDC); // �̱��� ��ü�� ������ ������ �޸𸮸� ���, �Ҹ��� ȣ��Ǵ½��� : ���α׷� ����
	
	//������ Pen �����
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu); // �޴��� ���� // �޴� �׸������ DeleteMenu
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ʱ��ػ� ����ڰ� ��
	// �ػ� ���� �����Ͽ� ������ ũ������ , Ÿ��Ʋâ+ �޴��� ���Ե� ��� �ȼ��� ����(������ �������� �ٸ�)
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, false); // ������ũ�⸦ ���� ������ ������� ���� �� �ְ� ũ�������� ���� ���� // ���� �޴��ٰ� ������ �����ؼ� ����ϱ����� true�� ���� 
	
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);//������ �����찴ü ,...

	// �޴��� ���� ���
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_WIN32API));

	m_hDC = GetDC(m_hwnd); // �����찡 �����ϰ� �ִ� ��Ʈ���� DC�� �������� ��ڴ�

	// ���߹��۸� �뵵�� ��Ʈ�ʰ� DC�� ����� => �ؽ��������� �����
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	//���� ����ϴ� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
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
	
	// �浹üũ
	CCollisionMgr::GetInst()->update();

	// UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();


	//Rendering	
	//ȭ�� Clear
	Clear();
	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();


	//�̺�Ʈ ����ó�� �� ���������ӿ� ����
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //HOLLOW BRUSH�� ��������쿡�� �⺻������ �����ϱ⶧���� get���� �ٷ� �޾ƿ�
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0,0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0,255,0));
}
