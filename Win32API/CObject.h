#pragma once


class CCollider;

class CObject
{

private:
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }


	void CreateCollider();

public:
	virtual void update() = 0; // 자식클래스에 update함수 강제시키기
	virtual void finalupdate() final; // 자식 클래스에서 오버라이딩하지 않고 final선언된 함수만 구동하게끔처리
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();

};

