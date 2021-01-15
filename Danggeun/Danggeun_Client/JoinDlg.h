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
	CString m_strID;						// 사용자 ID
	CString m_strPHONE;						// 전화번호
	CString m_strPW;						// 사용자 PW
	CComboBox m_Town;						// 동네
	CRoundButton2 m_tMyButton1;
	CRoundButtonStyle m_tMyButtonStyle;
	afx_msg void OnBnClickedButtonJoinOk();	// 회원가입 완료 버튼 클릭시 호출
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();			// 다이얼로그 초기화
};