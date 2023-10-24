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



enum class GROUP_TYPE
{
	DEFALUT,
	PLAYER,
	MISSILE,
	MONSTER,

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