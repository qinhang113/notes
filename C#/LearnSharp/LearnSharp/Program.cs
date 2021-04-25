using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class Program
    {
        static void Main(string[] args)
        {            
            Dictionary<string, BaseClass> dict = new Dictionary<string, BaseClass>();
            dict.Add("动态数组", new ArrayListClass());
            dict.Add("栈", new StackClass());
            dict.Add("队列", new QueueClass());
            dict.Add("哈希表", new HashtableClass()); 
            dict.Add("点阵列", new BitArrayClass());
            dict.Add("索引器", new IndexerClass());
            dict.Add("类", new ClassClass());
            dict.Add("属性", new PropertyClass());
            dict.Add("泛型", new TemplateClass());
            dict.Add("泛型列表", new ListClass());
            dict.Add("哈希集", new HashSetClass()); 
            dict.Add("排序集", new SortedSetClass());
            dict.Add("字典", new DictionaryClass());
            

            Console.WriteLine("输入如下指令进行操作:");
            int index = 0;
            foreach(var v in dict.Keys)
            {
                Console.WriteLine("{0}-{1}", index, v);
                index++;
            }
            string str = Console.ReadLine();
            BaseClass b = dict.ElementAt(Convert.ToInt32(str)).Value;
            b.TestFun();

            Console.ReadKey();
        }
    }
}
