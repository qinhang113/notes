
// OpencvTestDlg.h: 头文件
//

#pragma once

#include "ShowVideo.h"
#include "ShowImage.h"
// COpencvTestDlg 对话框
class COpencvTestDlg : public CDialogEx
{
// 构造
	IOpencvManager* IM{ nullptr };
	SIZE m_ImgSize;
public:
	COpencvTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void RunTest();
public:
	afx_msg void OnRelease();
	afx_msg void OnGauss();
	int m_ShowType;
	afx_msg void OnRadio(UINT id);
	afx_msg void OnClose();
	afx_msg void OnGray();
	afx_msg void OnZoom();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void GetImgSize(SIZE size);
	CScrollBar m_HScrollBar;
	CScrollBar m_VScrollBar;
};
