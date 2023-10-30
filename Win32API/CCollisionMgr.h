#pragma once
class CCollider;

//유니온 = 자료형 중 큰 자료형의 사이즈만 가지고 내부의 값을 비트해석함 
// ex) id로 봤을때 LONGLONG 8바이트로 // struct로 봤을때 내부 iLeft_id 4바이트 + iRight_id 4바이트
union COLLIDR_ID
{
	struct {
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG iD;
};


class CCollisionMgr
{

	SINGLE(CCollisionMgr);

private:
	// 충돌체 간의 이전 프레임 충돌정보
	map<ULONGLONG, bool> m_mapColInfo; // 탐색을 위해 map사용
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 32비트의 정수를 그룹개수만큼 보유하고 있어야한다.

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);// memset == 지정한 주소를 지정한 값으로 바이트값으로 세팅 
		//=>m_arrCheck을 sizeof(UINT) * (UINT)GROUP_TYPE::END 만큼의 사이즈를 0값으로 
	}

private:

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 그룹간 충돌갱신
	bool IsCollision(CCollider* _eLeftCol, CCollider* _RightCol);

};

