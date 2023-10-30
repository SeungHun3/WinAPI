#pragma once
class CCollider;

//���Ͽ� = �ڷ��� �� ū �ڷ����� ����� ������ ������ ���� ��Ʈ�ؼ��� 
// ex) id�� ������ LONGLONG 8����Ʈ�� // struct�� ������ ���� iLeft_id 4����Ʈ + iRight_id 4����Ʈ
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
	// �浹ü ���� ���� ������ �浹����
	map<ULONGLONG, bool> m_mapColInfo; // Ž���� ���� map���
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 32��Ʈ�� ������ �׷찳����ŭ �����ϰ� �־���Ѵ�.

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);// memset == ������ �ּҸ� ������ ������ ����Ʈ������ ���� 
		//=>m_arrCheck�� sizeof(UINT) * (UINT)GROUP_TYPE::END ��ŭ�� ����� 0������ 
	}

private:

	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // �׷찣 �浹����
	bool IsCollision(CCollider* _eLeftCol, CCollider* _RightCol);

};

