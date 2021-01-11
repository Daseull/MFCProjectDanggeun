#pragma once


// CLoginDlg 대화 상자

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)
private:
	CBrush m_bk_brush;
public:
	CLoginDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLoginDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CRoundButtonStyle m_tMyButtonStyle;
//	CButton m_tMyButton1;
//	CRoundButton2 m_tMyButton1;


	CRoundButton2 m_tMyButton1;
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton2;
	afx_msg void OnBnClickedButtonJoin();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonLogin();

protected:
	afx_msg LRESULT OnUwmCustom2(WPARAM wParam, LPARAM lParam);


public:
	CString m_strID;
	CString m_strPW;
};
