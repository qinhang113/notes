
// VisionDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Vision.h"
#include "VisionDlg.h"
#include "afxdialogex.h"

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


// CVisionDlg 对话框



CVisionDlg::CVisionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMaindlg = nullptr;
}

void CVisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_MenuControl[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_MenuControl[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_MenuControl[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_MenuControl[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_MenuControl[4]);
}

BEGIN_MESSAGE_MAP(CVisionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON1, IDC_BUTTON5, OnMainMenu)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CVisionDlg 消息处理程序

BOOL CVisionDlg::OnInitDialog()
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

	CRect btnRect;
	m_MenuControl[0].GetClientRect(btnRect);

	int iconh, iconw;
	iconh = iconw = btnRect.Height() / 2;
	HICON hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CAMERA), IMAGE_ICON, iconw, iconh, 0);
	m_MenuControl[0].SetIcon(hIcon);
	CString title = _T("导电柱1");
	m_MenuControl[0].SetText(title, _T("取封装机相机1图像"));
	m_Titles.Add(title);

	hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CAMERA), IMAGE_ICON, iconw, iconh, 0);
	m_MenuControl[1].SetIcon(hIcon);
	title = _T("导电柱2");
	m_MenuControl[1].SetText(title, _T("取封装机相机2图像"));
	m_Titles.Add(title);

	hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CAMERA), IMAGE_ICON, iconw, iconh, 0);
	m_MenuControl[2].SetIcon(hIcon);
	title = _T("埋入导电柱");
	m_MenuControl[2].SetText(title, _T("取封装机相机3图像"));
	m_Titles.Add(title);

	hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CAMERA), IMAGE_ICON, iconw, iconh, 0);
	m_MenuControl[3].SetIcon(hIcon);
	title = _T("成卡");
	m_MenuControl[3].SetText(title, _T("取封装机相机4图像"));
	m_Titles.Add(title);

	hIcon = (HICON) ::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CAMERA), IMAGE_ICON, iconw, iconh, 0);
	m_MenuControl[4].SetIcon(hIcon);
	title = _T("铣槽");
	m_MenuControl[4].SetText(title, _T("取铣槽机相机图像(横/纵向)"));
	m_Titles.Add(title);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVisionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVisionDlg::OnPaint()
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
HCURSOR CVisionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVisionDlg::OnMainMenu(UINT nID)
{
	int id = nID - IDC_BUTTON1;
	this->ShowWindow(SW_HIDE);
	if (m_pMaindlg != nullptr)
	{
		m_pMaindlg->DestroyWindow();
	}
	m_pMaindlg = new MainDlg(id, m_Titles.GetAt(id), this);
	m_pMaindlg->Create(IDD_MAIN, this);


	m_pMaindlg->ShowWindow(SW_NORMAL);
}

HBRUSH CVisionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	//return hbr;
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);
}
