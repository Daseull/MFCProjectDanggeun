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
    ON_WM_PAINT()
END_MESSAGE_MAP()



// CMainTabCtrl 메시지 처리기

BOOL CMainTabCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    CRect r;
    GetClientRect(r);
    //pDC->FillSolidRect(r, RGB(253, 235, 194));
	//return CTabCtrl::OnEraseBkgnd(pDC);
    return TRUE;
}

void CMainTabCtrl::DrawItem(LPDRAWITEMSTRUCT IpDrawItemStruct)
{
	// TODO: 여기에 구현 코드 추가.
    COLORREF m_select_border_color = RGB(253, 212, 129);
    COLORREF m_select_text_color = RGB(0, 0, 0);

    COLORREF m_unselect_border_color = RGB(255, 235, 194);
    COLORREF m_unselect_text_color = RGB(0, 0, 0);
    CFont fnt;

    int select_index = IpDrawItemStruct->itemID;
    if (select_index < 0)
        return;

    char tab_text[40];

    TC_ITEM data;
    data.mask = TCIF_TEXT;
    data.pszText = tab_text;
    data.cchTextMax = 39;

    // 선택된 탭의 정보를 얻는다.
    if (!GetItem(select_index, &data))
        return;

    CDC* pDC = CDC::FromHandle(IpDrawItemStruct->hDC);

    if (!pDC)
        return;


    CRect rect = IpDrawItemStruct->rcItem;

    // Tab이 그려진 테두리의 두께만큼 위치를 보정한다.
    rect.top += ::GetSystemMetrics(SM_CYEDGE);

    pDC->SetBkMode(TRANSPARENT);

    // 탭이 선택된 정보에 따라 배경색을 칠해준다.

    CFont* p_old_font = NULL;

    if (select_index == GetCurSel()) {
        pDC->FillSolidRect(rect, m_select_border_color);
        // 선택된 탭이라면...
        pDC->SetTextColor(m_select_text_color);
        // 텍스트의 위치를 보정하여 선택된 느낌이 강조되도록 만든다.
        rect.left += ::GetSystemMetrics(SM_CYEDGE) * 2;
        rect.bottom += ::GetSystemMetrics(SM_CYEDGE) * 6;
       pDC->DrawText(tab_text, rect,DT_SINGLELINE| DT_BOTTOM| DT_LEFT);
    }
    else {
        // 선택되지 않은 탭이라면...
        pDC->FillSolidRect(rect, m_unselect_border_color);
        rect.left += ::GetSystemMetrics(SM_CYEDGE) * 2;
        rect.bottom += ::GetSystemMetrics(SM_CYEDGE) * 6;

        pDC->SetTextColor(m_unselect_text_color);
        pDC->DrawText(tab_text, rect,DT_SINGLELINE | DT_BOTTOM | DT_LEFT );
    }

    pDC->SelectObject(p_old_font);
}

