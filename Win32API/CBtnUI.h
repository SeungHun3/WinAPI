#pragma once
#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

//void (CScene_Tool::* pMemFunc)(void);// CScene_Tool class의 멤버함수의 포인터 변수
typedef void(CScene::* SCENE_MEMFUNC)(void);
typedef void(CObject::* Object_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    // 함수포인터사용
    BTN_FUNC m_pFunc; // 전역함수 포인터
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

    SCENE_MEMFUNC m_pSceneFunc; //클래스 함수 포인터
    CScene* m_pSceneInst; // 클래스함수 호출하는 객체

public:
    virtual void MouseOn(); //호버 중일때
    virtual void MouseLbtnDown(); // 눌렀을때
    virtual void MouseLbtnUp(); // 누르고 뗏을때
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2);
    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI)


public:
    CBtnUI();
    ~CBtnUI();
};

