using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    sealed class ClassA
    {
        public int number;
        public string name;
    }
    //ERROR 不能派生自密封类
    //class ClassAA : ClassA
    //{
    //}
    static class ClassB
    {
        static string fun()
        {
            //ERROR 静态方法中不能使用this
            //this;
            return "ClassB";
        }
        //ERROR 静态类中不能定义实例成员
        //void fun1()
        //{
        //}
    }
    //ERROR 静态类不能作为基类
    //class ClassBB : ClassB
    //{
    //}
    abstract class ClassC
    {
        public abstract void funC();
        public void funC1()
        {

        }
    }

    class ClassCC : ClassC
    {
        public sealed override void funC()
        {

        }
        //ERROR funC1不为虚方法不能重写
        //public override void funC1()
        //{
        //}
    }

    class ClassCCC : ClassCC
    {
        //ERROR ClassCC中sealed使funC方法不再为虚方法
        //public override void funC()
        //{
        //}
    }

    interface IClassD
    {
        //ERROR 不能包含字段（可以包含属性），构造函数，析构函数，静态成员和常量。
        //string _name;
        string Name
        {
            get;
            set;
        }
        //默认为public
        void funD();
        //ERROR 不能实现方法
        //void fun1()
        //{ }

    }
    interface IClassDD
    {
        void funDD();
    }

    class D : IClassD,IClassDD
    {
        string _name = "D";
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
        //实现接口中的成员，不能使用override
        public /*override*/ void funD()
        {

        }
        public /*override*/ void funDD()
        {

        }
    }

    class ClassClass : BaseClass
    {
        public override void TestFun()
        {
            //ERROR 静态类不能实例化
            //ClassB b = new ClassB();

            //ERROR 抽象类不能实例化
            //ClassC c = new ClassC();

            //ERROR 接口不能实例化
            //IClassD d = new IClassD();

            //实例1，number和name为默认值
            ClassA a = new ClassA();

            //实例2，指定number和name值
            ClassA aaa = new ClassA { number = 1, name = "一" };

            //匿名对象
            var v = new { number = 1, name = "一" };            
        }
    }
}
