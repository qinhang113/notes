#pragma once
#include "../LearnCpp/BaseClass.h"
#include <array>
class ArrayClass : public BaseClass
{
public:
	void TestFun() override
	{
		std::array<int, 10> arr1;
		std::cout << arr1.size() << std::endl;//size = 10;
		arr1.fill(1);
		
		std::cout << arr1.empty() << std::endl;

		std::array<int, 10> arr2;
		arr2.fill(2);
		arr1.swap(arr2);

		int arr3[10] = { 0 };
		int p = arr3[10];//此处数组越界，但内置数组并不判断下标是否超出数组长度，只是指针的移动
		std::cout << "内置数组索引10值:" << p << std::endl;
		p = arr3[-1];//
		std::cout << "内置数组索引-1值:" << p << std::endl;

		p = arr2[-1];//断言
		p = arr2[10];//断言

	}
};