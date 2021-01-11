#include "pch.h"
#include "Danggeun_Client.h"
#include "JoinDlg.h"
#include "afxdialogex.h"
#include "UserDB.h"

IMPLEMENT_DYNAMIC(JoinDlg, CDialogEx)
JoinDlg::JoinDlg(CWnd* pParent /*=nullptr*/)
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
void JoinDlg::DoDataExchange(CDataExchange* pDX)
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
	ON_BN_CLICKED(IDC_BUTTON_JOIN_OK, &JoinDlg::OnBnClickedButtonJoinOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void JoinDlg::OnBnClickedButtonJoinOk()
{
	CUserDB* userDB;
	userDB = new CUserDB(); // new keyword -> pointer
	userDB->InitDB();

	//아이디
	CString id;
	GetDlgItemText(IDC_EDIT_JOIN_ID, id);

	//비밀번호
	CString pw;
	GetDlgItemText(IDC_EDIT_JOIN_PW, pw);	

	//동네
	CString tTown;
	int town;
	town = m_Town.GetCurSel();

	//번호
	CString phone;
	GetDlgItemText(IDC_EDIT_JOIN_PHONE, phone);

	CUserDTO user;
	user.SetUserID(id);
	user.SetUserPW(pw);
	user.SetTown(town);
	user.SetPhone(phone);
	userDB->dao.createUser(user);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	UpdateData(TRUE);
	if (m_strID.GetLength() == 0 || m_strPW.GetLength() == 0 || m_strPHONE.GetLength() == 0)
		MessageBox("fill out all forms");
	else {
		AfxMessageBox("Join Success !");
		::SendMessage(((JoinDlg*)GetParent())->GetSafeHwnd(), UWM_CUSTOM2, 0, 0);
	}
	
}

HBRUSH JoinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL JoinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_EDIT_JOIN_ID)->SetWindowTextA("");
	GetDlgItem(IDC_EDIT_JOIN_PW)->SetWindowTextA("");
	GetDlgItem(IDC_EDIT_JOIN_PHONE)->SetWindowTextA("");
	GetDlgItem(IDC_COMBO_JOIN_TOWN)->SetWindowTextA("");
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

