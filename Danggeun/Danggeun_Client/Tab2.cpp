// Tab2.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab2.h"
#include "afxdialogex.h"
#include "afxwin.h"


// CTab2 대화 상자

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab2, pParent)
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POST, m_list);
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab2::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTab2 메시지 처리기


void CTab2::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTab2::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


HBRUSH CTab2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CTab2::Init()
{
	m_ImageList.Create(40, 40, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 80);

	LoadMyPost();
}

void CTab2::LoadMyPost() {

	//초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();


	//if userID == postDao.GetUser;
	//postDat.getImagePath
	//postDat.getTitle
	//postDao.getPrice
	
	//상세페이지
	//m_list.GetItemData(i)


	UpdateData(FALSE);
	
}