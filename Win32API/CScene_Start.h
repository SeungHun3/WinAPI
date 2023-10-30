#pragma once
#include "CScene.h"
class CScene_Start :public CScene
{

public:
	// 자식에서 virtual 키워드를 붙이지 않아도 오버라이드는 된다
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

