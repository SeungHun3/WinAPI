#pragma once
#include "CObject.h"

// 플레이어 미사일, 몬스터 미사일 구분
class CMissile :
    public CObject
{
private:
    //float m_fTheta; // 각도

    Vec2 m_vDir; // 월드좌표가 아닌 원점을 중심으로 한 방향정보

public:
    //void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

    CMissile* Clone() { return new CMissile(*this); }

public:

    CMissile();
    ~CMissile();
};

