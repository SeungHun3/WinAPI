#pragma once

// 실행시 실행된 위치를 기억하고 있어서 받아올 수 있음
// 실행파일의 상위폴더로 가서 content 파일 진입(디버그모드일 경우에도 사용해야해서)
class CPathMgr
{

	SINGLE(CPathMgr)

private:
	wchar_t m_szContentPath[255]; // 윈도우에서 경로가 255로 제한되어있음

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};

