#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // collider를 소유하고 있는 오프젝트	
	Vec2 m_vOffsetPos; // 한 기준점을 기점으로 계산되는 포지션
	Vec2 m_vFinalPos; // finalupdate에서 매프레임마다 계산
	Vec2 m_vScale; // 충돌체의 크기


public:

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public: 
	void finalupdate();
	void render(HDC _dc); // 충돌체의 모습을 시각적으로 표현


public:

	CCollider();
	~CCollider();

	friend class CObject;

};

