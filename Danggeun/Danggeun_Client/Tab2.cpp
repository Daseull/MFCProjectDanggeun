﻿// Tab2.cpp: 구현 파일
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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_POST, &CTab2::OnDblclkListMyPost)
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


void CTab2::LoadMyPost() {

	//초기화
	int n = m_list.GetItemCount();
	while (n--)
		m_ImageList.Remove(0);
	m_list.DeleteAllItems();

	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;

	for (CPostDTO* post : postDB->postList) {
		if (post->GetUserID() == CurrentUser->GetUserID()) {
			CBitmap bmp;
			CImage img;
			img.Load("res\\" + post->GetImgName());
			if (img.IsNull()) {
				img.Load("res\\LoadError.png");
			}
			bmp.Attach(img);
			m_ImageList.Add(&bmp, RGB(255, 255, 255));

			int i = m_list.GetItemCount();
			m_list.AddItem(post->GetTitle(), i, 0, -1, i);
			m_list.AddItem("124800", i, 1);
			m_list.AddItem("거래완료", i, 2);
			//m_list.AddItem(post->GetPrice(), i, 1);
			//m_list.AddItem(post->GetState(), i, 2);

		}
	}

	//if userID == postDao.GetUser;
	//postDat.getImagePath
	//postDat.getTitle
	//postDao.getPrice
	
	//상세페이지
	//m_list.GetItemData(i)


	UpdateData(FALSE);
	
}

BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);
	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 390);
	m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);
	m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);

	LoadMyPost();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab2::OnDblclkListMyPost(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 글 상세 페이지.



	*pResult = 0;
}
