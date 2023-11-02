#pragma once

// ����� ����� ��ġ�� ����ϰ� �־ �޾ƿ� �� ����
// ���������� ���������� ���� content ���� ����(����׸���� ��쿡�� ����ؾ��ؼ�)
class CPathMgr
{

	SINGLE(CPathMgr)

private:
	wchar_t m_szContentPath[256]; // �����쿡�� ��ΰ� 256�� ���ѵǾ�����
	wchar_t m_szRelativePath[256];
public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
	wstring GetRelativePath(const wchar_t* _filepath); // ����� �����
};

