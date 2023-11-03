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
	//이전 프레임에 등록해준 Dead 오브젝트들을 삭제한다
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// 이벤트 처리
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
	case EVENT_TYPE::CREATE_OBJECT:// lParam = 오브젝트 주소, wParam = 그룹타입
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}


		break;
	case EVENT_TYPE::DELETE_OBJECT:// lParam = 오브젝트 주소, wParam = 그룹타입
	{
		//오브젝트를 Dead상태로 변경
		//삭제예정 오브젝트를 모아둔다
		CObject* pDeadObj = (CObject*)_eve.lParam;

		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
		
	case EVENT_TYPE::SCENE_CHANGE: // lParam : Next Scene Type
	{
		// Scene변경
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		// UI 포커스 해제 (이전 UI 포커싱해봐야함)
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
