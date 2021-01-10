// Tab1.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab1.h"
#include "afxdialogex.h"
#include "ChatBox.h"



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

void CTab1::LoadPostList()
{


	CImage img;
	img.Load("res\\1.bmp");
	if (img.IsNull()) AfxMessageBox("로드실패");

	CBitmap bmp;
	bmp.Attach(img);


	//CImageList ImgList;
	//ImgList.Add(&bmp, RGB(255, 255, 255));
	//m_list.SetImageList(&ImgList, LVSIL_NORMAL);
	//AfxMessageBox(ImgList.GetImageCount());

	

	
	//m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 180);
	//m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 70);

	int n = 3;
	while (n--) {
		//얘네는 원래 get from db
		CString title, price;
		title = "커피 팔아요 얼죽아아아아아아아아";
		price = "7000원";
		//CString price = "7,000원\n";
		//price.Format("%s", (char*)"7000원");

		title = title.Left(8);
		int i = m_list.GetItemCount();
		m_list.AddItem("cofffe parayo", i, 0, -1, 0);
		m_list.AddItem("7000원", i, 1);
	}

	UpdateData(FALSE);


}

void CTab1::SearchPost(CString Key)
{

	/*
	CString title, price;
	title = getTitle();
	if (title.Find(Key)) {
		title = title.Left(8);
		price = getPrice();

		int i = m_list.GetItemCount();
		m_list.AddItem(i, title, 0);
		m_list.AddItem(i, price, 0);
	}
	*/

	UpdateData(FALSE);
}

void CTab1::Init()
{

	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 180);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 70);

	LoadPostList();
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
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTab1::OnClickList1)
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
	UpdateData(FALSE);
	SearchPost(m_strSearch);

}

void CTab1::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox("List Clicked!");
	ChatBox dlg = new ChatBox;
	dlg.DoModal();
	*pResult = 0;
	/*
	// 행 클릭시 행 넘버값 받아오기
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int idx = pNMListView->iItem;

	// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	CString sIndexValue;
	sIndexValue = m_list.GetItemText(idx, 1);

	if (idx != -1) {
		ChatBox dlg = new ChatBox;
		dlg.DoModal();
	}
	*/
}
