#pragma once
#include "../LearnCpp/BaseClass.h"
#include <forward_list>

class ForwardlistClass : public BaseClass
{
public:
	void TestFun() override
	{
		std::forward_list<int> flist1;
		//flist1.push_front(0);
		//flist1.push_front(1);
		//flist1.push_front(2);
		//flist1 : 2,1,0
		flist1.assign({ 0,1,2 });
		for (auto& i : flist1)
		{
			std::cout << i << ",";//0,1,2
		}
		std::cout << std::endl;
		flist1.assign(3, 1);

		std::forward_list<int> flist2;
		flist2.assign(flist1.begin(), flist1.end());
	}
};