#pragma once
#include "CScene.h"
class CScene_Start :public CScene
{

public:
	// �ڽĿ��� virtual Ű���带 ������ �ʾƵ� �������̵�� �ȴ�
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

