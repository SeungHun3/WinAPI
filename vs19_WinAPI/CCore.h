#pragma once

// Ŭ���� ��ü�� �����Ϳ����� ���� �̱��� �������� ����

class CCore
{
public:
	static CCore* GetInst()
	{
		static CCore core; // �ھ��� ��ü �ϳ��� �����Ϳ����� �������

		return &core; // �����Ϳ����� �ִ� �޸� �ּҰ� ��ȯ
	}


private:
	CCore();
	~CCore();

};

