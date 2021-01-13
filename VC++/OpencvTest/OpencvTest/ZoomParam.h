#pragma once


// ZoomParam 对话框

class ZoomParam : public CDialogEx
{
	DECLARE_DYNAMIC(ZoomParam)

	CString m_WScale, m_HScale;
public:
	ZoomParam(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ZoomParam();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dWScale, m_dHScale;
	int m_iScaleType, m_Interpolation;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadio();
};
