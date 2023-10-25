#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	//: m_fTheta(PI) // m_fTheta : 0 ~ 1 = 0�� ~ 180��
	: m_vDir(Vec2(1.f,1.f)) // ������ǥ��� ������
{
	m_vDir.Normalize(); // ������ ���̸� 1�� ��ȯ

}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	// �밢�� �̵��� �̵��� 1 �����ֱ� => x, y �������
	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDT; 
	
	// ������ ���ʹ����� ��ȯ => �ٹ���� ��ġ��꿡 ����(  ex> ���ʿ��� �а�, �Ʒ����ʿ��� �ж�  )
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
