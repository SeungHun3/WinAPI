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

	void update();
	void render(HDC _dc);

	// ���� �����Լ��� ���� = Ŭ������ �߻�Ŭ������ ���� 
	// => �߻�Ŭ������  ���������� new ���� �Ұ�, �ڽ�Ŭ������ virtual�� �Լ��� �������̵����� ������ �߻�Ŭ������ �Ǿ����
	virtual void Enter() = 0; // ���Խ� ȣ��
	virtual void Exit() = 0;  // Ż��� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // �ζ��� �Լ� �ۼ��� �ٸ������� ȣ���ص� �ش� ���ÿ��� ȣ��Ǿ� ȣ�������
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

