#pragma once
#include "../LearnCpp/BaseClass.h"
#include <deque>

class DequeClass : public BaseClass
{
public :
	void TestFun() override
	{
		std::deque<int> de({ 0,1,2 });
		de.push_back(3);
		de.push_front(-1);

		for (auto& i : de)
		{
			std::cout << i << ",";
		}
		std::cout << std::endl;

		std::cout << "deque最大大小:" << de.max_size() << std::endl;
	}
};