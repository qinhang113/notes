#pragma once


// MenuBtn
//RGB(223, 223, 223);RGB(243, 243, 243)
class MenuBtn : public CButton
{
	DECLARE_DYNAMIC(MenuBtn)

	CString m_StrTitle, m_StrContent;
	COLORREF m_ColorBK, m_ColorTitle, m_ColorText, m_ColorFrame;
	bool m_bMouseOnControl;
	static CFont m_FontContent;
public:
	MenuBtn();
	virtual ~MenuBtn();

	void SetText(CString title,CString content);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


