#pragma once
#include "ImgPara.h"
class ImgPara3 : public ImgPara
{
public:
	double minAreaLeft, maxAreaLeft, minAreaRight, maxAreaRight;
public:
	virtual bool LoadFromFile(char* path);
	virtual bool SaveToFile(char* path);
	virtual bool ImgProcessing(cv::Mat& src, cv::Mat& dst);
};

