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
	CRoundButton2 m_tMyButton1;
	CRoundButton2 m_tMyButton2;
	CRoundButtonStyle m_tMyButtonStyle;
	CString m_strSearch;
	CString m_strTown;
	CListCtrlEx m_list;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedButtonSearch();
	afx_msg void OnBnClickedButtonNewpost();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButtonBack();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	CRoundButton2 m_tMyButton3;
};
