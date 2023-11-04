#pragma once
#include "global.h"
#include "CCamera.h"

//������Ʈ
class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{

private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity* m_pGravity;


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
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();

	virtual void OnCollision(CCollider* _pOther){}
	virtual void OnCollisionEnter(CCollider* _pOther){}
	virtual void OnCollisionExit(CCollider* _pOther){}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start(){}
	virtual void update() = 0; // �ڽ�Ŭ������ update�Լ� ������Ű��
	virtual void finalupdate(); // �ڽ� Ŭ�������� �������̵����� �ʰ� final����� �Լ��� �����ϰԲ�ó��
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;

};

