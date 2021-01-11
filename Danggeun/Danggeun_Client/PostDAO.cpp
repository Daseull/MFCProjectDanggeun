#include "pch.h"
#include "PostDAO.h"
#pragma warning(disable:4996)
CPostDAO::CPostDAO() {
	_post = NULL;
	_db = NULL;
	_stmt = NULL;
	_errmsg = NULL;
}

int CPostDAO::AnsiToUTF8(char* szSrc, char* strDest, int destSize)
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
int CPostDAO::UTF8ToAnsi(char* szSrc, char* strDest, int destSize)
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
	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//int sLen;

	//char* s_name;
	//char szName[100];
	//dataClean(s_name, szName, user.GetUserID(), &sLen);

	//char* s_pw;
	//char szTel[100];
	//dataClean(s_pw, szTel, user.GetPhone(), &sLen);


	//_errmsg = NULL;
	//char sql[255] = { 0 };
	//sprintf(sql, "insert into db(name, tel) values('%s','%s');", szName, szTel);

	//if (SQLITE_OK != sqlite3_exec(_db, sql, NULL, NULL, &_errmsg))
	//{
	//	//printf("insert");
	//	// insert Compelte
	//	result = false;
	//}

	//sqlite3_finalize(_stmt);
	char title[100];
	dataClean(title, post.GetTitle());

	char content[100];
	dataClean(content, post.GetContent());

	sqlite3_prepare_v2(_db, "insert into post(userID, town, title, content, imgName) values(?,?,?,?,?)", -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, post.GetUserID(), post.GetUserID().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 2, post.GetTown());
	sqlite3_bind_text(_stmt, 3, title, strlen(title), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 4, content, strlen(content), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 5, post.GetImgName(), post.GetImgName().GetLength(), SQLITE_STATIC);
	/*sqlite3_step(_stmt);
	sqlite3_finalize(_stmt);*/


	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		// 제대로 동작하지 않은 경우
		result = false;
	}
	// https://www.sqlite.org/c3ref/step.html
	// reset -> 
	sqlite3_reset(_stmt);
	sqlite3_finalize(_stmt);

	sqlite3_close(_db);

	return result;


}

// R
CPostDTO& CPostDAO::getPost(int postID) {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// "from user"
	_postList.clear();
	CString sTmp;
	sTmp.Format("select * from post where postID = ?");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, postID);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		throw NULL;
	}

	int i;
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

	_post->SetPostID(_postID);
	_post->SetUserID(_userID);
	_post->SetTown(_town);
	_post->SetTitle(_title);
	_post->SetContent(_content);
	_post->SetImgName(_imgName);

	sqlite3_finalize(_stmt);
	sqlite3_close(_db);
	return *_post;
}
std::vector<CPostDTO*> CPostDAO::getAll() {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// "from post"
	_postList.clear();
	CString sTmp;
	sTmp.Format("select * from post");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int i;
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

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}
std::vector<CPostDTO*> CPostDAO::getAllByTown(int townID) {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//sqlite3_finalize(_stmt);
	//sqlite3_prepare(_db, "INSERT ... (?,?)", -1, &_stmt, NULL);
	//sqlite3_bind_int(_stmt, 1, 123);
	//sqlite3_bind_int(_stmt, 2, 456);
	//sqlite3_step(_stmt);
	//sqlite3_finalize(_stmt);


	// "from user"
	_postList.clear();
	CString sTmp;
	//sTmp.Format(_T("select * from db where "));
	sTmp.Format(_T("select * from post where town = ?"));
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, townID);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int i;
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

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}
std::vector<CPostDTO*> CPostDAO::getAllByTitleSearch(CString q) {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//sqlite3_finalize(_stmt);
	//sqlite3_prepare(_db, "INSERT ... (?,?)", -1, &_stmt, NULL);
	//sqlite3_bind_int(_stmt, 1, 123);
	//sqlite3_bind_int(_stmt, 2, 456);
	//sqlite3_step(_stmt);
	//sqlite3_finalize(_stmt);


	// "from user"
	_postList.clear();
	CString sTmp;
	//sTmp.Format(_T("select * from db where "));

	char _q[100];
	dataClean(_q, q);
	sTmp.Format("SELECT * FROM post WHERE title like '%%%s%%'", q);

	char _sql[100];
	dataClean(_sql, sTmp);

	sqlite3_prepare_v2(_db, _sql, -1, &_stmt, NULL);
	//sqlite3_bind_text(_stmt, 1, _q, strlen(_q), SQLITE_STATIC);

	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int i;
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

		_post->SetPostID(_postID);
		_post->SetUserID(_userID);
		_post->SetTown(_town);
		_post->SetTitle(_title);
		_post->SetContent(_content);
		_post->SetImgName(_imgName);

		_postList.push_back(_post);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _postList;
}

// U
BOOL CPostDAO::updatePost(CPostDTO post) {


	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//sqlite3_finalize(_stmt);

	// userID는 불변
	sqlite3_prepare_v2(_db, "UPDATE post SET town = ?,"
										 "title = ?,"
										 "content = ?,"
										 "imgName = ?"
										 "WHERE postID = ?", -1, &_stmt, NULL);


	BOOL result = true;

	char title[100];
	dataClean(title, post.GetTitle());

	char content[100];
	dataClean(content, post.GetContent());

	//sqlite3_prepare_v2(_db, "insert into post(userID, town, title, content, imgName) values(?,?,?,?,?)", -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, post.GetTown());
	sqlite3_bind_text(_stmt, 2, title, strlen(title), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 3, content, strlen(content), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 4, post.GetImgName(), post.GetImgName().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 5, post.GetPostID());

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		// 제대로 동작하지 않은 경우
		result = false;
	}
	// https://www.sqlite.org/c3ref/step.html
	// reset -> 
	sqlite3_reset(_stmt);
	sqlite3_finalize(_stmt);

	sqlite3_close(_db);

	return result;
}

// D
BOOL CPostDAO::deletePost(int postID) {
	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//sqlite3_finalize(_stmt);


	// https://stackoverflow.com/a/61796041/14099774
	BOOL result = true;

	//_errmsg = NULL;
	//char sql[255] = { 0 };
	//sprintf_s(sql, "delete from user where userID = '%s';", userID);

	//if (SQLITE_OK != sqlite3_exec(_db, sql, NULL, NULL, &_errmsg))
	//{
	//	printf("delete");
	//}

	sqlite3_prepare(_db, "delete from post where postID = ?", -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, postID);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		// 제대로 동작하지 않은 경우
		result = false;
	}
	// https://www.sqlite.org/c3ref/step.html
	// reset -> 
	sqlite3_reset(_stmt);
	sqlite3_finalize(_stmt);

	sqlite3_close(_db);

	return result;
	
}

void CPostDAO::dataClean(char* dest, CString str) {
	char* tmp;
	//*sLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, NULL, 0, NULL, NULL);
	tmp = new char[str.GetLength() + 1];
	//WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, tmp, *sLen, NULL, NULL);
	strcpy(tmp, str);
	AnsiToUTF8(tmp, dest, 100); // 100?
	//WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)(LPCTSTR)str, -1, dest, str.GetLength(), NULL, NULL);

	delete[]tmp;
}
