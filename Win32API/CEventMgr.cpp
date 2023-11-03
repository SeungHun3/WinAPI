#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"


CEventMgr::CEventMgr()
{

}
CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	//���� �����ӿ� ������� Dead ������Ʈ���� �����Ѵ�
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:// lParam = ������Ʈ �ּ�, wParam = �׷�Ÿ��
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}


		break;
	case EVENT_TYPE::DELETE_OBJECT:// lParam = ������Ʈ �ּ�, wParam = �׷�Ÿ��
	{
		//������Ʈ�� Dead���·� ����
		//�������� ������Ʈ�� ��Ƶд�
		CObject* pDeadObj = (CObject*)_eve.lParam;

		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
		
	case EVENT_TYPE::SCENE_CHANGE: // lParam : Next Scene Type
	{
		// Scene����
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		// UI ��Ŀ�� ���� (���� UI ��Ŀ���غ�����)
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	case EVENT_TYPE::CHANGE_AI_STATE: // lParam : AI, wParam : NextType
	{
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
	}

		break;
	case EVENT_TYPE::END:
		break;
	default:
		break;
	}




}
