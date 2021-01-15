// LoginDlg.cpp: 구현 파일


#include "pch.h"
#include "Danggeun_Client.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "JoinDlg.h"
#include "UserDAO.h"
#include "UserDB.h"
#include "UserDTO.h"

// CLoginDlg 대화 상자

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)
extern CUserDTO* CurrentUser;
extern CUserDB* userDB;

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)		// 생성자
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strID(_T(""))
	, m_strPW(_T(""))
{
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)		// 컨트롤 - 변수 동기화
{
	CDialogEx::DoDataExchange(pDX);
	CRoundButtonStyle m_tMyButtonStyle;

	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_tMyButton1);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PW, m_strPW);
	DDX_Control(pDX, IDC_BUTTON_JOIN, m_tMyButton2);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CLoginDlg::OnBnClickedButtonJoin)		// 회원가입 버튼 클릭 시
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)		// 로그인 버튼 클릭 시
	ON_MESSAGE(UWM_CUSTOM2, &CLoginDlg::OnUwmCustom2)						// 회원가입 완료 시
	ON_COMMAND(IDOK, &CLoginDlg::OnIdok)
	ON_WM_CTLCOLOR()			
END_MESSAGE_MAP()



JoinDlg dlg = new JoinDlg;					// 회원 가입 다이얼로그 생성
void CLoginDlg::OnBnClickedButtonJoin()		// 회원 가입 버튼 클릭 시 호출
{
	dlg.DoModal();							// 회원가입 다이얼로그 열기
}


void CLoginDlg::OnBnClickedButtonLogin()	// 로그인 버튼 클릭 시 호출
{
	UpdateData(TRUE);
	extern CUserDB* userDB;
	userDB = new CUserDB();								// new keyword -> pointer
	userDB->InitDB();									// 데이터베이스 파일 생성 및 열기
	CUserDTO* user;
	user = userDB->dao.getUserByPw(m_strID, m_strPW);	// 입력된 ID/PW가 올바른지 확인
	if(user){											// 올바른 ID/PW가 입력되었을 경우
		CurrentUser = user;								// 사용자 DTO 저장
		MessageBox("Login Success!");					// 로그인 성공 메시지 출력
		::SendMessage(((CLoginDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM1, 0, 0);	// 메인 다이얼로그에 로그인 성공 메시지 보내기
	}
	else												// 올바르지 않은 ID/PW가 입력되었을 경우
		MessageBox("check your ID/PW");					// 로그인 실패 메시지 출력

}

afx_msg LRESULT CLoginDlg::OnUwmCustom2(WPARAM wParam, LPARAM lParam)	// 회원가입 완료 되었을 시
{
	dlg.EndDialog(IDOK);												// 회원가입 다이얼로그 종료
	return 0;
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
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
	return hbr;
}


void CLoginDlg::OnIdok()		// 엔터버튼 눌렀을 때
{
	OnBnClickedButtonLogin();	// 로그인 버튼 클릭 함수 호출
}
