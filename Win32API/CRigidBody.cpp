#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(50.f)
	, m_fMaxSpeed(200.f)
{	  
}	  

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
		//Vec2 vDir = m_vForce;
		//	vDir.Normalize();
		//// 가속도의 크기
		//float fAccel = fForce / m_fMass;
		 
		// 가속도
		m_vAccel = m_vForce / m_fMass;  // == vDir * fAccel;
		// 속도
		m_vVelocity += m_vAccel * fDT;
	}


	// 마찰, 저항 붙이기
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();


		// 마찰력에 의한 반대방향으로의 가속도 적용
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래속도보다 큰 경우 
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도제한 검사 : 저항
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize(); // 방향 유지 후 
		m_vVelocity *= m_fMaxSpeed; // 속력 붙인다
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
