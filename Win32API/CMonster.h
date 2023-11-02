#pragma once
#include "CObject.h"


struct tMonInfo
{
    float m_iHP;
    float m_fSpeed;
    float m_fRecogRange; // ��������
    float m_fAttRange;   //���� ��Ÿ�
    float m_fAtt;        // ���ݷ�
};




class AI;

class CMonster :
    public CObject
{

private:
    tMonInfo m_tInfo;
    AI* m_pAI;


public:
    float GetSpeed() { return m_tInfo.m_fSpeed; }
    void SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }

    void SetAI(AI* _pAI);

private:

    void SetMonInfo(const tMonInfo& _info)
    {
        m_tInfo = _info;
    }


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

