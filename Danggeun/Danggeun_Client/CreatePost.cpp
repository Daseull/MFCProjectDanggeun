// CreatePost.cpp: 구현 파일
//글 작성하기 페이지

#include "pch.h"
#include "Danggeun_Client.h"
#include "CreatePost.h"
#include "afxdialogex.h"


// CCreatePost 대화 상자
IMPLEMENT_DYNAMIC(CCreatePost, CDialogEx)
CString img_path = "";

//생성자
CCreatePost::CCreatePost(CPostDTO* post, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_POST, pParent)
	, m_post(post)
	, m_strTitle(_T("글 제목을 작성해주세요"))
	, m_strPrice(_T("가격을 입력해주세요"))
	, m_strText(_T("동네에 올릴 게시글 내용을 작성해주세요(가품 및 판매금지품목은 게시가 제한 될 수 있어요.)"))
	
{
	//변수 초기화
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
}

//해제자
CCreatePost::~CCreatePost()
{
}

//컨트롤의 값 변환
void CCreatePost::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_POST, m_tMyButton1);
	DDX_Text(pDX, IDC_EDIT_POST_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_POST_PRICE, m_strPrice);
	DDX_Text(pDX, IDC_EDIT_POST_TEXT, m_strText);
	DDX_Control(pDX, IDC_COMBO_STATE, m_state);
	DDX_Control(pDX, IDC_STATIC_ADDPIC, m_stcImg);
	DDX_Control(pDX, IDC_BUTTON_COMEDIT, m_tMyButton2);
}

//멤버함수 
BEGIN_MESSAGE_MAP(CCreatePost, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_POST, &CCreatePost::OnBnClickedButtonPost)
	ON_STN_CLICKED(IDC_STATIC_ADDPIC, &CCreatePost::OnStnClickedStaticAddpic)
	ON_BN_CLICKED(IDC_BUTTON_COMEDIT, &CCreatePost::OnClickedButtonComedit)
END_MESSAGE_MAP()


// CCreatePost 메시지 처리기

//다이아로그의 배경색상 칠하기
HBRUSH CCreatePost::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//여기서 DC의 특성을 변경합니다.
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


BOOL CCreatePost::OnInitDialog()		// 다이얼로그 초기화
{
	CDialogEx::OnInitDialog();
	if (m_post != nullptr) {									// 수정 상황일 때
		GetDlgItem(IDC_BUTTON_COMEDIT)->ShowWindow(SW_SHOW);	// 수정하기 버튼 보이게 하기
		GetDlgItem(IDC_BUTTON_POST)->ShowWindow(SW_HIDE);		// 완료 버튼 숨기기
		m_strTitle = m_post->GetTitle();						// 글 제목 받아오기
		m_strText = m_post->GetContent();						// 글 내용 받아오기
		m_strPrice = m_post->GetPrice();						// 상품 가격 받아오기
		img_path = m_post->GetImgName();						// 이미지 경로 받아오기

		CImage img;
		img.Load("res\\small_" + m_post->GetImgName());			// 이미지 로드
		HBITMAP h_bmp = (HBITMAP)img;							// 이미지 자료형 비트맵으로 변경
		m_stcImg.SetBitmap(h_bmp);								// 컨트롤에 이미지 설정
		img.Detach();											// 이미지 객체 윈도우와 분리
		UpdateData(FALSE);
	}

	else {														// 글쓰기 상황일 때
		GetDlgItem(IDC_BUTTON_COMEDIT)->ShowWindow(SW_HIDE);	// 수정 버튼 숨기기
		GetDlgItem(IDC_BUTTON_POST)->ShowWindow(SW_SHOW);		// 완료 버튼 보이기

	}
	// 콤보박스 상태 추가
	m_state.InsertString(0, "판매중");		
	m_state.InsertString(1, "예약중");
	m_state.InsertString(2, "거래완료");
	m_state.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CCreatePost::OnBnClickedButtonPost()	// 작성 완료 버튼 클릭 시
{
	extern CPostDB* postDB;
	UpdateData(TRUE);
	// 양식을 모두 입력하지 않았을 경우
	if (m_strTitle == "글 제목을 작성해주세요" || m_strPrice == "가격을 입력해주세요"
		|| m_strText == "동네에 올릴 게시글 내용을 작성해주세요(가품 및 판매금지품목은 게시가 제한 될 수 있어요.)"
		|| img_path == "") MessageBox("양식을 모두 입력해주세요!");
	else {											// 양식을 모두 입력했을 경우
		extern CUserDTO* CurrentUser;
		CPostDTO post;								// post DTO 객체 선언
		post.SetTitle(m_strTitle);					// 포스트의 제목 설정
		post.SetContent(m_strText);					// 포스트의 내용 설정
		post.SetImgName(img_path);					// 포스트의 이미지 경로 설정
		post.SetUserID(CurrentUser->GetUserID());	// 포스트의 사용자 ID 설정
		post.SetTown(CurrentUser->GetTown());		// 포스트의 동네 설정
		post.SetPrice(m_strPrice);					// 포스트의 가격 설정
		post.SetStauts(m_state.GetCurSel());		// 포스트의 상태 설정
		postDB->dao.createPost(post);				// DB에 포스트 추가
		MessageBox("작성 완료 !");
		postDB->postList = postDB->dao.getAll();	// 포스트 DB 동기화
		::SendMessage(((CCreatePost*)GetParent())->GetSafeHwnd(), UWM_CUSTOM3, 0, 0);	// 메인 다이얼로그에 작성완료 메시지 보내기
	}
	
}


void CCreatePost::OnClickedButtonComedit()			// 수정 버튼 클릭 시
{
	UpdateData(TRUE);
	m_post->SetTitle(m_strTitle);					// 원래 있던 포스트의 제목 설정
	m_post->SetImgName(img_path);					// 원래 있던 포스트의 이미지 경로 설정
	m_post->SetContent(m_strText);					// 원래 있던 포스트의 내용 설정
	extern CUserDTO* CurrentUser;
	m_post->SetTown(CurrentUser->GetTown());		// 원래 있던 포스트의 동네 설정
	m_post->SetPrice(m_strPrice);					// 원래 있던 포스트의 가격 설정
	m_post->SetStauts(m_state.GetCurSel());			// 원래 있던 포스트의 상태 설정

	CPostDTO newpost;
	newpost.SetPostID(m_post->GetPostID());			// 새로 작성한 포스트의 ID 설정
	newpost.SetTitle(m_strTitle);					// 새로 작성한 포스트의 제목 설정
	newpost.SetImgName(img_path);					// 새로 작성한 포스트의 이미지 경로 설정
	newpost.SetContent(m_strText);					// 새로 작성한 포스트의 내용 설정
	extern CUserDTO* CurrentUser;
	newpost.SetTown(CurrentUser->GetTown());		// 새로 작성한 포스트의 동네 설정
	newpost.SetPrice(m_strPrice);					// 새로 작성한 포스트의 가격 설정
	newpost.SetStauts(m_state.GetCurSel());			// 새로 작성한 포스트의 상태 설정
	extern CPostDB* postDB;

	postDB->dao.updatePost(newpost);				// 포스트 수정
	postDB->postList = postDB->dao.getAll();		// 포스트 DB 동기화
	AfxMessageBox("수정 완료!");
}

void CCreatePost::OnStnClickedStaticAddpic()
{
	char szFilter[] = " All Files(*.*)|*.*|";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);	// 파일 가져오는 dlg 생성
	if (IDOK == dlg.DoModal())										// 파일 가져오는 dlg 열기
	{	
		img_path = dlg.GetPathName();								// 이미지 경로 획득
		CImage img;
		img.Load(img_path);											// 이미지 로드
		while (img_path.Find("\\") != -1) {							
			img_path = img_path.Mid(img_path.Find("\\") + 1);
		}

		CImage copyImg;
		copyImg.Create(60, 60, 24);												
		img.StretchBlt(copyImg.GetDC(), 0, 0, 60, 60, 0, 0, 200,200, SRCCOPY);	// 이미지 복사

		img.Save("res\\" + img_path);						// 이미지 저장
		copyImg.Save("res\\small_" + img_path);
		copyImg.ReleaseDC();								// DC 해제
		img.Detach();

		
		CImage addpicresult;
		addpicresult.Load("res\\small_" + img_path);		// 이미지 로드
		HBITMAP h_bmp = (HBITMAP)addpicresult;				// 이미지 형식 비트맵으로 변환
		m_stcImg.SetBitmap(h_bmp);							// 컨트롤에 이미지 설정
		addpicresult.Detach();
	}
}

