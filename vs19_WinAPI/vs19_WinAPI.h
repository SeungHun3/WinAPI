#pragma once

#include "resource.h"

// class CCore;
// extern CCore core; // �̷� ��� ��ü���� ������ ���� �ʴ´�

/*
class CCore
{

	// �����θ� ����� �ִ� �Լ��� ���� // ��ü���� �Լ������ -> ��������Լ� static ȣ�� // CCore::GetInstance();
	// static ��� �Լ� = > ����� ������ �Ұ��� (this�� ����), ȣ���� ��ü�� ���� 
	// ��ü�� ���� ȣ���ص� this�� ���� ���ʿ� �׷��� ���������

	// => �����ϰ� ������ ������ ������� == ���� ����� ������ ���� ex class myCore { public : static int a;}; 
	// ��������(static), ��������(extern) : Data ������ �޸� ���
	// �������� : �Լ��ȿ����� ������ ���� VS �������� : ��𼭵� ������ ����
	
	// ��������
	//  1. �Լ��ȿ��� ���� 2. ���Ͼȿ��� ���� 
	//  3. Ŭ���� ���ο� ����( 100���� ���� Ŭ�������� heap, stack ��� �����Ǿ��� ���� ���ٰ���(this ���� �ϳ��� �޸𸮸� ��ȯ))
public:
	static int m_istatic;


private:
	// ���� ������ ����� ���� : �ּҸ� ������ �����鼭 ��ȯó���� �� �� �ְ�
	static CCore* g_pInst;

public:
	// ��������Լ�
	static CCore* GetInstance()
	{
		// ���� ȣ�������� 
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}
		return g_pInst;
	}

	static void Release() // �޸� ���������� �����ϱ�
	{
		CCore* p = GetInstance();
		delete p;
		g_pInst = nullptr;
	}

	

private:
	CCore(); // �����ڿ� �Ҹ��ڸ� �����
	
};


int CCore::m_istatic = 1; // Ŭ������ ������� ���� ���� // ���� ����� �ݵ�� �ڷ��� �ְ� ���� �ʱ�ȭ�� �������(�⺻ ����)

CCore* CCore::g_pInst = nullptr; // static �ʱ�ȭ

*/