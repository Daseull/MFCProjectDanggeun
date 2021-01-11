#include "pch.h"
#include "CSocServer.h"

void CSocServer::Init(HWND hWnd) {
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	//AfxMessageBox(_T("Accept!"));
	Accept(m_socCom);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom() {
	return &m_socCom;
}