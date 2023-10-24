#pragma once
// \ 후 줄바꿈시에도 내용 이어진다는것을 명시
// 싱글톤 매크로
#define SINGLE(type)	static type* GetInst() \
						{\
							static type mgr;\
					 		return &mgr;\
						}