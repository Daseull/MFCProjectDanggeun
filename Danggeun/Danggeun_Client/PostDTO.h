#pragma once
#include <afxstr.h>

// 
class CPostDTO {
public:
	CPostDTO();
private:
	int postID; // PK
	CString userID; // FK
	int town; 
	CString title;
	CString content; // �ſ� �� ������? NoSQL>??
	CString imgName; // img in res
	int status; // 0, 1, 2: �Ǹ���, ������, �Ǹ� �Ϸ�
	CString price; // ����� �������� ����.. ���������� ���� ��

public:
	// Getter
	int CPostDTO::GetPostID() { return postID; }
	CString CPostDTO::GetUserID() { return userID; }
	int CPostDTO::GetTown() { return town; }
	CString CPostDTO::GetTitle() { return title; }
	CString CPostDTO::GetContent() { return content; }
	CString CPostDTO::GetImgName() { return imgName; }
	int CPostDTO::GetStatus() { return status; }
	CString CPostDTO::GetPrice() { return price; }

	// Setter
	void CPostDTO::SetPostID(int postID);
	void CPostDTO::SetUserID(CString userID);
	void CPostDTO::SetTown(int town);
	void CPostDTO::SetTitle(CString title);
	void CPostDTO::SetContent(CString content);
	void CPostDTO::SetImgName(CString imgName);
	void CPostDTO::SetStauts(int status);
	void CPostDTO::SetPrice(CString  price);
};