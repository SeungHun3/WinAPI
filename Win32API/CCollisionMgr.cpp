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
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // 둘 중 작은값을 row로
			}
		}
	}


}


void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft); // 반환된 rvalue가 원본으로 lValue도 복사된 지역변수가 아닌 원본으로 받는다
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		//충돌체를 보유하지 않는경우
		if (nullptr == vecLeft[i]->GetCollider()) 
		{
			continue;
		}


		// 충돌체가 없거나 자기자신과의 충돌일 경우
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j]) 
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();
			
			COLLIDR_ID ID;
			ID.iLeft_id = pLeftCol->GetID(); // 두 충돌체의 아이디를 조합해
			ID.iRight_id = pRightCol->GetID();
			//ID.iD; // 맵으로 사용
			iter = m_mapColInfo.find(ID.iD);

			// 충돌정보가 미등록상태인경우 (최초 검사)
			if (m_mapColInfo.end() == iter) // id를 찾지 못했다면
			{
				m_mapColInfo.insert(make_pair(ID.iD, false)); // 값 넣어준다
				iter = m_mapColInfo.find(ID.iD);
			}

			if (IsCollision(pLeftCol, pRightCol)) // 충돌하고 있는경우
			{
				if (iter->second) // 이전에도 충돌하고 있는 경우 = 오버랩
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) // 삭제예정인 오브젝트의 경우 이후 update함수 도달하지 않음 => 직접 충돌해제 이벤트 발생시킨다
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
				else // 이전에는 충돌하지 않는 경우 = begin 오버랩 or hit
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead()) // 삭제예정인 오브젝트는 충돌하지 않은 것으로 취급
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}

					
				}
			}


			else // 충돌하지 않는경우
			{
				if (iter->second) // 이전에는 충돌했었다
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
	//중복되는 검사없이 비트연산
	//더 작은 값의 그룹타입을 행으로
	//큰 값을 열(비트)로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;


	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) //iCol 번째 비트가 설정되어 있는지 여부를 확인
	{
		m_arrCheck[iRow] &= ~(1 << iCol); //iCol 번째 비트는 0으로 설정되고, 나머지 비트는 그대로 유지
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); //iCol 번째 비트가 1로 설정되고, 나머지 비트는 그대로 유지
	}
}
