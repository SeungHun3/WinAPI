#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CTimeMgr.h"
#include "CCollider.h"
CMonster::CMonster()
	: m_tInfo{}
	, m_pAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}



void CMonster::update()
{
	m_pAI->update();
}


void CMonster::SetAI(AI* _pAI)
{
	m_pAI = _pAI;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		
	}
	
}