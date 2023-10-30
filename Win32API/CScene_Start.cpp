#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{

	//������Ʈ �߰�
	//pObj = new CObject; // �߻�Ŭ������ ����Ǿ� ���� �Ҵ� �Ұ�

	//Player
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	////Monster
	//CMonster* pMonsterObj = new CMonster;
	//pMonsterObj->SetPos(Vec2(640.f, 50.f));
	//pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//pMonsterObj->SetScale(Vec2(50.f, 50.f));
	//AddObject(pMonsterObj, GROUP_TYPE::DEFALUT);

	//����� ���ÿ� ������ �ϸ� ��������ڰ� ȣ�� => struct.h 34�� ������ ȣ��
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
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// �浹����
	// Player �׷�� Monster �׷찣�� �浹üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

}

void CScene_Start::Exit()
{
	//�׷쳢�� ���� �浹����
	CCollisionMgr::GetInst()->Reset();
}
