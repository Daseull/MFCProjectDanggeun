#include "pch.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

//생성자
CListCtrlEx::CListCtrlEx()
{
}

//소멸자
CListCtrlEx::~CListCtrlEx()
{

}

//메세지맵
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
END_MESSAGE_MAP()

//리스트 컨트롤에 글 정보를 나타내기 위한 함수
int CListCtrlEx::AddItem(LPCSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
//	TITLE, 행, 열, -1, 이미지
	
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;	//대부분 텍스트로 처리
	lvItem.iItem = nItem;		//항목 번호(항상 마지막 항목으로 추가된다)
	lvItem.iSubItem = nSubItem;	//컬럼 번호
	lvItem.pszText = (LPTSTR)strItem;	//내용

	//행의 첫 컬럼이 아닌 경우  state멤버 값만 사용
	if (nState != -1) {
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	
	//이미지를 추가하고 자 하는 경우 이미지리스트에서 해당 이미지 선택
	if (nImageIndex != -1) {
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	
	//사용하지 않는 항목 
	if (nParam != -1) {
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}

	
	if (nSubItem == 0)				//행의 첫 컬럼인경우
		return InsertItem(&lvItem); //행 추가
	else
		return SetItem(&lvItem); //행의 첫컬럼이 아닌경우, 현재 행에 마저 추가
}
