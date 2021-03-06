#include "pch.h"
#include "PostDB.h"

CPostDB::CPostDB() {
	dao = CPostDAO();
	dto = CPostDTO();
}

void CPostDB::InitDB() {
	// 데이터베이스 파일 생성 및 열기

	int rc = sqlite3_open(DB_FILE_NAME, &(dao._db));

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(dao._db);
		exit(1);
	}

	//SQL 테이블 생성
	char* sql;
	sql = "CREATE TABLE IF NOT EXISTS post("
	   	   "postID	INTEGER,"
	   	   "userID	TEXT,"
	  	   "town	INTEGER DEFAULT - 1,"
	  	   "title	TEXT NOT NULL,"
	  	   "content	TEXT NOT NULL,"
		   "imgName	TEXT NOT NULL,"
		   "status	INTEGER NOT NULL DEFAULT 0,"
		   "price	TEXT NOT NULL,"
	  	   "PRIMARY KEY(\"postID\" AUTOINCREMENT),"
	  	   "FOREIGN KEY(\"userID\") REFERENCES \"user\"(\"userID\") ON DELETE SET NULL)"; // 글 주인이 사라지면 NULL로 변경, 완결성 유지



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