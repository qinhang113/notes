#include "pch.h"
#include "ImgPara1.h"

ImgPara1::ImgPara1()
{
	markRect.assign(2, cv::Rect(0, 0, 0, 0));
}

bool ImgPara1::LoadFromFile(char* path)
{
	std::ifstream is(path);
	if (is.is_open())
	{
		std::string str;
		int i = 0;
		while (is >> str)
		{
			if (str.compare(0, 4, "rect") == 0)
			{
				int value;
				is >> value;
				direction[i] = (value == 1);
				is >> pointCount[i];
				std::vector<int> r;

				for (int j = 0; j < 4; j++)
				{
					is >> value;
					r.push_back(value);
				}
				cv::Rect rect(r[0], r[1], r[2], r[3]);
				markRect[i] = rect;
				GetSearchPoint(i);
				i++;
			}
		}
		is.close();
		return true;
	}
	return false;
}

bool ImgPara1::SaveToFile(char* path)
{
	std::ofstream os(path);
	for (int i = 0; i < 2; i++)
	{
		os << "rect" << i << "\n";
		os << (direction[i] ? 1 : 0) << "\n";
		os << pointCount[i] << "\n";

		cv::Rect r = markRect[i];
		os << r.x << " " << r.y << " " << r.width << " " << r.height << "\n";
	}
	os.close();
	return true;
}

void LineFitLeastSquares(std::vector<cv::Point>& v, std::vector<float>& vResult)
{
	float A = 0.0;
	float B = 0.0;
	float C = 0.0;
	float D = 0.0;
	float E = 0.0;
	float F = 0.0;

	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		A += v[i].x * v[i].x;
		B += v[i].x;
		C += v[i].x * v[i].y;
		D += v[i].y;
	}

	// 计算斜率a和截距b  
	float a, b, temp = 0;
	if (temp = (size * A - B * B))// 判断分母不为0  
	{
		a = (size * C - B * D) / temp;
		b = (A * D - B * C) / temp;
	}
	else
	{
		a = 1;
		b = 0;
	}

	// 计算相关系数r  
	float Xmean, Ymean;
	Xmean = B / size;
	Ymean = D / size;

	float tempSumXX = 0.0, tempSumYY = 0.0;
	for (int i = 0; i < size; i++)
	{
		tempSumXX += (v[i].x - Xmean) * (v[i].x - Xmean);
		tempSumYY += (v[i].y - Ymean) * (v[i].y - Ymean);
		E += (v[i].x - Xmean) * (v[i].y - Ymean);
	}
	F = sqrt(tempSumXX) * sqrt(tempSumYY);

	float r;
	r = E / F;

	vResult.push_back(a);
	vResult.push_back(b);
	vResult.push_back(r * r);
}

bool ImgPara1::ImgProcessing(cv::Mat& src, cv::Mat& dst)
{
	dst.release();
	src.copyTo(dst);
	cv::Mat grayImg, img_edge;
	cv::cvtColor(src, grayImg, cv::COLOR_BGR2GRAY);
	cv::threshold(grayImg, img_edge, 128, 255, cv::THRESH_BINARY);
	//cv::imshow("Image after threshold", img_edge);
	std::vector< std::vector< cv::Point > > contours;
	std::vector< cv::Vec4i > hierarchy;

	cv::findContours(
		img_edge,
		contours,
		hierarchy,
		cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE
	);

	std::vector<int> sortIdx(contours.size());
	std::vector<float> areas(contours.size());
	for (int n = 0; n < (int)contours.size(); n++) {
		sortIdx[n] = n;
		areas[n] = contourArea(contours[n], false);
	}
	//按照轮廓面积排序
	std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));
	//判断最大面积的轮廓
	int idx = sortIdx[0];
	std::vector<cv::Point>& v = contours[idx];


	for (int i = 0; i < 2; i++)
	{
		std::vector<cv::Point> pointFinal;

		for (int j = 0; j < rects[i].size(); j++)
		{
			std::vector<cv::Point> points;
			for (auto& p : v)
			{
				if (p.inside(rects[i].at(j)))
				{
					points.push_back(p);
				}
			}
			if (points.size() > 0)
			{
				if (direction[i])
				{
					std::sort(points.begin(), points.end(), [](cv::Point& a, cv::Point& b) -> bool {return a.y < b.y; });
				}
				else
				{
					std::sort(points.begin(), points.end(), [](cv::Point& a, cv::Point& b) -> bool {return a.y > b.y; });
				}
				pointFinal.push_back(points.at(0));
			}
		}
		if (pointFinal.size() > rects[i].size() * 0.5)
		{
			std::vector<float> result;
			LineFitLeastSquares(pointFinal, result);
			cv::line(dst, cv::Point(0, result[1]), cv::Point(dst.cols, dst.cols * result[0] + result[1]), i ? cv::Scalar(0, 128, 0) : cv::Scalar(0, 255, 0));
		}
	}
    return false;
}
void ImgPara1::SetRect(CRect rect, int index)
{
	markRect[index] = cv::Rect(rect.left, rect.top, rect.Width(), rect.Height());
	GetSearchPoint(index);
}
void ImgPara1::GetSearchPoint(int index)
{
	cv::Rect rect = markRect[index];

	int perwidth = (int)(rect.width / (pointCount[index] * 1.0) + 0.5);

	std::vector<cv::Rect> &s = rects[index];
	s.clear();
	for (int i = 0; i < pointCount[index]; i++)
	{
		s.push_back(cv::Rect(rect.x + i * perwidth, rect.y, perwidth, rect.height));
	}
}