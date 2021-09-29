
// VisionDlg.h: 头文件
//

#pragma once

#include "MenuBtn.h"
#include "MainDlg.h"
// CVisionDlg 对话框
class CVisionDlg : public CDialogEx
{
// 构造
	MenuBtn m_MenuControl[5];
	MainDlg* m_pMaindlg;
	CStringArray m_Titles;
public:
	CVisionDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_DIALOG };
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
public:
	void OnMainMenu(UINT nID);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
