#pragma once

#include "opencv.hpp"
#include <functional>
#include <type_traits>
#include <any>
#include <map>

enum class ProcessType
{
	ORIGIN = 0,
	GAUSS = 1,
	GRAY = 2,
	ZOOM = 3,
};
//typedef std::function<void(SIZE)> Callback;
using Callback = std::function<void(SIZE)>;
class IOpencvManager
{
	CWnd* m_Wnd{ nullptr };
	std::map<ProcessType, std::any> m_TableMap;
	ProcessType m_ProcessType;
	int m_xImgOffset{ 0 }, m_yImgOffset{ 0 };
public:
	virtual void OnRun() = 0;
	virtual void ReleaseImg() = 0;
	virtual ~IOpencvManager()
	{
		m_TableMap.clear();
		m_ProcessType = ProcessType::ORIGIN;
	}
	void RegistSizeCallback(Callback fun)
	{
		fCallback = fun;
	}

	template<typename... Args, typename Func>
	void Register(ProcessType key, Func&& func)
	{
		using invoke_result_t = typename std::invoke_result<Func, Args...>::type;
		auto f = std::function<invoke_result_t(Args&& ...)>([=](Args&& ... args) {return func(std::forward<Args>(args)...); });
		m_TableMap[key] = f;
	}

	template<typename R = void, typename... Args>
	R Execute(ProcessType key, Args&&... args)
	{
		auto it = m_TableMap.find(key);
		if (it == m_TableMap.end())
			return (R)nullptr;

		auto f = std::any_cast<std::function<R(Args&& ...)>>(it->second);
		return f(std::forward<Args>(args)...);
	}
	//不带参数的执行
	template<typename R>
	R Execute(ProcessType key)
	{
		auto it = m_TableMap.find(key);
		if (it == m_TableMap.end())
			return (R)nullptr;

		auto f = std::any_cast<std::function<void()>>(it->second);
		return f();
	}

	void SetImgXOffset(int x)
	{
		m_xImgOffset = x;
	}

	void SetImgYOffset(int y)
	{
		m_yImgOffset = y;
	}

	void ImageProcess(ProcessType type)
	{
		m_ProcessType = type;
	}

	void SetPlayWnd(CWnd* hWnd)
	{
		m_Wnd = hWnd;
	}

private:
	void InitBitMapInfo(BITMAPINFO* bmi, int width, int height, int bpp)
	{
		assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

		BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

		memset(bmih, 0, sizeof(*bmih));
		bmih->biSize = sizeof(BITMAPINFOHEADER);
		bmih->biWidth = width;
		bmih->biHeight = height;
		bmih->biPlanes = 1;
		bmih->biBitCount = (unsigned short)bpp;
		bmih->biCompression = BI_RGB;

		if (bpp == 8)
		{
			RGBQUAD* palette = bmi->bmiColors;
			int i;
			for (i = 0; i < 256; i++)
			{
				palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
				palette[i].rgbReserved = 0;
			}
		}
	}
protected:
	Callback fCallback;
	int m_WidthImg{ 0 }, m_HeigthImg{ 0 };
	bool DisPlayImg(cv::Mat &mat)
	{
		if (!::IsWindow(m_Wnd->GetSafeHwnd()))
		{
			return false;
		}
		CRect objRect;
		m_Wnd->GetClientRect(&objRect);
		int nWndWidth = objRect.Width();
		int nWndHeight = objRect.Height();

		cv::Mat processMat;
		Execute(m_ProcessType, (void*)(&mat), (void*)(&processMat));
		int ch = processMat.channels();


		uchar buffer[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
		BITMAPINFO* binfo = (BITMAPINFO*)buffer;

		m_WidthImg = processMat.cols;
		m_HeigthImg = processMat.rows;
		InitBitMapInfo(binfo, m_WidthImg, m_HeigthImg, ch * 8);

		HDC hDC = ::GetDC(m_Wnd->m_hWnd);		
		CDC* pDC = m_Wnd->GetDC();
		::SetStretchBltMode(hDC, COLORONCOLOR);
		::StretchDIBits(/*memDC*/hDC,
			0,
			0,
			nWndWidth,
			nWndHeight,
			m_xImgOffset,
			m_HeigthImg - nWndHeight - m_yImgOffset,
			nWndWidth,
			nWndHeight,
			processMat.data,
			binfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);
		mat = processMat;
		::ReleaseDC(m_Wnd->GetSafeHwnd(), pDC->m_hDC);
		return true;
	}

	void ConvertImg(cv::Mat& mat)
	{
		cv::Mat newMat;
		cv::flip(mat, newMat, 0);

		mat = newMat;
	}
};

