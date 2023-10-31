#pragma once
#include "CRes.h"

// ��ü�� �ؽ��� ����
// �ؽ��� ������ ��θ� �������� �Ͽ� ��� ����ϱ�: release���� ���������� content���� ���
// ������������ ��θ� ������� PathManager�ʿ�
class CTexture :
    public CRes
{
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

public:
    void Load(const wstring& _strFilePath); // �����κ���: ������Ʈ �Ӽ� => ��µ��丮 ����  $(SolutionDir)Output\bin_debug

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr; // ���ҽ��Ŵ��������� ������ �� �ְ�
};

