#pragma once

#include "../LearnCpp/BaseClass.h"
#include <vector>
class VectorClass : public BaseClass
{
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
		v.assign(8, 1);//����1:������n��,����2:ֵ����ʼ��vector����_Count��Ԫ��Ϊ_Val,�˲������ı�������size

		std::vector<int> v2(10);
		//void assign(_Iter _First, _Iter _Last)
		v2.assign(v.begin(), v.end());//������
		//int p = v2[2];
		try
		{
			int p = v2.at(8);
		}
		catch (const std::exception&)
		{
			std::cout << "�쳣!" << std::endl;
		}

		//for (auto i = v.begin(); i < v.end(); i++)
		//{
		//	v.erase(i);//error
		//}

		for (auto i = v.begin(); i < v.end();)
		{
			i = v.erase(i);
		}

	}
};

