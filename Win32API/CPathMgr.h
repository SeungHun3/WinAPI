#pragma once

// ����� ����� ��ġ�� ����ϰ� �־ �޾ƿ� �� ����
// ���������� ���������� ���� content ���� ����(����׸���� ��쿡�� ����ؾ��ؼ�)
class CPathMgr
{

	SINGLE(CPathMgr)

private:
	wchar_t m_szContentPath[255]; // �����쿡�� ��ΰ� 255�� ���ѵǾ�����

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};

