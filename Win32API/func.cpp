#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::CREATE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;
	even.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(even);
}

void DeleteObject(CObject* _pObj)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::DELETE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(even);

}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::SCENE_CHANGE;
	even.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(even);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::CHANGE_AI_STATE;
	even.lParam = (DWORD_PTR)_pAI;
	even.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(even);
}
