
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



CDanggeunServerDlg::CDanggeunServerDlg(CWnd* pParent /*=nullptr*/)	// 생성자
	: CDialogEx(IDD_DANGGEUN_SERVER_DIALOG, pParent)
	, m_strStatus(_T(""))
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDanggeunServerDlg::DoDataExchange(CDataExchange* pDX)			// 컨트롤 - 변수 동기화
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
	ON_MESSAGE(UM_ACCEPT, (LRESULT(AFX_MSG_CALL  CWnd::*)(WPARAM, LPARAM)) OnAccept)	// 접속 요청 받았을 때
	ON_MESSAGE(UM_RECEIVE, (LRESULT(AFX_MSG_CALL  CWnd::*)(WPARAM, LPARAM)) OnReceive)	// 메시지 받았을 때
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CDanggeunServerDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CDanggeunServerDlg message handlers

BOOL CDanggeunServerDlg::OnInitDialog()			// 다이얼로그 초기화
{
	CDialogEx::OnInitDialog();
	m_socCom = NULL;
	m_socServer.Create(5000);					// 포트 열기
	m_socServer.Listen();						// 클라이언트의 접속 기다리기
	m_socServer.Init(this->m_hWnd);				// 메인 핸들러 설정
	return TRUE;

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
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


LPARAM CDanggeunServerDlg::OnAccept(UINT wParam, LPARAM IParam) {	// 클라이언트로부터 접속요청 받았을 때
	m_strStatus = "접속성공";										// 컨트롤러에 접속 상태 표시
	m_socCom = new CSocCom;											// 통신용 소켓 생성
	m_socCom = m_socServer.GetAcceptSocCom();						// 통신용 소켓 설정
	m_socCom->Init(this->m_hWnd);									// 메인 핸들러 설정

	m_socCom->Send("접속성공", 256);								// 클라이언트에 접속성공 메시지 보내기

	UpdateData(FALSE);
	return TRUE;
}
// (LRESULT(_cdecl CWnd::*)(WPARAM, LPARAM))

LPARAM CDanggeunServerDlg::OnReceive(UINT wParam, LPARAM IParam) {	// 클라이언트로부터 메시지 받았을때
	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);										// 변수 초기화

	m_socCom->Receive(pTmp, 256);									// 메시지 받기
	strTmp.Format(_T("%s"), pTmp);									// 형 변환

	int i = m_list.GetCount();										// 리스트 행의 개수 받기
	m_list.InsertString(i, strTmp);									// 리스트에 받은 문자열 메시지 출력
	return TRUE;

}

void CDanggeunServerDlg::OnBnClickedButtonSend()					// 전송 버튼 클릭 시
{
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);										// 변수 초기화
	strcpy_s(pTmp, m_strSend);										// edit 컨트롤에 입력한 문자열 복사
	m_socCom->Send(pTmp, 256);										// 클라이언트에 보내기

	strTmp.Format(_T("%s"), pTmp);									// 형 변환
	int i = m_list.GetCount();										// 리스트 행의 개수 받기
	m_list.InsertString(i, strTmp);									// 리스트에 문자열 메시지 출력
}
