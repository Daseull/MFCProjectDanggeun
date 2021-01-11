
// Danggeun_ServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Danggeun_Server.h"
#include "Danggeun_ServerDlg.h"
#include "afxdialogex.h"
#pragma warning(disable:4996)

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


// CDanggeunServerDlg dialog



CDanggeunServerDlg::CDanggeunServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DANGGEUN_SERVER_DIALOG, pParent)
	, m_strStatus(_T(""))
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDanggeunServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
}

BEGIN_MESSAGE_MAP(CDanggeunServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT, (LRESULT(AFX_MSG_CALL  CWnd::*)(WPARAM, LPARAM)) OnAccept)
	ON_MESSAGE(UM_RECEIVE, (LRESULT(AFX_MSG_CALL  CWnd::*)(WPARAM, LPARAM)) OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CDanggeunServerDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CDanggeunServerDlg message handlers

BOOL CDanggeunServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_socCom = NULL;

	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);
	//AfxMessageBox(_T("Create!"));
	return TRUE;


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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDanggeunServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDanggeunServerDlg::OnPaint()
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
HCURSOR CDanggeunServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LPARAM CDanggeunServerDlg::OnAccept(UINT wParam, LPARAM IParam) {
	m_strStatus = "접속성공";
	m_socCom = new CSocCom;
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);

	UpdateData(FALSE);
	return TRUE;
}
// (LRESULT(_cdecl CWnd::*)(WPARAM, LPARAM))

LPARAM CDanggeunServerDlg::OnReceive(UINT wParam, LPARAM IParam) {
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	m_socCom->Receive(pTmp, 256);
	strTmp.Format(_T("%s"), pTmp);

	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	return TRUE;

}

void CDanggeunServerDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);
	strcpy_s(pTmp, m_strSend);
	m_socCom->Send(pTmp, 256);

	strTmp.Format(_T("%s"), pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
}
