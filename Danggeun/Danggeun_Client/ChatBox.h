#pragma once


// ChatBox 대화 상자

class ChatBox : public CDialogEx
{
	DECLARE_DYNAMIC(ChatBox)

public:
	ChatBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ChatBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSend;
	CListBox m_list;
	CSocCom m_socCom;
	virtual BOOL OnInitDialog();
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);
	afx_msg void OnBnClickedButtonSend();
};
