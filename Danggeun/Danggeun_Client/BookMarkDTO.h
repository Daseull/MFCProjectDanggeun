#pragma once
#include <afxstr.h>


// 
class CBookMarkDTO {
public:
	CBookMarkDTO();
private:
	CString userID;
	CString userPw;
	int town;
	CString phone;
	BOOL isAdmin;

public:
	// Getter
	CString CBookMarkDTO::GetUserID() { return userID; }
	CString CBookMarkDTO::GetUserPW() { return userPw; }
	int CBookMarkDTO::GetTown() { return town; }
	CString CBookMarkDTO::GetPhone() { return phone; }
	BOOL CBookMarkDTO::GetIsAdim() { return isAdmin; }

	// Setter
	void SetUserID(CString userID);
	void SetUserPW(CString userPw);
	void SetTown(int nTown);
	void SetPhone(CString phone);
	void SetIsAdim(BOOL isAdmin);
};