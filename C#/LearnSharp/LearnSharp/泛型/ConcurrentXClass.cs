using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace LearnSharp
{
    class ConcurrentXClass : BaseClass
    {
        public override void TestFun()
        {
            //以下并发集合不在展示使用
            //ConcurrentQueue<T>
            //ConcurrentStack<T>
            //ConcurrentBag<T>
            //ConcurrentDictionary<TKey, TValue>

            //BlockingCollection片段代码来自C#入门经典(第7版) 10.11章节
            #region BlockingCollection
            var sharedCollection = new BlockingCollection<int>();
            var events = new ManualResetEventSlim[2];
            var waits = new WaitHandle[2];

            for (int i = 0; i < 2; i++)
            {
                events[i] = new ManualResetEventSlim(false);
                waits[i] = events[i].WaitHandle;
            }
            var producer = new Thread(obj =>
            {
                var state = (Tuple<BlockingCollection<int>, ManualResetEventSlim>)obj;
                var coll = state.Item1;
                var ev = state.Item2;
                var r = new Random();

                for (int i = 0; i < 30; i++)
                {
                    int value = r.Next(3000);
                    coll.Add(value);
                    Console.WriteLine("Add  {0}", value);
                    Thread.Sleep(50);
                }
                ev.Set();
            });

            producer.Start(Tuple.Create<BlockingCollection<int>, ManualResetEventSlim>(sharedCollection, events[0]));
            var consumer = new Thread(obj =>
            {
                var state = (Tuple<BlockingCollection<int>, ManualResetEventSlim>)obj;
                var coll = state.Item1;
                var ev = state.Item2;
                for (int i = 0; i < 30; i++)
                {
                    int result = coll.Take();
                    Console.WriteLine("Take {0}", result);
                    Thread.Sleep(500);
                }
                ev.Set();
            });
            consumer.Start(Tuple.Create<BlockingCollection<int>, ManualResetEventSlim>(sharedCollection, events[1]));
            if (!WaitHandle.WaitAll(waits))
                Console.WriteLine("waite failed");
            else
                Console.WriteLine("reading/writing finished");
            #endregion
        }
    }
}
