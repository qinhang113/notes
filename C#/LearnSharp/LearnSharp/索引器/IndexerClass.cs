using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LearnSharp
{    
    class IndexerClass : BaseClass
    {
        string _name = "IndexerClass";
        int _id = 1;
        public string this[int index]
        {
            get
            {
                if (index == 0)
                    return _name;
                else
                    return _id.ToString();
            }
            set
            {
                if (index == 0)
                    _name = value;
                else
                    _id = Convert.ToInt32(value);
            }
        }
        public override void TestFun()
        {
            this[0] = "Name Changed";
            this[1] = "2";

            Console.WriteLine("索引器_name:{0},_id:{1}", _name, _id);
        }
    }
}
