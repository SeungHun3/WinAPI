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

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update(); // 부모함수 호출
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}


	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{

	//오브젝트 추가
	//pObj = new CObject; // 추상클래스로 변경되어 동적 할당 불가

	//Player
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	////복사 생성자를 이용한 개체복사
	//CObject* pOtherPlayer = pObj->Clone(); //new CPlayer(*(CPlayer*)pObj);
	//pOtherPlayer->SetPos(Vec2(440.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);


	//CCamera::GetInst()->SetTarget(pObj);



	////Monster
	//선언과 동시에 대입을 하면 복사생성자가 호출 => struct.h 34줄 생성자 호출
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	int iMonCount = 3;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	for (int i = 0; i < iMonCount; i++)
	{
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}
	//타일 로딩
	//LoadTile(L"tile\\Start.tile");


	// 충돌지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);


	//카메라 Look지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}



void CScene_Start::Exit()
{
	DeleteAll();

	//그룹끼리 묶은 충돌해제
	CCollisionMgr::GetInst()->Reset();
}
