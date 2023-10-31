#pragma once
// Ű�� ������ ����ȭ: ���� ������ ������ ���� Ű�� ���� ������ �̺�Ʈ�� ��������
// Ű�Է� �̺�Ʈ ó�� : tap, hold, away...


enum class KEY_STATE
{
	NONE,// �������� �ʾҰ�, �������� �������� ���� ����
	TAP, // �� ���� ����
	HOLD,// ������ �ִ�
	AWAY,// �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F,
	Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};
struct tKeyInfo
{
	KEY_STATE eState; // Ű�� ���°�
	bool bPrevPush; // ���������ӿ� Ű�� ���ȴ��� ����
};

class CKeyMgr
{
	SINGLE(CKeyMgr) // cpp���Ͽ� �̸� �����ϵ� ����� ���� ���� �Ŀ� ����� �о� ������Ͽ��� ��ũ�� ����� �����ϴ�

private:
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;


public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

	Vec2 GetMousePos() { return m_vCurMousePos; }
};

