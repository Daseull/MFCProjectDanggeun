#pragma once


// CMainTabCtrl

class CMainTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMainTabCtrl)

public:
	CMainTabCtrl();
	virtual ~CMainTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawItem(LPDRAWITEMSTRUCT IpDrawItemStruct);
};


