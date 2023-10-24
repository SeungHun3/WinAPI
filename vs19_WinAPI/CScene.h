#pragma once

class CObject; // 클래스 전방선언 = 전처리, 컴파일러, 어셈블러 통한 후 링커로 넘겨 매칭시킴, 클래스에 대한 구체적인 정보는 없는 상태 -> 포인터 타입으로 사용

class CScene
{
private:
	// vector에 포인터클래스를 담는 이유: 앞으로 파생될 부모클래스를 담아 범용성을 높이기 위한 용도
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 그룹개수만큼 선언
	wstring m_strName; // Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


public:
	CScene();
	virtual ~CScene();
};

