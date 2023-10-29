#pragma once
// Ŭ���� ��ü�� �����Ϳ����� ���� �̱��� �������� ����

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd; // ���� �������ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC; // ���� �����쿡 Draw�� DC

	//��Ʈ��: �����쿡�� ��� �ȼ��� �����ϰ� �ִ� ������
	HBITMAP m_hBit; // �纻�� ��Ʈ��
	HDC m_memDC; // �纻�� DC

	// ���� ����ϴ� GDI Object Grapic Device Interface Object
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

