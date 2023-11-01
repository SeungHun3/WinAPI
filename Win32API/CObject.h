#pragma once
#include "global.h"
#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{

private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	bool IsDead() { return !m_bAlive; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }


	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther){}
	virtual void OnCollisionEnter(CCollider* _pOther){}
	virtual void OnCollisionExit(CCollider* _pOther){}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update() = 0; // 자식클래스에 update함수 강제시키기
	virtual void finalupdate(); // 자식 클래스에서 오버라이딩하지 않고 final선언된 함수만 구동하게끔처리
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;

};

