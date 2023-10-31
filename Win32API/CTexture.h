#pragma once
#include "CRes.h"

// 객체에 텍스쳐 맵핑
// 텍스쳐 파일의 경로를 고정으로 하여 계속 사용하기: release버전 빌드폴더에 content폴더 사용
// 빌드폴더까지 경로를 담당해줄 PathManager필요
class CTexture :
    public CRes
{
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    void Load(const wstring& _strFilePath); // 빌드경로변경: 프로젝트 속성 => 출력디렉토리 변경  $(SolutionDir)Output\bin_debug

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr; // 리소스매니저에서만 생성할 수 있게
};

