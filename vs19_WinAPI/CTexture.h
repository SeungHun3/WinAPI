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


public:
    void Load(const wstring& _strFilePath); // �����κ���: ������Ʈ �Ӽ� => ��µ��丮 ����  $(SolutionDir)Output\bin_debug

public:
    CTexture();
    ~CTexture();;
};

