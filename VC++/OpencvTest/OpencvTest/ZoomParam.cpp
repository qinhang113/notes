// ZoomParam.cpp: 实现文件
//

#include "pch.h"
#include "OpencvTest.h"
#include "ZoomParam.h"
#include "afxdialogex.h"


// ZoomParam 对话框

IMPLEMENT_DYNAMIC(ZoomParam, CDialogEx)

ZoomParam::ZoomParam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOMPARAM, pParent)
	, m_WScale(_T("1.0"))
	, m_HScale(_T("1.0"))
	, m_iScaleType(0)
{
	m_dWScale = m_dHScale = 1.0;
	m_Interpolation = 0;
}

ZoomParam::~ZoomParam()
{
}

void ZoomParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_WScale);
	DDX_Text(pDX, IDC_EDIT2, m_HScale);
	DDX_Radio(pDX, IDC_RADIO1, m_iScaleType);
}


BEGIN_MESSAGE_MAP(ZoomParam, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ZoomParam::OnOK)
	ON_BN_CLICKED(IDC_RADIO1, &ZoomParam::OnRadio)
	ON_BN_CLICKED(IDC_RADIO3, &ZoomParam::OnRadio)
END_MESSAGE_MAP()


// ZoomParam 消息处理程序


BOOL ZoomParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO1);
	box->AddString(L"最近邻差值");//CV_INTER_NN 
	box->AddString(L"双线性差值");//CV_INTER_LINEAR 
	box->AddString(L"立方差值"); //CV_INTER_CUBIC
	box->AddString(L"像素关系重采样");//CV_INTER_AREA 
	box->SetCurSel(0);
	return TRUE;
}



void ZoomParam::OnOK()
{
	UpdateData(TRUE);
	m_dWScale = _ttof(m_WScale);
	m_dHScale = _ttof(m_HScale);
	CComboBox* box = (CComboBox*)GetDlgItem(IDC_COMBO1);
	m_Interpolation = box->GetCurSel();
	if (m_dWScale < 0.2 || m_dHScale < 0.2 || m_Interpolation == -1)
	{
		return;
	}

	CDialogEx::OnOK();
}

void ZoomParam::OnRadio()
{
	UpdateData(TRUE);
	CStatic* txt1 = (CStatic*)GetDlgItem(IDC_STATIC_1);
	CStatic* txt2 = (CStatic*)GetDlgItem(IDC_STATIC_2);
	if (m_iScaleType == 1)
	{
		txt1->SetWindowText(L"宽像素:");
		txt2->SetWindowText(L"高像素:");
		m_WScale = m_HScale = L"100";
	}
	else
	{
		txt1->SetWindowText(L"宽比例:");
		txt2->SetWindowText(L"高比例:");
		m_WScale = m_HScale = L"1.0";
	}
	UpdateData(FALSE);
}

