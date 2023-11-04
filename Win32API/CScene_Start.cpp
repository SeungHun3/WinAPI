#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"


CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	//CScene::update(); // 부모함수 호출

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); j++)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float vLen = vDiff.Length();
					
					if (vLen < m_fForceRadius)
					{
						// rigid body를 보유하고 있고 중력발생 범위안에 있을 경우
						float fRatio = 1.f - (vLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;
						
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}

				vecObj[j]->update();
			}
		}
	}
	// 여기까지 중력적용위해 부모함수 아닌 직접구현 



	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	// 카메라 마우스 클릭위치로 움직임
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}

}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}
	
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);


	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));

}

void CScene_Start::Enter()
{

	//오브젝트 추가
	//pObj = new CObject; // 추상클래스로 변경되어 동적 할당 불가

	//Player
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	ResisterPlayer(pObj);
	////복사 생성자를 이용한 개체복사
	//CObject* pOtherPlayer = pObj->Clone(); //new CPlayer(*(CPlayer*)pObj);
	//pOtherPlayer->SetPos(Vec2(440.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);


	//CCamera::GetInst()->SetTarget(pObj);



	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//Monster Event생성
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);


	// Ground 배치
	CObject* pGround = new CGround;
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(200.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);


	//타일 로딩
	//LoadTile(L"tile\\Start.tile");


	// 충돌지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);


	//카메라 Look지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();
}



void CScene_Start::Exit()
{
	DeleteAll();

	//그룹끼리 묶은 충돌해제
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);



}
