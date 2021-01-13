// GaussParam.cpp: 实现文件
//

#include "pch.h"
#include "OpencvTest.h"
#include "GaussParam.h"
#include "afxdialogex.h"


// GaussParam 对话框

IMPLEMENT_DYNAMIC(GaussParam, CDialogEx)

GaussParam::GaussParam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAUSSPARAM, pParent)
	, m_GaussSize(_T("1"))
	, m_XSigma(_T("1.0"))
	, m_YSigma(_T("1.0"))
{

}

GaussParam::~GaussParam()
{
}

void GaussParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_GaussSize);
	DDX_Text(pDX, IDC_EDIT2, m_XSigma);
	DDX_Text(pDX, IDC_EDIT3, m_YSigma);
}


BEGIN_MESSAGE_MAP(GaussParam, CDialogEx)
	ON_BN_CLICKED(IDC_SET, &GaussParam::OnOK)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &GaussParam::OnDeltaposSpin1)
END_MESSAGE_MAP()


// GaussParam 消息处理程序


void GaussParam::OnOK()
{
	UpdateData(TRUE);

	int gausssize = _ttoi(m_GaussSize);
	if (gausssize % 2 == 0)
	{
		AfxMessageBox(L"高斯核必须为奇数!", MB_ICONERROR);
		return;
	}
	CDialogEx::OnOK();
}



void GaussParam::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	//1向下按钮。-1向上按钮
	UpdateData(TRUE);
	int value = _ttoi(m_GaussSize);
	if (pNMUpDown->iDelta == 1)
	{
		value = value > 19 ? value : value + 2;
	}
	else if(pNMUpDown->iDelta == -1)
	{
		value = value < 3 ? value : value - 2;
	}
	else
	{
		value = value;
	}
	m_GaussSize.Format(L"%d", value);
	UpdateData(FALSE);
	*pResult = 0;
}


BOOL GaussParam::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->lParam == VK_RETURN)
	{
		OnOK();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
