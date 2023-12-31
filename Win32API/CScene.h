#pragma once
#include "CMonFactory.h"

class CObject; // 클래스 전방선언 = 전처리, 컴파일러, 어셈블러 통한 후 링커로 넘겨 매칭시킴, 클래스에 대한 구체적인 정보는 없는 상태 -> 포인터 타입으로 사용

class CScene
{
private:
	// vector에 포인터클래스를 담는 이유: 앞으로 파생될 부모클래스를 담아 범용성을 높이기 위한 용도
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 그룹개수만큼 선언
	wstring m_strName; // Scene 이름
	
	UINT m_iTileX; //타일 가로갯수
	UINT m_iTileY; //타일 세로갯수

	CObject* m_pPlayer; // 씬이 보유하고 있는 플레이어



public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	CObject* GetPlayer() { return m_pPlayer; }

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);


	// 순수 가상함수로 구현 = 클래스는 추상클래스로 변경 
	// => 추상클래스는  직접적으로 new 생성 불가, 자식클래스도 virtual로 함수를 오버라이드하지 않으면 추상클래스가 되어버림
	virtual void Enter() = 0; // 진입시 호출
	virtual void Exit() = 0;  // 탈출시 호출

public:

	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // 인라인 함수 작성시 다른곳에서 호출해도 해당 스택에서 호출되어 호출비용없음
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	void ResisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }


	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; } // 그룹 자체를 리턴
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _YCount);
	void LoadTile(const wstring& _strRelativePath);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

