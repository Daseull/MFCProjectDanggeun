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
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기


void CLoginDlg::OnBnClickedButtonJoin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	JoinDlg dlg = new JoinDlg;
	dlg.DoModal();
}


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStdioFile file;
	CString display_str, str;
	int chk = 0;
	if (file.Open("UserTable.txt", CFile::modeRead | CFile::typeText)) {
		// 성공적으로 파일이 열렸으면 원하는 작업을 한다.
		while (file.ReadString(str)) {
			// 읽어들인 한줄의 텍스트를 display_str 변수에 추가한다.
			if (str.Find(m_strID)!=-1) {
				file.ReadString(str);
				if (str.Find(m_strID)!=-1) MessageBox("로그인 성공 !");
				else MessageBox("ID/PW를 확인해주세요.");
				chk = 1;
				break;
			}
		}
		if (!chk) MessageBox("ID/PW를 확인해주세요.");
		// 작업을 마친후에 파일을 닫는다.
		file.Close();
	}

}
