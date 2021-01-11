#include "pch.h"
#include "UserDB.h"
#include "Danggeun_ClientDlg.h"

// SQLite는 UTF8을 사용하기 때문에 코드 변환이 필요합니다.
// 출처 - http://dolphin.ivyro.net/file/algorithm/SQLite/tutoria03.html

CUserDB::CUserDB() {
	dao = CUserDAO();
	dto = CUserDTO();
}

void CUserDB::InitDB() {
	// 데이터베이스 파일 생성 및 열기

	int rc = sqlite3_open("test.db", &(dao._db));

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(dao._db);
		exit(1);
	}

	//SQL 테이블 생성
	char* sql;
	sql = "CREATE TABLE IF NOT EXISTS user("
			"userID	TEXT NOT NULL,"
			"userPw	TEXT NOT NULL,"
			"town	INTEGER DEFAULT - 1,"
			"phone	TEXT NOT NULL,"
			"isAdmin	INTEGER DEFAULT 0,"
			"PRIMARY KEY(\"userID\"));";

	rc = sqlite3_exec(dao._db, sql, NULL, NULL, &(dao._errmsg));

	if (rc != SQLITE_OK)
	{
		printf("create table");
		sqlite3_free(dao._errmsg);
		sqlite3_close(dao._db);
		exit(1);
	}

	sqlite3_close(dao._db);
}