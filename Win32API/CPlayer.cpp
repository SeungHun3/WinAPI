#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture �ε��ϱ�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(200.f, 200.f));
}

CPlayer::~CPlayer()
{

}



void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width(); // width�� unsigned int�� ��ȯ������ BitBlt�� �� ������ ������ �� ���� ����(ȭ������� ������) => int ĳ����
	int iHeight = (int)m_pTex->Height();
	Vec2 vPos = GetPos();



	////BitBlt ��� �ȼ��� ����
	//BitBlt(_dc
	//	, int(vPos.x - (float)(iWidth / 2)) // x ������
	//	, int(vPos.y - (float)(iHeight / 2))// y ������
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);



	// ���ǿ� ���� �ȼ�����
	TransparentBlt(_dc
		//�ؽ��Ŀ���
		, int(vPos.x - (float)(iWidth / 2)) // x ������
		, int(vPos.y - (float)(iHeight / 2))// y ������
		, iWidth, iHeight		// x,y ����
		, m_pTex->GetDC()
		//���������� �ڸ� �ȼ�����
		, 0, 0, 64, 64//iWidth, iHeight	
		, RGB(255, 0, 255));
	// ���� �κ��� window.h�� �Ǿ������� ������Ʈ�� Library�� ������� #pragma comment (lib, "Msimg32.lib")

	// ������Ʈ�� �ִ°�� ����
	component_render(_dc);

}

void CPlayer::CreateMissile()
{

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile,GROUP_TYPE::PROJ_PLAYER);


}
