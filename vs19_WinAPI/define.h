#pragma once
// \ �� �ٹٲ޽ÿ��� ���� �̾����ٴ°��� ���
// �̱��� ��ũ��
#define SINGLE(type)	public:\
						static type* GetInst() \
						{\
							static type mgr;\
					 		return &mgr;\
						}\
						private:\
							type();\
							~type();

#define fDT CTimemgr::GetInst()->GetfDT();
#define DT CTimemgr::GetInst()->GetDT();