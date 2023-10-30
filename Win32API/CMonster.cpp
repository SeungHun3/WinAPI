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

	//����������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += m_fSpeed * m_iDir * fDT;

	//��ȸ�Ÿ� ���ط��� �Ѿ���� Ȯ��
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxdistance;

	if (0.f < fDist)
	{
		// ���� ���� + �ʰ��� �Ÿ���ŭ �����̱�
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}


	SetPos(vCurPos);
}