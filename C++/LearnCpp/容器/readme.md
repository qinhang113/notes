# 容器

## 顺序容器

### vector
* 特征:
    1. 动态数组，长度可变
    2. 内存连续
    3. 对任意元素快速访问，在序列末尾相对快速的添加/删除元素 
    4. 在尾部之外的位置添加/删除元素将会非常耗时。在一次插入或删除元素后，需要移动插入/删除之后的所有元素来保持连续存储。添加元素还可能分配额外的空间，此时没个元素都要移动到新的内存空间中
* 内存分配
    1. size是指容器已保存的元素数量，capacity是在不分配新的内存空间前提下容器最多保存多少元素
    2. vector&lt;T&gt;对象可在构造函数中定义初始容量，并填充默认值。此时capacity==size。
    ```C++
    vector<int> v(10);
    int size = v.size();//size=10
    int capacity = v.capacity();//capacity=10
    ```
    3. reserve()改变容量，如果它比当前使用的大则重新分配空间（`capacity = newsize > _Oldcapacity + _Oldcapacity / 2 ? newsize : _Oldcapacity + _Oldcapacity / 2`来自msvc STL）并填充默认值。若小于当前容量什么也不做。类似的resize只能改变容器的元素数目，同样不能减少容器的空间
    ```C++
    vector<int> v(10);
    v.resize(11);
    int capacity = v.capacity();//capacity=15
    v.resize(10);
    capacity = v.capacity();//capacity=15
    //v[12] = 1;//error不能通过下标访问
    ```
    4. push_back()元素数量超过capacity，将重新分配空间（参考上条）
* 操作
    1. `void assign(_CRT_GUARDOVERFLOW size_type _Count, const bool& _Val)` 参数1:个数（n）,参数2:值。vector设置_Count个元素为_Val,此操作将改变容器的size
    2. `void assign(_Iter _First, _Iter _Last)` 参数1:迭代器起始，参数2:迭代器终止。拷贝容器
    3. `at(const size_type _Pos)` 参数:索引 若_Pos>=size则抛出异常
    4. `operator[const size_type _Pos]` 类似at()，但_Pos>=size会触发断言
    4. `begin()` 返回迭代器指向容器头（该地址有元素存储）
    5. `end()`  返回迭代器指向容器尾+1（是一个不存在元素的位置）  
    7. `back()` 得到容器的最后一个元素的引用
    6. `clear()` 清空
    7. `iterator erase(const_iterator _Where)` 删除迭代器位置元素，指向删除元素(或范围)的下一个元素。注意迭代器失效的问题
    8. `iterator erase(const_iterator _First, const_iterator _Last)` 删除指定范围内的元素
    9. `push_back()` 容器尾添加数据
    10. `pop_back()` 容器尾删除数据
    11. `swap()` 与另一vector交换数据
* 总结
    1. 成（随机访问、尾部添加删除元素）也内存连续败（中间位置添加/删除元素）也内存连续
### array
* 特征:
    1. 固定大小数组
    2. 不支持添加删除元素
    3. 对比内置数组更安全
* 内存分配
    1. 


## 关联容器