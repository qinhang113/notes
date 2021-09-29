#pragma once
#include <opencv.hpp>
struct AreaCmp
{
	AreaCmp(const std::vector<float>& _areas) : areas(&_areas) {}
	bool operator()(int a, int b) const { return (*areas)[a] > (*areas)[b]; }
	const std::vector<float>* areas;
};

class ImgPara
{
public:
	virtual ~ImgPara() {}
	virtual bool LoadFromFile(char* path) = 0;
	virtual bool SaveToFile(char* path) = 0;
	virtual bool ImgProcessing(cv::Mat& src, cv::Mat& dst) = 0;
};

