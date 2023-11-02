#include "CBtnUI.h"


CBtnUI::CBtnUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}


void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc) // �����ؾ��� �Լ������Ͱ� nullptr�� �ƴ϶��
	{
		m_pFunc(m_param1, m_param2);
	}
	
	if (m_pSceneInst && m_pSceneFunc) // ��ü�� ȣ���� �Լ��ּҰ� �����Ҷ�
	{
		((*m_pSceneInst).*m_pSceneFunc)();

	}

}

void CBtnUI::SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
{
	m_pFunc = _pFunc;
	m_param1 = _param1;
	m_param2 = _param2;
}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}