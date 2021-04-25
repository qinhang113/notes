# 泛型

* 类似C++模板（Tempalte），但C#中泛型可以做约束

## 约束

1. 值类型约束 where T:struct 类型参数必须是值类型。可以指定除 Nullable 以外的任何值类型
2. 引用类型约束 where T:class 类型参数必须是引用类型
3. 无参构造参数约束 where T:new() 类型参数必须具有无参数的公共构造函数。当与其他约束一起使用时，new() 约束必须最后指定。
4. 基类约束 where T:classname 类型参数必须是指定的基类或派生自指定的基类(若为接口则可以多个接口同时约束)

## 泛型集合
* 泛型集合类型安全避免了装/拆箱操作，更为高效
### List
1. ArrayList的泛型等效类
### Dictionary
1. Hashtable的泛型等效类，但Hashtable自动通过hash值排序，Hashtable线程安全
2. Remove某元素后，后续添加的元素会填补这个被删除元素的位置。通过顺序遍历Dictionary（ElementAt）通常不是可靠的做法（与C++关联容器map类似）
### HashSet（哈希集）
1. 一组不包含重复元素的集合，并且其中存储的元素没有特定的顺序
### SortedSet（排序集）
1. 一组不包含重复元素的集合，并且其中存储的元素已做排序
### Dictionary
1. 字典也称映照和散列表
2. 能根据键快速查找值，也可以自由添加和删除元素。没有在内存中移动后续元素的性能开销
3. 用作字典键类型需要重写Object类的GetHashCode和实现IEquatable接口。对于引用类型，默认是比较这两个对象是否存储在同一个内存位置来判别它们是否相等的（若内存中地址不同默认GetHashCode方法返回值也可能不一样）。对于值类型（如struct）则比较彼此内存中存放的数据是否相等来判别两个对象是否相等。
    * HashCode值一致不意味着Object.Equals比较是相等的
    * Object.Equals比较相等则HashCode一致
    * 字典的性能取决于GetHashCode方法的实现
