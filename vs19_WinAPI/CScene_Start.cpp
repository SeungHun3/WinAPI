#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"
CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Texture 로딩하기
	CTexture* pTex = new CTexture;
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();

	//상대경로
	strFilepath += L"texture\\Player.bmp";
	pTex->Load(strFilepath);


	delete pTex;


	//오브젝트 추가
	//pObj = new CObject; // 추상클래스로 변경되어 동적 할당 불가
	
	//Player
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::DEFALUT);

	////Monster
	//CMonster* pMonsterObj = new CMonster;
	//pMonsterObj->SetPos(Vec2(640.f, 50.f));
	//pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//pMonsterObj->SetScale(Vec2(50.f, 50.f));
	//AddObject(pMonsterObj, GROUP_TYPE::DEFALUT);

	//선언과 동시에 대입을 하면 복사생성자가 호출 => struct.h 34줄 생성자 호출
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;

	int iMonCount = 10;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	for (int i = 0; i < iMonCount; i++)
	{
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFALUT);
	}

}

void CScene_Start::Exit()
{
}
