# 集合

* System.Collections命名空间包含动态数组（ArrayList）、栈（stack）、队列（queue）、点阵列（BitArray）和哈希表（hash table）等数据结构类型

## 动态数组（ArrayList）

1. 大小可按需动态增加的数组
2. 动态数组对象可以指定容量，每当容量占满后会重新开辟当前容量2倍的空间（如：5，10，20）
3. 可以调用TrimToSize()方法使容量设置为实际元素数目
4. 若要ArrayList存储自定义对象，将使用每个元数的 IComparable 实现。例:
```C#
    class DataArrayList : IComparable
    {
        public int number;
        public string name;

        public int CompareTo(object obj)
        {
            return this.number - ((DataArrayList)obj).number;
        }
    }
```

## 栈（stack）

1. 后进先出
2. Peek()返回栈顶元素（不删除此元素）

## 队列（queue）

1. 先进先出

## 点阵列（BitArray）

1. 位值数组（非动态）仅存储bool值
2. 初始化需指定长度，或者从int/byte/bool数组进行初始化
3. 使用CopyTo方法目标数组长度要设置合理（提示：4 * sizeof(byte) == sizeof(int) == 32bit,但如果目标数组为bool型则目标数组大小需要=BitArray大小）

## 哈希表（Hashtable）

1. 哈希表中存储为键值对
2. 键（key）不可重复，使用add方法添加重复键将抛出ArgumentException异常
3. 会根据键（key）的hash值自动排序
4. Hashtable线程安全

| 集合 | 线程安全 | 内存连续 | 动态大小 |
| :---- | :----: | :----: | :----: |
| ArrayList | × | √ | √ |
| Stack | × | × | √ |
| Queue | × | × | √ |
| BitArray | × | √ | × |
| Hashtable | √ | × | √ |