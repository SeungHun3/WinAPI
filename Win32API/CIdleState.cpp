#include "pch.h"
#include "CIdleState.h"


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


}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
