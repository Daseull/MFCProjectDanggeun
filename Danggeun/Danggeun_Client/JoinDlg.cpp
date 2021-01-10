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
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));

	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
}

JoinDlg::~JoinDlg()
{
}

void JoinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_JOIN_OK, m_tMyButton1);
}


BEGIN_MESSAGE_MAP(JoinDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// JoinDlg 메시지 처리기


void JoinDlg::OnEnChangeEditJoinPw()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


HBRUSH JoinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
