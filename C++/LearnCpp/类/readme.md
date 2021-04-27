# 类

## 继承/派生
* 构造顺序：实例化子类时先执行子类构造函数，然后执行父类构造
* 析构顺序
    1. 父类指针指向子类对象。删除指针时若父类的析构函数不为虚函数，则不会调用子类析构函数导致内存释放不完全。
    2. 先执行父类析构函数，后执行子类析构函数。
* 公有继承
 
|  | 基类pulic成员 | 基类private成员 | 基类protected成员 |
| ---- | ---- | ---- | ---- |
| public继承 | public | 不可访问 | protected |
| private继承 | private | 不可访问 | private |
| protected继承 | protected | 不可访问 | protected |

## 多态
* 动态多态（运行期多态）
    1. 通过父类的指针或引用调用虚函数
* 静态多态
    1. 通过函数重载完成

## 封装    
* 隐藏对象的属性和实现细节通过访问限定符实现

## 友元
* 友元函数
    1. 友元函数声明在类内，但定义在类外，并不受类访问限定符限制。以关键字friend修饰。
    2. 友元函数不是成员函数，但可以访问类的私有成员
    3. 友元破坏了类的封装和隐藏性
    4. 友元函数不能使用const修饰
    5. 一个函数可以是多个类的友元函数
* 友元类
    1. 当一个类作为另一个类的友元时，这就意味着这个类的所有成员函数都是另一个类的友元函数，都可以访问另一个类中的非公有成员。
    2. 友元关系是单向的
    3. 友元关系不可传递
    4. 友元关系不能继承

## 虚基类
* 如果一个派生类有多个直接基类，而这些直接基类又有一个共同的基类，则在最终的派生类中会保留该间接共同基类数据成员的多份同名成员
* 使用虚继承则使得在继承间接共同基类时只保留一份成员。
```C++
class A
{
protected: 
    int a;
};

class AA : public A// 应为class AA : virtual public A
{
};

class BB : public A// 应为class BB : virtual public A
{
};

class AABB : public AA, public BB
{
public:
    void SetValue(int v)
    {
        a = v;//error
    }
};
```

## 抽象类
* 至少有一个纯虚函数的类（纯虚函数没有函数体，并在虚函数后有“=0”）
* 抽象类无法被实例化
* 抽象类的派生类必须实现所有基类中的纯虚函数才能被实例化

## explicit
* 修饰构造函数防止隐式转换

```C++
class E
{
    int value;
public:
    /*explicit*/ E(int v) : value(v) {}
}

int main(void)
{
    E e = 3; //无explicit OK。有explicit error
}
```
## 特殊成员函数
* 构造函数
    1. 类如果没有提供任何构造函数，C++将创建默认构造函数
    2. 当自定义构造函数后将删除默认构造函数
    3. 可以用`default`重新恢复默认定义，或用`delete`删除默认构造函数
* 析构函数
    1. 格式 `~Class()`
    2. 析构函数没有参数，不能被重载，一个类只有一个析构函数，如果类未定义此函数，则会自动生成
* 复制（拷贝）构造函数
    1. 格式 `Class(const Class&)`或者`Class(Class&)`
    2. 如果类未定义此函数，则会自动生成。默认复制构造函数完成从源对象到目标对象逐个字节的复制
    3. 可以用`default`重新恢复默认定义，或用`delete`删除默认拷贝构造函数
* 赋值运算符
    1. 格式 `Class& operator=(const Class&)`
    2. 如果类未定义此函数，则会自动生成。
    3. 经初始化后的对象被赋值才会调用赋值运算符，例如`Class a(1);Class b(2);a = b;`会调用赋值运算符，而`Class a(1);Class b = a;`调用拷贝构造函数
* 移动构造函数
    1. 格式 `Class(Class &&)`
    2. 若定义此函数则默认赋值运算符将会删除
* 移动赋值运算符
    1. 格式 `Class& operator=(Class &&)`
    2. 经初始化后的对象被赋值才会调用移动赋值运算符

## 三/五法则
* 三法则：如果你需要显式定义特殊成员函数（析构函数、复制构造函数和赋值运算符）中一个，那么你可能也需要显式定义另外两个
* 五法则：C++11开始，特殊成员函数加入移动构造函数和移动赋值运算符。

```C++
class person
{
    std::string name;
    int age;

public:
    person(const std::string& name, int age);        // Ctor
    person(const person &) = default;                // Copy Ctor
    person(person &&) noexcept = default;            // Move Ctor
    person& operator=(const person &) = default;     // Copy Assignment
    person& operator=(person &&) noexcept = default; // Move Assignment
    ~person() noexcept = default;                    // Dtor
};
```

> [参考stackoverflow](https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three)