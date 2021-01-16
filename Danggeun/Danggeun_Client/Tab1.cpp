// Tab1.cpp: 구현 파일
//홈 

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab1.h"
#include "afxdialogex.h"
#include "ChatBox.h"
#include "CreatePost.h"
#include "afxwin.h" //비트맵때문에 넣은거
#include "LoginDlg.h"
#include "DetailPage.h"

// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

//생성자
CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab1, pParent)
	, m_strSearch(_T(""))
{
	//변수 초기화
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton3.SetRoundButtonStyle(&m_tMyButtonStyle);

}

//해제자
CTab1::~CTab1()
{

}

//글목록 가져오기
void CTab1::LoadTownPost()
{
	//글쓰기 버튼 보이고 돌아가기 버튼 안보이게 
	GetDlgItem(IDC_BUTTON_NEWPOST)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_HIDE);

	//글 목록 초기화
	int n = m_list.GetItemCount();

	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CString status[3];

	//같은 동네에서 작성된 글 가져오기
	for (CPostDTO* post : postDB->dao.getAllByTown(CurrentUser->GetTown())) {
		//이미지 목록 가져오기 
		CBitmap bmp;
		CImage img;
		img.Load("res\\small_" + post->GetImgName());
		if (img.IsNull()) {
			img.Load("res\\LoadError.png");
		}
		bmp.Attach(img);
		m_ImageList.Add(&bmp, RGB(255, 255, 255));
		
		//각 항목에 대한 값 설정
		int i = m_list.GetItemCount();
		m_list.AddItem(post->GetTitle(), i, 0, -1, i);
		m_list.AddItem(post->GetPrice(), i, 1);
		m_list.AddItem(status[post->GetStatus()], i, 2);

		//글의 id값 설정 
		int postid = post->GetPostID();
		CString postID;
		postID.Format("%d", postid);
		m_list.AddItem(postID, i, 3);
	}

	//동네명 설정
	extern CString town[];
	m_strTown = town[CurrentUser->GetTown()];
	//검색란 공백 설정 
	m_strSearch.Empty();
	UpdateData(FALSE);
}

//특정 단어로 글 찾기
void CTab1::SearchPost(CString Key)
{
	//글쓰기 버튼 안보이고 돌아가기 버튼 보이게 
	GetDlgItem(IDC_BUTTON_NEWPOST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_SHOW);

	//글목록 초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	//검색란이 공백이면 
	if (Key.IsEmpty()) {
		AfxMessageBox("검색어를 입력하세요");
		return;
	}

	//검색어 대문자로 변환
	Key = Key.MakeUpper();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CString status[3];

	//같은 동네에서 작성된 글들 중 글의 제목이 찾고자하는 단어와 일치하는 글 가져오기
	for (CPostDTO *post : postDB->dao.getAllByTitleSearch(Key, CurrentUser->GetTown())) {
			//이미지 목록 가져오기 
			CBitmap bmp;
			CImage img;
			img.Load("res\\small_" + post->GetImgName());
			if (img.IsNull()) {
				img.Load("res\\LoadError.png");
			}
			bmp.Attach(img);
			m_ImageList.Add(&bmp, RGB(255, 255, 255));

			//각 항목에 대한 값 설정
			int i = m_list.GetItemCount();
			m_list.AddItem(post->GetTitle(), i, 0, -1, i);
			m_list.AddItem(post->GetPrice(), i, 1);
			m_list.AddItem(status[post->GetStatus()], i, 2);
			
			//글의 id값 설정
			int postid = post->GetPostID();
			CString postID;
			postID.Format("%d", postid);
			m_list.AddItem(postID, i, 3);
	}
	
	UpdateData(FALSE);
}

//컨트롤의 값 변환
void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	DDX_Text(pDX, IDC_STATIC_TOWN, m_strTown);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON_NEWPOST, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton2);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_tMyButton3);
}

//멤버함수
BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab1::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTab1::OnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_NEWPOST, &CTab1::OnBnClickedButtonNewpost)
ON_WM_CTLCOLOR()
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CTab1::OnDblclkList1)
ON_BN_CLICKED(IDC_BUTTON_BACK, &CTab1::OnClickedButtonBack)
END_MESSAGE_MAP()


// CTab1 메시지 처리기

//확인 버튼 비활성화
void CTab1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
}

//취소버튼 비활성화
void CTab1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnCancel();
}

//검색 버튼 눌렀을 때
void CTab1::OnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	SearchPost(m_strSearch);
}

//글쓰기 버튼 눌렀을 때
void CTab1::OnBnClickedButtonNewpost()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::SendMessage(((CTab1*)GetParent()->GetParent())->GetSafeHwnd(), UWM_CUSTOM4, 0, 0);
}

//다이아로그의 배경색상 칠하기
HBRUSH CTab1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}
	//스태틱일 때 색상 설정
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	//버튼일 때 색상 설정
	if (nCtlColor == CTLCOLOR_BTN) {
		pDC->SetBkColor(RGB(0, 200, 255));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

//글목록 중 특정 글 클릭했을 때
void CTab1::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	// 행 클릭시 행 넘버값 받아오기
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int idx = pNMListView->iItem;

	if (idx != -1) {
		//선택된 행의 포스트아이디를 리스트 컨트롤의 세번째 컬럼에서 가져온다
		CString sIndexPostID;
		sIndexPostID = m_list.GetItemText(idx, 3);
		//스트링을 정수로 변환(포스트 아이디)
		int PostID = _ttoi(sIndexPostID);
		extern CPostDB* postDB;
		//해당글의 정보를 가진 상세페이지창 생성하기
		CDetailPage dlg(postDB->dao.getPost(PostID));
		dlg.DoModal();
	}
	*pResult = 0;
}

//다이아로그의 초기상태 설정
BOOL CTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//이미지 목록 생성 및 크기 지정 
	m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

	

	//글 선택시 해당 줄의 행이 전체 선택되게 설정
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//리스트 컨트롤의 컬럼 삽입
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);
	m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);
	//포스트 아이디는 컨트롤러에서 사용하며 사용자에게는 보이지 않도록 사이즈를 0으로 설정한다
	m_list.InsertColumn(3, "postID", LVCFMT_RIGHT, 0);
	
	//글 목록 가져오기
	LoadTownPost();

	return TRUE;
}

//엔터키에 대한 처리함수
BOOL CTab1::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		OnClickedButtonSearch();

	return CDialogEx::PreTranslateMessage(pMsg);
}

//돌아가기 버튼 눌렀을 때
void CTab1::OnClickedButtonBack()
{
	LoadTownPost();
}
