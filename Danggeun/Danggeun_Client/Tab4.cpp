// Tab4.cpp: 구현 파일
//내 정보

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab4.h"
#include "afxdialogex.h"


// CTab4 대화 상자

IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

//생성자
CTab4::CTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab4, pParent)
	, m_strPhone(_T(""))
	, m_strPW(_T(""))
	, m_strID(_T(""))
{
	//변수 초기화
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);

}

//해제자
CTab4::~CTab4()
{
}

//컨트롤의 값 변환
void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PW2, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_tMyButton2);
	DDX_Text(pDX, IDC_EDIT_CHANGEPHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_CHANGEPW, m_strPW);
	DDX_Control(pDX, IDC_COMBO_CHANGETOWN, m_Town);
	DDX_Text(pDX, IDC_STATIC_ID, m_strID);
	DDX_Control(pDX, IDC_STATIC_ID, m_userid);
}

//멤버함수
BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab4::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab4::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CHANGEOK, &CTab4::OnClickedButtonChangeok)
	ON_BN_CLICKED(IDC_BUTTON_WITHDRAW, &CTab4::OnClickedButtonWithdraw)
END_MESSAGE_MAP()


// CTab4 메시지 처리기

//확인 버튼 비활성화
void CTab4::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}

//취소버튼 비활성화
void CTab4::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}

//다이아로그의 배경색상 칠하기
HBRUSH CTab4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// 여기서 DC의 특성을 변경합니다.
	//다이로그일 때 색상 설정
	if (nCtlColor == CTLCOLOR_DLG) {
		return m_bk_brush;
	}
	//사용자의 id 스태틱에 대한 색상 설정
	if (m_userid.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(255, 133, 0));
		return m_bk_brush;
	}
	//그냥 스태틱에 대한 색상 설정 
	else if (nCtlColor == CTLCOLOR_STATIC) {
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

//다이아로그의 초기상태 설정
BOOL CTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//폰트 설정 

	//아이디 static
	CFont font3;
	LOGFONT lf3;
	::ZeroMemory(&lf3, sizeof(lf3));
	lf3.lfHeight = 30;
	lf3.lfWeight = FW_BOLD;
	::lstrcpy(lf3.lfFaceName, "나눔고딕");

	font3.CreateFontIndirectA(&lf3);
	GetDlgItem(IDC_STATIC_ID)->SetFont(&font3);
	font3.Detach();

	// 변경하기 static
	CFont font4;
	LOGFONT lf4;
	::ZeroMemory(&lf4, sizeof(lf4));
	lf4.lfHeight = 18;
	lf4.lfWeight = FW_SEMIBOLD;
	::lstrcpy(lf4.lfFaceName, "나눔고딕");

	font4.CreateFontIndirectA(&lf4);
	GetDlgItem(IDC_STATIC_PHONECHANGE)->SetFont(&font4);
	GetDlgItem(IDC_STATIC_PW_EDIT)->SetFont(&font4);
	GetDlgItem(IDC_STATIC_TOWNCHANGE)->SetFont(&font4);

	font4.Detach();
	
	//사용자의 기본정보를 edit컨트롤에 치환 
	extern CUserDTO* CurrentUser;
	extern CUserDB* userDB;
	m_strID = CurrentUser->GetUserID();
	m_strPhone = CurrentUser->GetPhone();
	m_strPW = CurrentUser->GetUserPW();
	m_Town.SetCurSel(CurrentUser->GetTown());


	UpdateData(FALSE);
	return TRUE;
}

//회원정보 변경하고 확인 버튼 눌렀을 때 
void CTab4::OnClickedButtonChangeok()
{
	UpdateData(TRUE);
	extern CUserDTO* CurrentUser;
	extern CUserDB* userDB;	
	extern CString town[25];

	//사용자의 정보 다시 설정
	CurrentUser->SetTown(m_Town.GetCurSel());
	CurrentUser->SetUserID(CurrentUser->GetUserID());
	CurrentUser->SetUserPW(m_strPW);
	CurrentUser->SetPhone(m_strPhone);
	userDB->dao.updateUser(*CurrentUser);

	//메시지박스 호출 
	AfxMessageBox("변경 완료!");
	::SendMessage(((CTab4*)GetParent()->GetParent())->GetSafeHwnd(), UWM_CUSTOM6, 0, 0);
}

//회원탈퇴 버튼 눌렀을 때
void CTab4::OnClickedButtonWithdraw()
{
	extern CUserDTO* CurrentUser;
	extern CUserDB* userDB;
	//메시지박스 호출 
	AfxMessageBox("회원 탈퇴 완료ㅠㅠ\n 다음에 또 이용해주세요!");
	//회원탈퇴
	userDB->dao.deleteUser(CurrentUser->GetUserID());
	//프로그램 종료
	exit(0);
}
