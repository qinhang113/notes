// MenuBtn.cpp: 实现文件
//

#include "pch.h"
#include "MenuBtn.h"


// MenuBtn

IMPLEMENT_DYNAMIC(MenuBtn, CButton)

CFont MenuBtn::m_FontContent;
MenuBtn::MenuBtn()
{
	m_ColorBK = RGB(0xff, 0xff, 0xff);
	m_ColorText = RGB(0x69, 0x69, 0x69);
	m_ColorTitle = RGB(0, 0, 0);
	m_ColorFrame = RGB(0xC0, 0xC0, 0xC0);
	m_bMouseOnControl = false;
}

MenuBtn::~MenuBtn()
{
}

void MenuBtn::SetText(CString title, CString content)
{
	m_StrTitle = title;
	m_StrContent = content;
}


BEGIN_MESSAGE_MAP(MenuBtn, CButton)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// MenuBtn 消息处理程序




void MenuBtn::OnPaint()
{
	CPaintDC dc(this);

	CRect rectBtn;
	GetClientRect(rectBtn);
	CDC* pDC = this->GetDC();
	pDC->SetBkMode(TRANSPARENT);
	CBrush brush;
	brush.CreateSolidBrush(m_ColorBK);
	pDC->FillRect(rectBtn, &brush);


	m_ColorFrame = m_bMouseOnControl ? RGB(0xC0, 0xC0, 0xC0) : RGB(0xff, 0xff, 0xff);
	//if (!m_bMouseOnControl)
	{
		CPen pen(PS_SOLID, 1, m_ColorFrame);
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)
			GetStockObject(NULL_BRUSH));
		CBrush * pOldBrush = dc.SelectObject(pBrush);

		CRect frameRect = rectBtn;
		frameRect.DeflateRect(-1, -1, -1, -1);
		pDC->Rectangle(frameRect);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}


	CFont* font = GetFont();
	LOGFONT logFont;
	font->GetLogFont(&logFont);

	int hfont = abs(logFont.lfHeight);

	logFont.lfHeight = logFont.lfHeight * 0.8;
	logFont.lfWidth = logFont.lfWidth * 0.8;
	m_FontContent.CreateFontIndirect(&logFont);
	m_FontContent.Detach();

	HICON iocn = GetIcon();
	ICONINFO	ii;
	::ZeroMemory(&ii, sizeof(ICONINFO));
	BOOL bRetValue = ::GetIconInfo(iocn, &ii);
	if (bRetValue == FALSE)
	{
		return;
	} // if
	DWORD iconWidth = (DWORD)(ii.xHotspot * 2);
	DWORD iconHeight = (DWORD)(ii.yHotspot * 2);
	::DeleteObject(ii.hbmMask);
	::DeleteObject(ii.hbmColor);

	int iconXPos = hfont;
	int iconYPos = (rectBtn.Height() - iconHeight) / 2;

	pDC->DrawState(CPoint(iconXPos, iconYPos),
		CSize(iconWidth, iconHeight),
		iocn,
		DSS_NORMAL,
		(CBrush*)NULL);


	pDC->SetTextColor(m_ColorTitle);
	CRect titleRect;
	titleRect.left = iconWidth + 2 * hfont;
	titleRect.right = rectBtn.right;
	titleRect.top = iconYPos;
	titleRect.bottom = titleRect.top + iconHeight / 2;
	pDC->SelectObject(font);
	pDC->DrawText(m_StrTitle, -1, &titleRect, DT_WORDBREAK | DT_LEFT);

	CRect contentRect = titleRect;
	contentRect.top = titleRect.bottom;
	contentRect.bottom = contentRect.top + iconHeight / 2;
	pDC->SetTextColor(m_ColorText);
	//pDC->SelectObject(m_FontContent);
	pDC->DrawText(m_StrContent, -1, &contentRect, DT_WORDBREAK | DT_LEFT);

}


void MenuBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* wndUnderMouse = NULL;
	CWnd* wndActive = this;
	TRACKMOUSEEVENT		csTME;

	CButton::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	// If the mouse enter the button with the left button pressed then do nothing
	if (nFlags & MK_LBUTTON && m_bMouseOnControl == false) return;

	if (wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd && wndActive)
	{
		if (!m_bMouseOnControl)
		{
			m_bMouseOnControl = true;
			Invalidate();

#ifdef	BTNST_USE_SOUND
			// Play sound ?
			if (m_csSounds[0].lpszSound)
				::PlaySound(m_csSounds[0].lpszSound, m_csSounds[0].hMod, m_csSounds[0].dwFlags);
#endif

			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		} // if
	}
	else
	{
		m_bMouseOnControl = false;
		Invalidate();
	}
}


void MenuBtn::OnMouseLeave()
{
	m_bMouseOnControl = false;
	Invalidate();
	CButton::OnMouseLeave();
}

