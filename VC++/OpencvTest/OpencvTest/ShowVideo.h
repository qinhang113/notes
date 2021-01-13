#pragma once
#include "IOpencvManager.h"
#include <thread>

class ShowVideo : public IOpencvManager
{
	bool m_bClose{ false }, m_bFirstFrame{ true };
public:
	virtual void OnRun() override;
	virtual void ReleaseImg() override;
};