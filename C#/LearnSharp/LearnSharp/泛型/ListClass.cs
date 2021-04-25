using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class ListClass : BaseClass
    {
        public override void TestFun()
        {
            List<BaseClass> vs = new List<BaseClass>();
            vs.Add(new TemplateClass());
            vs.Add(new ArrayListClass());
            vs.Add(new HashtableClass());
            vs.Add(new QueueClass());
            
            foreach(var v in vs)
            {
                v.TestFun();
            }
        }
    } 
}
