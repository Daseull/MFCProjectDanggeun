// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab3.h"
#include "afxdialogex.h"
#include "RoundButton2.h"
#include "RoundButtonStyle.h"

// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
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

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
	DDX_Text(pDX, IDC_STATIC_TOWN, m_strTown);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_tMyButton2);
	//  DDX_Control(pDX, IDC_LIST_HEART, m_list);
	DDX_Control(pDX, IDC_LIST_HEART, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_strSearch);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab3::OnBnClickedCancel)
//	ON_LBN_SELCHANGE(IDC_LIST_HEART, &CTab3::OnLbnSelchangeListHeart)
ON_WM_CTLCOLOR()
ON_STN_CLICKED(IDCANCEL, &CTab3::OnStnClickedCancel)
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTab3::OnBnClickedButtonSearch)
ON_BN_CLICKED(IDC_BUTTON_BACK, &CTab3::OnBnClickedButtonBack)
END_MESSAGE_MAP()


// CTab3 메시지 처리기


void CTab3::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTab3::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}




HBRUSH CTab3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CTab3::OnStnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	extern CString town[];
	extern CUserDTO* CurrentUser;
	m_strTown = town[CurrentUser->GetTown()];
	UpdateData(FALSE);

	m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);
	m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);

	LoadBookmarkPost();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTab3::LoadBookmarkPost() {

	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_HIDE);
	//초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	extern CString status[3];
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
					int i = m_list.GetItemCount();	// 이미지 순서 맞는지 확인하기
					m_list.AddItem(post->GetTitle(), i, 0, -1, i);
					m_list.AddItem(post->GetPrice(), i, 1);
					m_list.AddItem(status[post->GetStatus()], i, 2);
				}
			}
		}
	}
	UpdateData(FALSE);
}


void CTab3::SearchPost(CString Key)
{
	//TO DO: 뒤로가기 버튼 보이기는 여기에 해주세요
	GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_SHOW);

	//초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	if (Key.IsEmpty()) {
		AfxMessageBox("검색어를 입력하세요");
		return;
	}

	Key = Key.MakeUpper();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	extern CString status[3];
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
					}
				}
			}
		}
	}

	UpdateData(FALSE);
}


void CTab3::OnBnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	SearchPost(m_strSearch);
}


void CTab3::OnBnClickedButtonBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadBookmarkPost();
}
