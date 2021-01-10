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
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CRoundButtonStyle m_tMyButtonStyle;

	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_tMyButton1);
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);

	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CLoginDlg::OnBnClickedButtonJoin)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_MESSAGE(UWM_CUSTOM2, &CLoginDlg::OnUwmCustom2)
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
					MessageBox("로그인 성공 !");
					chk = 2;
				}
				else {
					MessageBox("ID/PW를 확인해주세요");
					chk = 1;
				}
				break;
			}
		}

		if (!chk) MessageBox("ID/PW를 확인해주세요");
		if(chk == 2) ::SendMessage(((CLoginDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM1, 0, 0);
		file.Close();
	}
}



afx_msg LRESULT CLoginDlg::OnUwmCustom2(WPARAM wParam, LPARAM lParam)
{
	dlg.EndDialog(IDOK);
	return 0;
}
