
// Danggeun_ClientDlg.h : header file
//

#pragma once
#include "RoundButton2.h"
#include "RoundButtonStyle.h"
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"
#include "MainTabCtrl.h"

// CDanggeunClientDlg dialog
class CTab1;
class CTab2;
class CTab3;
class CTab4;

class CDanggeunClientDlg : public CDialogEx
{
// Construction
public:
	CDanggeunClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DANGGEUN_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);

	CTab1* pDlg1;
	CTab2* pDlg2;
	CTab3* pDlg3;
	CTab4* pDlg4;	
//	CTabCtrl m_Tab;
	CMainTabCtrl m_Tab;
};
