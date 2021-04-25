# 泛型

* 类似C++模板（Tempalte），但C#中泛型可以做约束

## 约束

1. 值类型约束 where T:struct 类型参数必须是值类型。可以指定除 Nullable 以外的任何值类型
2. 引用类型约束 where T:class 类型参数必须是引用类型
3. 无参构造参数约束 where T:new() 类型参数必须具有无参数的公共构造函数。当与其他约束一起使用时，new() 约束必须最后指定。
4. 基类约束 where T:classname 类型参数必须是指定的基类或派生自指定的基类(若为接口则可以多个接口同时约束)

## 泛型集合
* 泛型集合类型安全避免了装/拆箱操作，更为高效
### List&lt;T&gt;
1. ArrayList的泛型等效类
### Dictionary&lt;T&gt;
1. Hashtable的泛型等效类，但Hashtable自动通过hash值排序，Hashtable线程安全
2. Remove某元素后，后续添加的元素会填补这个被删除元素的位置。通过顺序遍历Dictionary（ElementAt）通常不是可靠的做法（与C++关联容器map类似）
### HashSet&lt;T&gt;（哈希集）
1. 一组不包含重复元素的集合，并且其中存储的元素没有特定的顺序
### SortedSet&lt;T&gt;（排序集）
1. 一组不包含重复元素的集合，并且其中存储的元素已做排序
### Dictionary<TKey, TValue>
1. 字典也称映照和散列表
2. 能根据键快速查找值，也可以自由添加和删除元素。没有在内存中移动后续元素的性能开销
3. 用作字典键类型需要重写Object类的GetHashCode和实现IEquatable接口。对于引用类型，默认是比较这两个对象是否存储在同一个内存位置来判别它们是否相等的（若内存中地址不同默认GetHashCode方法返回值也可能不一样）。对于值类型（如struct）则比较彼此内存中存放的数据是否相等来判别两个对象是否相等。
    * HashCode值一致不意味着Object.Equals比较是相等的
    * Object.Equals比较相等则HashCode一致
    * 字典的性能取决于GetHashCode方法的实现

## 并发集合
* 命名空间System.Collections.Concurrent中提供线程安全集合类
* 定义了IProducerConsumerCollection<T>接口实现集合跨线程得安全访问
* 添加或提取某个元素，总要判断此动作是否执行成功

### ConcurrentQueue&lt;T&gt; 
1. 类似Queue&lt;T&gt;访问元素方法有TryEnqueue()、TryDequeue()、TryPeek()。
### ConcurrentStack&lt;T&gt;
1. 类似Stack&lt;T&gt;定义了Push()、PushRange()、TryPeek()、TryPop()、TryPopRange()方法。
### ConcurrentBag&lt;T&gt;
1. 类似List&lt;T&gt;定义了Add()、TryPeek()、TryTake()方法。
### ConcurrentDictionary<TKey, TValue>
1. 类似Dictionary<TKey, TValue>定义了TryAdd()、TryGetValue()、TryRemove()、TryUpdate()方法。ConcurrentDictionary<TKey, TValue>没有实现IProducerConsumerCollection&lt;T&gt;接口
### BlockingCollection&lt;T&gt; 
1. 这个集合在可以添加或提取元素之前，会阻塞线程并一直等待（使用Add()/Take()）。
2. 使用TryAdd(T item, TimeSpan timeout)、TryTake(out T item, TimeSpan timeout)可以设定超时时间。
3. Add(T item, CancellationToken cancellationToken)此方法可以传递一个cancellationToken令牌，该令牌允许取消被阻塞得调用。
4. BlockingCollection&lt;T&gt;这是对实现了IProducerConsumerCollection&lt;T&gt;接口的任意类的修饰器，它默认使用ConcurrentQueue&lt;T&gt;。还可以给构造函数传递任意实现了IProducerConsumerCollection&lt;T&gt;接口的类

| 接口 | 说明 |
| :---- | :---- |
| IEnumerable&lt;T&gt; | 如果将foreach语句用于集合，就需要IEnumerable接口。这个接口定义了方法Getenumerator(), 它返回一个实现了IEnummtor接口的枚举 |
| ICollection&lt;T&gt; | ICollection&lt;T&gt;接口由泛型集合类实现。使用这个接口可以获得集合中的元素个数，把集合复制到数组中，还可以从集合中添加和删除元素 |
| IList&lt;T&gt; | IList<T>接口用于可通过位置访问其中的元素列表，这个接口定义了一个索引器，可以在集合的指定位置插入或删除某些项。IList&lt;T&gt;接口派生自ICollection&lt;T&gt; |
| ISet&lt;T&gt; | 这个接口的集允许合并不同的集,获得两个集的交集, 检查两个集是否重叠。ISet&lt;T&gt;派生自ICollection&lt;T&gt; |
| IDictionary<TKey, TValue> | 由包含键和值的泛型集合类实现。使用这个接口可以访问所有的键和值，使用键类型的索引器可以访问某些项，还可以添加或删除某些项 |
| ILookup<TKey, TValue> | 和IDictionary<TKey, TValue>类似，可以通过一个键包含多个值 |
| IComparer&lt;T&gt; | 由比较器实现，通过Compare()方法给集合中的元素排序 |
| IEqualityComparer&lt;T&gt; | 由比较器实现，该比较器可用于字典中的键。使用这个接口可以对对象进行相等性比较。|
| IProducerConsumerCollection&lt;T&gt; | 支持新的线程安全的集合类 |
