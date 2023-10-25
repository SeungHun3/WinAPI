#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CPathMgr.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture �ε��ϱ�
	m_pTex = new CTexture;
	wstring strFilepath = CPathMgr::GetInst()->GetContentPath();

	//�����
	strFilepath += L"texture\\Player.bmp";
	m_pTex->Load(strFilepath);


}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
	{
		delete m_pTex;
	}

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
		, 0,0, 64,64//iWidth, iHeight	
		, RGB(255,0,255)); 
	// ���� �κ��� window.h�� �Ǿ������� ������Ʈ�� Library�� ������� #pragma comment (lib, "Msimg32.lib")

}

void CPlayer::CreateMissile()
{

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	CMissile* pMissile = new CMissile;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	//pMissile->SetDir(true);
	pMissile->SetDir(Vec2(0.f, -1.f));

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFALUT);


}
