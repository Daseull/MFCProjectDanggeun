// Tab1.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab1.h"
#include "afxdialogex.h"



// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab1, pParent)
	, m_strSearch(_T(""))
	, m_strTown(_T(""))
{

	
}

CTab1::~CTab1()
{
}

//price에 단위 콤마 표시
//CString InsertComma(__int64 _llAmount)
//{
//	CString strAmount;
//	strAmount.Format(_T("%I64d"), _llAmount);
//
//	NUMBERFMT nFmt = { 0, 0, 3, _T("."), _T(","), 1 };
//
//	TCHAR szBuffer[64];
//	::GetNumberFormat(NULL, NULL, strAmount, &nFmt, szBuffer, sizeof(szBuffer));
//
//	strAmount = szBuffer;
//
//	return strAmount;
//}

void CTab1::Init()
{

	
	CImage img;
	img.Load("res\\1.BMP");
	if (img.IsNull()) AfxMessageBox("로드실패");

	CBitmap bmp;
	bmp.Attach(&img);

	m_ImageList.Create(40, 40, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_ImageList.Add(&bmp, RGB(0, 128, 128));

	
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);
	
	//스크롤 해도 글쓰기 버튼 안움직이게 하려고 
	GetDlgItem(IDC_BUTTON_NEWPOST)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	GetDlgItem(IDC_LIST1)->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	GetDlgItem(IDC_BUTTON_NEWPOST)->BringWindowToTop();

	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 80);

	LoadPostList();
}



void CTab1::LoadPostList()
{

	int n = 4;
	while (n--) {
		//얘네는 원래 get from db
		CString title, price;
		title = "커피 팔아요 얼죽아아아아아아아아";
		price = "7000원";
		//title = title.Left(8);

		int i = m_list.GetItemCount();
		m_list.AddItem(title, i, 0, -1, 0);
		m_list.AddItem(price, i, 1);

		i = m_list.GetItemCount();
		m_list.AddItem("cofffeparayo", i, 0, -1, 0);
		m_list.AddItem("7000원", i, 1);

	}

	UpdateData(FALSE);


}

void CTab1::SearchPost(CString Key)
{
	m_list.DeleteAllItems();
	
	if (Key.IsEmpty()) {
		AfxMessageBox("검색어를 입력하세요");
		return;
	}


	Key = Key.MakeUpper();
	
	
	CString str[3] = { "지금은 검색 테스트 중", "hihellobye", "커피 커피 커피" };
	int n = 3;
	
	for (int i = 0; i < n; i++) {
		CString title = str[i];
		if (str[i].MakeUpper().Find(Key) != -1) {
			int nItem = m_list.GetItemCount();
			m_list.AddItem(title, nItem, 0);
			m_list.AddItem("71000", nItem, 1);
		}
	}
	

	UpdateData(FALSE);
}



void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	//  DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_STATIC_TOWN, m_strTown);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab1::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTab1::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTab1::OnClickedButtonSearch)
END_MESSAGE_MAP()


// CTab1 메시지 처리기


void CTab1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
}


void CTab1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnCancel();
}


void CTab1::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CTab1::OnClickedButtonSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	SearchPost(m_strSearch);

}
