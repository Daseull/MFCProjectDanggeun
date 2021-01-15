#include "pch.h"
#include <math.h>
#include ".\RoundButton2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//생성자
CRoundButton2::CRoundButton2(void):	
	  m_bDefaultButton(false)
	, m_bIsCheckButton(false)
	, m_bIsRadioButton(false)
	, m_bIsHotButton(false)
	, m_bMouseOnButton(false)
	, m_bIsChecked(false)	
	, m_ptRoundButtonStyle(NULL)
	, m_rBtnSize(CRect(0, 0, 0, 0))
	, m_bRedraw(false)
	, m_sOldCaption(_T(""))
	  {

	//표준 폰트 
	m_tLogFont.lfHeight			= 16;
	m_tLogFont.lfWidth			= 0;
	m_tLogFont.lfEscapement		= 0;
	m_tLogFont.lfOrientation	= 0;
	m_tLogFont.lfWeight			= FW_BOLD;
	m_tLogFont.lfItalic			= false;
	m_tLogFont.lfUnderline		= false;
	m_tLogFont.lfStrikeOut		= false;
	m_tLogFont.lfCharSet		= DEFAULT_CHARSET;
	m_tLogFont.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	m_tLogFont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_tLogFont.lfQuality		= ANTIALIASED_QUALITY;
	m_tLogFont.lfPitchAndFamily	= DEFAULT_PITCH;
	strcpy_s(m_tLogFont.lfFaceName, "나눔고딕");

	m_tBtnFont.CreateFontIndirect(&m_tLogFont);

	//표준 색상
	m_tTextColor.m_tDisabled	= RGB(255, 133, 0);
	m_tTextColor.m_tEnabled		= RGB( 255,  255,  255);
	m_tTextColor.m_tClicked		= RGB( 255,  255, 255);
	m_tTextColor.m_tPressed		= RGB( 255,  255,  255);
	m_tTextColor.m_tHot			= RGB( 0,  0,  0);
}

//파괴자
CRoundButton2::~CRoundButton2(void)
{
}

// 버튼 스타일
bool CRoundButton2::SetRoundButtonStyle(CRoundButtonStyle* _ptRoundButtonStyle)
{
	//버튼이 생성되어있을 때 false 리턴
	if (_ptRoundButtonStyle == NULL)
		return false;

	//버튼 스타일에 포인터를 할당한다
	m_ptRoundButtonStyle = _ptRoundButtonStyle;

	//버튼 디자인 입히기
	m_bRedraw = true;

	//완료
	return false;
}

//버튼의 폰트 생성 
bool CRoundButton2::SetFont(LOGFONT* _ptLogFont)
{
	//폰트가 없다면 false반환
	if (_ptLogFont == NULL)
		return false;

	//이미 할당된 폰트에 대해서는 해제
	if (m_tBtnFont.m_hObject != NULL)
		m_tBtnFont.DeleteObject();

	//폰트를 저장
	memcpy(&m_tLogFont, _ptLogFont, sizeof(LOGFONT));

	//새로운 폰트 생성
	m_tBtnFont.CreateFontIndirect(&m_tLogFont);

	//버튼 디자인 입히기
	m_bRedraw = true;

	return true;
}

//버튼의 폰트 설정
bool CRoundButton2::GetFont(LOGFONT* _ptLogFont)
{
	//폰트가 없다면 false반환
	if (_ptLogFont == NULL)
		return false;

	//폰트 저장
	memcpy(_ptLogFont, &m_tLogFont, sizeof(LOGFONT));

	return true;
}

//폰트 색상 설정
bool CRoundButton2::SetTextColor(tColorScheme* _ptTextColor)
{
	//폰트 색상이 없다면 false반환
	if (_ptTextColor == NULL)
		return false;

	//폰트 저장
	memcpy(&m_tTextColor, _ptTextColor, sizeof(tColorScheme));

	//버튼 디자인 입히기
	m_bRedraw = true;

	return true;
}

//폰트의 색상 가져오기
bool CRoundButton2::GetTextColor(tColorScheme* _ptTextColor)
{
	//폰트 색상이 없다면 false반환
	if (_ptTextColor == NULL)
		return false;

	//폰트 저장
	memcpy(_ptTextColor, &m_tTextColor, sizeof(tColorScheme));

	return true;
}

//비트맵 저장하기
void CRoundButton2::GenButtonBMPs(CDC* _pDC, CRect _rRect)
{
	if (m_tBmpBtn.m_hObject != NULL)
		m_tBmpBtn.DeleteObject();

	//비트맵 초기화
	m_tBmpBtn.m_hObject = NULL;

	//비트맵 생성
	if (m_tBmpBtn.CreateCompatibleBitmap(_pDC, _rRect.Width(), _rRect.Height() * BS_LAST_STATE) == FALSE)
	{
		m_rBtnSize = CRect(0, 0, 0, 0);
	}
	else
	{
		m_rBtnSize = _rRect;
	}
}

//버튼의 표면 입히기
void CRoundButton2::DrawButtonFace(CDC* _pDC)
{
	// 디자인이 입혀져있지않은 상태
	if (m_ptRoundButtonStyle == NULL)
		return;

	// 비트맵의 포인터 가져오기
	CBitmap* pButtonMasks = m_ptRoundButtonStyle->GetButtonEdge(_pDC);

	//메모리 생성하기 
	CDC SourceDC;
	SourceDC.CreateCompatibleDC(_pDC);

	// DC에서 선택
	HGDIOBJ hOldBmp1 = SourceDC.SelectObject(pButtonMasks);

	int nState;

	CSize tEdgeSize = m_ptRoundButtonStyle->GetEdgeSize();
	CSize tCorrectedEdgeSize;
	CSize tMaskSize = m_ptRoundButtonStyle->GetMaskSize();

	//작은 크기의 버튼은 테두리 사이즈 재설정
	tCorrectedEdgeSize.cx = __min(tEdgeSize.cx, __min(m_rBtnSize.Width() / 2, m_rBtnSize.Height() / 2));
	tCorrectedEdgeSize.cy = tCorrectedEdgeSize.cx;

	for (nState = 0; nState < BS_LAST_STATE; nState++)
	{
		//꼭짓점 채우기

		//왼쪽 위
		_pDC->StretchBlt(
			0, 
			nState * m_rBtnSize.Height(), 
			tCorrectedEdgeSize.cx, 
			tCorrectedEdgeSize.cy, 
			&SourceDC, 
			0, 
			nState * tMaskSize.cy,
			tEdgeSize.cx,
			tEdgeSize.cy,
			SRCCOPY);
		// 왼쪽 아래
		_pDC->StretchBlt(
			0, 
			nState * m_rBtnSize.Height() + m_rBtnSize.Height() - tCorrectedEdgeSize.cy, 
			tCorrectedEdgeSize.cx, 
			tCorrectedEdgeSize.cy, 
			&SourceDC, 
			0, 
			nState * tMaskSize.cy + tMaskSize.cy - tEdgeSize.cy, 
			tEdgeSize.cx,
			tEdgeSize.cy,
			SRCCOPY);
		// 오른쪽 위
		_pDC->StretchBlt(
			m_rBtnSize.Width() - tCorrectedEdgeSize.cx, 
			nState * m_rBtnSize.Height(), 
			tCorrectedEdgeSize.cx, 
			tCorrectedEdgeSize.cy, 
			&SourceDC, 
			tMaskSize.cx - tEdgeSize.cx, 
			nState * tMaskSize.cy, 
			tEdgeSize.cx,
			tEdgeSize.cy,
			SRCCOPY);
		// 오른쪽 아래
		_pDC->StretchBlt(
			m_rBtnSize.Width() - tCorrectedEdgeSize.cx, 
			nState * m_rBtnSize.Height() + m_rBtnSize.Height() - tCorrectedEdgeSize.cy, 
			tCorrectedEdgeSize.cx, 
			tCorrectedEdgeSize.cy, 
			&SourceDC, 
			tMaskSize.cx - tEdgeSize.cx, 
			nState * tMaskSize.cy + tMaskSize.cy - tEdgeSize.cy, 
			tEdgeSize.cx,
			tEdgeSize.cy,
			SRCCOPY);
		//테두리 그리기

		// 위
		_pDC->StretchBlt(
			tCorrectedEdgeSize.cx, 
			nState * m_rBtnSize.Height(),
			m_rBtnSize.Width() - 2 * tCorrectedEdgeSize.cx,
			tCorrectedEdgeSize.cy,
			&SourceDC,
			tEdgeSize.cx,
			nState * tMaskSize.cy,
			1,
			tEdgeSize.cy,
			SRCCOPY);
		// 아래
		_pDC->StretchBlt(
			tCorrectedEdgeSize.cx, 
			nState * m_rBtnSize.Height() + m_rBtnSize.Height() - tCorrectedEdgeSize.cy,
			m_rBtnSize.Width() - 2 * tCorrectedEdgeSize.cx,
			tCorrectedEdgeSize.cy,
			&SourceDC,
			tEdgeSize.cx,
			nState * tMaskSize.cy + tMaskSize.cy - tEdgeSize.cy,
			1,
			tEdgeSize.cy,
			SRCCOPY);
		//왼쪽
		_pDC->StretchBlt(
			0, 
			nState * m_rBtnSize.Height() + tCorrectedEdgeSize.cy,
			tCorrectedEdgeSize.cx,
			m_rBtnSize.Height() - 2 * tCorrectedEdgeSize.cy,
			&SourceDC,
			0,
			nState * tMaskSize.cy + tEdgeSize.cy,
			tEdgeSize.cx,
			1,
			SRCCOPY);
		// 오른쪽
		_pDC->StretchBlt(
			m_rBtnSize.Width() - tCorrectedEdgeSize.cx, 
			nState * m_rBtnSize.Height() + tCorrectedEdgeSize.cy,
			tCorrectedEdgeSize.cx,
			m_rBtnSize.Height() - 2 * tCorrectedEdgeSize.cy,
			&SourceDC,
			tMaskSize.cx - tEdgeSize.cx,
			nState * tMaskSize.cy + tEdgeSize.cy,
			tEdgeSize.cx,
			1,
			SRCCOPY);
		
		//안쪽 채우기
		_pDC->StretchBlt(
			tCorrectedEdgeSize.cx,
			nState * m_rBtnSize.Height() + tCorrectedEdgeSize.cy,
			m_rBtnSize.Width() - 2* tCorrectedEdgeSize.cx,
			m_rBtnSize.Height() - 2 * tCorrectedEdgeSize.cy,
			&SourceDC,
			tEdgeSize.cx,
			nState * tMaskSize.cy + tEdgeSize.cy,
			1,
			1,
			SRCCOPY);
	}

	//기존 버튼 선택하기 
	SourceDC.SelectObject(hOldBmp1);
}

//버튼에 글자 채우기
void CRoundButton2::DrawButtonCaption(CDC *_pDC)
{
	//배경색상 투명도 설정
	int nOldBckMode = _pDC->SetBkMode(TRANSPARENT);

	//예전 글자 색상 가져오기
	COLORREF tOldColor = _pDC->SetTextColor(RGB(255,255,255));

	//dc에서 폰트 설정하기
	HGDIOBJ hOldFont = _pDC->SelectObject(&m_tBtnFont);

	//버튼의 글자 채우기
	CString sCaption;
	this->GetWindowText(sCaption);

	for (int nState = 0; nState < BS_LAST_STATE; nState++)
	{
		switch(nState)
		{
			//버튼이 눌러졌을 때
		case BS_ENABLED:
			_pDC->SetTextColor(m_tTextColor.m_tEnabled);
			break;
			//버튼이 checkbox 버튼이고 선택되었을 때
		case BS_CLICKED:
			_pDC->SetTextColor(m_tTextColor.m_tClicked);
			break;
			//버튼이 눌려졌을 때 
		case BS_PRESSED:
			_pDC->SetTextColor(m_tTextColor.m_tPressed);
			break;
			//버튼이 hot버튼일 때 
		case BS_HOT:
			_pDC->SetTextColor(m_tTextColor.m_tHot);
			break;
			//버튼의 초기상태
		case BS_DISABLED:
		default:
			_pDC->SetTextColor(m_tTextColor.m_tDisabled);
			break;
		}
		//버튼 글자 입히기
		_pDC->DrawText(
			sCaption, 
			CRect(
				m_rBtnSize.left, 
				nState * m_rBtnSize.Height() + m_rBtnSize.top, 
				m_rBtnSize.right, 
				nState * m_rBtnSize.Height() + m_rBtnSize.bottom),
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//기존 폰트 선택
	_pDC->SelectObject(hOldFont);

	// 기존 배경색상 선택
	_pDC->SetBkMode(nOldBckMode);

	// 기존 폰트 색상 선택 
	_pDC->SetTextColor(tOldColor);

}

//
void CRoundButton2::PreSubclassWindow()
{
#ifdef _DEBUG
	// 버튼위에 디자인 입히기
	TCHAR buffer[255];
	GetClassName (m_hWnd, buffer, sizeof(buffer) / sizeof(TCHAR));
	ASSERT (CString (buffer) == _T("Button"));
#endif

	// 버튼의 초기상태인지
	if (GetStyle() & 0x0FL)
		m_bDefaultButton = true;

	//버튼에 디자인 입히기
	ModifyStyle (0x0FL, BS_OWNERDRAW | BS_AUTOCHECKBOX, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
}

//버튼의 외향 변경 
void CRoundButton2::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//버튼의 dc가져오기
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT (pDC != NULL);

	//버튼이 생성되어야하는가
	bool bGenerate = !m_rBtnSize.EqualRect(&lpDrawItemStruct->rcItem) || m_bRedraw;

	// 버튼이 사각형인지 체크
	if (bGenerate)
	{
		// 비트맵 생성하기
		GenButtonBMPs(pDC, lpDrawItemStruct->rcItem);

		//디자인 입히기 성공
		m_bRedraw = false;
	}

	//dc에 생성하기 
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	HGDIOBJ hOldBmp = MemDC.SelectObject(m_tBmpBtn);

	CString sActualCaption;
	//버튼 caption 읽기
	GetWindowText(sActualCaption);

	//버튼의 caption이 바뀌었는지 확인 
	if (sActualCaption != m_sOldCaption)
		bGenerate = true;

	//기존 caption 가져오기
	m_sOldCaption = sActualCaption;

	//버튼 생성하기
	if (bGenerate)
	{
		//버튼 그리기
		DrawButtonFace(&MemDC);

		//버튼에 글자 입히기
		DrawButtonCaption(&MemDC);
	}

	int nButtonState;
	//버튼이 눌러졌을 때
	nButtonState = BS_ENABLED;

	//버튼이 hot버튼일 때 
	if (m_bIsHotButton && m_bMouseOnButton)
		nButtonState = BS_HOT;

	//버튼이 선택해제되었을 때
	if ((lpDrawItemStruct->itemState & ODS_DISABLED) == ODS_DISABLED)
		nButtonState = BS_DISABLED;
	else
	{
		//버튼이 눌렸을 때
		if ((lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED)
			nButtonState = BS_PRESSED;
		else
		{
			//버튼이 checkbox 버튼이고 선택되었을 때
			if (this->m_bIsChecked)
			{
				nButtonState = BS_CLICKED;
			}
		}
	}

	// 비트맵 그리기
	pDC->BitBlt(
		lpDrawItemStruct->rcItem.left, 
		lpDrawItemStruct->rcItem.top, 
		m_rBtnSize.Width(), 
		m_rBtnSize.Height(), 
		&MemDC, 
		0, 
		m_rBtnSize.Height() * nButtonState, 
		SRCCOPY);

	MemDC.SelectObject(hOldBmp);
}

//멤버함수
BEGIN_MESSAGE_MAP(CRoundButton2, CButton)
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()

//버튼의 유형
void CRoundButton2::OnLButtonUp(UINT nFlags, CPoint point)
{
	//버튼이 체크박스 일때
	if (m_bIsCheckButton)
	{
		m_bIsChecked = !m_bIsChecked;
	}
	//버튼이 radio버튼일 때
	if (m_bIsRadioButton)
	{
		m_bIsChecked = true;
	}

	CButton::OnLButtonUp(nFlags, point);
}

//마우스의 움직임 파악
void CRoundButton2::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcClient;

	//버튼의 위치파악
	GetClientRect(rcClient);

	//마우스의 위치 
	if (rcClient.PtInRect(point))
	{
		// 마우스가 버튼 위에 놓여있을 때
		bool bRedrawNeeded = !m_bMouseOnButton;

		// 마우스가 버튼 위에 놓여있음  
		m_bMouseOnButton = true;

		//마우스의 위치 파악하기
		SetCapture();

		//버튼이 hot 버튼일때 
		if (m_bIsHotButton)
			Invalidate();
	}
	else
	{
		//마우스의 위치를 잃어버렸을 때
		m_bMouseOnButton = false;

		//마우스가 버튼에서 벗어났을 때
		ReleaseCapture();

		//버튼이 hot 버튼일때 
		if (m_bIsHotButton)
			Invalidate();
	}

	CButton::OnMouseMove(nFlags, point);
}

//마우스의 위치가 달라졌음 
void CRoundButton2::OnCaptureChanged(CWnd *pWnd)
{
	//마우스 위치를 잃었을 때 
	if (GetCapture() != this)
	{
		//마우스 위치를 잃어서 버튼의 위치를 모를 때
		m_bMouseOnButton = false;

		//버튼이 hot버튼일 때
		if (m_bIsHotButton)
			Invalidate();
	}

	CButton::OnCaptureChanged(pWnd);
}
