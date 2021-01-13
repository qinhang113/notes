#include "pch.h"
#include "ShowVideo.h"


void ShowVideo::OnRun()
{
	m_bFirstFrame = true;
	const char* windwosName = "���";
	cv::VideoCapture cap;
	if (!cap.open(0))
	{
		TRACE("δ�������!");
		return;
	}
	m_bClose = false;
	cv::Mat frame;
	while (!m_bClose)
	{
		cap >> frame;
		ConvertImg(frame);
		if (!DisPlayImg(frame))
			break;
		else
		{
			if (m_bFirstFrame)
			{
				SIZE size;
				size.cx = frame.cols;
				size.cy = frame.rows;
				fCallback(size);
				m_bFirstFrame = false;
			}
		}
		if (cv::waitKey(40) == 0x1B)//��������
			break;
	}
	cap.release();
}

void ShowVideo::ReleaseImg()
{
	m_bClose = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(40));
	cv::Mat mat = cv::imread("noimg.bmp");
	ConvertImg(mat);
	DisPlayImg(mat);
}
