
// Danggeun_ServerDlg.h : header file
//

#pragma once


// CDanggeunServerDlg dialog
class CDanggeunServerDlg : public CDialogEx
{
// Construction
public:
	CDanggeunServerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DANGGEUN_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM IParam);			// 클라이언트 접속 대기
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);			// 클라이언트에서 메시지 받았을 때
	DECLARE_MESSAGE_MAP()
public:
	CSocServer m_socServer;	// 서버용 소켓
	CSocCom* m_socCom;		// 통신용 소켓
	CListBox m_list;		// 채팅 리스트
	CString m_strStatus;	// 접속 상태
	CString m_strSend;		// 입력한 문자열
	afx_msg void OnBnClickedButtonSend();
};
