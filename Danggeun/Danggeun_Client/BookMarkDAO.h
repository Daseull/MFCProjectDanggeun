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
	std::vector<CBookMarkDTO*> _userList;
	CBookMarkDTO* _user;

public:
	int AnsiToUTF8(char* szSrc, char* strDest, int destSize);
	int UTF8ToAnsi(char* szSrc, char* strDest, int destSize);
	void dataClean(char* dest, CString str, int* sLen);
	void resetList(){ _userList.clear(); }
	// C
	BOOL createUser(CBookMarkDTO);
	// R
	CBookMarkDTO& getUser(CString userID);
	std::vector<CBookMarkDTO*> getAll();
	std::vector<CBookMarkDTO*> getAllByTown(int townID);
	// U
	BOOL updateUser(CBookMarkDTO);
	// D
	BOOL deleteUser(CString userID);
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