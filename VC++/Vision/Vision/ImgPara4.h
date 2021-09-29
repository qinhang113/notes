#pragma once
#include "ImgPara.h"
class ImgPara4 : public ImgPara
{
	std::vector<int> templateSortIndex;
	std::vector<float> templateAreas;
public:
	virtual bool LoadFromFile(char* path);
	virtual bool SaveToFile(char* path);
	virtual bool ImgProcessing(cv::Mat& src, cv::Mat& dst);
	bool SetTemplateImg(cv::Mat& src, cv::Mat& dst);
private:
	bool CompareArea(double a1, double a2);
	bool JudgeScratch(cv::Mat& src, cv::Mat& dst);
};

