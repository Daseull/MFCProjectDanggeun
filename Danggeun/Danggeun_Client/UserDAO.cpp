#include "pch.h"
#include "UserDAO.h"
#pragma warning(disable:4996)
CUserDAO::CUserDAO() {
	_user = NULL;
	_db = NULL;
	_stmt = NULL;
	_errmsg = NULL;
}

int CUserDAO::AnsiToUTF8(char* szSrc, char* strDest, int destSize)
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
int CUserDAO::UTF8ToAnsi(char* szSrc, char* strDest, int destSize)
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
BOOL CUserDAO::createUser(CUserDTO user) {


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
	char userID[100];
	int sLen;
	dataClean(userID, user.GetUserID());



	sqlite3_prepare_v2(_db, "insert into user(userID, userPw, town, phone, isAdmin) values(?,?,?,?,?)", -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, strlen(userID), SQLITE_STATIC);
	sqlite3_bind_text(_stmt, 2, user.GetUserPW(), user.GetUserPW().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 3, user.GetTown());
	sqlite3_bind_text(_stmt, 4, user.GetPhone(), user.GetPhone().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 5, user.GetIsAdim());
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
CUserDTO& CUserDAO::getUser(CString userID) {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// "from user"
	CString sTmp;
	sTmp.Format(_T("select * from user where userID = ?"));

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_TRANSIENT);

	if (sqlite3_step(_stmt) != SQLITE_DONE) {
		int num_cols = sqlite3_column_count(_stmt);

		_user = new CUserDTO();

		char szAnsi[300];
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 0), szAnsi, 300);
		CString _userID(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 1), szAnsi, 300);
		CString userPw(szAnsi);

		int town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString phone(szAnsi);

		bool isAdmin = sqlite3_column_int(_stmt, 4);

		_user->SetUserID(_userID);
		_user->SetUserPW(userPw);
		_user->SetTown(town);
		_user->SetPhone(phone);
		_user->SetIsAdim(isAdmin);
	}

	int i;



	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return *_user;
}

std::vector<CUserDTO*> CUserDAO::getAll() {
	// 테이블을 읽어와 리스트 컨트롤에 보여주기

	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	// "from user"
	CString sTmp;
	sTmp.Format("select * from user");

	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int i;
		int num_cols = sqlite3_column_count(_stmt);

		_user = new CUserDTO();

		char szAnsi[300];
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 0), szAnsi, 300);
		CString userID(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 1), szAnsi, 300);
		CString userPw(szAnsi);

		int town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString phone(szAnsi);

		bool isAdmin = sqlite3_column_int(_stmt, 4);

		_user->SetUserID(userID);
		_user->SetUserPW(userPw);
		_user->SetTown(town);
		_user->SetPhone(phone);
		_user->SetIsAdim(isAdmin);

		_userList.push_back(_user);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _userList;
}

std::vector<CUserDTO*> CUserDAO::getAllByTown(int townID) {
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
	CString sTmp;
	//sTmp.Format(_T("select * from db where "));
	sTmp.Format(_T("select * from user where town = ?"));
	sqlite3_prepare_v2(_db, sTmp, -1, &_stmt, NULL);
	sqlite3_bind_int(_stmt, 1, townID);
	while (sqlite3_step(_stmt) != SQLITE_DONE) {
		int i;
		int num_cols = sqlite3_column_count(_stmt);

		_user = new CUserDTO();

		char szAnsi[300];
		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 0), szAnsi, 300);
		CString userID(szAnsi);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 1), szAnsi, 300);
		CString userPw(szAnsi);

		int town = sqlite3_column_int(_stmt, 2);

		UTF8ToAnsi((char*)sqlite3_column_text(_stmt, 3), szAnsi, 300);
		CString phone(szAnsi);

		bool isAdmin = sqlite3_column_int(_stmt, 4);

		_user->SetUserID(userID);
		_user->SetUserPW(userPw);
		_user->SetTown(town);
		_user->SetPhone(phone);
		_user->SetIsAdim(isAdmin);

		_userList.push_back(_user);
	}

	sqlite3_finalize(_stmt);

	sqlite3_close(_db);
	return _userList;
}

// U
BOOL CUserDAO::updateUser(CUserDTO user) {


	int rc = sqlite3_open("test.db", &_db);
	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(_db);
		exit(1);
	}

	//sqlite3_finalize(_stmt);
	sqlite3_prepare_v2(_db, "UPDATE user SET userPw = ?,"
										 "town = ?,"
										 "phone = ?,"
										 "isAdmin = ?"
										 "WHERE userID = ? ", -1, &_stmt, NULL);


	// https://stackoverflow.com/a/61796041/14099774
	BOOL result = true;

	sqlite3_bind_text(_stmt, 1, user.GetUserPW(), user.GetUserPW().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 2, user.GetTown());
	sqlite3_bind_text(_stmt, 3, user.GetPhone(), user.GetPhone().GetLength(), SQLITE_STATIC);
	sqlite3_bind_int(_stmt, 4, user.GetIsAdim());
	sqlite3_bind_text(_stmt, 5, user.GetUserID(), user.GetUserID().GetLength(), SQLITE_STATIC);
	
	

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
BOOL CUserDAO::deleteUser(CString userID) {
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

	sqlite3_prepare_v2(_db, "delete from user where userID = ?", -1, &_stmt, NULL);
	sqlite3_bind_text(_stmt, 1, userID, userID.GetLength(), SQLITE_TRANSIENT);

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


void CUserDAO::dataClean(char* dest, CString str) {
	char* tmp;
	//*sLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, NULL, 0, NULL, NULL);
	tmp = new char[str.GetLength() + 1];
	//WideCharToMultiByte(CP_ACP, 0, (LPCWCH)(LPCTSTR)str, -1, tmp, *sLen, NULL, NULL);
	strcpy(tmp, str);
	AnsiToUTF8(tmp, dest, 100); // 100?
	//WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)(LPCTSTR)str, -1, dest, str.GetLength(), NULL, NULL);
	

	delete[]tmp;
}
