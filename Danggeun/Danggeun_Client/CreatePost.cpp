// CreatePost.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "CreatePost.h"
#include "afxdialogex.h"


// CCreatePost 대화 상자

IMPLEMENT_DYNAMIC(CCreatePost, CDialogEx)

CCreatePost::CCreatePost(CPostDTO* post, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_POST, pParent)
	, m_post(post)
	, m_strTitle(_T("글 제목을 작성해주세요"))
	, m_strPrice(_T("가격을 입력해주세요"))
	, m_strText(_T("동네에 올릴 게시글 내용을 작성해주세요(가품 및 판매금지품목은 게시가 제한 될 수 있어요.)"))
	
{
	

	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
}

CCreatePost::~CCreatePost()
{
}

void CCreatePost::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_POST, m_tMyButton1);
	DDX_Text(pDX, IDC_EDIT_POST_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_POST_PRICE, m_strPrice);
	DDX_Text(pDX, IDC_EDIT_POST_TEXT, m_strText);
	DDX_Control(pDX, IDC_COMBO_STATE, m_state);
	DDX_Control(pDX, IDC_STATIC_ADDPIC, m_stcImg);
}


BEGIN_MESSAGE_MAP(CCreatePost, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_POST, &CCreatePost::OnBnClickedButtonPost)
	ON_STN_CLICKED(IDC_STATIC_ADDPIC, &CCreatePost::OnStnClickedStaticAddpic)
	ON_BN_CLICKED(IDC_BUTTON_COMEDIT, &CCreatePost::OnClickedButtonComedit)
//	ON_COMMAND(IDOK, &CCreatePost::OnIdok)
END_MESSAGE_MAP()


// CCreatePost 메시지 처리기


HBRUSH CCreatePost::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	if (nCtlColor == CTLCOLOR_BTN) {
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(0, 200, 255));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


CString img_path = "";
BOOL CCreatePost::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (m_post != nullptr) {
		GetDlgItem(IDC_BUTTON_COMEDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POST)->ShowWindow(SW_HIDE);
		m_strTitle = m_post->GetTitle();
		m_strText = m_post->GetContent();
		m_strPrice = m_post->GetPrice();
		img_path = m_post->GetImgName();

		CImage img;
		img.Load("res\\small_" + m_post->GetImgName());
		HBITMAP h_bmp = (HBITMAP)img;
		m_stcImg.SetBitmap(h_bmp);
		img.Detach();
		UpdateData(FALSE);
	}

	else {
		GetDlgItem(IDC_BUTTON_COMEDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POST)->ShowWindow(SW_SHOW);
	}
	m_state.InsertString(0, "판매중");
	m_state.InsertString(1, "예약중");
	m_state.InsertString(2, "거래완료");
	m_state.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCreatePost::OnBnClickedButtonPost()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	extern CPostDB* postDB;
	UpdateData(TRUE);
	if (m_strTitle == "글 제목을 작성해주세요" || m_strPrice == "가격을 입력해주세요"
		|| m_strText == "동네에 올릴 게시글 내용을 작성해주세요(가품 및 판매금지품목은 게시가 제한 될 수 있어요.)"
		|| img_path == "") MessageBox("양식을 모두 입력해주세요!");
	else {
		extern CUserDTO* CurrentUser;
		CPostDTO post;
		post.SetTitle(m_strTitle);
		post.SetContent(m_strText);
		post.SetImgName(img_path);
		post.SetUserID(CurrentUser->GetUserID());
		post.SetTown(CurrentUser->GetTown());
		post.SetPrice(m_strPrice+"원");
		post.SetStauts(m_state.GetCurSel());
		postDB->dao.createPost(post);
		MessageBox("작성 완료 !");
		postDB->postList = postDB->dao.getAll();

		::SendMessage(((CCreatePost*)GetParent())->GetSafeHwnd(), UWM_CUSTOM3, 0, 0);
	}
	
}


void CCreatePost::OnClickedButtonComedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CPostDTO newpost;
	newpost.SetPostID(m_post->GetPostID());
	newpost.SetTitle(m_strTitle);
	newpost.SetImgName(img_path);
	newpost.SetContent(m_strText);
	extern CUserDTO* CurrentUser;
	newpost.SetTown(CurrentUser->GetTown());
	newpost.SetPrice(m_strPrice);
	newpost.SetStauts(m_state.GetCurSel());
	extern CPostDB* postDB;
	postDB->dao.updatePost(newpost);
	AfxMessageBox("수정 완료!");
	//SendMessage(IDCLOSE);

}


void CCreatePost::OnStnClickedStaticAddpic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szFilter[] = " All Files(*.*)|*.*|";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);
	if (IDOK == dlg.DoModal())
	{
		// 이미지 경로 획득
		img_path = dlg.GetPathName();
		CImage img;
		img.Load(img_path);
		
		while (img_path.Find("\\") != -1) {
			img_path = img_path.Mid(img_path.Find("\\") + 1);
		}

		CImage copyImg;
		copyImg.Create(60, 60, 24);
		img.StretchBlt(copyImg.GetDC(), 0, 0, 60, 60, 0, 0, 200,200, SRCCOPY);

		img.Save("res\\" + img_path);	
		copyImg.Save("res\\small_" + img_path);
		copyImg.ReleaseDC();
		img.Detach();

		
		CImage addpicresult;
		addpicresult.Load("res\\small_" + img_path);
		HBITMAP h_bmp = (HBITMAP)addpicresult;
		m_stcImg.SetBitmap(h_bmp);


		
		addpicresult.Detach();
	}
}







//void CCreatePost::OnIdok()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CDialogEx::Dest
//}


void CCreatePost::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}
