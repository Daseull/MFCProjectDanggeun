#include "pch.h"
#include "UserDTO.h"


CUserDTO::CUserDTO() {
	SetUserID("");
	SetUserPW("");
	SetTown(-1);
	SetPhone("");
	SetIsAdim(FALSE);
}

// Setter
void CUserDTO::SetUserID(CString userID) {
	this->userID = userID;
}
void CUserDTO::SetUserPW(CString userPw) {
	this->userPw = userPw;
}
void CUserDTO::SetTown(int nTown) {
	this->town = nTown;
}
void CUserDTO::SetPhone(CString phone) {
	this->phone = phone;

}
void CUserDTO::SetIsAdim(BOOL isAdmin) {
	this->isAdmin = isAdmin;
}