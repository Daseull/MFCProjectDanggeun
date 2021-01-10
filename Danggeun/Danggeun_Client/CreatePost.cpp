// CreatePost.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "CreatePost.h"
#include "afxdialogex.h"


// CCreatePost 대화 상자

IMPLEMENT_DYNAMIC(CCreatePost, CDialogEx)

CCreatePost::CCreatePost(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_POST, pParent)
	, m_strTitle(_T("글 제목을 작성해주세요"))
	, m_strPrice(_T("\\가격을 입력해주세요"))
	, m_strText(_T("동네에 올릴 게시글 내용을 작성해주세요(가품 및 판매금지품목은 게시가 제한 될 수 있어요.)"))
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));

	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
}

CCreatePost::~CCreatePost()
{
}

void CCreatePost::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_POST, m_tMyButton1);
	DDX_Text(pDX, IDC_EDIT_POST_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_POST_PRICE, m_strPrice);
	DDX_Text(pDX, IDC_EDIT_POST_TEXT, m_strText);
}


BEGIN_MESSAGE_MAP(CCreatePost, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCreatePost 메시지 처리기


HBRUSH CCreatePost::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
