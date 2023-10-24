#pragma once

// 클래스 자체를 데이터영역에 보내 싱글톤 패턴으로 설계

class CCore
{
public:
	static CCore* GetInst()
	{
		static CCore core; // 코어의 객체 하나를 데이터영역에 만들었음

		return &core; // 데이터영역에 있는 메모리 주소값 반환
	}


private:
	CCore();
	~CCore();

};

