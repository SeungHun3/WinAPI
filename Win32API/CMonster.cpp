#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"
CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxdistance(50.f)
	, m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}


void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	//진행방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += m_fSpeed * m_iDir * fDT;

	//배회거리 기준량을 넘어섰는지 확인
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxdistance;

	if (0.f < fDist)
	{
		// 방향 변경 + 초과한 거리만큼 움직이기
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}


	SetPos(vCurPos);
}