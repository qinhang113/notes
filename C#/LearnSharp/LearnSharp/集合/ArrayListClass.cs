using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class DataArrayList : IComparable
    {
        public int number;
        public string name;

        public int CompareTo(object obj)
        {
            return this.number - ((DataArrayList)obj).number;
        }
    }
    class ArrayListClass : BaseClass
    {
        public override void TestFun()
        {
            //ArrayList对象可以指定初始容量
            //每当容量占满后会重新开辟当前容量2倍的空间（如：5，10，20）
            ArrayList arrayList = new ArrayList(5);
            for (int i = 0; i < 6; i++) 
            {
                arrayList.Add(i);
            }
            Console.WriteLine("arrayList大小：{0}", arrayList.Count);
            Console.WriteLine("arrayList容量（可包含的元素数量）：{0}", arrayList.Capacity);
            for (int i = 0; i < 6; i++)
            {
                arrayList.Add(i);
            }
            Console.WriteLine("arrayList大小：{0}", arrayList.Count);
            Console.WriteLine("arrayList容量（可包含的元素数量）：{0}", arrayList.Capacity);

            arrayList.AddRange(new ArrayList { 8, 7, 6 });

            ArrayList list = arrayList.GetRange(6, 3);
            arrayList.IndexOf(6, 0, 9);

            arrayList.Reverse(0, 6);

            arrayList.Clear();

            ArrayList listData = new ArrayList();
            listData.Add(new DataArrayList { number = 1, name = "一" });
            listData.Add(new DataArrayList { number = 4, name = "四" });
            listData.Add(new DataArrayList { number = 2, name = "二" });
            listData.Add(new DataArrayList { number = 9, name = "九" });
            listData.Sort();
            foreach(var v in listData)
            {
                DataArrayList d = v as DataArrayList;
                Console.WriteLine("number:{0},name:{1}", d.number, d.name);
            }
        }
    }
}
