#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2 m_vForce; // 크기, 방향
	Vec2 m_vAccel; // 가속도
	Vec2 m_vAccelA; // 가속도 추가값
	float m_fMass; // 질량  ==> 힘 = 질량*가속도
	Vec2 m_vVelocity; // 속도 : 방향 + 속력

	// F = M * A
	// V += A * DT

	float m_fFricCoeff; // 마찰 계수
	Vec2 m_vMaxVelocity; // 최대속도 : 물체의 저항을 물리로 표현하기 어려워 속도제한을 걸어둠
		

public:
	void finalupdate();


public:
	void AddForce(Vec2 _vF)
	{
		m_vForce += _vF;
	}
	void SetMass(float _fMass)
	{
		m_fMass = _fMass;
	}
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	

	Vec2 GetVelocity() { return m_vVelocity; }
	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vec2 _vAccelA) { m_vAccelA = _vAccelA; }

private:
	void Move();


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

