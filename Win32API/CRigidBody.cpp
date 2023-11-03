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
	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		Vec2 vDir = m_vForce;
		vDir.Normalize();
		// ���ӵ��� ũ��
		float fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce / m_fMass;  // == vDir * fAccel;

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}

	// �ӵ��� ���� �̵�
	Move();


	// �� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �ӷ�
	float fSpeed = m_vVelocity.Length();
	if (0.f == fSpeed)
	{
		return;
	}

	// ����
	Vec2 vDir = m_vVelocity;
	vDir.Normalize();
	
	Vec2 vPos = m_pOwner->GetPos();
	
	vPos += m_vVelocity * fDT; // == vDir * fSpeed * fDT

	m_pOwner->SetPos(vPos);
}
