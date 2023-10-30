#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; // collider를 소유하고 있는 오프젝트	
	Vec2 m_vOffsetPos; // 한 기준점을 기점으로 계산되는 포지션
	Vec2 m_vFinalPos; // finalupdate에서 매프레임마다 계산
	Vec2 m_vScale; // 충돌체의 크기

	UINT m_iID; // 충돌체의 고유한 ID값
	UINT m_iCol;




public:

	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public: 
	void finalupdate();
	void render(HDC _dc); // 충돌체의 모습을 시각적으로 표현

public:
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출
	void OnCollisionEnter(CCollider* _pOther); // 충돌 시작시점 호출
	void OnCollisionExit(CCollider* _pOther); // 충돌을 벗어난경우

	CCollider& operator =(CCollider& _origin) = delete;// 대입연산자를 의도적으로 삭제

public:

	CCollider();
	CCollider(const CCollider& _origin); // 이전프레임의 정보를 위해 복사생성자 만들기 
	~CCollider();

	friend class CObject;

};

