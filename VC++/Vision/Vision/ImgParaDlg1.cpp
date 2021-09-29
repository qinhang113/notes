// ImgParaDlg1.cpp: 实现文件
//

#include "pch.h"
#include "Vision.h"
#include "ImgParaDlg1.h"
#include "afxdialogex.h"


// ImgParaDlg1 对话框

IMPLEMENT_DYNAMIC(ImgParaDlg1, CDialogEx)

ImgParaDlg1::ImgParaDlg1(ImgPara1* imgpara, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGPARA_1, pParent)
	, m_bIsDown1(FALSE)
	, m_bIsDown2(TRUE)
{
	if (imgpara == nullptr)
	{
		imgpara = new ImgPara1;
	}
	m_pImgPara = imgpara;
}

ImgParaDlg1::~ImgParaDlg1()
{
}

void ImgParaDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_bIsDown1);
	DDX_Radio(pDX, IDC_RADIO3, m_bIsDown2);
}


BEGIN_MESSAGE_MAP(ImgParaDlg1, CDialogEx)
END_MESSAGE_MAP()


// ImgParaDlg1 消息处理程序


BOOL ImgParaDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);
	return TRUE;
}

void ImgParaDlg1::Set()
{
	UpdateData(TRUE);
	CString str;
	GetDlgItemText(IDC_EDIT_POINTCOUNT1, str);
	int pointCount1 = _ttoi(str);
	bool isupsearch = !m_bIsDown1;
	m_pImgPara->pointCount[0] = pointCount1;
	m_pImgPara->direction[0] = isupsearch;

	GetDlgItemText(IDC_EDIT_POINTCOUNT2, str);
	int pointCount2 = _ttoi(str);
	isupsearch = !m_bIsDown2;
	m_pImgPara->pointCount[1] = pointCount2;
	m_pImgPara->direction[1] = isupsearch;
}

BOOL ImgParaDlg1::PreTranslateMessage(MSG* pMsg)
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

