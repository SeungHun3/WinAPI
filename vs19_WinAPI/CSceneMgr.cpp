#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{} // ��� �� nullptr�� ä��
{
}

CSceneMgr::~CSceneMgr()
{
	// �� ���� ����
	// ��class �ڽĿ� vitual �Ҹ��� ������ ���ٸ� �ڽ��� �Ҹ��ڴ� ȣ������ �ʰ� ��

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
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = nullptr;// = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = nullptr;// = new CScene_STAGE_01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = nullptr;// = new CScene_STAGE_02;


	//���� �� ����
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