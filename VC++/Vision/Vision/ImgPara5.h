#pragma once
#include "ImgPara.h"
class ImgPara5 : public ImgPara
{
public:
	double maxArea, minArea;
public:
	ImgPara5();
	virtual bool LoadFromFile(char* path);
	virtual bool SaveToFile(char* path);
	virtual bool ImgProcessing(cv::Mat& src, cv::Mat& dst);
private:
	bool ProcessingSecond(cv::Mat& src, cv::Mat& dst, float a, float b, float c);
};

