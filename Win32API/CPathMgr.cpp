#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}
CPathMgr::~CPathMgr()
{}

//경로 자동화만들기
void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath); // 현재 프로젝트 경로 받아오기 => 문제점: f5 실행시 실행파일과 위치 다름
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
	// 해결 : 속성 디버깅에서 모든 구성으로 변경 후 작업디렉토리 $(ProjectDir) 를 $(SolutionDir)Output\bin\ 으로 바꿔줌
	// => 여기서 상위경로 이동 후 bin\\content\\ 로 경로 잡기



	int iLen = wcslen(m_szContentPath);
	//상위폴더로 	//문자열 변환 '\\' => '\0'
	for (int i = iLen - 1; i >= 0; --i) // 문자열 뒤에서부터 탐색
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // \0문자 찾아서 뒤에 문자열 붙이기
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);


}
