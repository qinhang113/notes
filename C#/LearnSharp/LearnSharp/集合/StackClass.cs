using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class StackClass : BaseClass
    {
        public override void TestFun()
        {
            Stack stack = new Stack();
            for (int i = 0; i < 6; i++)
            {
                stack.Push(i);
            }
            //元素出栈
            Console.WriteLine("stack顶元素：{0}", stack.Pop());
            //返回顶元素
            Console.WriteLine("stack顶元素：{0}", stack.Peek());
        }
    }
}
