using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class DictionaryClass : BaseClass
    {
        class DataDictionary
        {
            public int number;
            public char name;
        }
        public override void TestFun()
        {
            Dictionary<DataDictionary, string> keyValuePairs = new Dictionary<DataDictionary, string>();

            DataDictionary d1 = new DataDictionary { number = 0, name = '0' };
            DataDictionary d2 = new DataDictionary { number = 1, name = '1' };
            DataDictionary d3 = new DataDictionary { number = 2, name = '2' };
            DataDictionary d4 = new DataDictionary { number = 3, name = '3' };
            DataDictionary d11 = new DataDictionary { number = 0, name = '0' };

            /***
             * 对于引用类型，默认是比较这两个对象是否存储在同一个内存位置来判别它们是否相等的。所以d11 != d1
             * 对于值类型（如struct）则比较彼此内存中存放的数据是否相等来判别两个对象是否相等。
             * HashCode值一致不意味着Object.Equals比较是相等的
             * Object.Equals比较相等则HashCode一致
            ***/

            keyValuePairs.Add(d1, "零");
            keyValuePairs.Add(d2, "一");
            keyValuePairs.Add(d3, "二");
            keyValuePairs.Add(d4, "三");
            keyValuePairs.Add(d11, "一一");

            Console.WriteLine(d1.Equals(d11));
            Console.WriteLine("{0},{1}", d1.GetHashCode(), d11.GetHashCode());

            //异常
            //Console.WriteLine("{0}", keyValuePairs[new DataDictionary { number = 0, name = '0' }]);
            Console.WriteLine("{0}", keyValuePairs[d2]);
            //需要实现IEquatable接口否则ContainsKey返回Flase
            Console.WriteLine(keyValuePairs.ContainsKey(d1));
        }
    }
}
