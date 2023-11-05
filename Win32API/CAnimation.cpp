#include "pch.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime )
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm) // 애니매이션을 다 썻다면
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration; // 넘어선 프레임시간만큼 넣어주기
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset; // Object에 Offset 만큼 추가이동위치 (다리기준 중심좌표 = 애니매이션 위로 올리기)

	vPos = CCamera::GetInst()->GetRenderPos(vPos);


	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f	)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)				
		, m_pTex->GetDC()									
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)					
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)					
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)				
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255));
	

	// 알파넣는 코드
	
	// BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127; //알파 강도조절 0~255
	//
	// 
	//AlphaBlend(_dc
	//, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
	//	, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
	//	, m_pTex->GetDC()
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.x)
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.y)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
	//	, bf);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}


}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	//// Animation의 이름을 저장한다
	//SaveWString(m_strName, pFile); // 바이트단위 눌러담은 데이터만 저장하여 파일 열었을때 사람이 알아보기 힘들다
	//
	//
	//
	//// 텍스쳐
	//SaveWString(m_pTex->GetKey(),pFile);
	//SaveWString(m_pTex->GetRelativePath(), pFile);
	//
	//// 프레임 개수
	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);
	////모든 프레임정보
	//fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);



	//인코딩 하기
	fprintf(pFile, "[Animation Name]\n");
	string strAnimName = string(m_strName.begin(), m_strName.end()); //1바이트 문자열로 변환
	fprintf(pFile, strAnimName.c_str());// 파일을 문자열로 저장시켜주는 함수
	fprintf(pFile, "\n");
	
	fprintf(pFile, "[Texture Name]\n");
	string strTexName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end()); 
	fprintf(pFile, strTexName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	string strPath = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end()); 
	fprintf(pFile, strPath.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n",(int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d, %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}


	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 애니매이션 이름읽기
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);
	LoadWString(m_strName, pFile);

	//텍스쳐
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);



	//프레임개수
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);
	//모든 프레임정보
	m_vecFrm.resize(iFrameCount);
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	fclose(pFile);
}
