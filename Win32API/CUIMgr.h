#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);


private:


public:
	void update();

private:
	// �θ� UI������ ������ Ÿ���õ� UI�� ã�Ƽ� ��ȯó��
	CUI* GetTargetedUI(CUI* _pParentUI); 


};

