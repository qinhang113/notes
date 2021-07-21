#pragma once
#include "../LearnCpp/BaseClass.h"
#include <thread>
#include <iostream>
#include <future>

class ThreadClass : public BaseClass
{

	bool m_bClosed = false;
public:
	virtual ~ThreadClass()
	{
	}
	void workfun()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "workfun running" << std::endl;
		m_bClosed = true;
	}
	virtual void TestFun() override
	{
		//这是啥时候写的？完全没印象Fuck
		//auto f = std::async(&ThreadClass::workfun, this);
		auto f = std::async([&] {std::this_thread::sleep_for(std::chrono::milliseconds(5000)); m_bClosed = true; });
		std::cout << "workfun end" << std::endl;
		
		std::thread t([&] {
			int index = 0;
			while (!m_bClosed)
			{
				index++;
				std::cout << index << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		});		
		t.join();
		f.wait();
		m_bClosed = false;
	}

};
