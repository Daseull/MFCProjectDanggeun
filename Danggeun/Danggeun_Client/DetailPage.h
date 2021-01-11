#pragma once


// CDetailPage 대화 상자

class CDetailPage : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailPage)
private:
	CBrush m_bk_brush;
public:
	CDetailPage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDetailPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChat();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton1;
	CStatic m_userid;
	CStatic m_usertown;
	CStatic m_state;
	virtual BOOL OnInitDialog();
	CStatic m_price;
	CBitmap m_bitmap;

//	CBitmapButton m_heart;
//	CButton m_heart;
//	CBitmapButton m_heart;
	CRoundButton2 m_tMyButton2;
};
