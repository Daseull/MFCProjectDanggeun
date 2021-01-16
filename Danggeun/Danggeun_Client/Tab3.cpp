// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "Danggeun_Client.h"
#include "Tab3.h"
#include "afxdialogex.h"
#include "RoundButton2.h"
#include "RoundButtonStyle.h"
#include "DetailPage.h"

// CTab3(관심글목록) 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

//생성자
CTab3::CTab3(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CTab3, pParent)
    , m_strSearch(_T(""))
{
    //그리기(디자인)용 변수 초기화
    m_bk_brush.CreateSolidBrush(RGB(253, 212, 129));
    m_tMyButton1.SetRoundButtonStyle(&m_tMyButtonStyle);
    m_tMyButton2.SetRoundButtonStyle(&m_tMyButtonStyle);

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_SEARCH, m_tMyButton1);
    DDX_Control(pDX, IDC_BUTTON_BACK, m_tMyButton2);
    DDX_Control(pDX, IDC_LIST_HEART, m_list);
    DDX_Text(pDX, IDC_EDIT1, m_strSearch);
}


// CTab3 메시지 처리기
BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
    ON_BN_CLICKED(IDOK, &CTab3::OnBnClickedOk)
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CTab3::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_BACK, &CTab3::OnBnClickedButtonBack)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_HEART, &CTab3::OnDblclkListHeart)
END_MESSAGE_MAP()



//엔터 쳐도 닫히지 않게 처리
void CTab3::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //CDialogEx::OnOK();
}


//다이얼로그의 배경 색상 칠하기
HBRUSH CTab3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  여기서 DC의 특성을 변경합니다.
    //다이얼로그 색상 설정
    if (nCtlColor == CTLCOLOR_DLG) {
        return m_bk_brush;
    }
    //스태틱 색상 설정
    if (nCtlColor == CTLCOLOR_STATIC) {
        pDC->SetBkColor(RGB(253, 212, 129));
        pDC->SetTextColor(RGB(0, 0, 0));
        return m_bk_brush;
    }
    // TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
    return hbr;
}



BOOL CTab3::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    // TODO:  여기에 추가 초기화 작업을 추가합니다.

    //글목록에 보일 썸네일 이미지 리스트
    m_ImageList.Create(60, 60, ILC_COLORDDB | ILC_MASK, 8, 8);

    //리스트 컨트롤에 이미지 리스트 세팅
    m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

    //글 선택시 해당 줄의 행이 전체 선택되게 설정
    m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    //리스트 컨트롤의 컬럼 삽입
    m_list.InsertColumn(0, "글 제목", LVCFMT_LEFT, 400);
    m_list.InsertColumn(1, "가격", LVCFMT_RIGHT, 100);
    m_list.InsertColumn(2, "판매상태", LVCFMT_RIGHT, 100);
    //포스트 아이디는 컨트롤러에서 사용하며 사용자에게는 보이지 않도록 사이즈를 0으로 설정한다
    m_list.InsertColumn(3, "postID", LVCFMT_RIGHT, 0);

    //LoadBookmarkPost()를 호출해 글목록 리스트업, 화면에 뿌리기
    LoadBookmarkPost();

    return TRUE;  // return TRUE unless you set the focus to a control
               // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//관심 기록으로 리스트 컨트롤 채우기
void CTab3::LoadBookmarkPost() {

    //되돌아가기 버튼 숨기기
    GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_HIDE);


    //이전의 글리스트가 있다면 초기화
    int n = m_list.GetItemCount();
    while (n--)
        m_ImageList.Remove(0);
    m_list.DeleteAllItems();

    //DanggeunCliengDlg에서 선언된 DB접근용 변수들 
    extern CUserDTO* CurrentUser;
    extern CPostDB* postDB;
    extern CBookMarkDB* bookmarkDB;
    //DanggeunCliengDlg에서 선언된 판매상태(정수) 매핑 스트링 
    extern CString status[3];

    //유저가 북마크 한 모든 글 조회
    for (CPostDTO* post : postDB->dao.getAllByBookMark(CurrentUser->GetUserID())) {

       CBitmap bmp;
       CImage img;
       //이미지 저장소에 저장된 썸네일 용 작은 사진 로드
       img.Load("res\\small_" + post->GetImgName());
       if (img.IsNull()) {
           //로드 실패 시 깨진 이미지 로드
          img.Load("res\\LoadError.png");
       }
       //이미지 리스트에 해당 사진 추가
       bmp.Attach(img);
       m_ImageList.Add(&bmp, RGB(255, 255, 255));

       //리스트 컨트롤에 글 추가
       int i = m_list.GetItemCount();   
       m_list.AddItem(post->GetTitle(), i, 0, -1, i);   //글 제목과 사진 추가
       m_list.AddItem(post->GetPrice(), i, 1);          //가격 추가
       m_list.AddItem(status[post->GetStatus()], i, 2); //판매 상태 추가

       //포스트 아이디를 구하고 리스트 컨트롤에 추가
       int postid = post->GetPostID();
       CString postID;
       postID.Format("%d", postid);
       m_list.AddItem(postID, i, 3);
    }
    
    UpdateData(FALSE);
}


//검색
void CTab3::SearchPost(CString Key)
{
    //되돌아가기 버튼 활성화
    GetDlgItem(IDC_BUTTON_BACK)->ShowWindow(SW_SHOW);
    
    //검색창 비우기
    m_strSearch = "";
 
    //기존의 리스트 컨트롤과 이미지 리스트에 있던 내용 비우기
    int n = m_list.GetItemCount();
    while (n--)
        m_ImageList.Remove(0);
    m_list.DeleteAllItems();

    //검색어가 공백인 경우 검색어를 입력하세요 알림 후 종료
    if (Key.IsEmpty()) {
        AfxMessageBox("검색어를 입력하세요");
        return;
    }

    //DanggeunCliengDlg에서 선언된 DB접근용 변수들 
    extern CUserDTO* CurrentUser;
    extern CPostDB* postDB;
    extern CBookMarkDB* bookmarkDB;
    //DanggeunCliengDlg에서 선언된 판매상태(정수) 매핑 스트링 
    extern CString status[3];


    //사용자의 관심리스트 중에 제목으로 검색어를 가진 글 탐색
    for (CPostDTO* post : postDB->dao.getAllByBookMarkAndSearch(CurrentUser->GetUserID(), Key)) {
        CBitmap bmp;
        CImage img;
        
        //이미지 저장소에서 썸네일용 작은 이미지 로드
        img.Load("res\\small_" + post->GetImgName());
        if (img.IsNull()) {
            //로드 실패시 깨진 이미지 로드
            img.Load("res\\LoadError.png");
        }
        //이미지 리스트에 로드한 사진 추가
        bmp.Attach(img);
        m_ImageList.Add(&bmp, RGB(255, 255, 255));

        //리스트 컨트롤에 글 추가
        int i = m_list.GetItemCount();  
        m_list.AddItem(post->GetTitle(), i, 0, -1, i);  //리스트 컨트롤에 사진, 글제목 추가
        m_list.AddItem(post->GetPrice(), i, 1);         //리스트 컨트롤에 가격 추가
        m_list.AddItem(status[post->GetStatus()], i, 2);    //리스트 컨트롤에 판매 상태 추가
        //리스트 컨트롤에 포스트 아이디 추가
        int postid = post->GetPostID();
        CString postID;
        postID.Format("%d", postid);
        m_list.AddItem(postID, i, 3);
    }

    UpdateData(FALSE);
}


//검색 버튼 눌렀을 경우
void CTab3::OnBnClickedButtonSearch()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //m_strSearch에 검색어 받아오기
    UpdateData(TRUE);
    //검색&리스트업 함수 호출
    SearchPost(m_strSearch);
}

//되돌아가기 버튼 클릭시
void CTab3::OnBnClickedButtonBack()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //관심기록을 기준으로 다시 글 리스트업
    LoadBookmarkPost();
}

//검색시 엔터눌렀을 경우
BOOL CTab3::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
        OnBnClickedButtonSearch();  //검색 함수 호출

    return CDialogEx::PreTranslateMessage(pMsg);
}


//리스트컨트롤의 글을 더블클릭 했을 경우
void CTab3::OnDblclkListHeart(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    

    *pResult = 0;

    //선택된 글이 리스트 컨트롤의 몇번째 글인지 구하기
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int idx = pNMListView->iItem;

    //정상 선택인 경우
    if (idx != -1) {
        //해당행의 포스트 아이디(3번째 컬럼) 가져오기
        CString sIndexPostID;
        sIndexPostID = m_list.GetItemText(idx, 3);

        //가져온 스트링을 정수로 변환
        int PostID = _ttoi(sIndexPostID);
        extern CPostDB* postDB;

        //포스트 아이디를 넘겨 해당 글 내용이 있는 디테일 페이지 창 생성    
        CDetailPage dlg(postDB->dao.getPost(PostID));
        dlg.DoModal();


    }
    *pResult = 0;
}