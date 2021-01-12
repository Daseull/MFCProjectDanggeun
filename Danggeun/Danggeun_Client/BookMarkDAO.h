#pragma once
#include <vector>
#include "BookMarkDTO.h"
#include "sqlite3.h"
#include <assert.h>

class CBookMarkDAO {
public:
	//CUserDAO(sqlite3* db, sqlite3_stmt* stmt, char* errmsg);
	CBookMarkDAO();

	sqlite3* _db;
	sqlite3_stmt* _stmt;
	char* _errmsg;
private:
	std::vector<CBookMarkDTO*> _bookMarkList;
	CBookMarkDTO* _bookMark;

public:
	int AnsiToUTF8(char* szSrc, char* strDest, int destSize);
	int UTF8ToAnsi(char* szSrc, char* strDest, int destSize);
	void dataClean(char* dest, CString str);
	void resetList(){ _bookMarkList.clear(); }
	// C
	BOOL createBookMark(CBookMarkDTO);
	// R
	CBookMarkDTO& getBookMark(int bookMarkID);
	CBookMarkDTO* getBookMarkByUserAndPost(CString& userID, int postID);
	std::vector<CBookMarkDTO*> getAll();
	std::vector<CBookMarkDTO*> getAllByUser(CString userID);
	std::vector<CBookMarkDTO*> getAllByPost(int postID);
	// U
	//BOOL updateBookMark(CBookMarkDTO);
	// D
	BOOL deleteBookMark(int bookMarkID);
};




// -C-
// createUser(UserDTO)

// return BOOL

// -R-
// getUser(id)
// getAll
// getAllByTown(townID)

// return data of vector


// -U-
// updateUser(id)

// -D-
// deleteUser(id)