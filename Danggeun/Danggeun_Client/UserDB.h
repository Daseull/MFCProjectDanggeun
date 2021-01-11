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
	void InitDB();
	
	
	CUserDTO dto;
	CUserDAO dao;
	std::vector<CUserDTO*> userList;
};
