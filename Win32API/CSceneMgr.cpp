#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{} // 모든 씬 nullptr로 채움
{
}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제
	// 씬class 자식에 vitual 소멸자 선언이 없다면 자식의 소멸자는 호출하지 않게 됨

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = nullptr;// = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = nullptr;// = new CScene_STAGE_01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = nullptr;// = new CScene_STAGE_02;


	//현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();

}

void CSceneMgr::update()
{
	m_pCurScene->update();

}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);

}
