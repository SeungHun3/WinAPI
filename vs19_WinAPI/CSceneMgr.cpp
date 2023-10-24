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

	for (UINT i = 0; (UINT)SCENE_TYPE::END; i++)
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
	m_arrScene[(UINT)SCENE_TYPE::TOOL];// = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01];// = new CScene_STAGE_01;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02];// = new CScene_STAGE_02;


	//���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

}
