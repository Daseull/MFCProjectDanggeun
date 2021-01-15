#include "pch.h"
#include "CSocServer.h"

void CSocServer::Init(HWND hWnd) {		// ���� �ڵ鷯 ����
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)	// Ŭ���̾�Ʈ�� ���� ��û �޾��� ��
{
	Accept(m_socCom);						// ��ſ� ���� �ޱ�
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);	// ���� �޽��� ������
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom() {	// ��ſ� ���� ��ȯ
	return &m_socCom;
}