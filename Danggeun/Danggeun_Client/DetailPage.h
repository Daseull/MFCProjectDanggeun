﻿#pragma once
#include "pch.h"

// CDetailPage 대화 상자

class CDetailPage : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailPage)
private:
	CBrush m_bk_brush;

public:
	CPostDTO* m_post = nullptr;
	CDetailPage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CDetailPage(CPostDTO* post, CWnd* pParent = nullptr);	//실제 사용하는 생성자
	virtual ~CDetailPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CRoundButtonStyle m_tMyButtonStyle;
	CRoundButton2 m_tMyButton1;
	virtual BOOL OnInitDialog();
	CBitmap m_bitmap;
	CRoundButton2 m_tMyButton2;

	CStatic m_stcUserID;
	CStatic m_stcPicture;
	CStatic m_stcPrice;
	CStatic m_stcState;
	CStatic m_stcText;
	CStatic m_stcTitle;
	CStatic m_stcTown;
	CBitmapButton m_btnheart;
	afx_msg void OnBnClickedButtonHeart();
	afx_msg void OnClickedButtonPostedit();
	void LoadDetailPage();

public:
	CRoundButton2 m_tMyButton3;
	afx_msg void OnClickedButtonChat();
};
