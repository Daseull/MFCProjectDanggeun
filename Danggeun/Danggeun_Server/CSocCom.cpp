#include "pch.h"
#include "CSocCom.h"

void CSocCom::Init(HWND hWnd) {		// 메인 핸들러 받아올 때 호출
	m_hWnd = hWnd;
}

void CSocCom::OnReceive(int nErrorCode)		// 서버에서 메시지 받을때 호출
{
	SendMessage(m_hWnd, UM_RECEIVE, 0, 0);	// 서버 다이얼로그에 메시지 전달
	CSocket::OnReceive(nErrorCode);
}