#pragma once

#include "ListCtrlEx.h"

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)
private: 
	CBrush m_bk_brush;

	CImageList m_ImageList;
	

public:
	CTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CFont m_font;
	virtual ~CTab1();
	void LoadTownPost();
	void SearchPost(CString Key);	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_strSearch;
	CString m_strTown;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrlEx m_list;
	afx_msg void OnClickedButtonSearch();
//	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	CRoundButton2 m_tMyButton1;
	CRoundButton2 m_tMyButton2;
	CRoundButtonStyle m_tMyButtonStyle;
	afx_msg void OnBnClickedButtonNewpost();
//	afx_msg void OnPaint();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg LRESULT OnUwmCustom3(WPARAM wParam, LPARAM lParam);
};
