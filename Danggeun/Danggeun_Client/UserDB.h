#pragma once
//#include "MFC_DBDlg.h"
#include "sqlite3.h"
#include "UserDAO.h"
#include "UserDTO.h"
#include <vector>

class CUserDB
{
public:
	CUserDB();
	void InitDB(); // 테이블 생성
	
	CUserDTO dto;
	CUserDAO dao;
	std::vector<CUserDTO*> userList;
};
