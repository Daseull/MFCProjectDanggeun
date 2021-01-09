
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
END_MESSAGE_MAP()


// CDanggeunClientDlg message handlers

BOOL CDanggeunClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

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

	// TODO: Add extra initialization here


	CFont font_sel;
	font_sel.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("굴림체"));

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
	pDlg1->MoveWindow(25, 0, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CTab2;
	pDlg2->Create(IDD_CTab2, &m_Tab);
	pDlg2->MoveWindow(25, 0, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_SHOW);

	pDlg3 = new CTab3;
	pDlg3->Create(IDD_CTab3, &m_Tab);
	pDlg3->MoveWindow(25, 0, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_SHOW);

	pDlg4 = new CTab4;
	pDlg4->Create(IDD_CTab4, &m_Tab);
	pDlg4->MoveWindow(25, 0, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_SHOW);

	font_sel.DeleteObject();

	

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
			break;
		case 1:
			pDlg2->ShowWindow(SW_SHOW);
			pDlg1->ShowWindow(SW_HIDE);
			pDlg3->ShowWindow(SW_HIDE);
			pDlg4->ShowWindow(SW_HIDE);
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
