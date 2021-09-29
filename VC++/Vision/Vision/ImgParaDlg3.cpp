// ImgParaDlg3.cpp: 实现文件
//

#include "pch.h"
#include "Vision.h"
#include "ImgParaDlg3.h"
#include "afxdialogex.h"
// ImgParaDlg3 对话框

IMPLEMENT_DYNAMIC(ImgParaDlg3, CDialogEx)

ImgParaDlg3::ImgParaDlg3(ImgPara3* imgpara, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGPARA_3, pParent)
{
	m_pImgPara = imgpara;
}

ImgParaDlg3::~ImgParaDlg3()
{
}

void ImgParaDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImgParaDlg3, CDialogEx)
END_MESSAGE_MAP()


// ImgParaDlg3 消息处理程序


BOOL ImgParaDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_LEFTMAXAREA, _T("7600"));
	SetDlgItemText(IDC_EDIT_LEFTMINAREA, _T("7100"));
	SetDlgItemText(IDC_EDIT_RIGHTMAXAREA, _T("7200"));
	SetDlgItemText(IDC_EDIT_RIGHTMINAREA, _T("6700"));
	return TRUE;
}


BOOL ImgParaDlg3::PreTranslateMessage(MSG* pMsg)
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

void ImgParaDlg3::Set()
{
	//minAreaLeft, maxAreaLeft, minAreaRight, maxAreaRight
	ASSERT(m_pImgPara != nullptr);
	CString str;
	GetDlgItemText(IDC_EDIT_LEFTMAXAREA, str);
	m_pImgPara->maxAreaLeft = _ttoi(str);

	GetDlgItemText(IDC_EDIT_LEFTMINAREA, str);
	m_pImgPara->minAreaLeft = _ttoi(str);

	GetDlgItemText(IDC_EDIT_RIGHTMAXAREA, str);
	m_pImgPara->maxAreaRight = _ttoi(str);

	GetDlgItemText(IDC_EDIT_RIGHTMINAREA, str);
	m_pImgPara->minAreaRight = _ttoi(str);
}