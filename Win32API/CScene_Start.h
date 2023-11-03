#pragma once
#include "CScene.h"
class CScene_Start :public CScene
{

private:
	Vec2 m_vForcePos;
	float m_fForceRadius;
	float m_fCurRadius;
	float m_fForce;
	bool m_bUseForce;


public:
	// 자식에서 virtual 키워드를 붙이지 않아도 오버라이드는 된다
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();

public:
	void CreateForce();

public:
	CScene_Start();
	~CScene_Start();
};

