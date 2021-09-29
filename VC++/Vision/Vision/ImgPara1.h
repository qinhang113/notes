#pragma once
#include <vector>
#include <ostream>
#include <istream>
#include "ImgPara.h"
class ImgPara1 : public ImgPara
{
protected:
	std::vector<cv::Rect> rects[2];
public:
	std::vector<cv::Rect> markRect;
	bool direction[2];
	int pointCount[2];
public:
	ImgPara1();
	virtual bool LoadFromFile(char* path);
	virtual bool SaveToFile(char* path);
	virtual bool ImgProcessing(cv::Mat& src, cv::Mat& dst);
	void GetSearchPoint(int index);
	void SetRect(CRect rect, int index);
};

