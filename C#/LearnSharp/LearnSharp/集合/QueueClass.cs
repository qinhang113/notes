using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class QueueClass : BaseClass
    {
        public override void TestFun()
        {
            Queue queue = new Queue();
            for (int i = 0; i < 6; i++)
            {
                queue.Enqueue(i);
            }
            //元素出列
            Console.WriteLine("queue头元素：{0}", queue.Dequeue());
            //返回队列头元素不出列
            Console.WriteLine("queue头元素：{0}", queue.Peek());
        }
    }
}
