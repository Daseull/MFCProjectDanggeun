
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


CUserDTO* CurrentUser;
CUserDB* userDB;
CPostDB* postDB;
CBookMarkDB* bookmarkDB;
CString town[25] = { "강남구", "강동구", "강북구", "강서구", "관악구", "광진구", "구로구", "금천구",
					"노원구", "도봉구", "동대문구", "동작구", "마포구", "서대문구", "서초구", "성동구", "성북구", "송파구",
					"양천구", "영등포구", "용산구","은평구", "종로구", "중구", "중랑구" };
CString status[3] = { "판매중", "예약중", "거래완료" };


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
	void OnClose();
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

	//ON_UM_CLOSE()
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
	ON_COMMAND(UM_CLOSE, &CDanggeunClientDlg::OnClose)
//	ON_COMMAND(IDC_BUTTON_SEARCH, &CDanggeunClientDlg::OnButtonSearch)
//  ON_WM_CLOSE()
//ON_WM_CLOSE()
ON_MESSAGE(UWM_CUSTOM4, &CDanggeunClientDlg::OnUwmCustom4)
ON_MESSAGE(UWM_CUSTOM3, &CDanggeunClientDlg::OnUwmCustom3)
ON_MESSAGE(UWM_CUSTOM5, &CDanggeunClientDlg::OnUwmCustom5)

//ON_MESSAGE(UM_CUSTOM6, &CDanggeunClientDlg::OnUmCostom6)
END_MESSAGE_MAP()


// CDanggeunClientDlg message handlers

CLoginDlg dlg = new CLoginDlg;

BOOL CDanggeunClientDlg::OnInitDialog()
{
	userDB = new CUserDB;

	CDialogEx::OnInitDialog();
	if (dlg.DoModal() == IDCANCEL) {		
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

	postDB = new CPostDB;
	postDB->InitDB();
	postDB->postList = postDB->dao.getAll();

	bookmarkDB = new CBookMarkDB;
	bookmarkDB->InitDB();
	bookmarkDB->bookMarkList = bookmarkDB->dao.getAll();


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

	pDlg1->ShowWindow(SW_SHOW);
	pDlg2->ShowWindow(SW_HIDE);
	pDlg3->ShowWindow(SW_HIDE);
	pDlg4->ShowWindow(SW_HIDE);
	

	
	//C/R/U/D
	
	/*CUserDB* _userDB = new CUserDB();
	_userDB->InitDB();
	CPostDB* _postDB = new CPostDB();
	_postDB->InitDB();
	CBookMarkDB* _bookDB = new CBookMarkDB();
	_bookDB->InitDB();

	CUserDTO _user;
	CPostDTO _post;
	CBookMarkDTO _book;

	CString str;*/

	// Create
	//for (int i = 0; i < 3; i++) {
		//str.Format("id%d", i);
		//_user.SetUserID(str);

		//str.Format("pw%d", i);
		//_user.SetUserPW(str);

		//_user.SetTown(i);

		//str.Format("010-%d", i);
		//_user.SetPhone(str);
		//_userDB->dao.createUser(_user);


		//str.Format("id%d", i);
		//_post.SetUserID(str);
		//_post.SetTitle("제목");
		//_post.SetImgName("");
		//_post.SetPrice("10000");
		//_post.SetStauts(0);
		//_post.SetContent("내용내용");
		//_post.SetTown(i);
		//_postDB->dao.createPost(_post);


		//_book.SetPostID(i + 1);
		//str.Format("id%d", i);
		//_book.SetUserID(str);
		//_bookDB->dao.createBookMark(_book);

	//}


	// Read All +update/delete
		//_userDB->userList = _userDB->dao.getAll(); good
	//_userDB->userList = _userDB->dao.getAllByTown(0); good
	/*for (CUserDTO* user : _userDB->userList) {
		str.Format(user->GetUserID());
		AfxMessageBox(str);
	}*/


	//_postDB->postList = _postDB->dao.getAll(); good
	//_postDB->postList = _postDB->dao.getAllByTitleSearch("제");
	//for (CPostDTO* post : _postDB->postList) {
	//	str.Format(post->GetUserID());
	//	AfxMessageBox(str);
	//	_postDB->dao.deletePost(post->GetPostID());
	//}

	//_postDB->postList = _postDB->dao.getAll(); good
	//_bookDB->bookMarkList = _bookDB->dao.getAll();
	//for (CBookMarkDTO* book : _bookDB->bookMarkList) {
	//	str.Format(book->GetUserID());
	//	AfxMessageBox(str);
	//	_bookDB->dao.deleteBookMark(book->GetBookMarkID());
	//}
	
	//for (int i = 0; i < 3; i++) {
	//	//str.Format("id%d", i);
	//	//_user = _userDB->dao.getUser(str);
	//	//_userDB->dao.deleteUser(_user.GetUserID());
	//	
	//	//str.Format("id%d", i);
	//	/*_post.SetUserID(str);
	//	_book.SetPostID()*/
	//	/*_post = _postDB->dao.getPost(8 + i);
	//	str.Format(_post->GetUserID());
	//	AfxMessageBox(str);*/

	//	/*_post = _postDB->dao.getPost(8 + i);
	//	str.Format(_post.GetUserID());
	//	AfxMessageBox(str);*/

	//	str.Format("id%d", i);
	//	_user = _userDB->dao.getUser(str);
	//	str.Format(_user.GetUserID());
	//	AfxMessageBox(str);
	//	//_user.SetUserPW(str);
	//	//_userDB->dao.updateUser(_user);
	//	_userDB->dao.deleteUser(str);

	//}

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



void CDanggeunClientDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnClose();
}

CCreatePost cDlg;
afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom4(WPARAM wParam, LPARAM lParam)
{
	cDlg.DoModal();
	return 0;
}


afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom3(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	cDlg.EndDialog(IDOK);
	pDlg1->LoadTownPost();
	return 0;
}


afx_msg LRESULT CDanggeunClientDlg::OnUwmCustom5(WPARAM wParam, LPARAM lParam)
{
	pDlg3->LoadBookmarkPost();
	return 0;
}




//afx_msg LRESULT CDanggeunClientDlg::OnUmCostom6(CPostDTO* post)
//{
//	return 0;
//}
