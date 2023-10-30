#pragma once

struct tEvent
{
	EVENT_TYPE eEvent;
	DWORD_PTR lParam; // DWORD_PTR = �÷����� ���� ũ�⸦ 4����Ʈ, 8����Ʈ�� �ٲ��ִ� �ڷ��� 
	DWORD_PTR wParam;
};


class CEventMgr
{

	SINGLE(CEventMgr)


private:
	vector<tEvent> m_vecEvent;

	vector<CObject*> m_vecDead; // �������� ������Ʈ ������ => ���������ӿ� �����ϰ� ����(�ٷ� ������ �����ϰ� �ִ� Ŭ�������� �����ɼ� ����)

public:

	void update();


private:
	void Excute(const tEvent& _eve);


public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); }

};

