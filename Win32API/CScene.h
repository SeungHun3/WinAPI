#pragma once


class CObject; // Ŭ���� ���漱�� = ��ó��, �����Ϸ�, ����� ���� �� ��Ŀ�� �Ѱ� ��Ī��Ŵ, Ŭ������ ���� ��ü���� ������ ���� ���� -> ������ Ÿ������ ���

class CScene
{
private:
	// vector�� ������Ŭ������ ��� ����: ������ �Ļ��� �θ�Ŭ������ ��� ���뼺�� ���̱� ���� �뵵
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� �׷찳����ŭ ����
	wstring m_strName; // Scene �̸�
	
	UINT m_iTileX; //Ÿ�� ���ΰ���
	UINT m_iTileY; //Ÿ�� ���ΰ���


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	// ���� �����Լ��� ���� = Ŭ������ �߻�Ŭ������ ���� 
	// => �߻�Ŭ������  ���������� new ���� �Ұ�, �ڽ�Ŭ������ virtual�� �Լ��� �������̵����� ������ �߻�Ŭ������ �Ǿ����
	virtual void Enter() = 0; // ���Խ� ȣ��
	virtual void Exit() = 0;  // Ż��� ȣ��

public:

	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // �ζ��� �Լ� �ۼ��� �ٸ������� ȣ���ص� �ش� ���ÿ��� ȣ��Ǿ� ȣ�������
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; } // �׷� ��ü�� ����
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _YCount);

public:
	CScene();
	virtual ~CScene();
};

