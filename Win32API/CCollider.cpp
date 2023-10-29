#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"


CCollider::CCollider()
	: m_pOwner(nullptr)
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
	//pen, brush를 받아서
	HPEN hGreenPen = CCore::GetInst()->GetPen(PEN_TYPE::GREEN);
	HBRUSH hHollowBrush = CCore::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//원래 쓰던 펜과 오브젝트를 돌려받는다
	HPEN hDefaultPen = (HPEN)SelectObject(_dc, hGreenPen);
	HBRUSH hDefaultBrush = (HBRUSH)SelectObject(_dc, hHollowBrush);

	Rectangle(_dc
		, m_vFinalPos.x - m_vScale.x / 2.f
		, m_vFinalPos.y - m_vScale.y / 2.f
		, m_vFinalPos.x + m_vScale.x / 2.f
		, m_vFinalPos.y + m_vScale.y / 2.f);


	SelectObject(_dc, hGreenPen);
	SelectObject(_dc, hHollowBrush);

}

