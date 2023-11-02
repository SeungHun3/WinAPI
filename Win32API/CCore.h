#pragma once
// Ŭ���� ��ü�� �����Ϳ����� ���� �̱��� �������� ����

class CTexture;

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hwnd; // ���� �������ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC; // ���� �����쿡 Draw�� DC

	CTexture* m_pMemTex; // ����� �ؽ���

	// ���� ����ϴ� GDI Object Grapic Device Interface Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];


	//�޴�
	HMENU m_hMenu; // Tool Scene������ ���

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

