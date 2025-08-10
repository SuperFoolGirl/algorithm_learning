## set, map, multiset, multimap
> 都是基于平衡二叉树实现(红黑树)
> 本质是动态维护有序数据
> 各方法时间复杂度普遍为$O(log n)$
- `size()`与`empty()`是所有容器公有的方法
- `clear()`
- `begin()`/`end()`，支持`++`/`--`来访问前驱/后继操作



### set/multiset
> set头文件包含了set和multiset，map同理
> set不允许有重复操作，所以自身天然可以去重
- `insert()`
- `find()`，返回迭代器。若不存在，返回end()对应的迭代器
- `count()`，返回元素个数。对于去重的set而言，作用相当于`find()`，但更高效
- `erase()`
  - 按值删除：`s.erase(x)`，输入值x，删除所有值为x的元素
  - 按迭代器删除：`s.erase(it)`，输入迭代器it，删除it指向的元素
- **`lower_bound()`，返回第一个==大于等于==x的元素的迭代器，参考二分查找**
- **`upper_bound()`，返回第一个==大于==x的元素的迭代器**



### map/multimap
> 存储映射关系的数据结构
- `insert()`，插入键值对，即一个pair类型的数据
- `operator[]`，在使用便利方面来说，取代了`find()`
- `erase()`
  - 按键删除：`m.erase(key)`，输入键key，删除所有键为key的元素
  - 按迭代器删除：`m.erase(it)`，输入迭代器it，删除it指向的元素
- **`lower_bound()`，返回第一个==大于等于==key的元素的迭代器，参考二分查找**
- **`upper_bound()`，返回第一个==大于==key的元素的迭代器**

	
---



## unordered_set, unordered_map, unordered_multiset, unordered_multimap
> 基于哈希表实现
> 本质是动态维护无序数据
> 各方法时间复杂度普遍为$O(1)$，高于上述四个数据结构
> 由于内部是无序的，不支持`lower_bound()`和`upper_bound()`以及`++`/`--`等**基于排序**的查询前驱/后继的操作。
> 其他操作与`set`和`map`系列类似
> 也就是牺牲了排序相关功能，但换来了更快的查找速度