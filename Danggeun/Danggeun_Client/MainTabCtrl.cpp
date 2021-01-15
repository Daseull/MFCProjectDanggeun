// MainTabCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "MainTabCtrl.h"


// CMainTabCtrl

IMPLEMENT_DYNAMIC(CMainTabCtrl, CTabCtrl)

//생성자
CMainTabCtrl::CMainTabCtrl()
{
}

//해제자
CMainTabCtrl::~CMainTabCtrl()
{
}

//멤버함수
BEGIN_MESSAGE_MAP(CMainTabCtrl, CTabCtrl)
	ON_WM_ERASEBKGND()
    ON_WM_PAINT()
END_MESSAGE_MAP()

// CMainTabCtrl 메시지 처리기

//배경색상 지우기 
BOOL CMainTabCtrl::OnEraseBkgnd(CDC* pDC)
{
    CRect r;
    GetClientRect(r);
    return TRUE;
}

//tab의 색상 설정
void CMainTabCtrl::DrawItem(LPDRAWITEMSTRUCT IpDrawItemStruct)
{
    //선택된 tab의 테두리와 글자 색상
    COLORREF m_select_border_color = RGB(247, 134, 59);
    COLORREF m_select_text_color = RGB(0, 0, 0);

    //선택되지 않은 tab의 테두리와 글자 색상 
    COLORREF m_unselect_border_color = RGB(255, 235, 194);
    COLORREF m_unselect_text_color = RGB(0, 0, 0);
    CFont fnt;

    //선택된 tab의 index값
    int select_index = IpDrawItemStruct->itemID;
    if (select_index < 0)
        return;

    //tab의 텍스트
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
    //tab의 크기
    CRect rect = IpDrawItemStruct->rcItem;

    // Tab이 그려진 테두리의 두께만큼 위치를 보정한다.
    rect.top += ::GetSystemMetrics(SM_CYEDGE);
    pDC->SetBkMode(TRANSPARENT);

    // 탭이 선택된 정보에 따라 배경색을 칠해준다.
    CFont* p_old_font = NULL;

    // 선택된 탭이라면
    if (select_index == GetCurSel()) {
        //tab색상
        pDC->FillSolidRect(rect, m_select_border_color);
        rect.left += ::GetSystemMetrics(SM_CYEDGE) * 2;
        rect.bottom += ::GetSystemMetrics(SM_CYEDGE) * 6;
        //텍스트 색상
        pDC->SetTextColor(m_select_text_color);
        pDC->DrawText(tab_text, rect,DT_SINGLELINE| DT_BOTTOM| DT_LEFT);
    }
    // 선택되지 않은 탭이라면
    else {
        //tab색상
        pDC->FillSolidRect(rect, m_unselect_border_color);
        rect.left += ::GetSystemMetrics(SM_CYEDGE) * 2;
        rect.bottom += ::GetSystemMetrics(SM_CYEDGE) * 6;
        //텍스트 색상
        pDC->SetTextColor(m_unselect_text_color);
        pDC->DrawText(tab_text, rect,DT_SINGLELINE | DT_BOTTOM | DT_LEFT );
    }
    //tab의 폰트는 유지
    pDC->SelectObject(p_old_font);
}

