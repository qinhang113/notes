#pragma once


// GaussParam 对话框

class GaussParam : public CDialogEx
{
	DECLARE_DYNAMIC(GaussParam)

public:
	GaussParam(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GaussParam();

// 对话框数据
	CString m_GaussSize, m_XSigma, m_YSigma;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAUSSPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
