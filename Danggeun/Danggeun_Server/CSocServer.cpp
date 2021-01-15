#include "pch.h"
#include "CSocServer.h"

void CSocServer::Init(HWND hWnd) {		// 메인 핸들러 설정
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)	// 클라이언트의 접속 요청 받았을 때
{
	Accept(m_socCom);						// 통신용 소켓 받기
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);	// 접속 메시지 보내기
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom() {	// 통신용 소켓 반환
	return &m_socCom;
}