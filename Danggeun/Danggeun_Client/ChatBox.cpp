// ChatBox.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "ChatBox.h"
#include "afxdialogex.h"


// ChatBox 대화 상자

IMPLEMENT_DYNAMIC(ChatBox, CDialogEx)

ChatBox::ChatBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATBOX, pParent)
	, m_strSend(_T(""))
{

}

ChatBox::~ChatBox()
{
}

void ChatBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDC_CHATBOX, m_list);
}


BEGIN_MESSAGE_MAP(ChatBox, CDialogEx)
	ON_MESSAGE(UM_RECEIVE, (LRESULT(_cdecl CWnd::*)(WPARAM, LPARAM))OnReceive)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &ChatBox::OnBnClickedButtonSend)
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
	
}
