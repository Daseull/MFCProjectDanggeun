#pragma once
//#include "MFC_DBDlg.h"
#include "sqlite3.h"
#include "BookMarkDAO.h"
#include "BookMarkDTO.h"
#include <vector>
class CBookMarkDB
{
public:
	CBookMarkDB();
	void InitDB();
	
	CBookMarkDTO dto;
	CBookMarkDAO dao;
	std::vector<CBookMarkDTO*> bookMarkList;
};
