// ChatBox.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "ChatBox.h"
#include "afxdialogex.h"
#include "DetailPage.h"

// ChatBox 대화 상자

IMPLEMENT_DYNAMIC(ChatBox, CDialogEx)

ChatBox::ChatBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATBOX, pParent)
	, m_strSend(_T(""))
{
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
}


ChatBox::~ChatBox()
{
}

void ChatBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_CHATBOX, m_list);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_tMyButton1);
	//  DDX_Control(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_picture);
	//  DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_price);
}


BEGIN_MESSAGE_MAP(ChatBox, CDialogEx)
	ON_MESSAGE(UM_RECEIVE, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM))OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &ChatBox::OnBnClickedButtonSend)
	ON_WM_CTLCOLOR()
	ON_COMMAND(IDOK, &ChatBox::OnIdok)
END_MESSAGE_MAP()


// ChatBox 메시지 처리기

LPARAM ChatBox::OnReceive(UINT wParam, LPARAM IParam) {

	char pTmp[256];
	CString strTmp;
	memset(pTmp, '\0', 256);

	m_socCom.Receive(pTmp, 256);
	strTmp.Format(_T("%s"), pTmp);

	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);
	return TRUE;

}

BOOL ChatBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);
	m_socCom.Create();
	m_socCom.Connect("127.0.0.1", 5000);
	m_socCom.Init(this->m_hWnd);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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



	m_image.Load("res\\small_" + ((CDetailPage*)GetParent())->m_post->GetImgName());
	HBITMAP h_bmp = (HBITMAP)m_image;
	m_picture.SetBitmap(h_bmp);

	m_title.SetWindowTextA( ((CDetailPage*)GetParent())->m_post->GetTitle());
	m_price.SetWindowTextA(((CDetailPage*)GetParent())->m_post->GetPrice());

	//UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ChatBox::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	char pTmp[256];
	CString strTmp;

	memset(pTmp, '\0', 256);
	strcpy_s(pTmp, m_strSend);
	m_socCom.Send(pTmp, 256);

	strTmp.Format(_T("%s"), pTmp);
	int i = m_list.GetCount();
	m_list.InsertString(i, strTmp);

	m_strSend.Empty();
	UpdateData(FALSE);
	
}


HBRUSH ChatBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void ChatBox::OnIdok()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnBnClickedButtonSend();
}
