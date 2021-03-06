#pragma once
#include <afxstr.h>


// 
class CBookMarkDTO {
public:
	CBookMarkDTO();
private:
	int bookMarkID; // PK
	CString userID; // FK
	int postID; // FK

public:
	// Getter
	int CBookMarkDTO::GetBookMarkID() { return bookMarkID; }
	CString CBookMarkDTO::GetUserID() { return userID; }
	int CBookMarkDTO::GetPostID() { return postID; }
	
	// Setter
	void CBookMarkDTO::SetBookMarkID(int bookMarkID);
	void CBookMarkDTO::SetUserID(CString userID);
	void CBookMarkDTO::SetPostID(int postID);
};