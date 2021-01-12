#pragma once
#include <vector>
#include "PostDTO.h"
#include "sqlite3.h"
#include <assert.h>

class CPostDAO {
public:
	//CPostDAO(sqlite3* db, sqlite3_stmt* stmt, char* errmsg);
	CPostDAO();

	sqlite3* _db;
	sqlite3_stmt* _stmt;
	char* _errmsg;
private:
	std::vector<CPostDTO*> _postList;
	CPostDTO* _post;

	int AnsiToUTF8(char* szSrc, char* strDest, int destSize);
	int UTF8ToAnsi(char* szSrc, char* strDest, int destSize);
	void dataClean(char* dest, CString str);
public:
	void resetList(){ _postList.clear(); }
	// C
	BOOL createPost(CPostDTO);
	// R
	CPostDTO* getPost(int postID);
	std::vector<CPostDTO*> getAll();
	std::vector<CPostDTO*> getAllByUser(CString userID);
	std::vector<CPostDTO*> getAllByTown(int townID);
	std::vector<CPostDTO*> getAllByBookMark(CString userID);
	std::vector<CPostDTO*> getAllByTitleSearch(CString q, int townID);
	// U
	BOOL updatePost(CPostDTO);
	// D
	BOOL deletePost(int postID);
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