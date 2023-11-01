#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}
void CTile::update()
{
}
void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iIdx)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;
	UINT iCurRow = m_iIdx / iMaxCol;
	UINT iCurCol = m_iIdx % iMaxCol;


	// �̹��� ������ ��� �ε���
	if (iMaxRow <= iCurRow)
		assert(nullptr);


	Vec2 vRenderPos = CCamera::GetInst()->GetRealPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
}