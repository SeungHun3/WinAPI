#pragma once
#include "CObject.h"

// 플레이어 미사일, 몬스터 미사일 구분
class CMissile :
    public CObject
{
private:
    float m_fTheta; // 각도

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }


public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    CMissile();
    ~CMissile();
};

