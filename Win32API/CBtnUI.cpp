#include "CBtnUI.h"



CBtnUI::CBtnUI()
	:CUI(false)
{
}

CBtnUI::~CBtnUI()
{
}


void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (nullptr == m_pFunc) // 실행해야할 함수포인터가 nullptr이다
	{
		return;
	}
	m_pFunc(m_param1, m_param2);

}
