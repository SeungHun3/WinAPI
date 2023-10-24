#pragma once
// 클래스 자체를 데이터영역에 보내 싱글톤 패턴으로 설계

class CCore
{
public:
	
	SINGLE(CCore);

public:
	int init();

private:
	CCore();
	~CCore();

};

