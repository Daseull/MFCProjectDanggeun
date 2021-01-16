
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
public:
	void OnClose();
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


//생성자
CDanggeunClientDlg::CDanggeunClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DANGGEUN_CLIENT_DIALOG, pParent)
{
	//멤버변수 초기화
	pDlg1 = NULL;
	pDlg2 = NULL;
	pDlg3 = NULL;
	pDlg4 = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDanggeunClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
}

BEGIN_MESSAGE_MAP(CDanggeunClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CDanggeunClientDlg::OnTcnSelchangeTabMain)

	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_COMMAND(UM_CLOSE, &CDanggeunClientDlg::OnClose)
	ON_MESSAGE(UWM_CUSTOM1, &CDanggeunClientDlg::OnUwmCustom1)
	ON_MESSAGE(UWM_CUSTOM3, &CDanggeunClientDlg::OnUwmCustom3)
	ON_MESSAGE(UWM_CUSTOM4, &CDanggeunClientDlg::OnUwmCustom4)
	ON_MESSAGE(UWM_CUSTOM6, &CDanggeunClientDlg::OnUwmCustom6)
END_MESSAGE_MAP()





//다른 클래스에서 사용할 수 있게 DB관련 변수들을 전역변수로 선언
CUserDTO* CurrentUser;
CUserDB* userDB;
CPostDB* postDB;
CBookMarkDB* bookmarkDB;

//다른 클래스에서는 동네, 판매상태를 정수로 갖고 있으므로, 매핑되는 문자열을 전역변수로 선언
CString town[25] = { "강남구", "강동구", "강북구", "강서구", "관악구", "광진구", "구로구", "금천구",
					"노원구", "도봉구", "동대문구", "동작구", "마포구", "서대문구", "서초구", "성동구", "성북구", "송파구",
					"양천구", "영등포구", "용산구","은평구", "종로구", "중구", "중랑구" };
CString status[3] = { "판매중", "예약중", "거래완료" };

//로그인 창
CLoginDlg LoginDlg;

BOOL CDanggeunClientDlg::OnInitDialog()
{
	//로그인을 위해 userDB 생성
	userDB = new CUserDB;

	CDialogEx::OnInitDialog();

	//로그인하지 않을 경우 프로그램이 닫혀 이용 불가능
	if (LoginDlg.DoModal() == IDCANCEL) {
		exit(0);
	}

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


	//다른 클래스에서 사용할 수 있도록 DB 접근에 필요한 객체들 생성, 업데이트
	postDB = new CPostDB;
	postDB->InitDB();
	postDB->postList = postDB->dao.getAll();
	bookmarkDB = new CBookMarkDB;
	bookmarkDB->InitDB();
	bookmarkDB->bookMarkList = bookmarkDB->dao.getAll();

	//탭 추가 및 이름 설정
	m_Tab.SetFont(&font_sel);
	m_Tab.InsertItem(0, "홈");
	m_Tab.InsertItem(1, "내 글 목록");
	m_Tab.InsertItem(2, "관심리스트");
	m_Tab.InsertItem(3, "내 정보");
	m_Tab.SetCurSel(0);

	//탭들의 위치를 조절하기 위해 MainTabCtrl의 사이즈를 가져온다
	CRect rect;
	m_Tab.GetWindowRect(&rect);

	//탭에 자식들 생성하고 붙이기
	pDlg1 = new CTab1;
	pDlg1->Create(IDD_CTab1, &m_Tab);
	pDlg1->MoveWindow(28, 0, rect.Width(), rect.Height());	//위치 조정
	pDlg1->ShowWindow(SW_SHOW);	//로그인 성공시 홈탭이 가장 먼저 보이게 설정
	
	
	pDlg2 = new CTab2;
	pDlg2->Create(IDD_CTab2, &m_Tab);
	pDlg2->MoveWindow(28, 0, rect.Width(), rect.Height()); //위치조정
	pDlg2->ShowWindow(SW_HIDE); //홈탭 제외 나머지는 숨기기

	pDlg3 = new CTab3;
	pDlg3->Create(IDD_CTab3, &m_Tab);
	pDlg3->MoveWindow(28, 0, rect.Width(), rect.Height()); //위치 조정
	pDlg3->ShowWindow(SW_HIDE); //홈탭 제외 나머지는 숨기기

	pDlg4 = new CTab4;
	pDlg4->Create(IDD_CTab4, &m_Tab);
	pDlg4->MoveWindow(28, 0, rect.Width(), rect.Height());	//위치 조정
	pDlg4->ShowWindow(SW_HIDE); //홈탭 제외 나머지는 숨기기


	font_sel.DeleteObject();

	m_Tab.ModifyStyle(0, TCS_OWNERDRAWFIXED);//tab 색상

	

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


//탭 선택 이벤트 핸들러(선택된 탭이 보이게 함)
void CDanggeunClientDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDC_TAB_MAIN == pNMHDR->idFrom) {
		int iSelect = m_Tab.GetCurSel();	//선택된 탭 구하기
		
		//선택된 탭만 보이게 하고, 해당 탭 내용 업데이트
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
			pDlg3->LoadBookmarkPost();
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

//다이아로그의 배경색상 칠하기
HBRUSH CDanggeunClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}
	return hbr;
}

//로그인 다이얼로그에서 보낸 메세지 : 로그인 성공 했으므로 로그인 창 닫음
afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom1(WPARAM wParam, LPARAM lParam)
{
	LoginDlg.EndDialog(IDOK);
	return 0;
}




CCreatePost* CreatePostDlg; //글 작성 대화상자 변수

//탭1에서 글작성 버튼 클릭시 오는 메세지
afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom4(WPARAM wParam, LPARAM lParam)
{
	//글작성 창 생성하고 띄움
	CreatePostDlg = new CCreatePost;
	CreatePostDlg->DoModal();
	return 0;
}

//글작성 창에서 완료버튼 클릭으로 받은 메세지
afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom3(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	
	//글작성 창 닫기
	CreatePostDlg->EndDialog(IDOK);

	//글이 추가 됐으므로 홈 탭 바로 업데이트
	pDlg1->LoadTownPost();
	return 0;
}

//탭4에서 수정 완료 버튼 클릭으로 받은 메세지
afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom6(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	//회원 수정된 내용으로 탭의 글 리스트 업데이트
	pDlg1->LoadTownPost();
	pDlg3->LoadBookmarkPost();
	return 0;
}


void CDanggeunClientDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnClose();
}