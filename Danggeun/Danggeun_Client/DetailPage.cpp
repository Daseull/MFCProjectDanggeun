// DetailPage.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "DetailPage.h"
#include "afxdialogex.h"
#include "ChatBox.h"
#include "afxwin.h"
#include "CreatePost.h"
#include "Danggeun_ClientDlg.h"

// CDetailPage 대화 상자

IMPLEMENT_DYNAMIC(CDetailPage, CDialogEx)

//생성자
CDetailPage::CDetailPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)

{
	//그리기(디자인)용 변수 초기화
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton3.SetRoundButtonStyle(&m_tMyButtonStyle);

}

//실제 호출되는 생성자( 인자로 글에 대한 객체를 갖는다 )
CDetailPage::CDetailPage(CPostDTO* post, CWnd* pParent) 
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
	,m_post(post) 

{
	
	//그리기(디자인)용 변수 초기화
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton3.SetRoundButtonStyle(&m_tMyButtonStyle);

}

CDetailPage::~CDetailPage()
{
}

void CDetailPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHAT, m_tMyButton1);
	DDX_Control(pDX, IDC_STATIC_ID, m_stcUserID);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_stcPicture);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_stcPrice);
	DDX_Control(pDX, IDC_STATIC_STATE, m_stcState);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_stcText);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_TOWN, m_stcTown);
	DDX_Control(pDX, IDC_BUTTON_HEART, m_btnheart);
	DDX_Control(pDX, IDC_BUTTON_POSTEDIT, m_tMyButton3);
}


// CDetailPage 메시지 처리기
BEGIN_MESSAGE_MAP(CDetailPage, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_HEART, &CDetailPage::OnBnClickedButtonHeart)
	ON_BN_CLICKED(IDC_BUTTON_POSTEDIT, &CDetailPage::OnClickedButtonPostedit)
	ON_BN_CLICKED(IDC_BUTTON_CHAT, &CDetailPage::OnClickedButtonChat)
END_MESSAGE_MAP()



//다이얼로그의 배경 색상 칠하기
HBRUSH CDetailPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}
	//사용자의 id 스태틱에 대한 색상 설정
	if (m_stcUserID.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253,212,129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	//사용자의 town 스태틱에 대한 색상 설정 
	else if (m_stcTown.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	//상품의 state 스태틱에 대한 색상 설정 
	else if (m_stcState.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 169, 76));
		return m_bk_brush;
	}
	//상품의 text 스태틱에 대한 색상 설정 
	else if (m_stcText.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_bk_brush;
	}
	//상품의 price 스태틱에 대한 색상 설정
	else if (m_stcPrice.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(61, 149, 255));
		return m_bk_brush;
	}
	//스태틱일 때 색상 설정
	else if (nCtlColor==CTLCOLOR_STATIC) {
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



BOOL CDetailPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//글씨체 설정
	//제목 
	CFont font1;
	LOGFONT lf1;
	::ZeroMemory(&lf1, sizeof(lf1));
	lf1.lfHeight = 22;
	lf1.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf1.lfFaceName, "나눔고딕");
	font1.CreateFontIndirectA(&lf1);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&font1);
	font1.Detach();

	//내용 
	CFont font2;
	LOGFONT lf2;
	::ZeroMemory(&lf2, sizeof(lf2));
	lf2.lfHeight = 18;
	lf2.lfWeight = FW_NORMAL;
	::lstrcpy(lf2.lfFaceName, "나눔고딕");

	font2.CreateFontIndirectA(&lf2);
	GetDlgItem(IDC_STATIC_TEXT)->SetFont(&font2);
	font2.Detach();

	//아이디 
	CFont font3;
	LOGFONT lf3;
	::ZeroMemory(&lf3, sizeof(lf3));
	lf3.lfHeight = 19;
	lf3.lfWeight = FW_SEMIBOLD;
	::lstrcpy(lf3.lfFaceName, "나눔고딕");

	font3.CreateFontIndirectA(&lf3);
	GetDlgItem(IDC_STATIC_ID)->SetFont(&font3);
	font3.Detach();

	//동네 
	CFont font4;
	LOGFONT lf4;
	::ZeroMemory(&lf4, sizeof(lf4));
	lf4.lfHeight = 16;
	lf4.lfWeight = FW_LIGHT;
	::lstrcpy(lf4.lfFaceName, "나눔고딕");

	font4.CreateFontIndirectA(&lf4);
	GetDlgItem(IDC_STATIC_TOWN)->SetFont(&font4);
	font4.Detach();

	//판매 상태 
	CFont font5;
	LOGFONT lf5;
	::ZeroMemory(&lf5, sizeof(lf5));
	lf5.lfHeight = 18;
	lf5.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf5.lfFaceName, "나눔고딕");

	font5.CreateFontIndirectA(&lf5);
	GetDlgItem(IDC_STATIC_STATE)->SetFont(&font5);
	font5.Detach();

	//가격 
	CFont font6;
	LOGFONT lf6;
	::ZeroMemory(&lf6, sizeof(lf6));
	lf6.lfHeight = 20;
	lf6.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf6.lfFaceName, "나눔고딕");

	font6.CreateFontIndirectA(&lf6);
	GetDlgItem(IDC_STATIC_PRICE)->SetFont(&font6);
	font6.Detach();

	
	//관심 처리
	//Danggeun_ClientDlg에 선언된 DB 접근용 객체들 
	extern CUserDTO* CurrentUser;
	extern CBookMarkDB* bookmarkDB;

	//글 작성자인 경우 수정버튼 활성화, 채팅/관심 버튼 비활성화
	if (m_post->GetUserID() == CurrentUser->GetUserID()) {
		GetDlgItem(IDC_BUTTON_POSTEDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_HEART)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CHAT)->ShowWindow(SW_HIDE);
	}

	//글 작성자 아닌경우
	else {
		//수정버튼 비활성화, 채팅/관심 버튼 활성화
		GetDlgItem(IDC_BUTTON_POSTEDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_HEART)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_CHAT)->ShowWindow(SW_SHOW);

		//관심등록 한 글이라면 관심버튼을 꽉 찬 하트 모양으로
		if (bookmarkDB->dao.getBookMarkByUserAndPost(CurrentUser->GetUserID(), m_post->GetPostID()) != NULL) {
			m_btnheart.LoadBitmaps(IDB_HEART2, NULL, NULL, NULL);
			m_btnheart.SizeToContent();
		}
		//관심등록 안 한 글이라면 관심버튼을 빈 하트 모양으로
		else {
			m_btnheart.LoadBitmaps(IDB_HEART, NULL, NULL, NULL);
			m_btnheart.SizeToContent();
		}
	}

	//LoadDetailPage()를 호출하여 글 내용 채움
	LoadDetailPage();
	return TRUE;  // return TRUE unless you set the focus to a control
}



//관심 버튼을 눌렀을 때
void CDetailPage::OnBnClickedButtonHeart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//Danggeul_ClientDlg 에 선언된 DB 접근 객체
	extern CUserDTO* CurrentUser;
	extern CPostDB* postDB;
	extern CBookMarkDB* bookmarkDB;
	
	//사용자id와 포스트 id로 북마크 기록 조회
	CBookMarkDTO* bookmark;
	bookmark = bookmarkDB->dao.getBookMarkByUserAndPost(CurrentUser->GetUserID(), m_post->GetPostID());
	
	//북마크가 안되어 있는 경우(관심리스트 추가)
	if (bookmark == NULL) {
		//관심 버튼 모양을 꽉 찬 하트로 변경
		m_btnheart.LoadBitmaps(IDB_HEART2, NULL, NULL, NULL);
		m_btnheart.SizeToContent();
		
		//알림메세지 생성
		MessageBox("관심리스트 추가!");
		
		//북마크 db 에 새 북마크 객체 추가
		CBookMarkDTO newbookmark;
		newbookmark.SetPostID(m_post->GetPostID());
		newbookmark.SetUserID(CurrentUser->GetUserID());
		bookmarkDB->dao.createBookMark(newbookmark);
	}

	//북마크가 되어 있는 경우(관심리스트에서 삭제)
	else {
		//관심버튼 모양을 빈 하트로 변경
		m_btnheart.LoadBitmaps(IDB_HEART, NULL, NULL, NULL);
		m_btnheart.SizeToContent();
		
		//알림메세지 생성
		MessageBox("관심리스트 삭제!");
		
		//북마크 db에서 해당 북마크 객체 삭제
		for (CBookMarkDTO* book : bookmarkDB->dao.getAllByUser(CurrentUser->GetUserID())) {
			if (m_post->GetPostID() == book->GetPostID()) {
				bookmarkDB->dao.deleteBookMark(book->GetBookMarkID());
			}
		}

	}

	//새로 업데이트 된 북마크 정보 가져오기
	bookmarkDB->bookMarkList = bookmarkDB->dao.getAll();
	//관심리스트도 업데이트
	((CDanggeunClientDlg*)GetParent())->pDlg3->LoadBookmarkPost();
}


//글수정 창 변수
CCreatePost* dlg;

void CDetailPage::OnClickedButtonPostedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//포스트 디티오 객체를 전달해 수정창 생성
	dlg = new CCreatePost(m_post);
	dlg->DoModal();

	//수정된 정보로 상세페이지 업데이트
	LoadDetailPage();
	//수정된 정보로 다른 탭 업데이트
	((CDanggeunClientDlg*)GetParent())->pDlg1->LoadTownPost();
	((CDanggeunClientDlg*)GetParent())->pDlg2->LoadMyPost();
	((CDanggeunClientDlg*)GetParent())->pDlg3->LoadBookmarkPost();
}


//상세페이지의 내용 채우기
void CDetailPage::LoadDetailPage()
{

	//해당글의 상품 이미지 로드
	CImage itemimage;
	itemimage.Load("res\\" + m_post->GetImgName());
	//이미지 로드 실패했을 경우 깨진 이미지 출력
	if (itemimage.IsNull()) {
		itemimage.Load("res\\LoadError.png");
	}

	//이미지 부착
	HBITMAP h_bmp = (HBITMAP)itemimage;
	CBitmap bmp;
	m_stcPicture.SetBitmap(h_bmp);
	itemimage.Detach();

	//판매자 아이디, 글 제목, 글 내용, 가격 셋팅
	m_stcUserID.SetWindowText("판매자\t" + m_post->GetUserID());
	m_stcTitle.SetWindowText(m_post->GetTitle());
	m_stcText.SetWindowText(m_post->GetContent());
	m_stcPrice.SetWindowText(m_post->GetPrice());

	//동네, 판매상태 셋팅
	extern CString town[];
	m_stcTown.SetWindowText(town[m_post->GetTown()]);
	extern CString status[];
	m_stcState.SetWindowText(status[m_post->GetStatus()]);
	
	UpdateData(FALSE);
}


//채팅으로 거래하기 버튼 눌렀을 때
void CDetailPage::OnClickedButtonChat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChatBox dlg;	//채팅 창 생성
	dlg.DoModal();
}
