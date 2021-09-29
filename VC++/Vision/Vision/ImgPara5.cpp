#include "pch.h"
#include "ImgPara5.h"

ImgPara5::ImgPara5()
{
	maxArea = minArea = 0;
}

bool ImgPara5::LoadFromFile(char* path)
{
	//double maxArea, minArea;
	std::ifstream is(path);
	if (is.is_open())
	{
		is >> maxArea;
		is >> minArea;
		is.close();
		return true;
	}
	return false;
}

bool ImgPara5::SaveToFile(char* path)
{
	std::ofstream os(path);
	os << maxArea << "\n"
		<< minArea;
	os.close();
	return true;
}

bool ImgPara5::ImgProcessing(cv::Mat& src, cv::Mat& dst)
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
		areas[n] = (float)contourArea(contours[n], false);
	}
	//按照轮廓面积排序
	std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));
	//判断最大面积的轮廓
	if (contours.size() < 4)
	{
		TRACE(_T("未找到足够数量的轮廓!\n"));
		return false;
	}

	int idx = sortIdx[0];
	float area = areas[idx];
	int fullimg = src.cols * src.rows;
	if (area < fullimg * 0.98)
	{
		TRACE(_T("未找到最外层轮廓,图像或者阈值设置不正确!\n"));
		return false;
	}
	idx = sortIdx[1];
	area = areas[idx];
	if (area < fullimg * 0.6f && area > fullimg * 0.72f)
	{
		TRACE(_T("未找到内层轮廓,图像或者阈值设置不正确!\n"));
		return false;
	}
	std::vector<std::vector<cv::Point> > contours_poly(2);
	std::vector<cv::Point2f>center(2);
	std::vector<float>radius(2);

	int searchCount = contours.size() > 10 ? 10 : contours.size() - 1;
	bool findEllipse = false;
	for (int i = 2; i < searchCount; i++)
	{
		idx = sortIdx[i];
		float area1 = areas[idx];
		if (area1 > minArea && area1 < maxArea)
		{
			cv::drawContours(
				dst, contours, idx,
				//BGR颜色
				cv::Scalar(0, 255, 0), 2, 8, hierarchy,
				0
			);
			approxPolyDP(cv::Mat(contours[idx]), contours_poly[0], 3, true);
			minEnclosingCircle(contours_poly[0], center[0], radius[0]);
			circle(dst, center[0], (int)radius[0], cv::Scalar(0, 255, 0), 2, 8, 0);

			idx = sortIdx[i + 1];
			float area2 = areas[idx];
			if (area2 > minArea && area2 < maxArea)
			{
				approxPolyDP(cv::Mat(contours[idx]), contours_poly[1], 3, true);
				minEnclosingCircle(contours_poly[1], center[1], radius[1]);
				circle(dst, center[1], (int)radius[1], cv::Scalar(0, 255, 0), 2, 8, 0);
				findEllipse = true;
				break;
			}
		}
	}
	if (findEllipse)
	{
		float a, b, c;
		//ax+by+c=0
		if (center[1].x == center[0].x)//垂直
		{
			a = 1.f;
			b = 0.f;
			c = -center[1].x;
		}
		else
		{
			a = (center[1].y - center[0].y) / (center[1].x - center[0].x);
			c = center[1].y - a * center[1].x;
			b = -1.f;
		}
		return ProcessingSecond(src, dst, a, b, c);
	}
	return false;
}

bool ImgPara5::ProcessingSecond(cv::Mat& src, cv::Mat& dst, float a, float b, float c)
{
	cv::Mat grayImg, img_edge;
	cv::cvtColor(src, grayImg, cv::COLOR_BGR2GRAY);
	cv::threshold(grayImg, img_edge, 220, 255, cv::THRESH_BINARY);
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
	//if ((int)contours.size() < 12)
	//{
	//	TRACE(_T("线数量不正确!\n"));
	//	return false;
	//}

	std::vector<int> sortIdx(contours.size());
	std::vector<float> areas(contours.size());
	for (int n = 0; n < (int)contours.size(); n++) {
		sortIdx[n] = n;
		areas[n] = (float)contourArea(contours[n], false);
	}
	//按照轮廓面积排序
	std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));

	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	std::vector<cv::Rect> boundRect;
	std::vector<cv::Point> center;

	for (size_t i = 0; i < areas.size(); i++)
	{
		int index = sortIdx[i];
		if (areas[index] < 20)
		{
			break;
		}
		cv::approxPolyDP(cv::Mat(contours[index]), contours_poly[i], 3, true);
		cv::Rect rect = cv::boundingRect(cv::Mat(contours_poly[i]));
		boundRect.push_back(rect);
		center.push_back(cv::Point(rect.x + (int)(rect.width / 2.0f + 0.5), rect.y + (int)(rect.height / 2.0f + 0.5)));
	}

	//│AXo＋BYo＋C│/√（A²＋B²）
	bool re = true;
	for (size_t i = 0; i < boundRect.size(); i++)
	{
		cv::Scalar color;
		cv::Point p = center.at(i);
		float d = abs((a * p.x + b * p.y + c) / sqrt(a * a + b * b));
		CString msg;
		if (d > 10.f)
		{
			color = cv::Scalar(0, 0, 255);
			msg.Format(_T("有断线!索引:%d 坐标(%d,%d)\n"), i, p.x, p.y);
			TRACE(msg);
			re = re && false;
		}
		else
		{
			color = cv::Scalar(0, 255, 0);
		}
		rectangle(dst, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
	}
	return re;
}
