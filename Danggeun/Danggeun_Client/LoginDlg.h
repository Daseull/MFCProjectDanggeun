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
	CRoundButton2 m_tMyButton1;
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton2;
	CString m_strID;											// 로그인 창에 입력된 사용자 ID
	CString m_strPW;											// 로그인 창에 입력된 사용자 PW
	afx_msg void OnBnClickedButtonJoin();						// 회원 가입 버튼 클릭 시 호출
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonLogin();						// 로그인 버튼 클릭 시 호출
	afx_msg LRESULT OnUwmCustom2(WPARAM wParam, LPARAM lParam);	// 회원가입 성공시 메시지 받기
	void OnIdok();
};
