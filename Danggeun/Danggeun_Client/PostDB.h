#pragma once
//#include "MFC_DBDlg.h"
#include "sqlite3.h"
#include "PostDAO.h"
#include "PostDTO.h"
#include <vector>

class CPostDB
{
public:
	CPostDB();
	void InitDB();
	
	CPostDAO dao;
	CPostDTO dto;
	std::vector<CPostDTO*> postList;
};
