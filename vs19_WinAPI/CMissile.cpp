#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	//: m_fTheta(PI) // m_fTheta : 0 ~ 1 = 0도 ~ 180도
	: m_vDir(Vec2(1.f,1.f)) // 벡터좌표계로 방향계산
{
	m_vDir.Normalize(); // 벡터의 길이를 1로 변환

}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	// 대각선 이동시 이동량 1 맞춰주기 => x, y 비율계산
	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT; 
	
	// 방향을 벡터단위로 변환 => 다방면의 수치계산에 용이(  ex> 왼쪽에서 밀고, 아래왼쪽에서 밀때  )
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;


	SetPos(vPos);

}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));


}
