#pragma once
// 키와 프레임 동기화: 동일 프레임 내에서 같은 키에 대해 동일한 이벤트를 가져간다
// 키입력 이벤트 처리 : tap, hold, away...


enum class KEY_STATE
{
	NONE,// 눌려있지 않았고, 이전에도 눌려있지 않은 상태
	TAP, // 막 누른 시점
	HOLD,// 누르고 있는
	AWAY,// 막 뗀 시점
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
	KEY_STATE eState; // 키의 상태값
	bool bPrevPush; // 이전프레임에 키가 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr) // cpp파일에 미리 컴파일된 헤더를 먼저 참조 후에 헤더를 읽어 헤더파일에서 매크로 사용이 가능하다

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

