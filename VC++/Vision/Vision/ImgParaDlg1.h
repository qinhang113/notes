#pragma once

#include "ImgPara1.h"
// ImgParaDlg1 对话框

class ImgParaDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(ImgParaDlg1)

	ImgPara1 *m_pImgPara;
public:
	ImgParaDlg1(ImgPara1 *imgpara, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ImgParaDlg1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGPARA_1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void Set();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL m_bIsDown1;
	BOOL m_bIsDown2;
};
