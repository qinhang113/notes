#pragma once
#include "../LearnCpp/BaseClass.h"

class A
{
public:
	A() { std::cout << "A������!" << std::endl; }
	virtual ~A() { std::cout << "A������!" << std::endl; }
protected:
	int a;
};
class AA : virtual public A
{
public:
	AA() { std::cout << "AA������!" << std::endl; }
	~AA() { std::cout << "AA������!" << std::endl; }
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

#pragma region ��Ԫ����
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


#pragma region ��Ԫ��
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
		std::cout << "E���캯��������,value:" << v << std::endl;
		name = new char[1024];
		sprintf_s(name, 1024, "CLASSE %d", v);
	}

	E(E& e)
	{
		value = e.value;
		int size = strlen(e.name) + 1;
		name = new char[size];
		memcpy(name, e.name, size);
		std::cout << "E�������캯��������,name:" << name << std::endl;
	}
	E& operator=(const E& e)
	{
		if (this != &e)//��ַ��ͬ
		{
			delete[] name;
			value = e.value;
			int size = strlen(e.name) + 1;
			name = new char[size];
			memcpy(name, e.name, size);
		}
		std::cout << "E��ֵ�����������,name:" << name << std::endl;
		return *this;
	}
	E(E&& e)
	{
		value = e.value;
		name = e.name;
		e.name = nullptr;
		std::cout << "E�ƶ��������캯��������,name:" << name << std::endl;
	}
	E& operator=(E&& e)
	{
		value = e.value;
		name = e.name;
		e.name = nullptr;
		std::cout << "E�ƶ���ֵ�����������,name:" << name << std::endl;
		return *this;
	}
	//E() = default;//Ĭ�Ϲ��캯�������Զ��幹�캯����û��Ĭ�Ϲ��캯����������default���¶���
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

		E e = 3;//��explicit OK����explicit error		
		E e1(e);//�������캯��������
		E *e2 = new E(2);
		*e2 = e;//��ֵ�����������

		//ͨ��Ĭ�Ͽ������캯����Ĭ�ϸ�ֵ��������е���ǳ������ֻ�ǰ�name��ָ���ַ�����˹�ȥ
		char* s = e.GetName();
		std::cout << "e.name�ĵ�ַ��" << (void*)s << std::endl;
		s = e2->GetName();
		std::cout << "e2.name�ĵ�ַ��" << (void*)s << std::endl;

		E e3(std::move(e));
		s = e3.GetName();
		std::cout << "e3.name�ĵ�ַ��" << (void*)s << std::endl;
		s = e.GetName();
		std::cout << "e.name�ĵ�ַ��" << (void*)s << std::endl;

		E* e4 = new E(4); 
		*e4 = std::move(e1);//�ƶ���ֵ�����������
		s = e4->GetName();
		std::cout << "e4.name�ĵ�ַ��" << (void*)s << std::endl;
	}
};