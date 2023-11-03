#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2 m_vForce; // ũ��, ����
	Vec2 m_vAccel; // ���ӵ�
	float m_fMass; // ����  ==> �� = ����*���ӵ�
	Vec2 m_vVelocity; // �ӵ� : ���� + �ӷ�

	// F = M * A
	// V += A * DT

	float m_fFricCoeff; // ���� ���
	float m_fMaxSpeed; // �ִ�ӵ� : ��ü�� ������ ������ ǥ���ϱ� ����� �ӵ������� �ɾ��


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

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void SetMaxVelocity(float _fSpeed) { m_fMaxSpeed = _fSpeed; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }


private:
	void Move();


public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

