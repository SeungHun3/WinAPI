#include "pch.h"
#include "CIdleState.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include"CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// 가만히 있기
	// 플레이어의 위치체크, 범위안에 있을경우 추적상태전환
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	Vec2 vMonPos = pMonster->GetPos();

	Vec2 vDiff = vPlayerPos - vMonPos;
	float fLen = vDiff.Length();

	// 플레이어가 몬스터 진입범위 안으로 진입
	if (fLen < pMonster->GetInfo().m_fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
	

	
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
