#pragma once
// \ 후 줄바꿈시에도 내용 이어진다는것을 명시
// 싱글톤 매크로
#define SINGLE(type)	public:\
						static type* GetInst() \
						{\
							static type mgr;\
					 		return &mgr;\
						}\
						private:\
							type();\
							~type();

#define fDT CTimeMgr::GetInst()->GetfDT();
#define DT CTimeMgr::GetInst()->GetDT();

#define CLONE(type) type* Clone() {return new type(*this);}


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state // true,false 반환
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()


#define PI 3.1415926535f

#define TILE_SIZE 32

enum class GROUP_TYPE
{
	//렌더링 순서
	DEFALUT, // 0
	TILE,
	GROUND,
	MONSTER,
	PLAYER,	 

	PROJ_PLAYER, // 플레이어 미사일
	PROJ_MONSTER, // 몬스터 미사일

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,

	END,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

	END,
};

#define PlayerAnimIdleLeft L"animation\\player_idle_left.anim"
#define PlayerAnimIdleRight L"animation\\player_idle_right.anim"

#define PlayerAnimWalkLeft L"animation\\player_walk_left.anim"
#define PlayerAnimWalkRight L"animation\\player_walk_right.anim"

#define PlayerAnimJumpLeft L"animation\\player_jump_left.anim"
#define PlayerAnimJumpRight L"animation\\player_jump_right.anim"