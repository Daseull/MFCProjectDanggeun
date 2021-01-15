#include "pch.h"
#include <math.h>
#include ".\RoundButton2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//������
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

	//ǥ�� ��Ʈ 
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
	strcpy_s(m_tLogFont.lfFaceName, "�������");

	m_tBtnFont.CreateFontIndirect(&m_tLogFont);

	//ǥ�� ����
	m_tTextColor.m_tDisabled	= RGB(255, 133, 0);
	m_tTextColor.m_tEnabled		= RGB( 255,  255,  255);
	m_tTextColor.m_tClicked		= RGB( 255,  255, 255);
	m_tTextColor.m_tPressed		= RGB( 255,  255,  255);
	m_tTextColor.m_tHot			= RGB( 0,  0,  0);
}

//�ı���
CRoundButton2::~CRoundButton2(void)
{
}

// ��ư ��Ÿ��
bool CRoundButton2::SetRoundButtonStyle(CRoundButtonStyle* _ptRoundButtonStyle)
{
	//��ư�� �����Ǿ����� �� false ����
	if (_ptRoundButtonStyle == NULL)
		return false;

	//��ư ��Ÿ�Ͽ� �����͸� �Ҵ��Ѵ�
	m_ptRoundButtonStyle = _ptRoundButtonStyle;

	//��ư ������ ������
	m_bRedraw = true;

	//�Ϸ�
	return false;
}

//��ư�� ��Ʈ ���� 
bool CRoundButton2::SetFont(LOGFONT* _ptLogFont)
{
	//��Ʈ�� ���ٸ� false��ȯ
	if (_ptLogFont == NULL)
		return false;

	//�̹� �Ҵ�� ��Ʈ�� ���ؼ��� ����
	if (m_tBtnFont.m_hObject != NULL)
		m_tBtnFont.DeleteObject();

	//��Ʈ�� ����
	memcpy(&m_tLogFont, _ptLogFont, sizeof(LOGFONT));

	//���ο� ��Ʈ ����
	m_tBtnFont.CreateFontIndirect(&m_tLogFont);

	//��ư ������ ������
	m_bRedraw = true;

	return true;
}

//��ư�� ��Ʈ ����
bool CRoundButton2::GetFont(LOGFONT* _ptLogFont)
{
	//��Ʈ�� ���ٸ� false��ȯ
	if (_ptLogFont == NULL)
		return false;

	//��Ʈ ����
	memcpy(_ptLogFont, &m_tLogFont, sizeof(LOGFONT));

	return true;
}

//��Ʈ ���� ����
bool CRoundButton2::SetTextColor(tColorScheme* _ptTextColor)
{
	//��Ʈ ������ ���ٸ� false��ȯ
	if (_ptTextColor == NULL)
		return false;

	//��Ʈ ����
	memcpy(&m_tTextColor, _ptTextColor, sizeof(tColorScheme));

	//��ư ������ ������
	m_bRedraw = true;

	return true;
}

//��Ʈ�� ���� ��������
bool CRoundButton2::GetTextColor(tColorScheme* _ptTextColor)
{
	//��Ʈ ������ ���ٸ� false��ȯ
	if (_ptTextColor == NULL)
		return false;

	//��Ʈ ����
	memcpy(_ptTextColor, &m_tTextColor, sizeof(tColorScheme));

	return true;
}

//��Ʈ�� �����ϱ�
void CRoundButton2::GenButtonBMPs(CDC* _pDC, CRect _rRect)
{
	if (m_tBmpBtn.m_hObject != NULL)
		m_tBmpBtn.DeleteObject();

	//��Ʈ�� �ʱ�ȭ
	m_tBmpBtn.m_hObject = NULL;

	//��Ʈ�� ����
	if (m_tBmpBtn.CreateCompatibleBitmap(_pDC, _rRect.Width(), _rRect.Height() * BS_LAST_STATE) == FALSE)
	{
		m_rBtnSize = CRect(0, 0, 0, 0);
	}
	else
	{
		m_rBtnSize = _rRect;
	}
}

//��ư�� ǥ�� ������
void CRoundButton2::DrawButtonFace(CDC* _pDC)
{
	// �������� �������������� ����
	if (m_ptRoundButtonStyle == NULL)
		return;

	// ��Ʈ���� ������ ��������
	CBitmap* pButtonMasks = m_ptRoundButtonStyle->GetButtonEdge(_pDC);

	//�޸� �����ϱ� 
	CDC SourceDC;
	SourceDC.CreateCompatibleDC(_pDC);

	// DC���� ����
	HGDIOBJ hOldBmp1 = SourceDC.SelectObject(pButtonMasks);

	int nState;

	CSize tEdgeSize = m_ptRoundButtonStyle->GetEdgeSize();
	CSize tCorrectedEdgeSize;
	CSize tMaskSize = m_ptRoundButtonStyle->GetMaskSize();

	//���� ũ���� ��ư�� �׵θ� ������ �缳��
	tCorrectedEdgeSize.cx = __min(tEdgeSize.cx, __min(m_rBtnSize.Width() / 2, m_rBtnSize.Height() / 2));
	tCorrectedEdgeSize.cy = tCorrectedEdgeSize.cx;

	for (nState = 0; nState < BS_LAST_STATE; nState++)
	{
		//������ ä���

		//���� ��
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
		// ���� �Ʒ�
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
		// ������ ��
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
		// ������ �Ʒ�
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
		//�׵θ� �׸���

		// ��
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
		// �Ʒ�
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
		//����
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
		// ������
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
		
		//���� ä���
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

	//���� ��ư �����ϱ� 
	SourceDC.SelectObject(hOldBmp1);
}

//��ư�� ���� ä���
void CRoundButton2::DrawButtonCaption(CDC *_pDC)
{
	//������ ���� ����
	int nOldBckMode = _pDC->SetBkMode(TRANSPARENT);

	//���� ���� ���� ��������
	COLORREF tOldColor = _pDC->SetTextColor(RGB(255,255,255));

	//dc���� ��Ʈ �����ϱ�
	HGDIOBJ hOldFont = _pDC->SelectObject(&m_tBtnFont);

	//��ư�� ���� ä���
	CString sCaption;
	this->GetWindowText(sCaption);

	for (int nState = 0; nState < BS_LAST_STATE; nState++)
	{
		switch(nState)
		{
			//��ư�� �������� ��
		case BS_ENABLED:
			_pDC->SetTextColor(m_tTextColor.m_tEnabled);
			break;
			//��ư�� checkbox ��ư�̰� ���õǾ��� ��
		case BS_CLICKED:
			_pDC->SetTextColor(m_tTextColor.m_tClicked);
			break;
			//��ư�� �������� �� 
		case BS_PRESSED:
			_pDC->SetTextColor(m_tTextColor.m_tPressed);
			break;
			//��ư�� hot��ư�� �� 
		case BS_HOT:
			_pDC->SetTextColor(m_tTextColor.m_tHot);
			break;
			//��ư�� �ʱ����
		case BS_DISABLED:
		default:
			_pDC->SetTextColor(m_tTextColor.m_tDisabled);
			break;
		}
		//��ư ���� ������
		_pDC->DrawText(
			sCaption, 
			CRect(
				m_rBtnSize.left, 
				nState * m_rBtnSize.Height() + m_rBtnSize.top, 
				m_rBtnSize.right, 
				nState * m_rBtnSize.Height() + m_rBtnSize.bottom),
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//���� ��Ʈ ����
	_pDC->SelectObject(hOldFont);

	// ���� ������ ����
	_pDC->SetBkMode(nOldBckMode);

	// ���� ��Ʈ ���� ���� 
	_pDC->SetTextColor(tOldColor);

}

//
void CRoundButton2::PreSubclassWindow()
{
#ifdef _DEBUG
	// ��ư���� ������ ������
	TCHAR buffer[255];
	GetClassName (m_hWnd, buffer, sizeof(buffer) / sizeof(TCHAR));
	ASSERT (CString (buffer) == _T("Button"));
#endif

	// ��ư�� �ʱ��������
	if (GetStyle() & 0x0FL)
		m_bDefaultButton = true;

	//��ư�� ������ ������
	ModifyStyle (0x0FL, BS_OWNERDRAW | BS_AUTOCHECKBOX, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
}

//��ư�� ���� ���� 
void CRoundButton2::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//��ư�� dc��������
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT (pDC != NULL);

	//��ư�� �����Ǿ���ϴ°�
	bool bGenerate = !m_rBtnSize.EqualRect(&lpDrawItemStruct->rcItem) || m_bRedraw;

	// ��ư�� �簢������ üũ
	if (bGenerate)
	{
		// ��Ʈ�� �����ϱ�
		GenButtonBMPs(pDC, lpDrawItemStruct->rcItem);

		//������ ������ ����
		m_bRedraw = false;
	}

	//dc�� �����ϱ� 
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	HGDIOBJ hOldBmp = MemDC.SelectObject(m_tBmpBtn);

	CString sActualCaption;
	//��ư caption �б�
	GetWindowText(sActualCaption);

	//��ư�� caption�� �ٲ������ Ȯ�� 
	if (sActualCaption != m_sOldCaption)
		bGenerate = true;

	//���� caption ��������
	m_sOldCaption = sActualCaption;

	//��ư �����ϱ�
	if (bGenerate)
	{
		//��ư �׸���
		DrawButtonFace(&MemDC);

		//��ư�� ���� ������
		DrawButtonCaption(&MemDC);
	}

	int nButtonState;
	//��ư�� �������� ��
	nButtonState = BS_ENABLED;

	//��ư�� hot��ư�� �� 
	if (m_bIsHotButton && m_bMouseOnButton)
		nButtonState = BS_HOT;

	//��ư�� ���������Ǿ��� ��
	if ((lpDrawItemStruct->itemState & ODS_DISABLED) == ODS_DISABLED)
		nButtonState = BS_DISABLED;
	else
	{
		//��ư�� ������ ��
		if ((lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED)
			nButtonState = BS_PRESSED;
		else
		{
			//��ư�� checkbox ��ư�̰� ���õǾ��� ��
			if (this->m_bIsChecked)
			{
				nButtonState = BS_CLICKED;
			}
		}
	}

	// ��Ʈ�� �׸���
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

//����Լ�
BEGIN_MESSAGE_MAP(CRoundButton2, CButton)
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()

//��ư�� ����
void CRoundButton2::OnLButtonUp(UINT nFlags, CPoint point)
{
	//��ư�� üũ�ڽ� �϶�
	if (m_bIsCheckButton)
	{
		m_bIsChecked = !m_bIsChecked;
	}
	//��ư�� radio��ư�� ��
	if (m_bIsRadioButton)
	{
		m_bIsChecked = true;
	}

	CButton::OnLButtonUp(nFlags, point);
}

//���콺�� ������ �ľ�
void CRoundButton2::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcClient;

	//��ư�� ��ġ�ľ�
	GetClientRect(rcClient);

	//���콺�� ��ġ 
	if (rcClient.PtInRect(point))
	{
		// ���콺�� ��ư ���� �������� ��
		bool bRedrawNeeded = !m_bMouseOnButton;

		// ���콺�� ��ư ���� ��������  
		m_bMouseOnButton = true;

		//���콺�� ��ġ �ľ��ϱ�
		SetCapture();

		//��ư�� hot ��ư�϶� 
		if (m_bIsHotButton)
			Invalidate();
	}
	else
	{
		//���콺�� ��ġ�� �Ҿ������ ��
		m_bMouseOnButton = false;

		//���콺�� ��ư���� ����� ��
		ReleaseCapture();

		//��ư�� hot ��ư�϶� 
		if (m_bIsHotButton)
			Invalidate();
	}

	CButton::OnMouseMove(nFlags, point);
}

//���콺�� ��ġ�� �޶����� 
void CRoundButton2::OnCaptureChanged(CWnd *pWnd)
{
	//���콺 ��ġ�� �Ҿ��� �� 
	if (GetCapture() != this)
	{
		//���콺 ��ġ�� �Ҿ ��ư�� ��ġ�� �� ��
		m_bMouseOnButton = false;

		//��ư�� hot��ư�� ��
		if (m_bIsHotButton)
			Invalidate();
	}

	CButton::OnCaptureChanged(pWnd);
}
