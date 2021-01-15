#include "pch.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

//������
CListCtrlEx::CListCtrlEx()
{
}

//������
CListCtrlEx::~CListCtrlEx()
{

}

//����Լ�
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
END_MESSAGE_MAP()

//����Ʈ ��Ʈ�ѿ� �����͸� �Է��ϴ� �Լ�
int CListCtrlEx::AddItem(LPCSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	
	LVITEM lvItem;
	//����ü ��� �� ����� ����
	lvItem.mask = LVIF_TEXT;
	//�׸��� ��ȣ ���� 
	lvItem.iItem = nItem;
	//�����׸��� ���� ���� ���� 
	lvItem.iSubItem = nSubItem;
	//�׸��� ���� ���ڿ�
	lvItem.pszText = (LPTSTR)strItem;

	//���°� ����
	if (nState != -1) {
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	//�̹����� �ε��� ���� 
	if (nImageIndex != -1) {
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	//������ �Ķ���� ����
	if (nParam != -1) {
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}

	//���� ������ �ε��� ��
	if (nSubItem == 0)
		return InsertItem(&lvItem);//������ �߰�
	else
		return SetItem(&lvItem);//��������� �߰�
}
