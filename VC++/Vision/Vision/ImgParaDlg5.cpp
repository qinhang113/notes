// ImgParaDlg5.cpp: 实现文件
//

#include "pch.h"
#include "Vision.h"
#include "ImgParaDlg5.h"
#include "afxdialogex.h"


// ImgParaDlg5 对话框

IMPLEMENT_DYNAMIC(ImgParaDlg5, CDialogEx)

ImgParaDlg5::ImgParaDlg5(ImgPara5* imgpara, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGPARA_5, pParent)
{
	m_pImgPara = imgpara;
}

ImgParaDlg5::~ImgParaDlg5()
{
}

void ImgParaDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImgParaDlg5, CDialogEx)
END_MESSAGE_MAP()


// ImgParaDlg5 消息处理程序


BOOL ImgParaDlg5::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_MAXAREA, _T("63000"));

	SetDlgItemText(IDC_EDIT_MINAREA, _T("59000"));

	return TRUE;
}


BOOL ImgParaDlg5::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void ImgParaDlg5::Set()
{
	ASSERT(m_pImgPara != nullptr);
	CString str;
	GetDlgItemText(IDC_EDIT_MAXAREA, str);
	m_pImgPara->maxArea = _ttoi(str);

	GetDlgItemText(IDC_EDIT_MINAREA, str);
	m_pImgPara->minArea = _ttoi(str);
}
