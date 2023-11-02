#pragma once
// 클래스 자체를 데이터영역에 보내 싱글톤 패턴으로 설계

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd; // 메인 윈도우핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC; // 메인 윈도우에 Draw할 DC

	CTexture* m_pMemTex; // 백버퍼 텍스쳐

	// 자주 사용하는 GDI Object Grapic Device Interface Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];


	//메뉴
	HMENU m_hMenu; // Tool Scene에서만 사용

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }
	HMENU GetMenu() { return m_hMenu; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

