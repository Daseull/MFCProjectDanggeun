#pragma once
#include <afxsock.h>
class CSocServer :
    public CSocket
{
public:
	HWND m_hWnd;		// 메인 윈도우 핸들
	CSocCom m_socCom;	// 통신용 소켓

	void Init(HWND m_hWnd);					// 메인 윈도우 초기화
	virtual void OnAccept(int nErrorCode);	// 클라이언트의 접속 요청 받았을 때
	CSocCom* GetAcceptSocCom();				// 통신용 소켓 받기

};

