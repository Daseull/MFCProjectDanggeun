// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab3.h"
#include "afxdialogex.h"
#include "RoundButton2.h"
#include "RoundButtonStyle.h"

// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab3, pParent)
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);


}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
	DDX_Text(pDX, IDC_STATIC_TOWN, m_strTown);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_tMyButton2);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab3::OnBnClickedCancel)
//	ON_LBN_SELCHANGE(IDC_LIST_HEART, &CTab3::OnLbnSelchangeListHeart)
ON_WM_CTLCOLOR()
ON_STN_CLICKED(IDCANCEL, &CTab3::OnStnClickedCancel)
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




HBRUSH CTab3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CTab3::OnStnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
