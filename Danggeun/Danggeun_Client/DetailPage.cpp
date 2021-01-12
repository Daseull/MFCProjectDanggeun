﻿// DetailPage.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "DetailPage.h"
#include "afxdialogex.h"
#include "ChatBox.h"
#include "afxwin.h"
#include "CreatePost.h"
#include "Danggeun_ClientDlg.h"
// CDetailPage 대화 상자

IMPLEMENT_DYNAMIC(CDetailPage, CDialogEx)

CDetailPage::CDetailPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)

{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	//m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
}

CDetailPage::CDetailPage(CPostDTO* post, CWnd* pParent) 
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
	,m_post(post) 

{
	
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
	
}

CDetailPage::~CDetailPage()
{
}

void CDetailPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHAT, m_tMyButton1);
	//  DDX_Control(pDX, IDC_BUTTON_HEART, m_heart);
	//  DDX_Control(pDX, IDC_BUTTON_HEART, m_heart);
	//  DDX_Control(pDX, IDC_BUTTON_HEART, m_heart);
	DDX_Control(pDX, IDC_STATIC_ID, m_stcUserID);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_stcPicture);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_stcPrice);
	DDX_Control(pDX, IDC_STATIC_STATE, m_stcState);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_stcText);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_TOWN, m_stcTown);
	DDX_Control(pDX, IDC_BUTTON_HEART, m_btnheart);
}


BEGIN_MESSAGE_MAP(CDetailPage, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON_CHAT, &CDetailPage::OnBnClickedButtonChat)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_STATE, &CDetailPage::OnStnClickedStaticState)
	ON_STN_CLICKED(IDC_STATIC_TITLE, &CDetailPage::OnStnClickedStaticTitle)
	ON_BN_CLICKED(IDC_BUTTON_HEART, &CDetailPage::OnBnClickedButtonHeart)
	ON_STN_CLICKED(IDC_STATIC_TEXT, &CDetailPage::OnStnClickedStaticText)
	ON_BN_CLICKED(IDC_BUTTON_POSTEDIT, &CDetailPage::OnClickedButtonPostedit)
END_MESSAGE_MAP()


// CDetailPage 메시지 처리기


HBRUSH CDetailPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  여기서 DC의 특성을 변경합니다.

	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}

	if (m_stcUserID.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253,212,129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	else if (m_stcTown.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	else if (m_stcState.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 169, 76));
		return m_bk_brush;
	}
	else if (m_stcText.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	else if (m_stcPrice.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(61, 149, 255));
		return m_bk_brush;
	}
	else if (nCtlColor==CTLCOLOR_STATIC) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}

	if (nCtlColor == CTLCOLOR_BTN) {
		pDC->SetBkColor(RGB(0, 200, 255));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

int heartstate = 0;	// 관심목록에 없음

BOOL CDetailPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	/*
		FW_DONTCARE         상관 안함
		FW_THIN             얇은
		FW_EXTRALIGHT
		FW_LIGHT
		FW_NORMAL           보통
		FW_MEDIUM
		FW_SEMIBOLD         조금 굵기
		FW_BOLD             굵게
		FW_EXTRABOLD        매우 굵게
		FW_HEAVY
		*/

		//제목 okay
	CFont font1;
	LOGFONT lf1;
	::ZeroMemory(&lf1, sizeof(lf1));
	lf1.lfHeight = 22;
	lf1.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf1.lfFaceName, "나눔고딕");
	font1.CreateFontIndirectA(&lf1);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&font1);
	font1.Detach();

	//내용 okay
	CFont font2;
	LOGFONT lf2;
	::ZeroMemory(&lf2, sizeof(lf2));
	lf2.lfHeight = 18;
	lf2.lfWeight = FW_NORMAL;
	::lstrcpy(lf2.lfFaceName, "나눔고딕");

	font2.CreateFontIndirectA(&lf2);
	GetDlgItem(IDC_STATIC_TEXT)->SetFont(&font2);
	font2.Detach();

	//아이디 okay
	CFont font3;
	LOGFONT lf3;
	::ZeroMemory(&lf3, sizeof(lf3));
	lf3.lfHeight = 19;
	lf3.lfWeight = FW_SEMIBOLD;
	::lstrcpy(lf3.lfFaceName, "나눔고딕");

	font3.CreateFontIndirectA(&lf3);
	GetDlgItem(IDC_STATIC_ID)->SetFont(&font3);
	font3.Detach();

	//동네 okay
	CFont font4;
	LOGFONT lf4;
	::ZeroMemory(&lf4, sizeof(lf4));
	lf4.lfHeight = 16;
	lf4.lfWeight = FW_LIGHT;
	::lstrcpy(lf4.lfFaceName, "나눔고딕");

	font4.CreateFontIndirectA(&lf4);
	GetDlgItem(IDC_STATIC_TOWN)->SetFont(&font4);
	font4.Detach();

	//상태 okay
	CFont font5;
	LOGFONT lf5;
	::ZeroMemory(&lf5, sizeof(lf5));
	lf5.lfHeight = 18;
	lf5.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf5.lfFaceName, "나눔고딕");

	font5.CreateFontIndirectA(&lf5);
	GetDlgItem(IDC_STATIC_STATE)->SetFont(&font5);
	font5.Detach();

	//가격 okay
	CFont font6;
	LOGFONT lf6;
	::ZeroMemory(&lf6, sizeof(lf6));
	lf6.lfHeight = 20;
	lf6.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf6.lfFaceName, "나눔고딕");

	font6.CreateFontIndirectA(&lf6);
	GetDlgItem(IDC_STATIC_PRICE)->SetFont(&font6);
	font6.Detach();


	m_btnheart.LoadBitmaps(IDB_HEART, IDB_HEART2, IDB_HEART2, IDB_HEART);
	m_btnheart.SizeToContent();


	//관심 처리
	extern CUserDTO* CurrentUser;
	extern CBookMarkDB* bookmarkDB;

	//글 작성자인 경우 수정버튼 활성화, 채팅/관심 버튼 비활성화
	if (m_post->GetUserID() == CurrentUser->GetUserID()) {
		GetDlgItem(IDC_BUTTON_POSTEDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_HEART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CHAT)->ShowWindow(SW_HIDE);

	}
	//글 작성자 아닌경우
	else {
		GetDlgItem(IDC_BUTTON_POSTEDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_HEART)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_CHAT)->ShowWindow(SW_SHOW);

		// 1/12 수정 필요

		for (CBookMarkDTO* bookmark : bookmarkDB->bookMarkList) {
			if (bookmark->GetPostID() == m_post->GetPostID()) {
				heartstate = 1; break;	// 관심목록에 있음
			}
		}

		if (heartstate != 1) {
			m_btnheart.LoadBitmaps(IDB_HEART, NULL, NULL, NULL);
			m_btnheart.SizeToContent();
		}
		else {
			m_btnheart.LoadBitmaps(IDB_HEART2, NULL, NULL, NULL);
			m_btnheart.SizeToContent();
		}

	}

	m_image.Load("res\\" + m_post->GetImgName());
	if (m_image.IsNull()) {
		m_image.Load("res\\LoadError.png");
	}


	//페이지 내용 처리
	HBITMAP h_bmp = (HBITMAP)m_image;
	CBitmap bmp;
	m_stcPicture.SetBitmap(h_bmp);

	m_stcUserID.SetWindowText("판매자\t" + m_post->GetUserID());
	m_stcTitle.SetWindowText(m_post->GetTitle());
	m_stcText.SetWindowText(m_post->GetContent());
	m_stcPrice.SetWindowText(m_post->GetPrice());

	extern CString town[];
	m_stcTown.SetWindowText(town[m_post->GetTown()]);
	extern CString status[];
	m_stcState.SetWindowText(status[m_post->GetStatus()]);
	

	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDetailPage::OnStnClickedStaticState()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDetailPage::OnStnClickedStaticTitle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CDetailPage::OnBnClickedButtonHeart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	CBookMarkDTO book;
	if (!heartstate) {
		m_btnheart.LoadBitmaps(IDB_HEART2, NULL, NULL, NULL);
		m_btnheart.SizeToContent();
		MessageBox("관심리스트 추가!");
		heartstate = 1;
		book.SetPostID(m_post->GetPostID());
		book.SetUserID(CurrentUser->GetUserID());
		bookmarkDB->dao.createBookMark(book);
	}
	else {
		m_btnheart.LoadBitmaps(IDB_HEART, NULL, NULL, NULL);
		m_btnheart.SizeToContent();
		MessageBox("관심리스트 삭제!");
		heartstate = 0;

		//1/12 수정필요
		for (CBookMarkDTO* bookmark : bookmarkDB->bookMarkList) {
			if (bookmark->GetPostID() == m_post->GetPostID()) {
				//MessageBox("찾았다");
				bookmarkDB->dao.deleteBookMark(bookmark->GetBookMarkID());
				break;
			}
		}

	}
	bookmarkDB->bookMarkList = bookmarkDB->dao.getAll();
	::SendMessage(((CDetailPage*)GetParent())->GetSafeHwnd(), UWM_CUSTOM5, 0, 0);
}


void CDetailPage::OnStnClickedStaticText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

CCreatePost* dlg;

void CDetailPage::OnClickedButtonPostedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	AfxMessageBox("닫히다");
	dlg = new CCreatePost(m_post);
	((CDanggeunClientDlg*)GetParent())->pDlg1->LoadTownPost();
	//dlg->EndDialog(IDOK);
	dlg->DoModal();
}


