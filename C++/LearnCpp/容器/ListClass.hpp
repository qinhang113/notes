#pragma once
#include "../LearnCpp/BaseClass.h"
#include <list>

class ListData
{
public:
	std::string name;
	int number;
	ListData(int number, std::string name)
	{
		this->number = number;
		this->name = name;
	}
	bool operator<(const ListData& data)
	{
		return this->number < data.number;
	}
};

struct compareData
{
	bool operator()(const ListData& data1, const ListData& data2)
	{
		return data1.number < data2.number;
	}
};

class ListClass : public BaseClass
{
public :
	void TestFun() override
	{
		std::list<int> list1({ 0,1,2 });
		//list.assign(10, 1);
		//for (auto& i : list1)
		//{
		//	std::cout << i << ",";
		//}
		//std::cout << std::endl;
		list1.assign(list1.begin(), list1.end());

		std::list<int> list2({ 5,4,3 });
		list2.sort();
		list1.merge(list2/*, std::greater<int>()*/);
		for (auto& i : list1)
		{
			std::cout << i << ",";
		}
		std::cout << std::endl;

		std::list<ListData> list3;
		list3.push_back(ListData(3, "����"));
		list3.push_back(ListData(2, "����"));
		list3.push_back(ListData(1, "����ʶ"));
		list3.sort();
		for (auto& i : list3)
		{
			std::cout << i.name << ",";
		}
		std::cout << std::endl;

		std::list<ListData> list4;
		list4.emplace_back(6, "����");
		//list4.push_back(ListData(6, "����"));
		list4.push_back(ListData(5, "����"));
		list4.push_back(ListData(4, "����"));
		list4.sort();
		list3.merge(list4, compareData());
		for (auto& i : list3)
		{
			std::cout << i.name << ",";
		}
		std::cout << std::endl;

		list3.reverse();
		for (auto& i : list3)
		{
			std::cout << i.name << ",";
		}
		std::cout << std::endl;
	}
};