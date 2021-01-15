// ChatBox.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "ChatBox.h"
#include "afxdialogex.h"
#include "DetailPage.h"

// ChatBox 대화 상자

IMPLEMENT_DYNAMIC(ChatBox, CDialogEx)

ChatBox::ChatBox(CWnd* pParent /*=nullptr*/)				// 생성자
	: CDialogEx(IDD_CHATBOX, pParent)
	, m_strSend(_T(""))										
{
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
}


ChatBox::~ChatBox()
{
}

void ChatBox::DoDataExchange(CDataExchange* pDX)			// 컨트롤 - 변수 동기화
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_CHATBOX, m_list);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_price);
}


BEGIN_MESSAGE_MAP(ChatBox, CDialogEx)
	ON_MESSAGE(UM_RECEIVE, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnReceive)	// 서버로 부터 메시지 받을 때
	ON_BN_CLICKED(IDC_BUTTON_SEND, &ChatBox::OnBnClickedButtonSend)						// 보내기 버튼 클릭했을 때
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ChatBox 메시지 처리기
LPARAM ChatBox::OnReceive(UINT wParam, LPARAM IParam) {

	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);			// 변수 초기화

	m_socCom.Receive(pTmp, 256);		// 서버가 보낸 문자열 받아옴
	strTmp.Format(_T("%s"), pTmp);

	int i = m_list.GetCount();			// 리스트에 채팅 내용 출력
	m_list.InsertString(i, strTmp);
	return TRUE;

}

BOOL ChatBox::OnInitDialog()			// 다이얼로그 초기화
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);
	m_socCom.Create();						// 접속용 소켓 생성
	m_socCom.Connect("127.0.0.1", 21000);	// 서버에 접속
	m_socCom.Init(this->m_hWnd);			// 메인 핸들러 받아옴

	//제목
	CFont font1;
	LOGFONT lf1;
	::ZeroMemory(&lf1, sizeof(lf1));
	lf1.lfHeight = 20;
	lf1.lfWeight = FW_EXTRABOLD;
	::lstrcpy(lf1.lfFaceName, "나눔고딕");
	font1.CreateFontIndirectA(&lf1);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&font1);
	font1.Detach();

	//가격
	CFont font6;
	LOGFONT lf6;
	::ZeroMemory(&lf6, sizeof(lf6));
	lf6.lfHeight = 16;
	lf6.lfWeight = FW_BOLD;
	::lstrcpy(lf6.lfFaceName, "나눔고딕");

	font6.CreateFontIndirectA(&lf6);
	GetDlgItem(IDC_STATIC_PRICE)->SetFont(&font6);
	font6.Detach();



	m_image.Load("res\\small_" + ((CDetailPage*)GetParent())->m_post->GetImgName());// 이미지 경로 받아옴
	HBITMAP h_bmp = (HBITMAP)m_image;												// 이미지 비트맵으로 변환
	m_picture.SetBitmap(h_bmp);														// 컨트롤에 표시할 비트맵 지정

	m_title.SetWindowTextA(((CDetailPage*)GetParent())->m_post->GetTitle());		// 글 제목 받아옴
	m_price.SetWindowTextA(((CDetailPage*)GetParent())->m_post->GetPrice());		// 상품 가격 받아옴


	return TRUE;  
}


void ChatBox::OnBnClickedButtonSend()		// 전송 버튼 클릭했을때
{
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);			// 변수 초기화
	strcpy_s(pTmp, m_strSend);			// edit 컨트롤에 입력된 내용 변수에 복사
	m_socCom.Send(pTmp, 256);			// 서버에 문자열 보내기

	strTmp.Format(_T("%s"), pTmp);		// 변수 형 변환
	int i = m_list.GetCount();			// 리스트에 저장된 항목 개수 받아오기
	m_list.InsertString(i, strTmp);		// 리스트의 마지막 인덱스에 문자열 추가

	m_strSend.Empty();					// edit 컨트롤 비우기
	UpdateData(FALSE);
	
}

//다이아로그의 배경색상 칠하기
HBRUSH ChatBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// 여기서 DC의 특성을 변경합니다.
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

void ChatBox::OnIdok()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnBnClickedButtonSend();
}
