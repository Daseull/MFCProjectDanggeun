#pragma once
#include <afxsock.h>
class CSocServer :
    public CSocket
{
public:
	HWND m_hWnd;		// ���� ������ �ڵ�
	CSocCom m_socCom;	// ��ſ� ����

	void Init(HWND m_hWnd);					// ���� ������ �ʱ�ȭ
	virtual void OnAccept(int nErrorCode);	// Ŭ���̾�Ʈ�� ���� ��û �޾��� ��
	CSocCom* GetAcceptSocCom();				// ��ſ� ���� �ޱ�

};

