#include "pch.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

//생성자
CListCtrlEx::CListCtrlEx()
{
}

//해제자
CListCtrlEx::~CListCtrlEx()
{

}

//멤버함수
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
END_MESSAGE_MAP()

//리스트 컨트롤에 데이터를 입력하는 함수
int CListCtrlEx::AddItem(LPCSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	
	LVITEM lvItem;
	//구조체 멤버 중 멤버값 설정
	lvItem.mask = LVIF_TEXT;
	//항목의 번호 지정 
	lvItem.iItem = nItem;
	//세부항목의 현재 상태 지정 
	lvItem.iSubItem = nSubItem;
	//항목의 실제 문자열
	lvItem.pszText = (LPTSTR)strItem;

	//상태값 설정
	if (nState != -1) {
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	//이미지의 인덱스 설정 
	if (nImageIndex != -1) {
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	//저장할 파라미터 설정
	if (nParam != -1) {
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}

	//서브 아이템 인덱스 값
	if (nSubItem == 0)
		return InsertItem(&lvItem);//아이템 추가
	else
		return SetItem(&lvItem);//서브아이템 추가
}
