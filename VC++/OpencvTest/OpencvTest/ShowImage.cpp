#include "pch.h"
#include "ShowImage.h"

void ShowImage::ReleaseImg()
{
	cv::Mat mat = cv::imread("noimg.bmp");
	ConvertImg(mat);
	DisPlayImg(mat);
}

void ShowImage::OnRun()
{
	cv::Mat mat = cv::imread("img.bmp");
	ConvertImg(mat);
	DisPlayImg(mat);
	SIZE size;
	size.cx = mat.cols;
	size.cy = mat.rows;
	fCallback(size);
}
