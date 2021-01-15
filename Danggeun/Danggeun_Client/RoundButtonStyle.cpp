
#include "pch.h"

#include "math.h"
#include ".\roundbuttonstyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//생성자 
CRoundButtonStyle::CRoundButtonStyle(void)
: m_bButtonDrawn(false)
{
	//이미지가 없으면 사이즈 0으로 초기화
	m_tBtnSize	= CSize(0, 0);

	// 위신호 제거 크기
	m_tButtonStyle.m_dSizeAA					= 1.0;

	//테두리 두께 설정
	m_tButtonStyle.m_dHighLightX				=  0.0;
	m_tButtonStyle.m_dHighLightY				= -7.0;

	// 꼭짓점의 곡률
	m_tButtonStyle.m_dRadius					= 10.0;
	m_tButtonStyle.m_dBorderRatio				= 0.2;

	// 버튼의 높이
	m_tButtonStyle.m_dHeightBorder				= 0.0;
	m_tButtonStyle.m_dHeightButton				= 0.2;

	// 테두리 곡률
	m_tButtonStyle.m_dRadiusHighLight			= 3.0;
	m_tButtonStyle.m_dPowerHighLight			= 0.2;

	// 버튼의 상태에 따른 색상 설정

	//버튼의 초기상태
	m_tButtonStyle.m_tColorBack.m_tDisabled		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tDisabled	= RGB(255, 255, 255);
	m_tButtonStyle.m_tColorFace.m_tDisabled		= RGB(255, 255, 255);
	
	//버튼이 선택되었을 때
	m_tButtonStyle.m_tColorBack.m_tEnabled		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tEnabled	= RGB(255, 205, 105);
	m_tButtonStyle.m_tColorFace.m_tEnabled		= RGB(247, 134, 59);

	//버튼이 checkbox일 때
	m_tButtonStyle.m_tColorBack.m_tClicked		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tClicked	= RGB(255, 140, 16);
	m_tButtonStyle.m_tColorFace.m_tClicked		= RGB(255, 140, 16);

	//버튼이 눌렸을 때
	m_tButtonStyle.m_tColorBack.m_tPressed		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tPressed	= RGB(255, 174, 0);
	m_tButtonStyle.m_tColorFace.m_tPressed		= RGB(255, 174, 0);

	//버튼이 hot버튼일 때
	m_tButtonStyle.m_tColorBack.m_tHot			= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tHot		= RGB(255, 133, 0);
	m_tButtonStyle.m_tColorFace.m_tHot			= RGB(255, 133, 0);
}

//파괴자
CRoundButtonStyle::~CRoundButtonStyle(void)
{
}

//기존 버튼의 스타일 가져오기
bool CRoundButtonStyle::GetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	//버튼스타일 포인터가 생성되었는지 확인 
	if (_ptButtonStyle == NULL)
		return false;

	//특정 스타일로 버튼 디자인 입히기
	memcpy(_ptButtonStyle, &m_tButtonStyle, sizeof(tButtonStyle));

	//모두 완료
	return true;
}

//새로운 디자인으로 버튼 입히기
bool CRoundButtonStyle::SetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	//새로운 버튼 스타일이 할당되었는지 확인
	if (_ptButtonStyle == NULL)
		return false;

	//버튼 스타일 
	memcpy(&m_tButtonStyle, _ptButtonStyle, sizeof(tButtonStyle));

	//버튼의 디자인 다시 그려야할지 여부 
	m_bButtonDrawn = false;

	//모두 완료
	return true;
}

// 버튼의 테두리정보를 비트맵에 전달
CBitmap* CRoundButtonStyle::GetButtonEdge(CDC* _pDC)
{
	// 버튼의 상태가 바꼈는지
	if (!m_bButtonDrawn)
	{
		//버튼 디자인 입히기
		DrawMasks(_pDC);

		m_bButtonDrawn = true;
	}

	//비트맵에 포인터 return
	return &m_tBmpButtonEdge;
}

//버튼 크기
bool CRoundButtonStyle::DrawMasks(CDC* _pDC)
{
	CDC MemDC;

	//메모리에 dc생성
	if (MemDC.CreateCompatibleDC(_pDC) == FALSE)
		return false;

	// 버튼의 중앙으로부터 거리
	double		fDistCenter	= 0.0;
	// 하이라이트로부터 거리
	double		fDistHigh	= 0.0;
	// 하이라이트의 x좌표
	double		fXHigh;
	// 하이라이트의 y좌표
	double		fYHigh;
	// 배경색상
	double		fFacBack	= 0.0;
	// 테두리 색상 
	double		fFacBorder	= 0.0;
	// 버튼 내부 색상
	double		fFacFace	= 0.0;
	// 하이라이트 색상 
	double		fFacHigh	= 0.0;
	// 빨간색
	double		fFacR;
	// 초록색
	double		fFacG;
	// 파란색
	double		fFacB;
	// 실제 픽셀
	COLORREF	tColPixel;
	// 위신호제거 크기
	double		fSizeAA;
	// 바깥 테두리 곡률
	double		fRadOuter;
	// 내부 테두리 곡률
	double		fRadInner;
	// 테두리 곡률
	double		fRatioBorder;
	// 테두리 높이
	double		fHeightBorder;
	// 내부 높이
	double		fHeightButton;
	// 하이라이트 높이
	double		fRadHigh;
	// 하이라이트 두께
	double		fPowHigh;
	// 크기
	int			nSizeEdge = 0;

	// 하이라이트 값들 설정
	fSizeAA	= m_tButtonStyle.m_dSizeAA;

	fXHigh	= m_tButtonStyle.m_dHighLightX;
	fYHigh	= m_tButtonStyle.m_dHighLightY;

	fRadOuter		= m_tButtonStyle.m_dRadius;
	fRatioBorder	= m_tButtonStyle.m_dBorderRatio;

	fHeightBorder	= m_tButtonStyle.m_dHeightBorder;
	fHeightButton	= m_tButtonStyle.m_dHeightButton;

	fRadHigh		= m_tButtonStyle.m_dRadiusHighLight;
	fPowHigh		= m_tButtonStyle.m_dPowerHighLight;

	// 내부 테두리 설정
	fRadInner = __min(fRadOuter, __max(0.0f, fRadOuter * (1.0f - fRatioBorder)));

	// 꼭짓점 계산
	nSizeEdge = (int)ceil(fRadOuter + fSizeAA / 2.0);

	//버튼 사이즈 설정
	m_tBtnSize.SetSize(nSizeEdge, nSizeEdge);

	// 예전 비트맵 삭제하기
	if (m_tBmpButtonEdge.m_hObject != NULL)
		m_tBmpButtonEdge.DeleteObject();

	// 새로운 비트맵 생성
	m_tBmpButtonEdge.CreateCompatibleBitmap(
		_pDC, 
		2 * nSizeEdge + 1, 
		(2 * nSizeEdge + 1) * BS_LAST_STATE);

	// 버튼의 비트맵 가져오기
	HGDIOBJ hOldBmp = MemDC.SelectObject(m_tBmpButtonEdge);

	// 버튼의 꼭짓점들 
	int nX;
	int nY;
	int nState;

	//색상 변수 
	COLORREF	tColorBack;
	COLORREF	tColorBorder;
	COLORREF	tColorFace;
	
	for (nX = -nSizeEdge; nX <= nSizeEdge; nX++)
	{
		for (nY = -nSizeEdge; nY <= nSizeEdge; nY++)
		{
			// 중앙으로부터 버튼의 거리 계산하기
			fDistCenter	= sqrt((double)nX * (double)nX + (double)nY * (double)nY);

			//버튼의 바깥 계산하기
			fFacBack	= __max(0.0, __min(1.0, 0.5 + (fDistCenter - fRadOuter) * 2.0 / fSizeAA));

			// 테두리 두께 계산하기
			fFacBorder	= 1.0 - fHeightBorder * pow((fRadOuter + fRadInner - fDistCenter * 2.0) / (fRadOuter - fRadInner) ,2);
			fFacBorder	= __max(0.0, __min(1.0, 0.5 - (fDistCenter - fRadOuter) * 2.0 / fSizeAA)) * fFacBorder;
			fFacBorder	= __max(0.0, __min(1.0, 0.5 + (fDistCenter - fRadInner) * 2.0 / fSizeAA)) * fFacBorder;

			for (nState = 0; nState < BS_LAST_STATE; nState++)
			{
				//각 상태의 색상 설정하기
				switch(nState)
				{
					//버튼이 선택되었을 때
				case BS_ENABLED:
					tColorBack		= RGB(253, 212, 129);
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tEnabled;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tEnabled;
					break;
					//버튼이 checkbox일 때
				case BS_CLICKED:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tClicked;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tClicked;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tClicked;
					break;
					//버튼이 눌렸을 때
				case BS_PRESSED:
					tColorBack		= RGB(253, 212, 129);
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tPressed;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tPressed;
					break;
					//버튼이 hot버튼일 때
				case BS_HOT:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tHot;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tHot;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tHot;
					break;
					//초기값
				case BS_DISABLED:
				default:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tDisabled;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tDisabled;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tDisabled;
					break;
				}

				//버튼의 테두리 두께 계산하기
				fDistHigh	= sqrt(((double)nX - fXHigh) * ((double)nX - fXHigh) + ((double)nY - fYHigh) * ((double)nY - fYHigh));

				//내부 색상 계산하기
				if (fHeightButton > 0)
					fFacFace	= 1.0 - fHeightButton * (fDistCenter / fRadInner) * (fDistCenter / fRadInner);
				else
					fFacFace	= 1.0 + fHeightButton - fHeightButton * (fDistCenter / fRadInner) * (fDistCenter / fRadInner);
				fFacFace	= __max(0.0, __min(1.0, 0.5 - (fDistCenter - fRadInner) * 2.0 / fSizeAA)) * fFacFace;

				// 테두리 색상 계산하기
				fFacHigh	= 1.0 + __max(-1.0, __min(1.0, 1.0 - fHeightButton * fDistHigh / fRadHigh)) * fPowHigh;
				fFacFace = fFacFace * fFacHigh;

				// 색상 계산하기
				fFacR = 
					(float)GetRValue(tColorBack)	* fFacBack +
					(float)GetRValue(tColorBorder)	* fFacBorder +
					(float)GetRValue(tColorFace)	* fFacFace;
				fFacG = 
					(float)GetGValue(tColorBack)	* fFacBack +
					(float)GetGValue(tColorBorder)	* fFacBorder +
					(float)GetGValue(tColorFace)	* fFacFace;
				fFacB = 
					(float)GetBValue(tColorBack)	* fFacBack +
					(float)GetBValue(tColorBorder)	* fFacBorder +
					(float)GetBValue(tColorFace)	* fFacFace;

				//픽셀의 실제 값 계산하기
				tColPixel = RGB(
					__max(0, __min(255, (int)fFacR)),
					__max(0, __min(255, (int)fFacG)),
					__max(0, __min(255, (int)fFacB))
					);

				//픽셀 그리기
				MemDC.SetPixel(nSizeEdge + nX, nSizeEdge + nY + (2 * nSizeEdge + 1) * nState, tColPixel);
			}
		}
	}

	//기존 비트맵 가져오기
	MemDC.SelectObject(hOldBmp);

	return true;
}
