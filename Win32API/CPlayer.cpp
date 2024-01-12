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
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"


CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_iPrevDir(1)
	, m_iDir(1)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, -4.f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));

	CreateRigidBody();

	
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	CreateAnimator();

	// 애니매이션 세이브
	
	//CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\Player01_L.bmp"); 
	//CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\Player01_R.bmp");
	//
	//
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pRightTex, Vec2(0.f, 0.f), Vec2(45.f, 50.f), Vec2(47.f, 0.f), 2.f, 2);
	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", pLeftTex, Vec2(555.f, 0.f), Vec2(45.f, 50.f), Vec2(-47.f, 0.f), 2.f, 2);
	//
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pRightTex, Vec2(0.f, 85.f), Vec2(45.f, 50.f), Vec2(60.f, 0.f), 0.15f, 8);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pLeftTex, Vec2(555.f, 85.f), Vec2(45.f, 50.f), Vec2(-60.f, 0.f), 0.15f, 8);
	//
	//GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pRightTex, Vec2(5.f, 170.f), Vec2(50.f, 50.f), Vec2(60.f, 0.f), 0.15f, 2);
	//GetAnimator()->CreateAnimation(L"JUMP_LEFT", pLeftTex, Vec2(548.f, 170.f), Vec2(50.f, 50.f), Vec2(-60.f, 0.f), 0.15f, 2);
	//
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(PlayerAnimIdleRight);
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(PlayerAnimIdleLeft);
	//
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(PlayerAnimWalkRight);
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(PlayerAnimWalkLeft);
	//
	//GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(PlayerAnimJumpRight);
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(PlayerAnimJumpLeft);



	//애니매이션 로드
	
	GetAnimator()->LoadAnimation(PlayerAnimIdleLeft);
	GetAnimator()->LoadAnimation(PlayerAnimIdleRight);
	
	GetAnimator()->LoadAnimation(PlayerAnimWalkLeft);
	GetAnimator()->LoadAnimation(PlayerAnimWalkRight);
	
	GetAnimator()->LoadAnimation(PlayerAnimJumpLeft);
	GetAnimator()->LoadAnimation(PlayerAnimJumpRight);


	GetAnimator()->Play(L"IDLE_RIGHT",true);
	//// 애니매이션 오프셋
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	//for(UINT i = 0; i< pAnim->GetMaxFrame(); ++i)
	//pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);

	//중력 컴포넌트
	CreateGravity();

}

CPlayer::~CPlayer()
{

}



void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{

	// 컴포넌트가 있는경우 렌더
	component_render(_dc);

	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane",L"texture\\Player_A.bmp");
	//
	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);
	//
	//float width = (float)pTex->Width();
	//float height = (float)pTex->Height();
	//
	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127; //알파 강도조절 0~255
	//
	//AlphaBlend(_dc
	//	, (int)(vPos.x - width / 2.f)
	//	, (int)(vPos.y - height / 2.f)
	//	, (int)width
	//	, (int)height
	//	, pTex->GetDC()
	//	, 0, 0, (int)width, (int)height
	//	, bf);

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

void CPlayer::update_state()
{
	
	if (KEY_TAP(KEY::A))
	{
		m_iDir = -1;

	}
	if (KEY_TAP(KEY::D))
	{
		m_iDir = 1;
	}
	
	float fXLen = abs(GetRigidBody()->GetVelocity().x);
	
	if (PLAYER_STATE::JUMP != m_eCurState) 
	{
		if (0.5f > fXLen)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
		else
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		//CreateMissile();
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -400.f));
		}
	}

}

void CPlayer::update_move()
{
	//Vec2 vPos = GetPos();

	CRigidBody* pRigid = GetRigidBody();
	if (m_eCurState == PLAYER_STATE::JUMP)
		return;

	if (KEY_HOLD(KEY::A))
	{
		//vPos.x -= 200.f * fDT;
		pRigid->AddForce(Vec2(-300.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		//vPos.x += 200.f * fDT;
		pRigid->AddForce(Vec2(300.f, 0.f));
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-50.f, pRigid->GetVelocity().y));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(50.f, pRigid->GetVelocity().y));
	}

	//SetPos(vPos);
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir >0)
		{
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		}
		else
		{
			GetAnimator()->Play(L"IDLE_LEFT", true);
		}
		
	}

		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir >0)
		{
			GetAnimator()->Play(L"WALK_RIGHT", true);
		}
		else
		{
			GetAnimator()->Play(L"WALK_LEFT", true);
		}
	}

		break;
	case PLAYER_STATE::JUMP:
		if (m_iDir > 0)
		{
			GetAnimator()->Play(L"JUMP_RIGHT", true);
		}
		else
		{
			GetAnimator()->Play(L"JUMP_LEFT", true);
		}

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	default:
		break;
	}

}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f,500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		Vec2 vPos = GetPos();
		
		if (vPos.y < pOtherObj->GetPos().y)
		{
			float fXLen = abs(GetRigidBody()->GetVelocity().x);
			if (0.5f > fXLen)
			{
				m_eCurState = PLAYER_STATE::IDLE;
			}
			else
			{
				m_eCurState = PLAYER_STATE::WALK;
			}
		}

	}
}
