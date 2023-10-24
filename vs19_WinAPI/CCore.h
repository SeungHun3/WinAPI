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

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void Update();
	void Render();

public:
	HWND GetMainHwnd() {	return m_hwnd;	}


};

