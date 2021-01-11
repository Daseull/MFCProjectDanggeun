#include "pch.h"
#include "PostDTO.h"

CPostDTO::CPostDTO() {
	CPostDTO::SetPostID(-1);
	CPostDTO::SetUserID("");
	CPostDTO::SetTown(-1);
	CPostDTO::SetTitle("");
	CPostDTO::SetContent("");
	CPostDTO::SetImgName("");
}

// Setter
void CPostDTO::SetPostID(int postID) {
	this->postID = postID;
}
void CPostDTO::SetUserID(CString userID) {
	this->userID = userID;
}
void CPostDTO::SetTown(int town) {
	this->town = town;
}
void CPostDTO::SetTitle(CString title) {
	this->title = title;
}
void CPostDTO::SetContent(CString content) {
	this->content = content;
}
void CPostDTO::SetImgName(CString imgName) {
	this->imgName = imgName;
}