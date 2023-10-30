#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// 오브젝트의 위치를 따라간다
	Vec2 vObjectPos = m_pOwner->GetPos();

	m_vFinalPos = vObjectPos + m_vOffsetPos;

}

void CCollider::render(HDC _dc)
{
	SelectGDI p(_dc, PEN_TYPE::GREEN); // 임시객체 생성할때 소멸하면 해당 함수종료시 소멸자 호출됨(소멸자에 오브젝트 반환함수처리)
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));


}



void CCollider::OnCollision(CCollider* _pOther)
{
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
}

