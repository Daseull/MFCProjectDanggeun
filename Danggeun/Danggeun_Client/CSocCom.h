#pragma once
#include <afxsock.h>
class CSocCom :
    public CSocket
{

public: 
    HWND m_hWnd;            // 메인 핸들러
    void Init(HWND m_hWnd); // 메인 핸들러 설정
    virtual void OnReceive(int nErrorCode); // 서버에서 온 메시지 받기
};

