// JoinDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "JoinDlg.h"
#include "afxdialogex.h"


// JoinDlg 대화 상자

IMPLEMENT_DYNAMIC(JoinDlg, CDialogEx)

JoinDlg::JoinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_JOIN, pParent)
	, m_strID(_T(""))
	, m_strPHONE(_T(""))
	, m_strPW(_T(""))
{

}

JoinDlg::~JoinDlg()
{
}

void JoinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JOIN_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_JOIN_PHONE, m_strPHONE);
	DDX_Text(pDX, IDC_EDIT_JOIN_PW, m_strPW);
	DDX_Control(pDX, IDC_COMBO1, m_Town);
}


BEGIN_MESSAGE_MAP(JoinDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_JOIN_OK, &JoinDlg::OnBnClickedButtonJoinOk)
END_MESSAGE_MAP()


// JoinDlg 메시지 처리기


void JoinDlg::OnBnClickedButtonJoinOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	CStdioFile file;
	CFileException ex;
	if (file.Open("UserTable.txt", CFile::modeWrite, &ex)) {
		UpdateData(TRUE);
		file.SeekToEnd();
		m_strID += "\n";
		m_strPW += "\n";
		m_strPHONE += "\n";
		file.WriteString(m_strID);
		file.WriteString(m_strPW);
		file.WriteString(m_strPHONE);

		// 종료한다. 
		file.Close();
		MessageBox("회원가입 성공 !");
		::SendMessage(((JoinDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM1, 0, 0);
	}
}
