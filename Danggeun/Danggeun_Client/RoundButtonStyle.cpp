
#include "pch.h"

#include "math.h"
#include ".\roundbuttonstyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//������ 
CRoundButtonStyle::CRoundButtonStyle(void)
: m_bButtonDrawn(false)
{
	//�̹����� ������ ������ 0���� �ʱ�ȭ
	m_tBtnSize	= CSize(0, 0);

	// ����ȣ ���� ũ��
	m_tButtonStyle.m_dSizeAA					= 1.0;

	//�׵θ� �β� ����
	m_tButtonStyle.m_dHighLightX				=  0.0;
	m_tButtonStyle.m_dHighLightY				= -7.0;

	// �������� ���
	m_tButtonStyle.m_dRadius					= 10.0;
	m_tButtonStyle.m_dBorderRatio				= 0.2;

	// ��ư�� ����
	m_tButtonStyle.m_dHeightBorder				= 0.0;
	m_tButtonStyle.m_dHeightButton				= 0.2;

	// �׵θ� ���
	m_tButtonStyle.m_dRadiusHighLight			= 3.0;
	m_tButtonStyle.m_dPowerHighLight			= 0.2;

	// ��ư�� ���¿� ���� ���� ����

	//��ư�� �ʱ����
	m_tButtonStyle.m_tColorBack.m_tDisabled		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tDisabled	= RGB(255, 255, 255);
	m_tButtonStyle.m_tColorFace.m_tDisabled		= RGB(255, 255, 255);
	
	//��ư�� ���õǾ��� ��
	m_tButtonStyle.m_tColorBack.m_tEnabled		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tEnabled	= RGB(255, 205, 105);
	m_tButtonStyle.m_tColorFace.m_tEnabled		= RGB(247, 134, 59);

	//��ư�� checkbox�� ��
	m_tButtonStyle.m_tColorBack.m_tClicked		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tClicked	= RGB(255, 140, 16);
	m_tButtonStyle.m_tColorFace.m_tClicked		= RGB(255, 140, 16);

	//��ư�� ������ ��
	m_tButtonStyle.m_tColorBack.m_tPressed		= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tPressed	= RGB(255, 174, 0);
	m_tButtonStyle.m_tColorFace.m_tPressed		= RGB(255, 174, 0);

	//��ư�� hot��ư�� ��
	m_tButtonStyle.m_tColorBack.m_tHot			= GetSysColor(COLOR_3DFACE);
	m_tButtonStyle.m_tColorBorder.m_tHot		= RGB(255, 133, 0);
	m_tButtonStyle.m_tColorFace.m_tHot			= RGB(255, 133, 0);
}

//�ı���
CRoundButtonStyle::~CRoundButtonStyle(void)
{
}

//���� ��ư�� ��Ÿ�� ��������
bool CRoundButtonStyle::GetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	//��ư��Ÿ�� �����Ͱ� �����Ǿ����� Ȯ�� 
	if (_ptButtonStyle == NULL)
		return false;

	//Ư�� ��Ÿ�Ϸ� ��ư ������ ������
	memcpy(_ptButtonStyle, &m_tButtonStyle, sizeof(tButtonStyle));

	//��� �Ϸ�
	return true;
}

//���ο� ���������� ��ư ������
bool CRoundButtonStyle::SetButtonStyle(tButtonStyle* _ptButtonStyle)
{
	//���ο� ��ư ��Ÿ���� �Ҵ�Ǿ����� Ȯ��
	if (_ptButtonStyle == NULL)
		return false;

	//��ư ��Ÿ�� 
	memcpy(&m_tButtonStyle, _ptButtonStyle, sizeof(tButtonStyle));

	//��ư�� ������ �ٽ� �׷������� ���� 
	m_bButtonDrawn = false;

	//��� �Ϸ�
	return true;
}

// ��ư�� �׵θ������� ��Ʈ�ʿ� ����
CBitmap* CRoundButtonStyle::GetButtonEdge(CDC* _pDC)
{
	// ��ư�� ���°� �ٲ�����
	if (!m_bButtonDrawn)
	{
		//��ư ������ ������
		DrawMasks(_pDC);

		m_bButtonDrawn = true;
	}

	//��Ʈ�ʿ� ������ return
	return &m_tBmpButtonEdge;
}

//��ư ũ��
bool CRoundButtonStyle::DrawMasks(CDC* _pDC)
{
	CDC MemDC;

	//�޸𸮿� dc����
	if (MemDC.CreateCompatibleDC(_pDC) == FALSE)
		return false;

	// ��ư�� �߾����κ��� �Ÿ�
	double		fDistCenter	= 0.0;
	// ���̶���Ʈ�κ��� �Ÿ�
	double		fDistHigh	= 0.0;
	// ���̶���Ʈ�� x��ǥ
	double		fXHigh;
	// ���̶���Ʈ�� y��ǥ
	double		fYHigh;
	// ������
	double		fFacBack	= 0.0;
	// �׵θ� ���� 
	double		fFacBorder	= 0.0;
	// ��ư ���� ����
	double		fFacFace	= 0.0;
	// ���̶���Ʈ ���� 
	double		fFacHigh	= 0.0;
	// ������
	double		fFacR;
	// �ʷϻ�
	double		fFacG;
	// �Ķ���
	double		fFacB;
	// ���� �ȼ�
	COLORREF	tColPixel;
	// ����ȣ���� ũ��
	double		fSizeAA;
	// �ٱ� �׵θ� ���
	double		fRadOuter;
	// ���� �׵θ� ���
	double		fRadInner;
	// �׵θ� ���
	double		fRatioBorder;
	// �׵θ� ����
	double		fHeightBorder;
	// ���� ����
	double		fHeightButton;
	// ���̶���Ʈ ����
	double		fRadHigh;
	// ���̶���Ʈ �β�
	double		fPowHigh;
	// ũ��
	int			nSizeEdge = 0;

	// ���̶���Ʈ ���� ����
	fSizeAA	= m_tButtonStyle.m_dSizeAA;

	fXHigh	= m_tButtonStyle.m_dHighLightX;
	fYHigh	= m_tButtonStyle.m_dHighLightY;

	fRadOuter		= m_tButtonStyle.m_dRadius;
	fRatioBorder	= m_tButtonStyle.m_dBorderRatio;

	fHeightBorder	= m_tButtonStyle.m_dHeightBorder;
	fHeightButton	= m_tButtonStyle.m_dHeightButton;

	fRadHigh		= m_tButtonStyle.m_dRadiusHighLight;
	fPowHigh		= m_tButtonStyle.m_dPowerHighLight;

	// ���� �׵θ� ����
	fRadInner = __min(fRadOuter, __max(0.0f, fRadOuter * (1.0f - fRatioBorder)));

	// ������ ���
	nSizeEdge = (int)ceil(fRadOuter + fSizeAA / 2.0);

	//��ư ������ ����
	m_tBtnSize.SetSize(nSizeEdge, nSizeEdge);

	// ���� ��Ʈ�� �����ϱ�
	if (m_tBmpButtonEdge.m_hObject != NULL)
		m_tBmpButtonEdge.DeleteObject();

	// ���ο� ��Ʈ�� ����
	m_tBmpButtonEdge.CreateCompatibleBitmap(
		_pDC, 
		2 * nSizeEdge + 1, 
		(2 * nSizeEdge + 1) * BS_LAST_STATE);

	// ��ư�� ��Ʈ�� ��������
	HGDIOBJ hOldBmp = MemDC.SelectObject(m_tBmpButtonEdge);

	// ��ư�� �������� 
	int nX;
	int nY;
	int nState;

	//���� ���� 
	COLORREF	tColorBack;
	COLORREF	tColorBorder;
	COLORREF	tColorFace;
	
	for (nX = -nSizeEdge; nX <= nSizeEdge; nX++)
	{
		for (nY = -nSizeEdge; nY <= nSizeEdge; nY++)
		{
			// �߾����κ��� ��ư�� �Ÿ� ����ϱ�
			fDistCenter	= sqrt((double)nX * (double)nX + (double)nY * (double)nY);

			//��ư�� �ٱ� ����ϱ�
			fFacBack	= __max(0.0, __min(1.0, 0.5 + (fDistCenter - fRadOuter) * 2.0 / fSizeAA));

			// �׵θ� �β� ����ϱ�
			fFacBorder	= 1.0 - fHeightBorder * pow((fRadOuter + fRadInner - fDistCenter * 2.0) / (fRadOuter - fRadInner) ,2);
			fFacBorder	= __max(0.0, __min(1.0, 0.5 - (fDistCenter - fRadOuter) * 2.0 / fSizeAA)) * fFacBorder;
			fFacBorder	= __max(0.0, __min(1.0, 0.5 + (fDistCenter - fRadInner) * 2.0 / fSizeAA)) * fFacBorder;

			for (nState = 0; nState < BS_LAST_STATE; nState++)
			{
				//�� ������ ���� �����ϱ�
				switch(nState)
				{
					//��ư�� ���õǾ��� ��
				case BS_ENABLED:
					tColorBack		= RGB(253, 212, 129);
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tEnabled;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tEnabled;
					break;
					//��ư�� checkbox�� ��
				case BS_CLICKED:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tClicked;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tClicked;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tClicked;
					break;
					//��ư�� ������ ��
				case BS_PRESSED:
					tColorBack		= RGB(253, 212, 129);
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tPressed;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tPressed;
					break;
					//��ư�� hot��ư�� ��
				case BS_HOT:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tHot;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tHot;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tHot;
					break;
					//�ʱⰪ
				case BS_DISABLED:
				default:
					tColorBack		= m_tButtonStyle.m_tColorBack.m_tDisabled;
					tColorBorder	= m_tButtonStyle.m_tColorBorder.m_tDisabled;
					tColorFace		= m_tButtonStyle.m_tColorFace.m_tDisabled;
					break;
				}

				//��ư�� �׵θ� �β� ����ϱ�
				fDistHigh	= sqrt(((double)nX - fXHigh) * ((double)nX - fXHigh) + ((double)nY - fYHigh) * ((double)nY - fYHigh));

				//���� ���� ����ϱ�
				if (fHeightButton > 0)
					fFacFace	= 1.0 - fHeightButton * (fDistCenter / fRadInner) * (fDistCenter / fRadInner);
				else
					fFacFace	= 1.0 + fHeightButton - fHeightButton * (fDistCenter / fRadInner) * (fDistCenter / fRadInner);
				fFacFace	= __max(0.0, __min(1.0, 0.5 - (fDistCenter - fRadInner) * 2.0 / fSizeAA)) * fFacFace;

				// �׵θ� ���� ����ϱ�
				fFacHigh	= 1.0 + __max(-1.0, __min(1.0, 1.0 - fHeightButton * fDistHigh / fRadHigh)) * fPowHigh;
				fFacFace = fFacFace * fFacHigh;

				// ���� ����ϱ�
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

				//�ȼ��� ���� �� ����ϱ�
				tColPixel = RGB(
					__max(0, __min(255, (int)fFacR)),
					__max(0, __min(255, (int)fFacG)),
					__max(0, __min(255, (int)fFacB))
					);

				//�ȼ� �׸���
				MemDC.SetPixel(nSizeEdge + nX, nSizeEdge + nY + (2 * nSizeEdge + 1) * nState, tColPixel);
			}
		}
	}

	//���� ��Ʈ�� ��������
	MemDC.SelectObject(hOldBmp);

	return true;
}
