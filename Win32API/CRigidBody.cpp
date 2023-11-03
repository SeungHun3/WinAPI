#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
{	  
}	  
Vec2 m_vVelocity;
CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		Vec2 vDir = m_vForce;
		vDir.Normalize();
		// 가속도의 크기
		float fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce / m_fMass;  // == vDir * fAccel;

		// 속도
		m_vVelocity += m_vAccel * fDT;
	}

	// 속도에 따른 이동
	Move();


	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 속력
	float fSpeed = m_vVelocity.Length();
	if (0.f == fSpeed)
	{
		return;
	}

	// 방향
	Vec2 vDir = m_vVelocity;
	vDir.Normalize();
	
	Vec2 vPos = m_pOwner->GetPos();
	
	vPos += m_vVelocity * fDT; // == vDir * fSpeed * fDT

	m_pOwner->SetPos(vPos);
}
