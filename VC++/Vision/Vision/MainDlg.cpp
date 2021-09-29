// MainDlg.cpp: 实现文件
//

#include "pch.h"
#include "Vision.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(int index, CString title, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
{
	m_Index = index;
	m_Title = title;
	m_pImgParaDlg1 = nullptr;
	m_pImgPara = nullptr;
	m_pConvertImg = nullptr;
	m_CurrentBoxIndex = 0;
	m_CurrentScale = 0.;
	m_bDrawing = false;
	m_bWindowClose = false;
}

MainDlg::~MainDlg()
{
	if (m_Index == 0 || m_Index == 1)
	{
		delete m_pImgParaDlg1;
	}
	if (m_Index == 4)
	{
		delete m_pImgParaDlg5;
	}
	if (m_pImgPara != nullptr)
	{
		delete m_pImgPara;
		m_pImgPara = nullptr;
	}
	if (m_pConvertImg != nullptr)
	{
		delete m_pConvertImg;
		m_pConvertImg = nullptr;
	}
	delete m_pThread;
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_LOAD, &MainDlg::OnLoadImg)
	ON_BN_CLICKED(IDC_BTN_TEST, &MainDlg::OnTest)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &MainDlg::OnClear)
	ON_BN_CLICKED(IDC_BTNSAVE, &MainDlg::OnSave)
END_MESSAGE_MAP()


// MainDlg 消息处理程序


BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CButton* btn = (CButton*)GetDlgItem(IDC_BTNSAVE);
	btn->SetWindowText(_T("保存设置"));
	SetWindowText(m_Title);
	m_pConvertImg = new ConvertImg;
	m_Rects.assign(2, CRect(0, 0, 0, 0));
	if (m_Index == 0 || m_Index == 1)
	{
		m_pImgPara = new ImgPara1;
		m_pImgParaDlg1 = new ImgParaDlg1(dynamic_cast<ImgPara1*>(m_pImgPara));
		m_pImgParaDlg1->Create(IDD_IMGPARA_1, this);
		ShowImgParadlg();
	}
	else if (m_Index == 2)
	{
		//IDC_BTNSAVE
		m_pImgPara = new ImgPara3;
		m_pImgParaDlg3 = new ImgParaDlg3(dynamic_cast<ImgPara3*>(m_pImgPara));
		m_pImgParaDlg3->Create(IDD_IMGPARA_3, this);
		ShowImgParadlg();
	}
	else if (m_Index == 3)
	{
		//IDC_BTNSAVE
		m_pImgPara = new ImgPara4;
		btn->SetWindowText(_T("设为模板"));
	}
	else if (m_Index == 4)
	{
		m_pImgPara = new ImgPara5;
		m_pImgParaDlg5 = new ImgParaDlg5(dynamic_cast<ImgPara5*>(m_pImgPara));
		m_pImgParaDlg5->Create(IDD_IMGPARA_5, this);
		ShowImgParadlg();
	}

	if (m_pImgPara != nullptr)
	{
		char path[100] = { 0 };
		sprintf_s(path, 100, "%d.ini", m_Index);
		m_pImgPara->LoadFromFile(path);
	}

	m_pThread = new std::thread(&MainDlg::DrawThreadFun, this);
	return TRUE;
}


BOOL MainDlg::PreTranslateMessage(MSG* pMsg)
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


void MainDlg::OnClose()
{
	this->ShowWindow(SW_HIDE);
	this->GetParent()->ShowWindow(SW_NORMAL);
	m_bWindowClose = true;
	CDialogEx::OnClose();
}

void MainDlg::ShowImgParadlg()
{
	CWnd* configWnd = nullptr;
	if (m_Index == 0 || m_Index == 1)
	{
		configWnd = m_pImgParaDlg1;
	}
	else if (m_Index == 2)
	{
		configWnd = m_pImgParaDlg3;
	}
	else if (m_Index == 4)
	{
		configWnd = m_pImgParaDlg5;
	}

	CWnd* pWnd = GetDlgItem(IDC_BTN_LOAD);
	CRect btnRect, rect;
	pWnd->GetWindowRect(btnRect);
	ScreenToClient(btnRect);

	rect.top = btnRect.bottom;
	rect.left = btnRect.left;
	rect.right = btnRect.right;
	pWnd = GetDlgItem(IDC_BTN_TEST);
	pWnd->GetWindowRect(btnRect);
	ScreenToClient(btnRect);
	rect.bottom = btnRect.top;
	configWnd->MoveWindow(rect);
	configWnd->ShowWindow(TRUE);
}


void MainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);

	CRect rect, oldRect;
	pWnd->GetWindowRect(rect);
	oldRect = rect;
	ScreenToClient(rect);

	CRect& box = m_Rects[m_CurrentBoxIndex];
	if (rect.PtInRect(point))
	{
		if (point.x < m_Xpos)
		{
			box.left = box.right = 0;
		}
		else
		{
			box.right = box.left = (int)((point.x - m_Xpos) * m_CurrentScale + 0.5);
		}
		if (point.y < m_Ypos)
		{
			box.top = box.bottom = 0;
		}
		else
		{
			box.top = box.bottom = (int)((point.y - m_Ypos) * m_CurrentScale + 0.5);
		}
		m_bDrawing = true;
	}
	else
	{
		m_bDrawing = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void MainDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDrawing = false;
	CRect &box = m_Rects[m_CurrentBoxIndex];
	if (box.Width() > 0 && box.Height() > 0)
	{
		m_pConvertImg->DrawBox(m_pConvertImg->m_ImgTmp, cv::Rect(box.left, box.top, box.Width(), box.Height()), m_CurrentBoxIndex);
		m_pConvertImg->Mat2CImage(m_pConvertImg->m_ImgTmp, m_CurrentImg);
		PostMessage(WM_PAINT);
		m_CurrentBoxIndex = m_CurrentBoxIndex ? 0 : 1;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void MainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);
	CRect rect;
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	CRect& box = m_Rects[m_CurrentBoxIndex];
	if (rect.PtInRect(point))
	{
		if (m_bDrawing)
		{
			box.right = (int)((point.x - m_Xpos) * m_CurrentScale + 0.5);
			box.bottom = (int)((point.y - m_Ypos) * m_CurrentScale + 0.5);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void MainDlg::DrawThreadFun()
{
	while (!m_bWindowClose)
	{
		if (m_bDrawing)
		{
			CRect& box = m_Rects[m_CurrentBoxIndex];
			if (m_OldBox != box)
			{
				cv::Mat mat;
				m_pConvertImg->m_ImgTmp.copyTo(mat);
				m_pConvertImg->DrawBox(mat, cv::Rect(box.left, box.top, box.Width(), box.Height()), m_CurrentBoxIndex);
				m_pConvertImg->Mat2CImage(mat, m_CurrentImg);
				SendMessage(WM_PAINT);
			}
			m_OldBox = box;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void  WriteBmp(CBitmap* PBitmap, CString m_FileName)
{
	if (PBitmap->m_hObject)
	{
		CImage imgTemp;
		// CImage是MFC中的类。
		imgTemp.Attach(PBitmap->operator HBITMAP());
		imgTemp.Save(m_FileName);
	}
}

void MainDlg::OnPaint()
{
	CPaintDC dc(this);

	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);
	if (pWnd)
	{
		if (::IsWindow(pWnd->GetSafeHwnd()))
		{
			if (!m_CurrentImg.IsNull())
			{
				CRect rect;
				pWnd->GetWindowRect(rect);
				ScreenToClient(rect);
				CDC* pDc = GetDC();
				int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
				double scalex = m_CurrentImg.GetWidth() / (rect.Width() * 1.0);
				double scaley = m_CurrentImg.GetHeight() / (rect.Height() * 1.0);
				m_CurrentScale = scalex > scaley ? scalex : scaley;

				m_Xpos = (rect.Width() - m_CurrentImg.GetWidth() / m_CurrentScale) / 2;
				m_Ypos = (rect.Height() - m_CurrentImg.GetHeight() / m_CurrentScale) / 2;

				CDC MemDC; //首先定义一个显示设备对象
				CBitmap MemBitmap;//定义一个位图对象
				//随后建立与屏幕显示兼容的内存显示设备
				MemDC.CreateCompatibleDC(NULL);
				//这时还不能绘图，因为没有地方画 ^_^
				//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小，也可以自己定义（如：有滚动条时就要大于当前窗口的大小，在BitBlt时决定拷贝内存的哪部分到屏幕上）

				int nWidth = rect.Width();
				int nHeight = rect.Height();
				MemBitmap.CreateCompatibleBitmap(pDc, nWidth, nHeight);
				//将位图选入到内存显示设备中
				//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
				CBitmap* pOldBit = MemDC.SelectObject(&MemBitmap);
				MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(0x80, 0x80, 0x80));
				//绘图

				SetStretchBltMode(MemDC, STRETCH_HALFTONE);

				m_CurrentImg.StretchBlt(MemDC,
					m_Xpos, m_Ypos, rect.Width() - 2 * m_Xpos, rect.Height() - 2 * m_Ypos,
					0, 0, m_CurrentImg.GetWidth(), m_CurrentImg.GetHeight(),
					SRCCOPY);
				//SetStretchBltMode(MemDC, ModeOld);
				//CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
				//MemDC.SelectObject(&pen);
				//CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				//CBrush* pOldBrush = MemDC.SelectObject(pBrush);
				//MemDC.Rectangle(m_Box);
				//将内存中的图拷贝到屏幕上进行显示
				pDc->BitBlt(rect.left, rect.top, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);
				//绘图完成后的清理
				//把前面的pOldBit选回来.在删除MemBitmap之前要先从设备中移除它
				MemDC.SelectObject(pOldBit);

				//WriteBmp(&MemBitmap, _T("1.bmp"));

				MemBitmap.DeleteObject();
				MemDC.DeleteDC();
				//img.StretchBlt(pDc->m_hDC,
				//	rect.left, rect.top, rect.Width(), rect.Height(),
				//	0, 0, img.GetWidth(), img.GetHeight(),
				//	SRCCOPY);
				//
				//::StretchBlt
				ReleaseDC(pDc);
			}
		}
	}
}


void MainDlg::OnLoadImg()
{
	TCHAR* szFilter = _T("BMP Files(*.bmp) | *.bmp| All Files(*.*) | *.*||");
	CFileDialog OpenDlg(TRUE, NULL, NULL/*LastFilePath*/, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL);
	OpenDlg.m_ofn.lpstrTitle = _T("Open Picture");
	if (OpenDlg.DoModal() == IDOK)
	{
		CString picname = OpenDlg.GetPathName();
		LONG len;
		len = WideCharToMultiByte(CP_ACP, 0, picname, -1, NULL, 0, NULL, NULL);
		char* ptr = new char[len + 1];
		memset(ptr, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, picname, -1, ptr, len + 1, NULL, NULL);

		m_pConvertImg->LoadPicture(ptr, m_CurrentImg);
		PostMessage(WM_PAINT);
	}
}

void MainDlg::OnTest()
{
	ASSERT(m_pImgPara != nullptr);
	if (m_Index == 0 || m_Index == 1)
	{
		m_pImgParaDlg1->Set();
		//ImgPara1* p = dynamic_cast<ImgPara1*>(m_pImgPara);
		//for (int i = 0; i < 2; i++)
		//{
		//	p->SetRect(m_Rects.at(i), i);
		//}
	}
	else if (m_Index == 2)
	{
		m_pImgParaDlg3->Set();
	}
	else if (m_Index == 4)
	{
		m_pImgParaDlg5->Set();
	}

	cv::Mat mat;
	m_pImgPara->ImgProcessing(m_pConvertImg->GetImgMat(), mat);
	m_pConvertImg->Mat2CImage(mat, m_CurrentImg);
	PostMessage(WM_PAINT);
}


void MainDlg::OnClear()
{
	m_pConvertImg->ReloadImg(m_CurrentImg);
	PostMessage(WM_PAINT);
}


void MainDlg::OnSave()
{
	if (m_Index == 0 || m_Index == 1)
	{
		ImgPara1* p = dynamic_cast<ImgPara1*>(m_pImgPara);
		for (int i = 0; i < 2; i++)
		{
			p->SetRect(m_Rects.at(i), i);
		}
	}
	if (m_Index == 3)
	{
		ImgPara4* p = dynamic_cast<ImgPara4*>(m_pImgPara);
		cv::Mat mat;
		p->SetTemplateImg(m_pConvertImg->GetImgMat(), mat);
		m_pConvertImg->Mat2CImage(mat, m_CurrentImg);
		PostMessage(WM_PAINT);
	}
	char path[100] = { 0 };
	sprintf_s(path, 100, "%d.ini", m_Index);
	m_pImgPara->SaveToFile(path);	
}
