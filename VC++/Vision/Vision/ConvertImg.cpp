#include "pch.h"
#include "ConvertImg.h"

void ConvertImg::LoadPicture(const char* path, CImage& cImage)
{
	m_Imgdata.release();
	m_ImgTmp.release();
	m_Imgdata = cv::imread(path);
	m_Imgdata.copyTo(m_ImgTmp);
	Mat2CImage(m_ImgTmp, cImage);
}

void ConvertImg::Mat2CImage(cv::Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits();
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			if (channels == 1) //»Ò¶ÈÍ¼  
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3)
			{
				for (int k = 0; k < 3; ++k)
				{
					*(pimg + i * step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
}

void ConvertImg::DrawBox(cv::Mat& mat, cv::Rect rect, int index)
{
	cv::rectangle(
		mat,
		rect.tl(),
		rect.br(),
		index ? cv::Scalar(0x00, 0x00, 0xff) : cv::Scalar(0xff, 0x00, 0x00)    /* red */
	);
}

void ConvertImg::ReloadImg(CImage& cImage)
{
	m_ImgTmp.release();
	m_Imgdata.copyTo(m_ImgTmp);
	Mat2CImage(m_ImgTmp, cImage);
}
