#include "pch.h"
#include "Danggeun_Client.h"
#include "JoinDlg.h"
#include "afxdialogex.h"
#include "UserDB.h"

IMPLEMENT_DYNAMIC(JoinDlg, CDialogEx)
JoinDlg::JoinDlg(CWnd* pParent /*=nullptr*/)				// 생성자
	: CDialogEx(IDD_DIALOG_JOIN, pParent)
	, m_strID(_T(""))
	, m_strPHONE(_T(""))
	, m_strPW(_T(""))
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
}
JoinDlg::~JoinDlg()
{
}
void JoinDlg::DoDataExchange(CDataExchange* pDX)			// 컨트롤 - 변수 동기화
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JOIN_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_JOIN_PHONE, m_strPHONE);
	DDX_Text(pDX, IDC_EDIT_JOIN_PW, m_strPW);
	DDX_Control(pDX, IDC_COMBO1, m_Town);
	DDX_Control(pDX, IDC_BUTTON_JOIN_OK, m_tMyButton1);
	DDX_Control(pDX, IDC_COMBO_JOIN_TOWN, m_Town);
}
BEGIN_MESSAGE_MAP(JoinDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_JOIN_OK, &JoinDlg::OnBnClickedButtonJoinOk)	// 회원 가입 버튼 클릭시
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void JoinDlg::OnBnClickedButtonJoinOk()			// 회원 가입 버튼 클릭시
{
	extern CUserDB* userDB;						
	userDB = new CUserDB();						// new keyword -> pointer
	userDB->InitDB();							// 데이터베이스 파일 생성 및 열기
	
	int town;									
	town = m_Town.GetCurSel();					// 동네 콤보박스 인덱스 받아오기

	UpdateData(TRUE);
	if (m_strID.GetLength() == 0 || m_strPW.GetLength() == 0 || m_strPHONE.GetLength() == 0)	// 회원가입 양식이 모두 입력되지 않았을 경우
		MessageBox("fill out all forms");														
	else {															// 양식 모두 입력했을 경우
		CUserDTO* user;
		user = userDB->dao.getUser(m_strID);						// 중복된 아이디 있는지 확인
		if(user) AfxMessageBox("Please use a different ID");		// 중복된 아이디 있을 경우
		else {														// 중복된 아이디 없을 경우
			CUserDTO user;											// 사용자 DTO 객체 선언
			user.SetUserID(m_strID);								// ID 설정
			user.SetUserPW(m_strPW);								// PW 설정
			user.SetTown(town);										// 동네 설정
			user.SetPhone(m_strPHONE);								// 전화번호 설정
			userDB->dao.createUser(user);							// 데이터베이스에 사용자 정보추가
			AfxMessageBox("Join Success !");
			::SendMessage(((JoinDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM2, 0, 0);	// 로그인 다이얼로그에 메시지 보내기
		}
	}
	
}

//다이아로그의 배경색상 칠하기
HBRUSH JoinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL JoinDlg::OnInitDialog()		// 다이얼로그 초기화
{
	CDialogEx::OnInitDialog();

	// 입력 양식 모두 공백으로 보이게 하기
	GetDlgItem(IDC_EDIT_JOIN_ID)->SetWindowTextA("");	
	GetDlgItem(IDC_EDIT_JOIN_PW)->SetWindowTextA("");
	GetDlgItem(IDC_EDIT_JOIN_PHONE)->SetWindowTextA("");
	GetDlgItem(IDC_COMBO_JOIN_TOWN)->SetWindowTextA("");
	UpdateData(TRUE);

	return TRUE; 
}



BOOL JoinDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)	// 엔터 버튼 클릭했을 때
		OnBnClickedButtonJoinOk();									// 회원가입 버튼 클릭 시의 함수 호출
	return CDialogEx::PreTranslateMessage(pMsg);
}
