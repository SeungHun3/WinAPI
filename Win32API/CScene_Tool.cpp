#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update(); // 부모함수 호출
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Tool::Enter()
{
}

void CScene_Tool::Exit()
{
}
