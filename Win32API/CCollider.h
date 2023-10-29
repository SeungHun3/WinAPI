#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // collider�� �����ϰ� �ִ� ������Ʈ	
	Vec2 m_vOffsetPos; // �� �������� �������� ���Ǵ� ������
	Vec2 m_vFinalPos; // finalupdate���� �������Ӹ��� ���
	Vec2 m_vScale; // �浹ü�� ũ��


public:

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public: 
	void finalupdate();
	void render(HDC _dc); // �浹ü�� ����� �ð������� ǥ��


public:

	CCollider();
	~CCollider();

	friend class CObject;

};

