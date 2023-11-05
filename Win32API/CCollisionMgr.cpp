#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}
CCollisionMgr::~CCollisionMgr()
{

}


void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol<(UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // �� �� �������� row��
			}
		}
	}


}


void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft); // ��ȯ�� rvalue�� �������� lValue�� ����� ���������� �ƴ� �������� �޴´�
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		//�浹ü�� �������� �ʴ°��
		if (nullptr == vecLeft[i]->GetCollider()) 
		{
			continue;
		}


		// �浹ü�� ���ų� �ڱ��ڽŰ��� �浹�� ���
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j]) 
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			
			COLLIDR_ID ID;
			ID.iLeft_id = pLeftCol->GetID(); // �� �浹ü�� ���̵� ������
			ID.iRight_id = pRightCol->GetID();
			//ID.iD; // ������ ���
			iter = m_mapColInfo.find(ID.iD);

			// �浹������ �̵�ϻ����ΰ�� (���� �˻�)
			if (m_mapColInfo.end() == iter) // id�� ã�� ���ߴٸ�
			{
				m_mapColInfo.insert(make_pair(ID.iD, false)); // �� �־��ش�
				iter = m_mapColInfo.find(ID.iD);
			}

			if (IsCollision(pLeftCol, pRightCol)) // �浹�ϰ� �ִ°��
			{
				if (iter->second) // �������� �浹�ϰ� �ִ� ��� = ������
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) // ���������� ������Ʈ�� ��� ���� update�Լ� �������� ���� => ���� �浹���� �̺�Ʈ �߻���Ų��
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else // �������� �浹���� �ʴ� ��� = begin ������ or hit
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()) // ���������� ������Ʈ�� �浹���� ���� ������ ���
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}

					
				}
			}


			else // �浹���� �ʴ°��
			{
				if (iter->second) // �������� �浹�߾���
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				
			}

		}
		
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//�ߺ��Ǵ� �˻���� ��Ʈ����
	//�� ���� ���� �׷�Ÿ���� ������
	//ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;


	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) //iCol ��° ��Ʈ�� �����Ǿ� �ִ��� ���θ� Ȯ��
	{
		m_arrCheck[iRow] &= ~(1 << iCol); //iCol ��° ��Ʈ�� 0���� �����ǰ�, ������ ��Ʈ�� �״�� ����
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); //iCol ��° ��Ʈ�� 1�� �����ǰ�, ������ ��Ʈ�� �״�� ����
	}
}
