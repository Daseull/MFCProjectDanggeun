﻿
// Danggeun_Client.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDanggeunClientApp:
// See Danggeun_Client.cpp for the implementation of this class
//

class CDanggeunClientApp : public CWinApp
{
public:
	CDanggeunClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()//수정
};

extern CDanggeunClientApp theApp;
