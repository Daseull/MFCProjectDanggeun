// LoginDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "JoinDlg.h"

// CLoginDlg 대화 상자

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strID(_T(""))
	, m_strPW(_T(""))
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));

	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CRoundButtonStyle m_tMyButtonStyle;

	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_tMyButton1);

	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
	DDX_Control(pDX, IDC_BUTTON_JOIN, m_tMyButton2);

}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CLoginDlg::OnBnClickedButtonJoin)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_MESSAGE(UWM_CUSTOM2, &CLoginDlg::OnUwmCustom2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기
JoinDlg dlg = new JoinDlg;

void CLoginDlg::OnBnClickedButtonJoin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	dlg.DoModal();


}


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStdioFile file;
	CString str;
	int chk = 0;
	UpdateData(TRUE);
	if (file.Open("UserTable.txt", CFile::modeRead)) {
		while (file.ReadString(str)) {
			if (!strcmp(str, m_strID)) {
				file.ReadString(str);
				if (!strcmp(str, m_strPW)) {
					MessageBox("Login Success !");
					chk = 2;
				}
				else {
					MessageBox("check your ID/PW");
					chk = 1;
				}
				break;
			}
		}

		if (!chk) MessageBox("check your ID/PW");
		if(chk == 2) ::SendMessage(((CLoginDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM1, 0, 0);
		file.Close();
	}
}



afx_msg LRESULT CLoginDlg::OnUwmCustom2(WPARAM wParam, LPARAM lParam)
{
	dlg.EndDialog(IDOK);
	return 0;
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	if (nCtlColor == CTLCOLOR_BTN) {
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(0, 200, 255));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
