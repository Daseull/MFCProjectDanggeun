#pragma once
#include "ListCtrlEx.h"

// CTab2 대화 상자

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)
	CImageList m_ImageList;
public:
	CTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTab2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrlEx m_list;
	void Init();
	void LoadMyPost();
};
