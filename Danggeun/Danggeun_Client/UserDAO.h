#pragma once
#include <vector>
#include "UserDTO.h"
#include "sqlite3.h"
#include <assert.h>

class CUserDAO {
public:
	//CUserDAO(sqlite3* db, sqlite3_stmt* stmt, char* errmsg);
	CUserDAO();

	sqlite3* _db;
	sqlite3_stmt* _stmt;
	char* _errmsg;
private:
	std::vector<CUserDTO*> _userList;
	CUserDTO* _user;
	int AnsiToUTF8(char* szSrc, char* strDest, int destSize);
	int UTF8ToAnsi(char* szSrc, char* strDest, int destSize);

	void dataClean(char* dest, CString str);
public:
	// C
	BOOL createUser(CUserDTO);
	// R
	CUserDTO* getUser(CString userID);
	CUserDTO* getUserByPw(CString userID, CString pw);
	std::vector<CUserDTO*> getAll();
	std::vector<CUserDTO*> getAllByTown(int townID);
	// U
	BOOL updateUser(CUserDTO);
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