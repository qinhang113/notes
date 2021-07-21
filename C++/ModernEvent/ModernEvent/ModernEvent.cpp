// ModernEvent.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "CEvent.h"

void Trigger(CEvent* _e)
{
    _e->Trigger(1001);
    this_thread::sleep_for(chrono::milliseconds(10000));
    _e->Trigger(1002);
}

int main()
{
    CEvent* _e = new CEvent;
    _e->Register(1001, [] {std::cout << "事件1001触发！" << endl; });
    _e->Register(1002, [] {std::cout << "事件1002触发！" << endl; });
    _e->Start();

    thread t(Trigger, _e);
    t.join();
    delete _e;
    std::cout << "Hello World!\n";
}
