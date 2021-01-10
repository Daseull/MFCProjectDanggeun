// MainTabCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "MainTabCtrl.h"


// CMainTabCtrl

IMPLEMENT_DYNAMIC(CMainTabCtrl, CTabCtrl)

CMainTabCtrl::CMainTabCtrl()
{

}

CMainTabCtrl::~CMainTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMainTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMainTabCtrl 메시지 처리기

BOOL CMainTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(255, 0, 0));
	COLORREF color_data = RGB(64, 128, 255);

	CBrush* pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);

	return CTabCtrl::OnEraseBkgnd(pDC);
}

void CMainTabCtrl::DrawItem(LPDRAWITEMSTRUCT IpDrawItemStruct)
{
	// TODO: 여기에 구현 코드 추가.
	COLORREF m_select_border_color = RGB(255,255, 255);
	COLORREF m_select_text_color = RGB(10, 155, 202);
	COLORREF m_unselect_border_color = RGB(255, 255, 255);
	COLORREF m_unselect_text_color = RGB(0, 0, 0);

	int select_index = IpDrawItemStruct->itemID;

	if (select_index < 0)
		return;

	char tab_text[50];

	TC_ITEM data;
	data.mask = TCIF_TEXT | TCIF_IMAGE;
	data.pszText = tab_text;
	data.cchTextMax = 49;

	if (!GetItem(select_index, &data))
		return;
	
	CDC* pDC = CDC::FromHandle(IpDrawItemStruct->hDC);
	CRect rect = IpDrawItemStruct->rcItem;

	rect.top += ::GetSystemMetrics(SM_CYEDGE);

	pDC->SetBkMode(TRANSPARENT);

	if (select_index == GetCurSel()) {
		pDC->FillSolidRect(rect, m_select_border_color);
	}
	else {
		pDC->FillSolidRect(rect, m_unselect_border_color);
	}
	CImageList* p_image_list = GetImageList();
	
	if (p_image_list != NULL && data.iImage >= 0) {
		rect.left += pDC->GetTextExtent(" ").cx;

		IMAGEINFO image_info;
		p_image_list->GetImageInfo(data.iImage, &image_info);
		CRect image_rect(image_info.rcImage);

		p_image_list->Draw(pDC, data.iImage, CPoint(rect.left, rect.top), ILD_TRANSPARENT);
		rect.left += image_rect.Width();
	}
	
	CFont* p_old_font = NULL;
	if (select_index == GetCurSel()) {
		pDC->SetTextColor(m_select_text_color);
		rect.top -= ::GetSystemMetrics(SM_CYEDGE);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	else {
		pDC->SetTextColor(m_unselect_text_color);
		pDC->DrawText(tab_text, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
	pDC->SelectObject(p_old_font);
}

