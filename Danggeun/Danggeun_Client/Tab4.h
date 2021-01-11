#pragma once


// CTab4 대화 상자

class CTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab4)
private:
	CBrush m_bk_brush;

public:
	CTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton1;
	afx_msg void OnBnClickedButtonQuit();
	CRoundButton2 m_tMyButton2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	CString m_userId;
	CStatic m_userid;
};
