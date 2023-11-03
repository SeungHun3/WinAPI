#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "resource.h"

#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"


void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// �޴��� ����
	CCore::GetInst()->DockMenu();

	//Ÿ�ϻ���
	CreateTile(5, 5);
	
	//UI �ϳ� �����
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;

	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f,150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x,0.f));


	CBtnUI* pBtnUI = new CBtnUI;

	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	// �����Լ��� �ƴ� Ŭ���� �����Լ��� ��� �ּҸ� �� => Ʋ�� ���� ĳ���ñ��� �������
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData); 
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	//���纻 UI
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	//
	//AddObject(pClonePanel, GROUP_TYPE::UI);
	//
	//m_pUI = pClonePanel;

	//ī�޶� Look����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	//�޴��� �и�
	CCore::GetInst()->DivideMenu();
	DeleteAll();
}


void CScene_Tool::update()
{
	CScene::update(); // �θ��Լ� ȣ��
	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT))
	//{
	//	//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	//	SaveTileData();
	//}
	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}

}


void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f|| iTileY <= iRow)
		{
			return;
		}


		UINT iIdx = iRow * iTileX + iCol; // �̹����� �ε������ϱ�
		
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();

	}
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0; // �⺻ All�� ���� 1 = tile
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); //â�� ������ �ʱ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //��ο� ������ �ݵ�� �����ؾ���


	//Modal ��� = �ش�â�� ��Ŀ���� �Ǿ� �ٸ� â���� �������� ���� => ���ϰ� ������
	if (GetSaveFileName(&ofn)) // ����: true, ���: false
	{
		//���� ������ �����̸��� szName�� ����(������ ����)
		SaveTile(szName);
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// FILE = Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb"); // ���: w ����, r �б�
	assert(pFile); // nullptr�̶�� ���� ���� ����

	// ������ ����
	// Ÿ�� ���μ���
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);


	// ��� Ÿ�ϵ��� ���������� ������ ������
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0; // �⺻ All�� ���� 1 = tile
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); //â�� ������ �ʱ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //��ο� ������ �ݵ�� �����ؾ���


	//Modal ��� = �ش�â�� ��Ŀ���� �Ǿ� �ٸ� â���� �������� ���� => ���ϰ� ������
	if (GetOpenFileName(&ofn)) // ����: true, ���: false
	{
		//���� ������ �����̸��� szName�� ����(������ ����)
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		//����η� �־��ֱ�
		LoadTile(strRelativePath);
	}
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

//Ÿ�� ī��Ʈ ������ ���ν���
//CALLBACK == __stdcall
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false); //Edit Box�� ���� int�� ������
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}