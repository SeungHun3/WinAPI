#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{

private:
    float m_fSpeed;
    Vec2 m_vCenterPos;
    float m_fMaxdistance;
    int m_iDir; // 진행방향 1 or -1
public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxdistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();

public:
    CMonster();
    ~CMonster();
};

