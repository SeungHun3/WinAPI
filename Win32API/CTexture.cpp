#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void CTexture::Load(const wstring& _strFilePath)
{
	//파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);// LoadImage구글 검색=>LR_CREATEDIBSECTION | LR_LOADFROMFILE 비트연산식
	assert(m_hBit);	//if (nullptr == m_hBit) 로딩이 제대로 안됬을 경우  => 경고창

	// 비트맵과 연결될 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);

	// 가로 세로 길이 = 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo); // 오브젝트에 대한 정보를 알려주는 함수 // 파일로 부터 받은 오브젝트 ,저장받을 사이즈,  정보를 받을 주소
	//m_bitInfo.bmWidth;
	//m_bitInfo.bmHeight;






}