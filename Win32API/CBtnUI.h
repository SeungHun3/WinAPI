#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
public:
    virtual void MouseOn(); //ȣ�� ���϶�
    virtual void MouseLbtnDown(); // ��������
    virtual void MouseLbtnUp(); // ������ ������

    CLONE(CBtnUI)


public:
    CBtnUI();
    ~CBtnUI();
};

