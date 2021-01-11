#include "pch.h"
#include "BookMarkDTO.h"


CBookMarkDTO::CBookMarkDTO() {
	SetUserID("");
	SetUserPW("");
	SetTown(-1);
	SetPhone("");
	SetIsAdim(FALSE);
}

// Setter
void CBookMarkDTO::SetUserID(CString userID) {
	this->userID = userID;
}
void CBookMarkDTO::SetUserPW(CString userPw) {
	this->userPw = userPw;
}
void CBookMarkDTO::SetTown(int nTown) {
	this->town = nTown;
}
void CBookMarkDTO::SetPhone(CString phone) {
	this->phone = phone;

}
void CBookMarkDTO::SetIsAdim(BOOL isAdmin) {
	this->isAdmin = isAdmin;
}