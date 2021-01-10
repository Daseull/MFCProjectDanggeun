#pragma once
#include <afxcmn.h>
class CListCtrlEx :
    public CListCtrl
{
    DECLARE_DYNAMIC(CListCtrlEx)

public:
	CListCtrlEx();
	//addItem 인자 확인(수정가능)
	int AddItem(LPCSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
	virtual ~CListCtrlEx();

protected:
	DECLARE_MESSAGE_MAP()
   
public:
//	afx_msg void OnNMClick(NMHDR* pNMHDR, LRESULT* pResult);
};

