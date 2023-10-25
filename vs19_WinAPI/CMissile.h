#pragma once
#include "CObject.h"

// 플레이어 미사일, 몬스터 미사일 구분
class CMissile :
    public CObject
{
private:
    float m_fDir; // 위 아래 방향

public:
    void SetDir(bool _Up)
    {
        if (_Up)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }


public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    CMissile();
    ~CMissile();
};

