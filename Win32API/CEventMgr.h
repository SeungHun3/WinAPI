#pragma once

struct tEvent
{
	EVENT_TYPE eEvent;
	DWORD_PTR lParam; // DWORD_PTR = 플랫폼에 따라 크기를 4바이트, 8바이트로 바꿔주는 자료형 
	DWORD_PTR wParam;
};


class CEventMgr
{

	SINGLE(CEventMgr)


private:
	vector<tEvent> m_vecEvent;

	vector<CObject*> m_vecDead; // 삭제예정 오브젝트 모으기 => 다음프레임에 안전하게 삭제(바로 삭제시 참조하고 있는 클래스에서 문제될수 있음)

public:

	void update();


private:
	void Excute(const tEvent& _eve);


public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

