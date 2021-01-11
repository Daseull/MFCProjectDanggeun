﻿// Tab4.cpp: 구현 파일
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
	
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
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
	//  DDX_Text(pDX, IDC_STATIC_ID, m_userId);
	DDX_Control(pDX, IDC_STATIC_ID, m_userid);
}


BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab4::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab4::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_BUTTON_QUIT, &CTab4::OnBnClickedButtonQuit)
	ON_WM_CTLCOLOR()
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






HBRUSH CTab4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	
	if (m_userid.m_hWnd == pWnd->m_hWnd) {
		

		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(255, 133, 0));
		return m_bk_brush;
	}

	else if (nCtlColor == CTLCOLOR_STATIC) {
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
