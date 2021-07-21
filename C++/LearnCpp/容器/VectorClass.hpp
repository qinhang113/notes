#pragma once

#include "../LearnCpp/BaseClass.h"
#include <vector>
class VectorClass : public BaseClass
{
	int ivalue;
public:
	virtual void TestFun()
	{
		std::vector<int> v(10);
		for (auto& i : v)
		{
			std::cout << i << std::endl;
		}
		v.resize(11);
		v.resize(8);
		std::cout << v.capacity() << std::endl;

		//void assign(_CRT_GUARDOVERFLOW size_type _Count, const bool& _Val)
		v.assign(8, 1);//参数1:个数（n）,参数2:值。初始化vector设置_Count个元素为_Val,此操作将改变容器的size

		std::vector<int> v2(10);
		//void assign(_Iter _First, _Iter _Last)
		v2.assign(v.begin(), v.end());//拷贝，
		//int p = v2[2];
		try
		{
			v2.at(8);
		}
		catch (const std::exception&)
		{
			std::cout << "异常!" << std::endl;
		}

		//for (auto i = v.begin(); i < v.end(); i++)
		//{
		//	v.erase(i);//error
		//}

		for (auto i = v.begin(); i < v.end();)
		{
			i = v.erase(i);
		}
		//插入数组
		int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
		//iterator insert(const_iterator _Where, _Iter _First, _Iter _Last)
		v.insert(v.begin(), std::begin(arr), std::begin(arr) + 2);
		//iterator insert(const_iterator _Where, initializer_list<_Ty> _Ilist)
		v.insert(v.begin() + 2, { 2,3 });
		for (auto& i : v)
		{
			std::cout << i << std::endl;
		}
	}
};

