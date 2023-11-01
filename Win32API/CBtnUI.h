#pragma once
#include "CUI.h"

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    // 함수포인터사용
    BTN_FUNC m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;
public:
    virtual void MouseOn(); //호버 중일때
    virtual void MouseLbtnDown(); // 눌렀을때
    virtual void MouseLbtnUp(); // 누르고 뗏을때
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    CLONE(CBtnUI)


public:
    CBtnUI();
    ~CBtnUI();
};

