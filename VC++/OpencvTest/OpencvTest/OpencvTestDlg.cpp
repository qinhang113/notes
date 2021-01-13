
// OpencvTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "OpencvTest.h"
#include "OpencvTestDlg.h"
#include "afxdialogex.h"
#include "GaussParam.h"
#include "ZoomParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpencvTestDlg 对话框



COpencvTestDlg::COpencvTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVTEST_DIALOG, pParent)
	, m_ShowType(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpencvTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_ShowType);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_HScrollBar);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_VScrollBar);
}

BEGIN_MESSAGE_MAP(COpencvTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &COpencvTestDlg::RunTest)
	ON_BN_CLICKED(IDC_BUTTON3, &COpencvTestDlg::OnRelease)
	ON_BN_CLICKED(IDC_BUTTON2, &COpencvTestDlg::OnGauss)
	ON_COMMAND_RANGE(IDC_RADIO1, IDC_RADIO2, OnRadio)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &COpencvTestDlg::OnGray)
	ON_BN_CLICKED(IDC_BUTTON5, &COpencvTestDlg::OnZoom)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// COpencvTestDlg 消息处理程序

BOOL COpencvTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_HScrollBar.SetScrollRange(0, 100);
	m_HScrollBar.SetScrollPos(0);

	m_VScrollBar.SetScrollRange(0, 100);
	m_VScrollBar.SetScrollPos(0);

	OnRadio(IDC_RADIO1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COpencvTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COpencvTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COpencvTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpencvTestDlg::RunTest()
{
	IM->ImageProcess(ProcessType::ORIGIN);
	IM->OnRun();
}



void COpencvTestDlg::OnRelease()
{
	if (IM != nullptr)
	{
		IM->ImageProcess(ProcessType::ORIGIN);
		IM->ReleaseImg();
		//delete IM;
		//IM = nullptr;
	}
}


void COpencvTestDlg::OnGauss()
{
	GaussParam dlg;
	if (dlg.DoModal() == IDOK)
	{
		cv::Size size = cv::Size(_ttoi(dlg.m_GaussSize), _ttoi(dlg.m_GaussSize));
		double xsigma = _ttof(dlg.m_XSigma);
		double ysigma = _ttof(dlg.m_YSigma);
		IM->Register<void*, void*>(ProcessType::GAUSS, [=](void* input, void* output) {cv::GaussianBlur(*((cv::Mat*)input), *((cv::Mat*)output), size, xsigma, ysigma); });

		IM->ImageProcess(ProcessType::GAUSS);
		if (m_ShowType == 1)
		{
			//静态图片需要重新绘制一下
			IM->OnRun();
		}
	}
}


void COpencvTestDlg::OnRadio(UINT id)
{
	UpdateData(TRUE);
	if (IM != nullptr)
	{
		//IM->ReleaseImg();
		delete IM;
		IM = nullptr;
	}
	if (m_ShowType == 0)
	{
		IM = new ShowVideo();
	}
	else if (m_ShowType == 1)
	{
		IM = new ShowImage();
	}
	else
	{
		return;
	}
	Callback fun = std::bind(&COpencvTestDlg::GetImgSize, this, std::placeholders::_1);
	IM->RegistSizeCallback(fun);
	IM->SetPlayWnd(GetDlgItem(IDC_STATIC_VIDEO));
	IM->Register<void*, void*>(ProcessType::ORIGIN, [=](void* input, void* output) {*((cv::Mat*)output) = (*((cv::Mat*)input)).clone(); });
	//IM->Register<void*, void*>(ProcessType::GRAY, [](void* input, void* output) {cv::cvtColor(*((cv::Mat*)input), *((cv::Mat*)output), cv::COLOR_RGB2GRAY, CV_8UC3); });
}


void COpencvTestDlg::OnClose()
{
	if (IM != nullptr)
	{
		IM->ReleaseImg();
		delete IM;
		IM = nullptr;
	}

	CDialogEx::OnClose();
}



void COpencvTestDlg::OnGray()
{
	IM->Register<void*, void*>(ProcessType::GRAY, [=](void* input, void* output) {cv::cvtColor(*((cv::Mat*)input), *((cv::Mat*)output), cv::COLOR_RGB2GRAY, CV_8UC3); });
	
	IM->ImageProcess(ProcessType::GRAY);
	if (m_ShowType == 1)
	{
		//静态图片需要重新绘制一下
		IM->OnRun();
	}
}


void COpencvTestDlg::OnZoom()
{
	ZoomParam dlg;
	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_STATIC_VIDEO)->RedrawWindow();
		double _w = dlg.m_dHScale;
		double _h = dlg.m_dWScale;

		int scaletype = dlg.m_Interpolation;
		if (dlg.m_iScaleType == 1)
		{
			IM->Register<void*, void*>(ProcessType::ZOOM, [=](void* input, void* output) {cv::resize(*((cv::Mat*)input), *((cv::Mat*)output), cv::Size((int)_w, (int)_h), scaletype); });
		}
		else
		{
			IM->Register<void*, void*>(ProcessType::ZOOM, [=](void* input, void* output) {cv::resize(*((cv::Mat*)input), *((cv::Mat*)output), cv::Size(), _w, _h, scaletype); });
		}
		IM->ImageProcess(ProcessType::ZOOM);
		if (m_ShowType == 1)
		{
			//静态图片需要重新绘制一下
			IM->OnRun();
		}
	}
}


void COpencvTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_VScrollBar.GetScrollPos();
	int min(0), max(0);
	m_VScrollBar.GetScrollRange(&min, &max);

	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1
	case SB_LINEUP:
		pos -= (int)(max * 0.01);
		break;
		// 如果向右滚动一列，则pos加1
	case SB_LINEDOWN:
		pos += (int)(max * 0.01);
		break;
		// 如果向左滚动一页，则pos减10
	case SB_PAGEUP:
		pos -= (int)(max * 0.1);
		break;
		// 如果向右滚动一页，则pos加10
	case SB_PAGEDOWN:
		pos += (int)(max * 0.1);
		break;
		// 如果滚动到最左端，则pos为1
	case SB_TOP:
		pos = 0;
		break;
		// 如果滚动到最右端，则pos为100
	case SB_BOTTOM:
		pos = max;
		break;
		// 如果拖动滚动块到指定位置，则pos赋值为nPos的值
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// 下面的m_horiScrollbar.SetScrollPos(pos);执行时
		// 会第二次进入此函数，最终确定滚动块位置，并且会
		// 直接到default分支，所以在此处设置编辑框中显示数值
	default:
		IM->SetImgYOffset(pos);
		if (m_ShowType == 1)
		{
			IM->OnRun();
		}
		return;
	}

	// 设置滚动块位置
	m_VScrollBar.SetScrollPos(pos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void COpencvTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = m_HScrollBar.GetScrollPos();

	int min(0), max(0);
	m_HScrollBar.GetScrollRange(&min, &max);

	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1
	case SB_LINELEFT:
		pos -= (int)(max * 0.01);
		break;
		// 如果向右滚动一列，则pos加1
	case SB_LINERIGHT:
		pos += (int)(max * 0.01);
		break;
		// 如果向左滚动一页，则pos减10
	case SB_PAGELEFT:
		pos -= (int)(max * 0.1);
		break;
		// 如果向右滚动一页，则pos加10
	case SB_PAGERIGHT:
		pos += (int)(max * 0.1);
		break;
		// 如果滚动到最左端，则pos为1
	case SB_LEFT:
		pos = 0;
		break;
		// 如果滚动到最右端，则pos为100
	case SB_RIGHT:
		pos = max;
		break;
		// 如果拖动滚动块到指定位置，则pos赋值为nPos的值
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// 下面的m_horiScrollbar.SetScrollPos(pos);执行时
		// 会第二次进入此函数，最终确定滚动块位置，并且会
		// 直接到default分支，所以在此处设置编辑框中显示数值
	default:
		IM->SetImgXOffset(pos);
		if (m_ShowType == 1)
		{
			IM->OnRun();
		}
		return;
	}

	// 设置滚动块位置
	m_HScrollBar.SetScrollPos(pos);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void COpencvTestDlg::GetImgSize(SIZE size)
{
	m_ImgSize = size;
	CRect objRect;
	CWnd* w = GetDlgItem(IDC_STATIC_VIDEO);
	w->GetClientRect(&objRect);
	
	int nWndWidth = objRect.Width();
	int nWndHeight = objRect.Height();

	int scrollW(0), scrollH(0);
	if (nWndWidth > size.cx)
	{
		m_HScrollBar.ShowWindow(FALSE);
		scrollW = 0;
	}
	else
	{
		m_HScrollBar.ShowWindow(TRUE);
		scrollW = size.cx - nWndWidth;
	}

	if (nWndHeight > size.cy)
	{
		m_VScrollBar.ShowWindow(FALSE);
		scrollH = 0;
	}
	else
	{
		m_VScrollBar.ShowWindow(TRUE);
		scrollH = size.cy - nWndHeight;
	}

	bool sam = false;
	int min(0), max(0);
	m_HScrollBar.GetScrollRange(&min, &max);
	if (max == scrollW)
	{
		sam = true;
	}
	m_VScrollBar.GetScrollRange(&min, &max);
	if (max == scrollH)
	{
		sam = (sam && true);
	}
	if (sam)
	{
		return;
	}

	m_HScrollBar.SetScrollRange(0, scrollW);
	m_VScrollBar.SetScrollRange(0, scrollH);

	m_HScrollBar.SetScrollPos(0);
	m_VScrollBar.SetScrollPos(0);
}
