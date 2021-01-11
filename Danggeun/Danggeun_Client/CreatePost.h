#pragma once


// CCreatePost 대화 상자

class CCreatePost : public CDialogEx
{
	DECLARE_DYNAMIC(CCreatePost)
private:
	CBrush m_bk_brush;
public:
	CCreatePost(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCreatePost();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_POST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CRoundButton2 m_tMyButton1;
	CRoundButtonStyle m_tMyButtonStyle;
	CString m_strTitle;
	CString m_strPrice;
	CString m_strText;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_state;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPost();
	afx_msg void OnStnClickedStaticAddpic();
	CStatic m_img;
};
