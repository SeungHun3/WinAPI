#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; // collider�� �����ϰ� �ִ� ������Ʈ	
	Vec2 m_vOffsetPos; // �� �������� �������� ���Ǵ� ������
	Vec2 m_vFinalPos; // finalupdate���� �������Ӹ��� ���
	Vec2 m_vScale; // �浹ü�� ũ��

	UINT m_iID; // �浹ü�� ������ ID��

public:

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	UINT GetID() { return m_iID; }

public: 
	void finalupdate();
	void render(HDC _dc); // �浹ü�� ����� �ð������� ǥ��

public:
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���۽��� ȣ��
	void OnCollisionExit(CCollider* _pOther); // �浹�� ������

	CCollider& operator =(CCollider& _origin) = delete;// ���Կ����ڸ� �ǵ������� ����

public:

	CCollider();
	CCollider(const CCollider& _origin); // ������������ ������ ���� ��������� ����� 
	~CCollider();

	friend class CObject;

};
