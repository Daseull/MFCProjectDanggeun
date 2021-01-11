﻿
// Danggeun_ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Danggeun_Client.h"
#include "Danggeun_ClientDlg.h"
#include "afxdialogex.h"
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"
#include "JoinDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString CurrentUser;
CUserDB* userDB;
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:

	//afx_msg_안녕
	DECLARE_MESSAGE_MAP()
//	afx_msg LRESULT OnUwmCustom1(WPARAM wParam, LPARAM lParam);
public:
//	virtual BOOL OnInitDialog();
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CDanggeunClientDlg dialog
// where ??


CDanggeunClientDlg::CDanggeunClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DANGGEUN_CLIENT_DIALOG, pParent)
{
	pDlg1 = NULL;
	pDlg2 = NULL;
	pDlg3 = NULL;
	pDlg4 = NULL;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDanggeunClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//  DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
	DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
}

BEGIN_MESSAGE_MAP(CDanggeunClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CDanggeunClientDlg::OnTcnSelchangeTabMain)
	ON_MESSAGE(UWM_CUSTOM1, &CDanggeunClientDlg::OnUwmCustom1)

	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
//	ON_COMMAND(IDC_BUTTON_SEARCH, &CDanggeunClientDlg::OnButtonSearch)
END_MESSAGE_MAP()


// CDanggeunClientDlg message handlers
extern CLoginDlg dlg = new CLoginDlg;

BOOL CDanggeunClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	dlg.DoModal();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bk_brush.CreateSolidBrush(RGB(255, 241, 211));

	// TODO: Add extra initialization here
	CFont font_sel;
	font_sel.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("나눔고딕"));

	m_Tab.SetFont(&font_sel);
	m_Tab.InsertItem(0, "홈");
	m_Tab.InsertItem(1, "내 글 목록");
	m_Tab.InsertItem(2, "관심리스트");
	m_Tab.InsertItem(3, "내 정보");
	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	pDlg1 = new CTab1;
	pDlg1->Create(IDD_CTab1, &m_Tab);
	pDlg1->MoveWindow(28, 0, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CTab2;
	pDlg2->Create(IDD_CTab2, &m_Tab);
	pDlg2->MoveWindow(28, 0, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_SHOW);

	pDlg3 = new CTab3;
	pDlg3->Create(IDD_CTab3, &m_Tab);
	pDlg3->MoveWindow(28, 0, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_SHOW);

	pDlg4 = new CTab4;
	pDlg4->Create(IDD_CTab4, &m_Tab);
	pDlg4->MoveWindow(28, 0, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_SHOW);


	font_sel.DeleteObject();

	m_Tab.ModifyStyle(0, TCS_OWNERDRAWFIXED);//tab 색상

	//여기다가 login 창 생성하고 doModao == IDOK(또는 로그인 성공 메세지,else면은 창 닫히고)
	//if (log.DoModal() == IDOK) 
	if (TRUE) {
		pDlg1->Init();
		////내 글 목록
		pDlg2->Init();
		////관심글 록록
		//pDlg3->LoadPost();

		//처음 켰을 땐 홈 탭이 보이게 설정
		pDlg1->ShowWindow(SW_SHOW);
		pDlg2->ShowWindow(SW_HIDE);
		pDlg3->ShowWindow(SW_HIDE);
		pDlg4->ShowWindow(SW_HIDE);
	}
	
	/* DB Init

	*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDanggeunClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDanggeunClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDanggeunClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDanggeunClientDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDC_TAB_MAIN == pNMHDR->idFrom) {
		int iSelect = m_Tab.GetCurSel();

		switch (iSelect) {
		case 0:
			pDlg1->ShowWindow(SW_SHOW);
			pDlg2->ShowWindow(SW_HIDE);
			pDlg3->ShowWindow(SW_HIDE);
			pDlg4->ShowWindow(SW_HIDE);
			pDlg1->LoadTownPost();
			break;
		case 1:
			pDlg2->ShowWindow(SW_SHOW);
			pDlg1->ShowWindow(SW_HIDE);
			pDlg3->ShowWindow(SW_HIDE);
			pDlg4->ShowWindow(SW_HIDE);
			pDlg2->LoadMyPost();
			break;
		case 2:
			pDlg3->ShowWindow(SW_SHOW);
			pDlg1->ShowWindow(SW_HIDE);
			pDlg2->ShowWindow(SW_HIDE);
			pDlg4->ShowWindow(SW_HIDE);
			break;
		case 3:
			pDlg4->ShowWindow(SW_SHOW);
			pDlg1->ShowWindow(SW_HIDE);
			pDlg2->ShowWindow(SW_HIDE);
			pDlg3->ShowWindow(SW_HIDE);
			break;
		
		}
	}
	*pResult = 0;

}




void CDanggeunClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_bk_brush.DeleteObject();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


HBRUSH CDanggeunClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom1(WPARAM wParam, LPARAM lParam)
{
	dlg.EndDialog(IDOK);
	return 0;
}





//BOOL CAboutDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  여기에 추가 초기화 작업을 추가합니다.
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
//}
