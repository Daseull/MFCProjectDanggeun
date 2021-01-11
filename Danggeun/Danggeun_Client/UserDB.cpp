#include "pch.h"
#include "UserDB.h"
#include "Danggeun_ClientDlg.h"

// SQLite�� UTF8�� ����ϱ� ������ �ڵ� ��ȯ�� �ʿ��մϴ�.
// ��ó - http://dolphin.ivyro.net/file/algorithm/SQLite/tutoria03.html

CUserDB::CUserDB() {
	dao = CUserDAO();
	dto = CUserDTO();
}

void CUserDB::InitDB() {
	// �����ͺ��̽� ���� ���� �� ����

	int rc = sqlite3_open("test.db", &(dao._db));

	if (rc != SQLITE_OK)
	{
		printf("Failed to open DB\n");
		sqlite3_close(dao._db);
		exit(1);
	}

	//SQL ���̺� ����
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