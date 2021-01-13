#pragma once
#include "IOpencvManager.h"

class ShowImage : public IOpencvManager
{
public:
	virtual void ReleaseImg() override;
	virtual void OnRun() override;
};

