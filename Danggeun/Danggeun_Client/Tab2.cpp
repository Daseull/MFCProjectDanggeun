// Tab2.cpp: 구현 파일
//내 글 목록

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab2.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "DetailPage.h"


// CTab2 대화 상자

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)
//생성자
CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab2, pParent)
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
}

//해제자
CTab2::~CTab2()
{
}

//컨트롤의 값 변환
void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POST, m_list);
}

//멤버함수
BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab2::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_POST, &CTab2::OnDblclkListMyPost)
END_MESSAGE_MAP()


// CTab2 메시지 처리기

//확인버튼 비활성화 
void CTab2::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}

//취소버튼 비활성화
void CTab2::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}

//다이아로그의 배경색상 칠하기
HBRUSH CTab2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정 
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}

	return hbr;
}

//내 글 목록 가져오기
void CTab2::LoadMyPost() {

	//초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CString status[3];

	//사용자가 작성한 글 가져오기 
	for (CPostDTO* post : postDB->dao.getAllByUser(CurrentUser->GetUserID())) {
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

//다이아로그의 초기상태 설정
BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//이미지 목록 생성 및 크기 지정 
	m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

	//스크롤 해도 글쓰기 버튼 안움직이게 하려고 
	GetDlgItem(IDC_LIST_POST)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	
	//글 목록의 항목 생성
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 390);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);
	m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);
	m_list.InsertColumn(3, "postID", LVCFMT_RIGHT, 0);

	//내가 작성한 글 목록 가져오기
	LoadMyPost();

	return TRUE;  
}

//글목록 중 특정 글 클릭했을 때
void CTab2::OnDblclkListMyPost(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int idx = pNMListView->iItem;

	// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	if (idx != -1) {
		CString sIndexPostID;
		sIndexPostID = m_list.GetItemText(idx, 3);
		int PostID = _ttoi(sIndexPostID);
		extern CPostDB* postDB;

		//상세페이지창 생성하기
		CDetailPage dlg(postDB->dao.getPost(PostID));
		dlg.DoModal();
	}
	*pResult = 0;

}