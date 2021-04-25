using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class HashtableClass : BaseClass
    {
        public override void TestFun()
        {
            Hashtable hashtable = new Hashtable();
            try
            {
                hashtable.Add(0, "零");
                hashtable.Add(1, "一");
                hashtable.Add(2, "二");
                hashtable.Add(3, "三");
                hashtable.Add(4, "四");
                hashtable.Add(5, "五");
                //异常 key重复
                //hashtable.Add(5, "伍");
                hashtable.Add(7, "七");
                hashtable.Add(6, "六");
                hashtable.Add("五", "伍");
            }
            catch(ArgumentException ex)
            {
                Console.WriteLine(ex.Message);
            }

            foreach (var v in hashtable.Keys)
            {
                Console.Write("key:{0},hash:{1},", v, v.GetHashCode());
            }
            Console.Write("\n");
        }
    }
}
