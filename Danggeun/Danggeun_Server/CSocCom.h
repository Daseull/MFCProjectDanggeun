#pragma once
#include <afxsock.h>
class CSocCom :
    public CSocket
{
public:
    HWND m_hWnd;

    void Init(HWND m_hWnd);
    virtual void OnReceive(int nErrorCode);

};

