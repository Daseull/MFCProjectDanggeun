// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab3.h"
#include "afxdialogex.h"
#include "RoundButton2.h"
#include "RoundButtonStyle.h"
#include "DetailPage.h"

// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)				// 생성자
	: CDialogEx(IDD_CTab3, pParent)
	, m_strSearch(_T(""))
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)			// 컨트롤 - 변수 동기화
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
	DDX_Text(pDX, IDC_STATIC_TOWN, m_strTown);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_tMyButton2);
	DDX_Control(pDX, IDC_LIST_HEART, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_strSearch);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTab3::OnBnClickedButtonSearch)
ON_BN_CLICKED(IDC_BUTTON_BACK, &CTab3::OnBnClickedButtonBack)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_HEART, &CTab3::OnDblclkListHeart)
END_MESSAGE_MAP()


// CTab3 메시지 처리기

HBRUSH CTab3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	//스태틱일 때 색상 설정
	if (nCtlColor == CTLCOLOR_STATIC) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	return hbr;
}


BOOL CTab3::OnInitDialog()						// 다이얼로그 초기화
{
	extern CString town[];				
	extern CUserDTO* CurrentUser;
	m_strTown = town[CurrentUser->GetTown()];	// 현재 사용자의 동네 표기
	UpdateData(FALSE);

	m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);	// 이미지 리스트 생성
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);				// 리스트에 이미지 추가

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);		// 리스트에 글 제목 컬럼 추가
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);			// 리스트에 가격 컬럼 추가
	m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);		// 리스트에 판매상태 컬럼 추가
	m_list.InsertColumn(3, "postID", LVCFMT_RIGHT, 0);			// 리스트에 postID 컬럼 추가

	LoadBookmarkPost();											// 글 리스트 로드하는 함수 호출
	return TRUE; 
}


void CTab3::LoadBookmarkPost() {
	

	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_HIDE);	// 돌아가기 버튼 숨기기
	int n = m_list.GetItemCount();						// 리스트 행의 개수만큼
	while (n--)											// 이미지 리스트 지우기
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();							// 리스트 초기화

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	extern CString status[3];
	
	extern CString town[];
	m_strTown = town[CurrentUser->GetTown()];
	/*
	for (CBookMarkDTO* bookmark : bookmarkDB->bookMarkList) {
		if (bookmark->GetUserID() == CurrentUser->GetUserID()) {
			for (CPostDTO* post : postDB->postList) {
				if (bookmark->GetPostID() == post->GetPostID()) {
					CBitmap bmp;
					CImage img;
					img.Load("res\\small_" + post->GetImgName());
					if (img.IsNull()) {
						img.Load("res\\LoadError.png");
					}
					bmp.Attach(img);
					m_ImageList.Add(&bmp, RGB(255, 255, 255));

	//				int i = m_list.GetItemCount();	// 이미지 순서 맞는지 확인하기
	//				m_list.AddItem(post->GetTitle(), i, 0, -1, i);
	//				m_list.AddItem(post->GetPrice(), i, 1);
	//				m_list.AddItem(status[post->GetStatus()], i, 2);

					int postid = post->GetPostID();
					CString postID;
					postID.Format("%d", postid);
					m_list.AddItem(postID, i, 3);
				}
			}
		}
	}
	*/
	
	for (CPostDTO* post : postDB->dao.getAllByBookMark(CurrentUser->GetUserID())) {		// 현재 사용자가 북마크한 포스트 찾기
		CBitmap bmp;
		CImage img;
		img.Load("res\\small_" + post->GetImgName());		// 이미지 로드
		if (img.IsNull()) {									// 경로가 없을 때.
			img.Load("res\\LoadError.png");					
		}
		bmp.Attach(img);									// 이미지 비트맵으로 연결
		m_ImageList.Add(&bmp, RGB(255, 255, 255));			// 이미지 리스트에 이미지 추가

		int i = m_list.GetItemCount();						// 리스트 행의 개수 가져오기
		m_list.AddItem(post->GetTitle(), i, 0, -1, i);		// 리스트에 글 제목 추가
		m_list.AddItem(post->GetPrice(), i, 1);				// 리스트에 가격 추가
		m_list.AddItem(status[post->GetStatus()], i, 2);	// 리스트에 판매 상태 추가

		int postid = post->GetPostID();						// postID 가져오기
		CString postID;
		postID.Format("%d", postid);						// 형 변환
		m_list.AddItem(postID, i, 3);						// 리스트에 postID 추가
	}
	UpdateData(FALSE);				
}


void CTab3::SearchPost(CString Key)
{
	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_SHOW);		// 돌아가기 버튼 보이기
	m_strSearch = "";										// 검색창 비우기
	UpdateData(FALSE);

	int n = m_list.GetItemCount();							// 리스트 행의 개수만큼
	while (n--)												// 이미지 리스트 지우기
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();								// 리스트 초기화

	if (Key.IsEmpty()) {									// 검색어가 없을 때
		AfxMessageBox("검색어를 입력하세요");
		return;
	}
	Key = Key.MakeUpper();									// 검색어 모두 대문자로 바꾸기
	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	extern CString status[3];

	for (CPostDTO* post : postDB->dao.getAllByBookMark(CurrentUser->GetUserID())) {		// 현재 사용자가 북마크한 포스트 찾기
		CString title = post->GetTitle();			// 글 제목 가져오기
		if (title.MakeUpper().Find(Key) != -1) {	// 글 제목에 찾는 키워드가 있을 때
			CBitmap bmp;
			CImage img;
			img.Load("res\\small_" + post->GetImgName());		// 이미지 로드
			if (img.IsNull()) {									// 경로가 없을 때.
				img.Load("res\\LoadError.png");
			}
			bmp.Attach(img);									// 이미지 비트맵으로 연결
			m_ImageList.Add(&bmp, RGB(255, 255, 255));			// 이미지 리스트에 이미지 추가

			int i = m_list.GetItemCount();						// 리스트 행의 개수 가져오기
			m_list.AddItem(post->GetTitle(), i, 0, -1, i);		// 리스트에 글 제목 추가
			m_list.AddItem(post->GetPrice(), i, 1);				// 리스트에 가격 추가
			m_list.AddItem(status[post->GetStatus()], i, 2);	// 리스트에 판매 상태 추가

			int postid = post->GetPostID();						// postID 가져오기
			CString postID;
			postID.Format("%d", postid);						// 형 변환
			m_list.AddItem(postID, i, 3);						// 리스트에 postID 추가
		}
	}
	UpdateData(FALSE);

	/*
	for (CBookMarkDTO* bookmark : bookmarkDB->bookMarkList) {
		if (bookmark->GetUserID() == CurrentUser->GetUserID()) {
			for (CPostDTO* post : postDB->postList) {
				if (bookmark->GetPostID() == post->GetPostID()) {
					CString title = post->GetTitle();
					if (title.MakeUpper().Find(Key) != -1) {
						CBitmap bmp;
						CImage img;
						img.Load("res\\small_" + post->GetImgName());
						if (img.IsNull()) {
							img.Load("res\\LoadError.png");
						}
						bmp.Attach(img);
						m_ImageList.Add(&bmp, RGB(255, 255, 255));

						int i = m_list.GetItemCount();
						m_list.AddItem(post->GetTitle(), i, 0, -1, i);
						m_list.AddItem(post->GetPrice(), i, 1);
						m_list.AddItem(status[post->GetStatus()], i, 2);
						int postid = post->GetPostID();
						CString postID;
						postID.Format("%d", postid);
						m_list.AddItem(postID, i, 3);
					}
				}
			}
		}
	}

	UpdateData(FALSE);
	*/
}


void CTab3::OnBnClickedButtonSearch()	// 검색 버튼 클릭 시
{
	UpdateData(TRUE);
	SearchPost(m_strSearch);			// 검색 함수 호출
}


void CTab3::OnBnClickedButtonBack()		// 뒤로가기 버튼 클릭 시
{
	LoadBookmarkPost();					// 글 로드 함수 호출
}


BOOL CTab3::PreTranslateMessage(MSG* pMsg)	
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)	// 엔터 버튼 눌렀을 때
		OnBnClickedButtonSearch();									// 검색 함수 호출
	return CDialogEx::PreTranslateMessage(pMsg);
}




void CTab3::OnDblclkListHeart(NMHDR* pNMHDR, LRESULT* pResult)		// 관심 리스트 클릭 시
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int idx = pNMListView->iItem;									// 해당 인덱스 가져오기
	if (idx != -1) {												// 리스트에 있는 인덱스 클릭 시
		CString sIndexPostID;
		sIndexPostID = m_list.GetItemText(idx, 3);					// 포스트 아이디 가져오기
		int PostID = _ttoi(sIndexPostID);							// 형 변환
		extern CPostDB* postDB;						
		CPostDTO* post;
		post = postDB->dao.getPost(PostID);							// DB에서 해당 포스트 찾기
		CDetailPage dlg(post);										// 해당 포스트의 상세 페이지 선언
		dlg.DoModal();												// 상세 페이지 열기

		/*
		for (CPostDTO* post : postDB->postList) {
			if (post->GetPostID() == PostID) {
				CDetailPage dlg(post);
				dlg.DoModal();
				break;
			}
		}
		*/
	}
	*pResult = 0;
}
