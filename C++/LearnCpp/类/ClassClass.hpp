#pragma once
#include "../LearnCpp/BaseClass.h"

class A
{
public:
	A() { std::cout << "A被构造!" << std::endl; }
	virtual ~A() { std::cout << "A被析构!" << std::endl; }
protected:
	int a;
};
class AA : virtual public A
{
public:
	AA() { std::cout << "AA被构造!" << std::endl; }
	~AA() { std::cout << "AA被析构!" << std::endl; }
};

class BB : virtual public A
{

};

class AABB : public AA, public BB
{
public:
	void SetValue(int v) 
	{ 
		//ERROR
		a = v; 
	}
};

#pragma region 友元函数
class C;
class D;
class B
{
	int b;
public:
	int GetValue(C* c, D* d);
};
class C
{
	int c;
	friend int B::GetValue(C* c, D* d);
public:
	C(int v) :c(v) {}
};
class D
{
	int d;
	friend int B::GetValue(C* c, D* d);
public:
	D(int v) :d(v) {}
};

int B::GetValue(C* c, D* d)
{
	return c->c + d->d;
}
#pragma endregion


#pragma region 友元类
//class B
//{
//	int b;
//	friend class C;
//public:
//
//};
//class C
//{
//	B* b;
//public:
//	int GetBValue()
//	{
//		return b->b;
//	}
//};
#pragma endregion

class E
{
public:
	/*explicit */E(int v) :value(v)
	{
		std::cout << "E构造函数被调用,value:" << v << std::endl;
		name = new char[1024];
		sprintf_s(name, 1024, "CLASSE %d", v);
	}

	E(E& e)
	{
		value = e.value;
		int size = strlen(e.name) + 1;
		name = new char[size];
		memcpy(name, e.name, size);
		std::cout << "E拷贝构造函数被调用,name:" << name << std::endl;
	}
	E& operator=(const E& e)
	{
		if (this != &e)//地址不同
		{
			delete[] name;
			value = e.value;
			int size = strlen(e.name) + 1;
			name = new char[size];
			memcpy(name, e.name, size);
		}
		std::cout << "E赋值运算符被调用,name:" << name << std::endl;
		return *this;
	}
	E(E&& e)
	{
		value = e.value;
		name = e.name;
		e.name = nullptr;
		std::cout << "E移动拷贝构造函数被调用,name:" << name << std::endl;
	}
	E& operator=(E&& e)
	{
		value = e.value;
		name = e.name;
		e.name = nullptr;
		std::cout << "E移动赋值运算符被调用,name:" << name << std::endl;
		return *this;
	}
	//E() = default;//默认构造函数，当自定义构造函数后将没有默认构造函数，可以用default重新定义
	//E& operator=(const E&) = delete;
	//E(const E&) = delete;

	int GetValue()
	{
		return value;
	}
	char* GetName()
	{
		return name;
	}
private:
	int value;
	char* name;
};

class ClassClass : public BaseClass
{
public:
	virtual void TestFun() override
	{
		//C c(2);
		//D d(3);
		//B b;
		//std::cout << b.GetValue(&c, &d) << std::endl;
		AA* aa = new AA;
		delete aa;

		E e = 3;//无explicit OK。有explicit error		
		E e1(e);//拷贝构造函数被调用
		E *e2 = new E(2);
		*e2 = e;//赋值运算符被调用

		//通过默认拷贝构造函数、默认赋值运算符进行的是浅拷贝，只是把name的指针地址复制了过去
		char* s = e.GetName();
		std::cout << "e.name的地址：" << (void*)s << std::endl;
		s = e2->GetName();
		std::cout << "e2.name的地址：" << (void*)s << std::endl;

		E e3(std::move(e));
		s = e3.GetName();
		std::cout << "e3.name的地址：" << (void*)s << std::endl;
		s = e.GetName();
		std::cout << "e.name的地址：" << (void*)s << std::endl;

		E* e4 = new E(4); 
		*e4 = std::move(e1);//移动赋值运算符被调用
		s = e4->GetName();
		std::cout << "e4.name的地址：" << (void*)s << std::endl;
	}
};