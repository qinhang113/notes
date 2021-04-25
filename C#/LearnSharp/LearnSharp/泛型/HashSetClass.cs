using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class HashSetClass : BaseClass
    {
        public override void TestFun()
        {
            //使用hashset去除string重复
            string str1 = "CDAABEFFG";
            char[] c1 = str1.ToArray<char>();
            HashSet<char> vs = new HashSet<char>(c1);
            
            char[] c2 = new char[vs.Count];
            vs.CopyTo(c2, 0);

            string str2 = new string(c2);
            Console.WriteLine(str2);
            
        }
    }
}
