#include "pch.h"
#include "CSocCom.h"

void CSocCom::Init(HWND hWnd) {		// ���� �ڵ鷯 �޾ƿ� �� ȣ��
	m_hWnd = hWnd;
}

void CSocCom::OnReceive(int nErrorCode)		// �������� �޽��� ������ ȣ��
{
	SendMessage(m_hWnd, UM_RECEIVE, 0, 0);	// ���� ���̾�α׿� �޽��� ����
	CSocket::OnReceive(nErrorCode);
}