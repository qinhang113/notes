using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class PropertyClass : BaseClass
    {
        string _name = "PropertyClass";
        int _id;
        //只读属性
        public string Name
        {
            get
            {
                return _name;
            }
        }
        public int Id
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value < 0 ? 0 : value;
            }
        }
        public PropertyClass()
        {
            //Error Name只读即使在类内和类的构造函数中
            //Name = "";
        }
        public override void TestFun()
        {
            //Error Name只读即使在类内
            //Name = "";
            Console.WriteLine("Name:{0},ID:{1}", this.Name, this.Id);
        }
    }
}
