#pragma once
#include <afxsock.h>
class CSocCom :
    public CSocket
{

public: 
    HWND m_hWnd;            // ���� �ڵ鷯
    void Init(HWND m_hWnd); // ���� �ڵ鷯 ����
    virtual void OnReceive(int nErrorCode); // �������� �� �޽��� �ޱ�
};

