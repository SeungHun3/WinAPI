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



	int iLen = wcslen(m_szContentPath);
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
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);


}
