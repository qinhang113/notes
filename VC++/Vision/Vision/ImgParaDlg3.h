#pragma once

#include "ImgPara3.h"
// ImgParaDlg3 对话框

class ImgParaDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(ImgParaDlg3)

	ImgPara3* m_pImgPara;
public:
	ImgParaDlg3(ImgPara3* imgpara, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ImgParaDlg3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGPARA_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void Set();
};
