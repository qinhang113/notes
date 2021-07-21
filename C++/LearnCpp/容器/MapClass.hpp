#pragma once
#include "../LearnCpp/BaseClass.h"
#include <map>
#include <string>
#include <functional>
#include <iostream>
//�Զ���key 1.����<
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
//2.����std::function
bool CompareBooks(const MapDataBook& book1, const MapDataBook& book2)
{
	return book1.isbn < book2.isbn;
}

class MapClass : public BaseClass
{
public :
	void TestFun() override
	{
		//std::map<MapDataPerson, std::string> m1 = { {MapDataPerson(1, "����ʶ"),"һ��"},{MapDataPerson(2, "����"),"����"} };
		std::map<MapDataPerson, std::string> m1 = { {MapDataPerson(1, "����ʶ"),"1"}, };
		m1.insert(std::make_pair<MapDataPerson, std::string>(MapDataPerson(1, "����ʶ"), "һ��"));
		m1[MapDataPerson(1, "����ʶ")] = "1";//���滻����һ��MapDataPerson(1, "һ")��ֵ��
		m1.insert(std::make_pair(MapDataPerson(2, "����"), "����"));
		auto re1 = m1.insert(std::make_pair(MapDataPerson(2, "����"), "2"));//����ʧ�ܷ��ص�Ϊpair(������,bool)
		if (!re1.second)
		{			
			std::cout << (re1.first)->second << ",m1����ʧ��!" << std::endl;
		}
		m1[MapDataPerson(4, "����")] = "�ĺ�";
		m1[MapDataPerson(3, "����")] = "����";
		auto re2 = m1.emplace(MapDataPerson(3, "����"), "3");
		if (!re2.second)
		{
			std::cout<< (re2.first)->second << ",m1����ʧ��!" << std::endl;
		}
		auto last = m1.find(MapDataPerson(3, "����"));
		//m1.erase(last);
		auto cmp = m1.key_comp();
		cmp(MapDataPerson(4, "����"), MapDataPerson(3, "����"));
		m1.erase(m1.begin(), last);
		//m1.insert(m1.begin(), std::make_pair(MapDataPerson(0, "������"), "0"));//�ڵ�����λ��ǰ����
		std::cout << "����m1" << std::endl;
		for (auto& p : m1)
		{
			std::cout << p.first.name << std::endl;
		}
;		std::cout << "--------------" << std::endl;
		std::map<MapDataBook, std::string, std::function<bool(const MapDataBook&, const MapDataBook&)>> m2(CompareBooks);
		m2.emplace(MapDataBook(1, "3�쾫ͨC++"), "�ұ�1");
		m2.emplace(MapDataBook(2, "����˿��������"), "�ұ�2");
		auto re3 = m2.emplace(MapDataBook(2, "15�����˯��"), "��");
		if (!re3.second)
		{
			std::cout << (re3.first)->first.name <<",m2����ʧ��!" << std::endl;
		}
	}
};