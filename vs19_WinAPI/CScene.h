#pragma once

class CObject; // Ŭ���� ���漱�� = ��ó��, �����Ϸ�, ����� ���� �� ��Ŀ�� �Ѱ� ��Ī��Ŵ, Ŭ������ ���� ��ü���� ������ ���� ���� -> ������ Ÿ������ ���

class CScene
{
private:
	// vector�� ������Ŭ������ ��� ����: ������ �Ļ��� �θ�Ŭ������ ��� ���뼺�� ���̱� ���� �뵵
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� �׷찳����ŭ ����
	wstring m_strName; // Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


public:
	CScene();
	virtual ~CScene();
};

