#include "pch.h"
#include "BookMarkDB.h"


CBookMarkDB::CBookMarkDB() {
	dao = CBookMarkDAO();
	dto = CBookMarkDTO();
}

void CBookMarkDB::InitDB() {
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
	sql = "CREATE TABLE IF NOT EXISTS bookmark("
		 	"bookMarkID	INTEGER,"
		 	"userID	TEXT NOT NULL,"
		 	"postID	INTEGER NOT NULL,"
		 	"FOREIGN KEY(\"postID\") REFERENCES \"post\"(\"postID\") ON DELETE CASCADE,"
		 	"FOREIGN KEY(\"userID\") REFERENCES \"user\"(\"userID\") ON DELETE CASCADE,"
		 	"PRIMARY KEY(\"bookMarkID\" AUTOINCREMENT));";

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