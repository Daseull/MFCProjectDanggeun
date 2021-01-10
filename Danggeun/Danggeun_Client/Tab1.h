#pragma once

#include "ListCtrlEx.h"

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)
	CImageList m_ImageList;
	


public:
	CTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1();
	void LoadTownPost();
	void SearchPost(CString Key);
	void Init();
	

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
//	CListCtrl m_list;
	CString m_strTown;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrlEx m_list;
	afx_msg void OnClickedButtonSearch();
};
