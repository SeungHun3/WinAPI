#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}
CPathMgr::~CPathMgr()
{}

//��� �ڵ�ȭ�����
void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath); // ���� ������Ʈ ��� �޾ƿ��� => ������: f5 ����� �������ϰ� ��ġ �ٸ�
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
	// �ذ� : �Ӽ� ����뿡�� ��� �������� ���� �� �۾����丮 $(ProjectDir) �� $(SolutionDir)Output\bin\ ���� �ٲ���
	// => ���⼭ ������� �̵� �� bin\\content\\ �� ��� ���

	int iLen = (int)wcslen(m_szContentPath);
	//���������� 	//���ڿ� ��ȯ '\\' => '\0'
	for (int i = iLen - 1; i >= 0; --i) // ���ڿ� �ڿ������� Ž��
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // \0���� ã�Ƽ� �ڿ� ���ڿ� ���̱�

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); //������â�� Ȯ���غ���
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;
	size_t AbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(AbsLen, iFullLen - AbsLen);

	return strRelativePath;
}
