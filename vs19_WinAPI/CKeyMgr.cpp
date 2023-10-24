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
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false}); // 모든키 값 초기화
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기 
	HWND hWnd = GetFocus(); // 포커싱이 없다면 nullptr반환


	// 포커싱 처리 하지 않는다면 창을 내려도 입력이 반영된다
	if (nullptr != hWnd) // 포커싱 중이라면
	{
		// 내가 설정한 enum값과 키보드 가상키값 매칭
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)  //GetAsyncKeyState(g_arrVK[i]) : 가상키값이 & 0x8000 키가 눌려있다면
			{
				if (m_vecKey[i].bPrevPush) // 이전에도 눌려있다면
				{
					m_vecKey[i].eState = KEY_STATE::HOLD; // 내가 설정한 값에 HOLD를 줌
				}
				else // 이전에 눌려있지 않았다면
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true; // 현재 상태 업데이트
			}

			else // 지금 눌려있지 않다면
			{
				if (m_vecKey[i].bPrevPush) // 이전에 눌려있다면
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else // 이전에도 눌려있지 않다면
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}

		}
	}
	else // 포커싱이 아니라면
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;
			// 상태 순차적으로 해제
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
