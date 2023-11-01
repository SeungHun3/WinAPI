#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2 m_vDragStart;

public:
    virtual void MouseOn(); //호버 중일때
    virtual void MouseLbtnDown(); // 눌렀을때
    virtual void MouseLbtnUp(); // 누르고 뗏을때

public:
    CPanelUI();
    ~CPanelUI();
};

