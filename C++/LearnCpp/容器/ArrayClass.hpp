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
		int p = arr3[10];//�˴�����Խ�磬���������鲢���ж��±��Ƿ񳬳����鳤�ȣ�ֻ��ָ����ƶ�
		std::cout << "������������10ֵ:" << p << std::endl;
		p = arr3[-1];//
		std::cout << "������������-1ֵ:" << p << std::endl;

		p = arr2[-1];//����
		p = arr2[10];//����

	}
};