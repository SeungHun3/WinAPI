#pragma once
// \ �� �ٹٲ޽ÿ��� ���� �̾����ٴ°��� ���
// �̱��� ��ũ��
#define SINGLE(type)	static type* GetInst() \
						{\
							static type mgr;\
					 		return &mgr;\
						}