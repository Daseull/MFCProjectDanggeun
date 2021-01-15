#include "pch.h"
#include "BookMarkDAO.h"
#pragma warning(disable:4996)
CBookMarkDAO::CBookMarkDAO() {
	_bookMark = NULL;
	_db = NULL;
	_stmt = NULL;
	_errmsg = NULL;
}

int CBookMarkDAO::AnsiToUTF8(char* szSrc, char* strDest, int destSize) // 입력 -> DB
{
	WCHAR 	szUnicode[255];
	char 	szUTF8code[255];

	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, szSrc, (int)strlen(szSrc), szUnicode, sizeof(szUnicode));
	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, szUnicode, nUnicodeSize, szUTF8code, sizeof(szUTF8code), NULL, NULL);
	assert(destSize > nUTF8codeSize);
	memcpy(strDest, szUTF8code, nUTF8codeSize);
	strDest[nUTF8codeSize] = 0;
	return nUTF8codeSize;
}
int CBookMarkDAO::UTF8ToAnsi(char* szSrc, char* strDest, int destSize) // DB -> 출력
{
	WCHAR 	szUnicode[255];
	char 	szAnsi[255];

	int nSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, 0, 0);
	int nUnicodeSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, szUnicode, nSize);
	int nAnsiSize = WideCharToMultiByte(CP_ACP, 0, szUnicode, nUnicodeSize, szAnsi, sizeof(szAnsi), NULL, NULL);
	assert(destSize > nAnsiSize);
	memcpy(strDest, szAnsi, nAnsiSize);
	strDest[nAnsiSize] = 0;
	return nAnsiSize;
}

// C
BOOL CBookMarkDAO::createBookMark(CBookMarkDTO bookMark) {


	BOOL result = true;
	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	sqlite3_prepare_v2(_db, "insert into bookmark(userID, postID) values(?,?)", -1, &_stmt, NULL);
	// statement 통해서 쿼리 구성
	sqlite3_bind_text(_stmt, 1, bookMark.GetUserID(), bookMark.GetUserID().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 2, bookMark.GetPostID());


	if (sqlite3_step(_stmt) == SQLITE_DONE) {
		// 제대로 동작하지 않은 경우
		result = false;
	}
	// https://www.sqlite.org/c3ref/step.html
	
	sqlite3_reset(_stmt);
	sqlite3_finalize(_stmt);

	sqlite3_close(_db);

	return result;
}

// R
CBookMarkDTO* CBookMarkDAO::getBookMark(int bookMarkID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	CString sTmp;
	sTmp.Format("select * from bookmark where bookMarkID = ?");
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, bookMarkID);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_bookMark = new CBookMarkDTO();

		int _bookMarkID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _postID = sqlite3_column_int(_stmt, 2);

		_bookMark->SetPostID(_bookMarkID);
		_bookMark->SetUserID(_userID);
		_bookMark->SetPostID(_postID);

		sqlite3_finalize(_stmt);
		sqlite3_close(_db);
	}
	else {
		_bookMark = NULL; // 일치하는 결과 없으면 NULL 반환
	}

	return _bookMark;
}
CBookMarkDTO* CBookMarkDAO::getBookMarkByUserAndPost(CString& userID, int postID){

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// from bookmark
	CString sTmp;
	sTmp.Format("select * from bookmark where userID = ? and postID = ?");
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 2, postID);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_bookMark = new CBookMarkDTO();

		int _bookMarkID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _postID = sqlite3_column_int(_stmt, 2);

		_bookMark->SetPostID(_bookMarkID);
		_bookMark->SetUserID(_userID);
		_bookMark->SetPostID(_postID);

		sqlite3_finalize(_stmt);
		sqlite3_close(_db);
	}
	else {
		_bookMark = NULL; // 일치하는 결과 없으면 NULL 반환
	}

	return _bookMark;
}
std::vector<CBookMarkDTO*> CBookMarkDAO::getAll() {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	
	_bookMarkList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from bookmark");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_bookMark = new CBookMarkDTO();

		int _bookMarkID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _postID = sqlite3_column_int(_stmt, 2);

		_bookMark->SetBookMarkID(_bookMarkID);
		_bookMark->SetUserID(_userID);
		_bookMark->SetPostID(_postID);

		_bookMarkList.push_back(_bookMark);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _bookMarkList;
}

std::vector<CBookMarkDTO*> CBookMarkDAO::getAllByUser(CString userID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	_bookMarkList.clear(); // 초기화
	CString sTmp;
	
	sTmp.Format("select * from bookmark where userID = ?");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_STATIC);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_bookMark = new CBookMarkDTO();

		int _bookMarkID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _postID = sqlite3_column_int(_stmt, 2);

		_bookMark->SetBookMarkID(_bookMarkID);
		_bookMark->SetUserID(_userID);
		_bookMark->SetPostID(_postID);

		_bookMarkList.push_back(_bookMark);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _bookMarkList;
}

std::vector<CBookMarkDTO*> CBookMarkDAO::getAllByPost(int postID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// from bookmark
	_bookMarkList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from bookmark where postID = ?");
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, postID);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_bookMark = new CBookMarkDTO();

		int _bookMarkID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _postID = sqlite3_column_int(_stmt, 2);

		_bookMark->SetPostID(_bookMarkID);
		_bookMark->SetUserID(_userID);
		_bookMark->SetPostID(_postID);

		_bookMarkList.push_back(_bookMark);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _bookMarkList;
}

// D
BOOL CBookMarkDAO::deleteBookMark(int bookMarkID) {
	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// https://stackoverflow.com/a/61796041/14099774
	BOOL result = true;


	sqlite3_prepare_v2(_db, "delete from bookmark where bookMarkID = ?", -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, bookMarkID);

	if (sqlite3_step(_stmt) == SQLITE_DONE) {
		// 제대로 동작하지 않은 경우
		result = false;
	}
	// https://www.sqlite.org/c3ref/step.html
	sqlite3_reset(_stmt);
	sqlite3_finalize(_stmt);

	sqlite3_close(_db);

	return result;
}


void CBookMarkDAO::dataClean(char* dest, CString str) { // 멀티 바이트 UTF8 인코딩 과정
	char* tmp;
	//*sLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, NULL, 0, NULL, NULL);
	tmp = new char[str.GetLength() + 1];
	//WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, tmp, *sLen, NULL, NULL);
	strcpy(tmp, str);
	AnsiToUTF8(tmp, dest, 100); // 100?
	//WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)(LPCTSTR)str, -1, dest, str.GetLength(), NULL, NULL);
	

	delete[]tmp;
}
