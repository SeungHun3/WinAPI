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
	ReleaseDC(m_hwnd, m_hDC); // �̱��� ��ü�� ������ ������ �޸𸮸� ���, �Ҹ��� ȣ��Ǵ½��� : ���α׷� ����

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
	
	m_hDC = GetDC(m_hwnd);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();


	// ������Ʈ �ʱ�ȭ : �ػ� / 2 =>ȭ���߾�
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
	//if (iCurCount - iPrevCount > 1000) // 1�� ���̰� ������ 
	//{
	//	iPrevCount = iCurCount; // �ߴ����ɾ� ȣ��ī���������� callcount = 13���� => 1�ʿ� 13���� ȣ��
	//	callcount = 0;
	//}


	// Manager Update
	CTimeMgr::GetInst()->update();

	Update();
	
	Render();

}

//��ü���� ������(��ǥ ��..) üũ�� �Լ�
void CCore::Update()
{
	//�񵿱�: ��Ŀ�� �Ǿ����� �ʾƵ� �Լ� ȣ���
	//����ȭ�� ���� ���� �����ϸ� �����ʿ�
	
	//GetAsyncKeyState(VK_LEFT); // Ű�� ���ȴ��� => Ű�� ���°� ��Ʈ ���� �� ��ȯ
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ��Ʈ����: Ű�� ���ȴ��� Ȯ��
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
	// �׸���
	// ������Ʈ �ϳ��ϳ����� �׸��� �ִ� ������ �����ִ°� �ƴ� ��� �� �׷����� �����ִ�ȭ������ �ٲ������

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_hDC, int(vPos.x - vScale.x /2.f)
				   , int(vPos.y - vScale.y / 2.f)
				   , int(vPos.x + vScale.x / 2.f)
				   , int(vPos.y + vScale.y / 2.f));

}

