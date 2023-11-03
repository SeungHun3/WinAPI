#pragma once
#include "CObject.h"



enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    DEAD,

};


//enum class PLAYER_ATTACK_STATE
//{
//    NORMAL_ATT_1,
//    NORMAL_ATT_2,
//    NORMAL_ATT_3,
//    NORMAL_ATT_1,
//};



class CTexture;

class CPlayer :
    public CObject
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    PLAYER_STATE m_eCurState;
    PLAYER_STATE m_ePrevState;
    int m_iDir;

private:
    void CreateMissile();

    void update_state();
    void update_move();
    void update_animation();

    CLONE(CPlayer);

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //    , m_pTex(_origin.m_pTex)
    //{}

    ~CPlayer();
};

