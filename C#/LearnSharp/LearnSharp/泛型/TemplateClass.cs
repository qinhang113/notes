using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class Temp1<T> where T : struct
    {

    }
    class Temp2<T> where T : class
    {

    }
    class Temp3<T> where T : BaseClass
    {

    }
    class Temp4<T> where T : BaseClass, IClassD, IClassDD
    {

    }
    class TemplateClass : BaseClass
    {
        public override void TestFun()
        {
            //ERROR 约束为值类型
            //Temp<BaseClass> t;
            //ERROR 约束
            //Temp4<int> temp4;
            Temp3<TemplateClass> temp4 = new Temp3<TemplateClass>();
        }
    }
}
