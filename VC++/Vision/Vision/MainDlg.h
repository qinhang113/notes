#pragma once

#include <thread>
#include "ImgParaDlg1.h"
#include "ImgParaDlg3.h"
#include "ImgParaDlg5.h"
#include "ConvertImg.h"
#include "ImgPara1.h"
#include "ImgPara2.h"
#include "ImgPara3.h"
#include "ImgPara4.h"
#include "ImgPara5.h"
// MainDlg 对话框

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg)

	CString m_Title;
	int m_Index;
	ImgParaDlg1* m_pImgParaDlg1;
	ImgParaDlg3* m_pImgParaDlg3;
	ImgParaDlg5* m_pImgParaDlg5;
	ImgPara* m_pImgPara;
	ConvertImg* m_pConvertImg;

	CImage m_CurrentImg;
	double m_CurrentScale;
	bool m_bDrawing;
	std::thread *m_pThread;
	std::vector<CRect> m_Rects;
	CRect m_OldBox;
	int m_Xpos, m_Ypos;
	int m_CurrentBoxIndex;
	bool m_bWindowClose;
public:
	MainDlg(int index, CString title, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	void ShowImgParadlg();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawThreadFun();
	afx_msg void OnPaint();
	afx_msg void OnLoadImg();
	afx_msg void OnTest();
	afx_msg void OnClear();
	afx_msg void OnSave();
};
