#pragma once

class CObject;

class CCamera
{

	SINGLE(CCamera)

private:
	Vec2 m_vLookAt; // 카메라가 보고 있는 위치
	Vec2 m_vCurLookAt; // 이전위치와 현재위치 보정위치
	Vec2 m_vPevLookAt; // 이전 프레임에 봤던 위치
	CObject* m_pTargetObj; // 카메라 타겟 오브젝트

	Vec2 m_vDiff; // 해상도 중심위치와 카메라 LookAt차이값

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	Vec2 GetLookAt() { return m_vCurLookAt; }

	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
public:
	void update();

private:
	void CalDiff();

};

