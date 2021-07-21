#pragma once
#include "..\LearnCpp\BaseClass.h"
#include <atomic>
#include <future>
#include <iostream>

class AtomicClass : public BaseClass
{
	std::atomic<bool> ready = false;
    std::atomic_flag winner = ATOMIC_FLAG_INIT;
public:
	virtual void TestFun() override
	{
		std::atomic<bool> run = true;
        /*std::future<bool>*/ auto fut = std::async(&AtomicClass::is_prime, this, 700020007, std::ref(run));

        std::vector<std::thread> threads;
        std::cout << "spawning 10 threads that count to 1 million...\n";
        ready = true;
        for (int i = 1; i <= 10; ++i)
        {
            //std::thread t(&AtomicClass::countm, this, i);//error
            threads.push_back(std::thread(&AtomicClass::countm, this, i));
        }
        for (auto& t : threads)
        {
            t.join();
        }
        std::cout << "是否为质数:" << fut.get() << "\n";
        ready = false;
	}
private:
    bool is_prime(int x, std::atomic<bool>& run)
    {
        for (int i = 2; i < sqrt(x); ++i)
        {
            if (!run)
            {
                throw std::runtime_error("timeout");
            }
            if (x % i == 0)
                return false;
        }
        return true;
    }
    void countm(int id)
    {
        while (!ready) { std::this_thread::yield(); } // 等待 ready 变为 true.

        for (volatile int i = 0; i < 1000000; ++i) {} // 计数

        if (!winner.test_and_set()) {
            std::cout << "thread #" << id << " won!\n";
        }
    }
};
