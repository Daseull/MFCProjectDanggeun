#pragma once
#include <afxstr.h>


// 
class CUserDTO {
public:
	CUserDTO();
private:
	CString userID;
	CString userPw;
	int town;
	CString phone;
	BOOL isAdmin;

public:
	// Getter
	CString CUserDTO::GetUserID() { return userID; }
	CString CUserDTO::GetUserPW() { return userPw; }
	int CUserDTO::GetTown() { return town; }
	CString CUserDTO::GetPhone() { return phone; }
	BOOL CUserDTO::GetIsAdim() { return isAdmin; }

	// Setter
	void SetUserID(CString userID);
	void SetUserPW(CString userPw);
	void SetTown(int nTown);
	void SetPhone(CString phone);
	void SetIsAdim(BOOL isAdmin);
};