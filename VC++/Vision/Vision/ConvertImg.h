#pragma once
#include <opencv.hpp>
class ConvertImg
{
	cv::Mat m_Imgdata;
public:
	void LoadPicture(const char* path, CImage& cImage);
	void Mat2CImage(cv::Mat& mat, CImage& cImage);
	void DrawBox(cv::Mat& mat, cv::Rect rect, int index);
	void ReloadImg(CImage& cImage);
	cv::Mat& GetImgMat()
	{
		return m_Imgdata;
	}
	cv::Mat m_ImgTmp;
};

