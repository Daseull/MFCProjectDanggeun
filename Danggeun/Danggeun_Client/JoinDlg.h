#pragma once


// JoinDlg 대화 상자

class JoinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(JoinDlg)
private:
	CBrush m_bk_brush;

public:
	JoinDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~JoinDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_JOIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strID;
	CString m_strPHONE;
	CString m_strPW;
//	CComboBox m_Town;
	afx_msg void OnBnClickedButtonJoinOk();
//	virtual BOOL OnInitDialog();
	CRoundButton2 m_tMyButton1;
	CRoundButtonStyle m_tMyButtonStyle;
	afx_msg void OnEnChangeEditJoinPw();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_Town;
	virtual BOOL OnInitDialog();
};