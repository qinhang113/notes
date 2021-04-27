// LearnCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../类/ClassClass.hpp"
#include "../容器/VectorClass.hpp"
int main()
{
    std::map<std::string, BaseClass*> baseMap;

    baseMap.insert(std::make_pair("类", new ClassClass())); 
    baseMap.insert(std::make_pair("vector", new VectorClass()));
    std::cout << "请输入序号进行操作:\n";
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
    std::cin >> number;
    baseMap[classnames[number]]->TestFun();

    system("pause");
}

