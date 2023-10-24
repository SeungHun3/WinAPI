#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] = 
{
	VK_LEFT,	//LEFT,
	VK_RIGHT,	//RIGHT,
	VK_UP,		//UP,
	VK_DOWN,	//DOWN,
	//
	'Q','W','E','R','T','Y','U','O','P',//Q,W,E,R,T,Y,U,O,P,
	'A','S','D','F',					//A,S,D,F,
	'Z','X','C','V','B',				//Z,X,C,V,B,
	//
	VK_MENU,	//ALT,
	VK_CONTROL,	//CTRL,
	VK_LSHIFT,	//LSHIFT,
	VK_SPACE,	//SPACE,
	VK_RETURN,	//ENTER,
	VK_ESCAPE,	//ESC,
	//
	//
	//LAST
};




CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false}); // ���Ű �� �ʱ�ȭ
	}
}

void CKeyMgr::update()
{
	// ������ ��Ŀ�� �˾Ƴ��� 
	HWND hWnd = GetFocus(); // ��Ŀ���� ���ٸ� nullptr��ȯ


	// ��Ŀ�� ó�� ���� �ʴ´ٸ� â�� ������ �Է��� �ݿ��ȴ�
	if (nullptr != hWnd) // ��Ŀ�� ���̶��
	{
		// ���� ������ enum���� Ű���� ����Ű�� ��Ī
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)  //GetAsyncKeyState(g_arrVK[i]) : ����Ű���� & 0x8000 Ű�� �����ִٸ�
			{
				if (m_vecKey[i].bPrevPush) // �������� �����ִٸ�
				{
					m_vecKey[i].eState = KEY_STATE::HOLD; // ���� ������ ���� HOLD�� ��
				}
				else // ������ �������� �ʾҴٸ�
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true; // ���� ���� ������Ʈ
			}

			else // ���� �������� �ʴٸ�
			{
				if (m_vecKey[i].bPrevPush) // ������ �����ִٸ�
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else // �������� �������� �ʴٸ�
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}

		}
	}
	else // ��Ŀ���� �ƴ϶��
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;
			// ���� ���������� ����
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState) 
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}

}
