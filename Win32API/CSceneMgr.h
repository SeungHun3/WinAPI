#pragma once
class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END]; // 모든 씬목록
	CScene* m_pCurScene; // 현재씬



public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext); // 즉시 바꾸게되면 참조문제 발생할 수 있어 이벤트 처리를 통한 호출로 구현함
	friend class CEventMgr;
};

