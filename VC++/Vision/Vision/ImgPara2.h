#pragma once
#include "ImgPara1.h"
class ImgPara2 : public ImgPara1
{
public:
	virtual bool LoadFromFile(char* path);
	virtual bool SaveToFile(char* path);
};

