#pragma once
#include <afxsock.h>
class CSocServer :
    public CSocket
{
public:
	HWND m_hWnd; // 메인 윈도우 핸들
	CSocCom m_socCom;

	void Init(HWND m_hWnd);
	virtual void OnAccept(int nErrorCode);
	CSocCom* GetAcceptSocCom();

};

