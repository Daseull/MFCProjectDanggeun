// Tab4.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab4.h"
#include "afxdialogex.h"


// CTab4 대화 상자

IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

CTab4::CTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab4, pParent)
{
	


	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PW2, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_tMyButton2);
}


BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab4::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab4::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_BUTTON_QUIT, &CTab4::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// CTab4 메시지 처리기


void CTab4::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTab4::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}




