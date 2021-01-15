#pragma once
#include "DetailPage.h"

// ChatBox 대화 상자

class ChatBox : public CDialogEx
{
	DECLARE_DYNAMIC(ChatBox)
private:
	CBrush m_bk_brush;
	CImage m_image;
	CRect m_rect;
public:
	ChatBox(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ChatBox();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSend;										// edit 컨트롤
	CListBox m_list;										// list 컨트롤 
	CSocCom m_socCom;										// 통신용 소켓
	virtual BOOL OnInitDialog();							// 다이얼로그 초기화
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM IParam);	// 서버에서 메시지 받기
	afx_msg void OnBnClickedButtonSend();					// 전송 버튼 클릭 시
	CRoundButtonStyle m_tMyButtonStyle;			
	CRoundButton2 m_tMyButton1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_picture;										// 상품 사진
	CStatic m_title;										// 글 제목
	CStatic m_price;										// 상품 가격
};
