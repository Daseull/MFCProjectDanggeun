#include "pch.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{

}

CListCtrlEx::~CListCtrlEx()
{

}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
//	ON_NOTIFY_REFLECT(NM_CLICK, &CListCtrlEx::OnNMClick)
END_MESSAGE_MAP()


int CListCtrlEx::AddItem(LPCSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1) {
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}

	if (nImageIndex != -1) {
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}

	if (nParam != -1) {
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}

	if (nSubItem == 0)
		return InsertItem(&lvItem);
	else
		return SetItem(&lvItem);

}



//void CListCtrlEx::OnNMClick(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}
