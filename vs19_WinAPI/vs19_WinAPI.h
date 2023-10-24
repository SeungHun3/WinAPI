#pragma once

#include "resource.h"

// class CCore;
// extern CCore core; // 이럴 경우 객체생성 방지가 되지 않는다

/*
class CCore
{

	// 스스로를 만들어 주는 함수를 제공 // 객체없이 함수만들기 -> 정적멤버함수 static 호출 // CCore::GetInstance();
	// static 멤버 함수 = > 멤버에 접근이 불가함 (this가 없음), 호출한 객체가 없다 
	// 객체를 만들어서 호출해도 this가 없다 애초에 그렇게 만들어졌다

	// => 유일하게 접근이 가능한 멤버존재 == 정적 멤버는 접근이 가능 ex class myCore { public : static int a;}; 
	// 정적변수(static), 전역변수(extern) : Data 영역의 메모리 사용
	// 정적변수 : 함수안에서만 접근이 가능 VS 전역변수 : 어디서든 접근이 가능
	
	// 정적변수
	//  1. 함수안에서 선언 2. 파일안에서 선언 
	//  3. 클래스 내부에 선언( 100개의 같은 클래스에서 heap, stack 어디서 생성되었든 전부 접근가능(this 없이 하나의 메모리만 반환))
public:
	static int m_istatic;


private:
	// 정적 변수로 만들어 놓기 : 주소를 가지고 있으면서 반환처리도 할 수 있게
	static CCore* g_pInst;

public:
	// 정적멤버함수
	static CCore* GetInstance()
	{
		// 최초 호출됬을경우 
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}
		return g_pInst;
	}

	static void Release() // 메모리 생성했으니 해제하기
	{
		CCore* p = GetInstance();
		delete p;
		g_pInst = nullptr;
	}

	

private:
	CCore(); // 생성자와 소멸자를 숨긴다
	
};


int CCore::m_istatic = 1; // 클래스의 정적멤버 직접 변경 // 정적 멤버는 반드시 자료형 넣고 직접 초기화를 해줘야함(기본 문법)

CCore* CCore::g_pInst = nullptr; // static 초기화

*/