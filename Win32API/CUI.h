#pragma once
#include "CObject.h"

class CUI :
    public CObject
{
 
private:
    vector<CUI*> m_vecChildUI;
    CUI* m_pParentUI; // nullptr이라면 부모가 없는 최상위 부모클래스

    Vec2 m_vFinalPos;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);


private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    CLONE(CUI);

public:
    CUI();
    ~CUI();
};

