#pragma once

#include "ImgPara5.h"
// ImgParaDlg5 对话框

class ImgParaDlg5 : public CDialogEx
{
	DECLARE_DYNAMIC(ImgParaDlg5)

	ImgPara5* m_pImgPara;
public:
	ImgParaDlg5(ImgPara5* imgpara, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ImgParaDlg5();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGPARA_5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Set();
};
