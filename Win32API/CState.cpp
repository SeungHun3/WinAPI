#include "pch.h"
#include "CState.h"
#include "AI.h"
#include "CMonster.h"


CState::CState(MON_STATE _eState)
	: m_eState(_eState)
{
}

CState::~CState()
{
	
}

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}
