// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <afxsock.h>
#include "CSocCom.h"
#include "UserDAO.h"
#include "UserDB.h"
#include "UserDTO.h"
#include "PostDAO.h"
#include "PostDB.h"
#include "PostDTO.h"
#include "BookMarkDAO.h"
#include "BookMarkDB.h"
#include "BookMarkDTO.h"

#define UM_RECEIVE	WM_USER+2
#define UWM_CUSTOM1	WM_USER+3
#define UWM_CUSTOM2	WM_USER+4
#define UM_CLOSE	WM_USER+5
#define UWM_CUSTOM3	WM_USER+6
#define UWM_CUSTOM4	WM_USER+7
#define UWM_CUSTOM5	WM_USER+8
#endif //PCH_H

//��64���� �������Ѵٰ� ��������... �ٵ� ���� �����س����...?
//#ifndef _AFX_NO_DB_SUPPORT
//#include <afxdao.h>
//#endif