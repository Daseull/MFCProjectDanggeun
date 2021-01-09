// LoginDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 대화 상자

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
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

}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoginDlg 메시지 처리기
