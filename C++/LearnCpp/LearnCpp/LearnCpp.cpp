// LearnCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../类/ClassClass.hpp"
#include "../容器/VectorClass.hpp"
#include "../容器/ArrayClass.hpp"
#include "../容器/DequeClass.hpp"
#include "../容器/ListClass.hpp"
#include "../容器/ForwardlistClass.hpp"
#include "../容器/MapClass.hpp"
#include "../线程/ThreadClass.hpp"
#include "../线程/AtomicClass.hpp"
int main()
{
    std::map<std::string, BaseClass*> baseMap;

    baseMap.insert(std::make_pair("类", new ClassClass())); 
    baseMap.insert(std::make_pair("vector", new VectorClass()));
    baseMap.insert(std::make_pair("array", new ArrayClass())); 
    baseMap.insert(std::make_pair("deque", new DequeClass()));
    baseMap.insert(std::make_pair("list", new ListClass())); 
    baseMap.insert(std::make_pair("forward_list", new ForwardlistClass())); 
    baseMap.insert(std::make_pair("map", new MapClass())); 
    baseMap.insert(std::make_pair("thread", new ThreadClass()));
    baseMap.insert(std::make_pair("Atomic", new AtomicClass()));
    
    int index = 0;
    char str[1024] = { 0 };

    std::vector<std::string> classnames;
    for (auto& b : baseMap)
    {
        classnames.push_back(b.first);
        sprintf_s(str, "%d-%s\n", index, b.first.c_str());
        std::cout << str;
        index++;
    }
    int number;
    std::string choose;
    while (true)
    {
        std::cout << "请输入序号进行操作:\n";
        std::cin >> number;
        try
        {
            choose = classnames.at(number);
        }
        catch (const std::exception&)
        {
            std::cout << "输入序号不正确!\n";
            continue;
        }
        baseMap[classnames[number]]->TestFun();
    }

    system("pause");
}

