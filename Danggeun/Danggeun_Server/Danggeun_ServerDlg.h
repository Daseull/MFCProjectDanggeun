
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
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM IParam);
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);
	DECLARE_MESSAGE_MAP()
public:
	CSocServer m_socServer;
	CSocCom* m_socCom;
	CListBox m_list;
	CString m_strStatus;
	CString m_strSend;
	afx_msg void OnBnClickedButtonSend();
};
