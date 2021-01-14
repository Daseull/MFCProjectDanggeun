#include "pch.h"
#include "BookMarkDTO.h"


CBookMarkDTO::CBookMarkDTO() {
	CBookMarkDTO::SetBookMarkID(-1);
	CBookMarkDTO::SetPostID(-1);
	CBookMarkDTO::SetUserID("");
}

// Setter
void CBookMarkDTO::SetBookMarkID(int bookMarkID) {
	this->bookMarkID = bookMarkID;
}
void CBookMarkDTO::SetPostID(int postID) {
	this->postID = postID;
}
void CBookMarkDTO::SetUserID(CString userID) {
	this->userID = userID;
}