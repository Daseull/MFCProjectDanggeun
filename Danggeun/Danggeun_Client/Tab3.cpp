// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab3.h"
#include "afxdialogex.h"


// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab3, pParent)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab3::OnBnClickedCancel)
//	ON_LBN_SELCHANGE(IDC_LIST_HEART, &CTab3::OnLbnSelchangeListHeart)
END_MESSAGE_MAP()


// CTab3 메시지 처리기


void CTab3::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTab3::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


