#include "pch.h"
#include "PostDAO.h"
#pragma warning(disable:4996)
CPostDAO::CPostDAO() {
	_post = NULL;
	_db = NULL;
	_stmt = NULL;
	_errmsg = NULL;
}

int CPostDAO::AnsiToUTF8(char* szSrc, char* strDest, int destSize) // 입력 -> DB
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
int CPostDAO::UTF8ToAnsi(char* szSrc, char* strDest, int destSize)// DB -> 출력
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
BOOL CPostDAO::createPost(CPostDTO post) {
	BOOL result = true;
	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// dataClean: 한글 인코딩
	char title[100];
	dataClean(title, post.GetTitle());

	char content[4096];
	dataClean(content, post.GetContent());

	char imgName[100];
	dataClean(imgName, post.GetImgName());

	char price[100];
	dataClean(price, post.GetPrice());

	sqlite3_prepare_v2(_db, "insert into post(userID, town, title, content, imgName, status, price) values(?,?,?,?,?,?,?)", -1, &_stmt, NULL);
	// statement 통해서 쿼리 구성
	sqlite3_bind_text(_stmt, 1, post.GetUserID(), post.GetUserID().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 2, post.GetTown());
	sqlite3_bind_text(_stmt, 3, title, strlen(title), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 4, content, strlen(content), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 5, imgName, strlen(imgName), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 6, post.GetStatus());
	sqlite3_bind_text(_stmt, 7, price, strlen(price), SQLITE_STATIC);


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
CPostDTO* CPostDAO::getPost(int postID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	CString sTmp;
	sTmp.Format("select * from post where postID = ?");


	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, postID);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300); // 한글 출력
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);
	}
	else {
		_post = NULL; // 일치하는 결과 없으면 NULL 반환
	}

	sqlite3_finalize(_stmt);
	sqlite3_close(_db);
	return _post;
}
std::vector<CPostDTO*> CPostDAO::getAll() {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// "from post"
	_postList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from post order by postID desc");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300); // 한글 출력
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

std::vector<CPostDTO*> CPostDAO::getAllByUser(CString userID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	// from post
	_postList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from post where userID = ? order by postID desc"); // 최근 글이 상단에 오도록 정렬
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_STATIC);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300); // 한글 출력
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

std::vector<CPostDTO*> CPostDAO::getAllByTown(int townID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	// from post
	_postList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from post where town = ? order by postID desc"); // 최근 글이 상단에 오도록 정렬
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, townID);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

std::vector<CPostDTO*> CPostDAO::getAllByBookMark(CString userID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	// from post
	_postList.clear(); // 초기화
	CString sTmp;
	sTmp.Format("select * from post where postID in (select postID from bookmark where userID = ?) ORDER by postID desc"); // 최근 글이 상단에 오도록 정렬

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_STATIC);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

std::vector<CPostDTO*> CPostDAO::getAllByBookMarkAndSearch(CString userID, CString q) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// from post
	_postList.clear(); // 초기화
	CString sTmp;

	char _q[130];
	dataClean(_q, q); // 
	sTmp.Format("select * from post where postID in (select postID from bookmark where userID = ?) and title like '%%%s%%' ORDER by postID desc", q);

	char _sql[300];
	dataClean(_sql, sTmp);

	sqlite3_prepare_v2(_db, _sql, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_STATIC);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

std::vector<CPostDTO*> CPostDAO::getAllByTitleSearch(CString q, int townID) {

	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	// from post
	_postList.clear(); // 초기화
	CString sTmp;

	char _q[100];
	dataClean(_q, q);
	sTmp.Format("SELECT * FROM post WHERE title like '%%%s%%' and town = %d", q, townID);

	char _sql[100];
	dataClean(_sql, sTmp);

	sqlite3_prepare_v2(_db, _sql, -1, &_stmt, NULL);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		char szAnsi[300];
		_post = new CPostDTO();

		int _postID = sqlite3_column_int(_stmt, 0);
		CString _userID(sqlite3_column_text(_stmt, 1));
		int _town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString _title(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 4), szAnsi, 300);
		CString _content(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 5), szAnsi, 300);
		CString _imgName(szAnsi);

		int _status = sqlite3_column_int(_stmt, 6);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 7), szAnsi, 300);
		CString _price(szAnsi);

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);
		_post->SetStauts(_status);
		_post->SetPrice(_price);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

// U
BOOL CPostDAO::updatePost(CPostDTO post) {
	int rc = sqlite3_open(DB_FILE_NAME, &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// userID는 불변
	sqlite3_prepare_v2(_db, "UPDATE post SET town = ?,"
										 "title = ?,"
										 "content = ?,"
										 "imgName = ?,"
										 "status = ?,"
										 "price = ?"
										 "WHERE postID = ?", -1, &_stmt, NULL);


	BOOL result = true;

	char title[100];
	dataClean(title, post.GetTitle());

	char content[4096];
	dataClean(content, post.GetContent());

	char price[100];
	dataClean(price, post.GetPrice());

	sqlite3_bind_int(_stmt, 1, post.GetTown());
	sqlite3_bind_text(_stmt, 2, title, strlen(title), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 3, content, strlen(content), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 4, post.GetImgName(), post.GetImgName().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 5, post.GetStatus());
	sqlite3_bind_text(_stmt, 6, price, strlen(price), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 7, post.GetPostID());

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

// D
BOOL CPostDAO::deletePost(int postID) {
	int rc = sqlite3_open(DB_FILE_NAME, &_db);

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}


	// https://stackoverflow.com/a/61796041/14099774
	// 삭제 정책 활성화
	char* sql = "PRAGMA foreign_keys = ON;";
	rc = sqlite3_exec(_db, sql, NULL, 0, &_errmsg);

	BOOL result = true;


	sqlite3_prepare(_db, "delete from post where postID = ?", -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, postID);

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

void CPostDAO::dataClean(char* dest, CString str) { // 멀티 바이트 UTF8 인코딩 과정
	char* tmp;
	//*sLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, NULL, 0, NULL, NULL);
	tmp = new char[str.GetLength() + 1];
	//WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, tmp, *sLen, NULL, NULL);
	strcpy(tmp, str);
	AnsiToUTF8(tmp, dest, 300); // 100?
	//WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)(LPCTSTR)str, -1, dest, str.GetLength(), NULL, NULL);

	delete[]tmp;
}
