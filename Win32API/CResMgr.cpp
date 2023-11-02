#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey); // 키가 중복되어 이미 있는 값이라면
	if (nullptr != pTex)
	{
		return pTex; // 바로 반환
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	CTexture* pTex = FindTexture(_strKey); // 키가 중복되어 이미 있는 값이라면
	if (nullptr != pTex)
	{
		return pTex; // 바로 반환
	}

	pTex = new CTexture;
	pTex->Create(_iWidth, _iHeight);
	pTex->SetKey(_strKey);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end()) // iterator가 end라면 찾지 못했다는 뜻이니 nullptr반환 
	{
		return nullptr;
	}

	return (CTexture*)iter->second; // 찾았다면 반환
}
