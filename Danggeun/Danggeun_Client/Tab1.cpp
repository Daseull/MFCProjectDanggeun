// Tab1.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab1.h"
#include "afxdialogex.h"


// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab1, pParent)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab1::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTab1 메시지 처리기


void CTab1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
}


void CTab1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnCancel();
}
