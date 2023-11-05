#pragma once


class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT; // 좌상단 좌표
	Vec2 vSlice; // 크기
	Vec2 vOffset;
	float fDuration; // 시간,속도
};

class CAnimation
{

private:
	wstring m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;			//애니매이션이 사용하고 있는 텍스쳐
	vector<tAnimFrm> m_vecFrm;  // 모든 애니매이션 프레임정보
	int m_iCurFrm;				// 현재 애니매이션 프레임정보
	float m_fAccTime;			// 시간누적

	bool m_bFinish;				// 재생 끝에 도달여부

public:

	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) // 수정가능하게 레퍼런스로
	{
		return m_vecFrm[_iIdx];
	}
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }


private:

	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}


public:

	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:

	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

