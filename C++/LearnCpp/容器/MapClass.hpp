#pragma once
#include "../LearnCpp/BaseClass.h"
#include <map>
#include <string>
#include <functional>
#include <iostream>
//自定义key 1.重载<
class MapDataPerson
{
public:
	int number;
	std::string name;

	MapDataPerson(int number, std::string name)
	{
		this->number = number;
		this->name = name;
	}
	bool operator<(const MapDataPerson& data) const
	{
		return this->number < data.number;
	}
};

class MapDataBook
{
public:
	int isbn;
	std::string name;

	MapDataBook(int isbn, std::string name)
	{
		this->isbn = isbn;
		this->name = name;
	}
};
//2.传入std::function
bool CompareBooks(const MapDataBook& book1, const MapDataBook& book2)
{
	return book1.isbn < book2.isbn;
}

class MapClass : public BaseClass
{
public :
	void TestFun() override
	{
		//std::map<MapDataPerson, std::string> m1 = { {MapDataPerson(1, "不认识"),"一号"},{MapDataPerson(2, "王二"),"二号"} };
		std::map<MapDataPerson, std::string> m1 = { {MapDataPerson(1, "不认识"),"1"}, };
		m1.insert(std::make_pair<MapDataPerson, std::string>(MapDataPerson(1, "不认识"), "一号"));
		m1[MapDataPerson(1, "不认识")] = "1";//将替换掉上一个MapDataPerson(1, "一")键值对
		m1.insert(std::make_pair(MapDataPerson(2, "王二"), "二号"));
		auto re1 = m1.insert(std::make_pair(MapDataPerson(2, "王二"), "2"));//插入失败返回的为pair(迭代器,bool)
		if (!re1.second)
		{			
			std::cout << (re1.first)->second << ",m1插入失败!" << std::endl;
		}
		m1[MapDataPerson(4, "李四")] = "四号";
		m1[MapDataPerson(3, "张三")] = "三号";
		auto re2 = m1.emplace(MapDataPerson(3, "张三"), "3");
		if (!re2.second)
		{
			std::cout<< (re2.first)->second << ",m1插入失败!" << std::endl;
		}
		auto last = m1.find(MapDataPerson(3, "张三"));
		//m1.erase(last);
		auto cmp = m1.key_comp();
		cmp(MapDataPerson(4, "李四"), MapDataPerson(3, "张三"));
		m1.erase(m1.begin(), last);
		//m1.insert(m1.begin(), std::make_pair(MapDataPerson(0, "零零零"), "0"));//在迭代器位置前插入
		std::cout << "遍历m1" << std::endl;
		for (auto& p : m1)
		{
			std::cout << p.first.name << std::endl;
		}
;		std::cout << "--------------" << std::endl;
		std::map<MapDataBook, std::string, std::function<bool(const MapDataBook&, const MapDataBook&)>> m2(CompareBooks);
		m2.emplace(MapDataBook(1, "3天精通C++"), "乱编1");
		m2.emplace(MapDataBook(2, "吃铁丝儿拉笊篱"), "乱编2");
		auto re3 = m2.emplace(MapDataBook(2, "15秒深度睡眠"), "真");
		if (!re3.second)
		{
			std::cout << (re3.first)->first.name <<",m2插入失败!" << std::endl;
		}
	}
};