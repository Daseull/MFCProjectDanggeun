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
	void InitDB(); // 테이블 생성
	
	CBookMarkDTO dto;
	CBookMarkDAO dao;
	std::vector<CBookMarkDTO*> bookMarkList;
};
