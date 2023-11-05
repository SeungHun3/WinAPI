#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::CREATE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;
	even.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(even);
}

void DeleteObject(CObject* _pObj)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::DELETE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(even);

}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::SCENE_CHANGE;
	even.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(even);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent even = {};

	even.eEvent = EVENT_TYPE::CHANGE_AI_STATE;
	even.lParam = (DWORD_PTR)_pAI;
	even.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(even);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	//������ ����ȭ
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);
	
	_str = szBuff;
}

void FScanf(char* _outBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_outBuff[i++] = '\0';
			break;
		}
		_outBuff[i++] = c;
	}
}
