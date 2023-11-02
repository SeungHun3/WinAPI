#pragma once
#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

//void (CScene_Tool::* pMemFunc)(void);// CScene_Tool class�� ����Լ��� ������ ����
typedef void(CScene::* SCENE_MEMFUNC)(void);
typedef void(CObject::* Object_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    // �Լ������ͻ��
    BTN_FUNC m_pFunc; // �����Լ� ������
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

    SCENE_MEMFUNC m_pSceneFunc; //Ŭ���� �Լ� ������
    CScene* m_pSceneInst; // Ŭ�����Լ� ȣ���ϴ� ��ü

public:
    virtual void MouseOn(); //ȣ�� ���϶�
    virtual void MouseLbtnDown(); // ��������
    virtual void MouseLbtnUp(); // ������ ������
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2);
    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI)


public:
    CBtnUI();
    ~CBtnUI();
};

