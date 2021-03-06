﻿
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
#include "UserDB.h"
#include "PostDB.h"
#include "BookMarkDB.h"
#include "CreatePost.h"
#pragma comment(lib, "sqlite3.lib")

// CDanggeunClientDlg dialog
//얘네 뭐야...?
class CTab1;
class CTab2;
class CTab3;
class CTab4;



class CDanggeunClientDlg : public CDialogEx
{
private:
	CBrush m_bk_brush;
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
	afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);

	CMainTabCtrl m_Tab;
	CTab1* pDlg1;
	CTab2* pDlg2;
	CTab3* pDlg3;
	CTab4* pDlg4;	
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnClose();
protected:
	afx_msg LRESULT OnUwmCustom1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUwmCustom4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUwmCustom3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUwmCustom6(WPARAM wParam, LPARAM lParam);
};
