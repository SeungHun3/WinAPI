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
	// Texture 로딩하기
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
	int iWidth = (int)m_pTex->Width(); // width는 unsigned int로 반환되지만 BitBlt에 들어갈 정보는 음수가 들어갈 수도 있음(화면밖으로 나갈때) => int 캐스팅
	int iHeight = (int)m_pTex->Height();
	Vec2 vPos = GetPos();



	////BitBlt 모든 픽셀을 복사
	//BitBlt(_dc
	//	, int(vPos.x - (float)(iWidth / 2)) // x 시작점
	//	, int(vPos.y - (float)(iHeight / 2))// y 시작점
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);



	// 조건에 따른 픽셀복사
	TransparentBlt(_dc
		//텍스쳐원본
		, int(vPos.x - (float)(iWidth / 2)) // x 시작점
		, int(vPos.y - (float)(iHeight / 2))// y 시작점
		, iWidth, iHeight		// x,y 끝점
		, m_pTex->GetDC()
		//원본에서의 자를 픽셀범위
		, 0, 0, 64, 64//iWidth, iHeight	
		, RGB(255, 0, 255));
	// 선언 부분은 window.h에 되어있으나 구현파트가 Library에 들어있음 #pragma comment (lib, "Msimg32.lib")

	// 컴포넌트가 있는경우 렌더
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
