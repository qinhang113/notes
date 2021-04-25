using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class SortedSetClass : BaseClass
    {
        public override void TestFun()
        {
            //使用SortedSet去除string重复并排序
            string str1 = "CDAABEFFG";
            char[] c1 = str1.ToArray<char>();
            SortedSet<char> vs = new SortedSet<char>(c1);

            char[] c2 = new char[vs.Count];
            vs.CopyTo(c2, 0);

            string str2 = new string(c2);
            Console.WriteLine(str2);
        }
    }
}
