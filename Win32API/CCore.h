#pragma once
// 클래스 자체를 데이터영역에 보내 싱글톤 패턴으로 설계

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd; // 메인 윈도우핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC; // 메인 윈도우에 Draw할 DC

	//비트맵: 윈도우에서 모든 픽셀을 저장하고 있는 데이터
	HBITMAP m_hBit; // 사본용 비트맵
	HDC m_memDC; // 사본용 DC

	// 자주 사용하는 GDI Object Grapic Device Interface Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];


public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

