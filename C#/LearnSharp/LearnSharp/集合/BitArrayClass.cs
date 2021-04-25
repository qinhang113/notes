using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{
    class BitArrayClass : BaseClass
    {
        public override void TestFun()
        {
            //实例化需指定长度
            //BitArray bitArray = new BitArray(6 * 32);
            int[] iarr1 = { 1, 2, 3, 4, 5, 6 };
            BitArray bitArray = new BitArray(iarr1);
            //192
            Console.WriteLine("bitArray大小:{0}", bitArray.Count);
            int[] iarr2 = new int[6];
            bitArray.CopyTo(iarr2, 0);
            foreach(var i in iarr2)
            {
                Console.Write("{0},", i);
            }
            Console.Write("\n");
            //ERROR 长度不匹配
            //bool[] barr = new bool[6];
            bool[] barr = new bool[6 * 32];
            bitArray.CopyTo(barr, 0);
            foreach (var i in barr)
            {
                Console.Write("{0},", i);
            }
            Console.Write("\n");
            //不是很理解，sizeof(bool) == sizeof(byte)同样是占8位凭什么
            byte[] barr2 = new byte[6 * 4];
            bitArray.CopyTo(barr2, 0);
            foreach (var i in barr2)
            {
                Console.Write("{0},", i);
            }
            Console.Write("\n");
            //ERROR CopyTo仅支持byte[],int[],bool[]
            //char[] carr = new char[12];
            //bitArray.CopyTo(carr, 0);
        }
    }
}
