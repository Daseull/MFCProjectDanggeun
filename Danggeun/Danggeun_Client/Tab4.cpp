// Tab4.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab4.h"
#include "afxdialogex.h"


// CTab4 대화 상자

IMPLEMENT_DYNAMIC(CTab4, CDialogEx)

CTab4::CTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTab4, pParent)
	, m_strPhone(_T(""))
	, m_strPW(_T(""))
{
	
	m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
	m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
	m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PW2, m_tMyButton1);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_tMyButton2);
	//  DDX_Text(pDX, IDC_STATIC_ID, m_userId);
	DDX_Control(pDX, IDC_STATIC_ID, m_userid);
	DDX_Text(pDX, IDC_EDIT_CHANGEPHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_CHANGEPW, m_strPW);
	DDX_Control(pDX, IDC_COMBO_CHANGETOWN, m_Town);
}


BEGIN_MESSAGE_MAP(CTab4, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab4::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab4::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_BUTTON_QUIT, &CTab4::OnBnClickedButtonQuit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CHANGEOK, &CTab4::OnClickedButtonChangeok)
	ON_BN_CLICKED(IDC_BUTTON_WITHDRAW, &CTab4::OnClickedButtonWithdraw)
END_MESSAGE_MAP()


// CTab4 메시지 처리기


void CTab4::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTab4::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}






HBRUSH CTab4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG) {//dlg
		return m_bk_brush;
	}
	
	if (m_userid.m_hWnd == pWnd->m_hWnd) {
		pDC->SetBkColor(RGB(253, 212, 129));
		pDC->SetTextColor(RGB(255, 133, 0));
		return m_bk_brush;
	}

	else if (nCtlColor == CTLCOLOR_STATIC) {
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


BOOL CTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	extern CString CurrentUser;
	extern CUserDB* userDB;
	
	
	for (CUserDTO* user : userDB->userList) {
		if (CurrentUser == user->GetUserID()) {
			CString CurrentUser = user->GetUserID();
			m_strPhone = user->GetPhone();
			m_strPW = user->GetUserPW();
			m_Town.SetCurSel(user->GetTown());
		}
	}


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab4::OnClickedButtonChangeok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	CUserDTO user;
	extern CString CurrentUser;
	extern CUserDB* userDB;

	user.SetTown(m_Town.GetCurSel());
	user.SetUserID(CurrentUser);
	user.SetUserPW(m_strPW);
	user.SetPhone(m_strPhone);
	userDB->dao.updateUser(user);
	AfxMessageBox("변경 완료!");

}




void CTab4::OnClickedButtonWithdraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	extern CString CurrentUser;
	extern CUserDB* userDB;

	AfxMessageBox("회원 탈퇴 완료ㅠㅠ\n 다음에 또 이용해주세요!");
	userDB->dao.deleteUser(CurrentUser);
	exit(0);
}
