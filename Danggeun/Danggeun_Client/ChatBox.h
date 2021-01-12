#pragma once
#include "DetailPage.h"

// ChatBox 대화 상자

class ChatBox : public CDialogEx
{
	DECLARE_DYNAMIC(ChatBox)
private:
	CBrush m_bk_brush;
	CImage m_image;
	CRect m_rect;
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
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnIdok();
//	CStatic m_strTitle;
	CStatic m_picture;
//	CString m_strTitle;
	CStatic m_title;
	CStatic m_price;
};
