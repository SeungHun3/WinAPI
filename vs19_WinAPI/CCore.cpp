#include "pch.h"
#include "CCore.h"

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

	// ������Ʈ �ʱ�ȭ : �ػ� / 2 =>ȭ���߾�
	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2 , m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100,100 };


	return S_OK;
}



void CCore::progress()
{
	static int callcount = 0;
	++callcount;
	static int iPrevCount = GetTickCount();

	int iCurCount = GetTickCount();

	if (iCurCount - iPrevCount > 1000) // 1�� ���̰� ������ 
	{
		iPrevCount = iCurCount; // �ߴ����ɾ� ȣ��ī���������� callcount = 13���� => 1�ʿ� 13���� ȣ��
		callcount = 0;
	}


	Update();
	
	Render();

}

//��ü���� ������(��ǥ ��..) üũ�� �Լ�
void CCore::Update()
{
	//�񵿱�: ��Ŀ�� �Ǿ����� �ʾƵ� �Լ� ȣ���
	//����ȭ�� ���� ���� �����ϸ� �����ʿ�
	
	//GetAsyncKeyState(VK_LEFT); // Ű�� ���ȴ��� => Ű�� ���°� ��Ʈ ���� �� ��ȯ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ��Ʈ����: Ű�� ���ȴ��� Ȯ��
	{
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}

}

void CCore::Render()
{
	// �׸���
	// ������Ʈ �ϳ��ϳ����� �׸��� �ִ� ������ �����ִ°� �ƴ� ��� �� �׷����� �����ִ�ȭ������ �ٲ������
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x /2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);

}

