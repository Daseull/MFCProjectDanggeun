#pragma once

#include "ListCtrlEx.h"
// CTab3 대화 상자

class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)
private:
	CBrush m_bk_brush;
	CImageList m_ImageList;
public:
	CTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeListHeart();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton1;
	CString m_strTown;
	afx_msg void OnStnClickedCancel();
	CRoundButton2 m_tMyButton2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonBack();
	void LoadBookmarkPost();
	void SearchPost(CString Key);

	CListCtrlEx m_list;
	CString m_strSearch;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDblclkListHeart(NMHDR* pNMHDR, LRESULT* pResult);
};
