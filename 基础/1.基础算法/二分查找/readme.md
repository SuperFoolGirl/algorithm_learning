### 讲一个更容易理解的方法--找分界线
#### 之前的不同写法太恶心了，不具有普遍性，记忆负担太重了。新版只需要理解性记忆
1. l的值为**最小下标-1**，r的值为**最大下标+1**
2. 根据题目条件，确定好蓝红区域，以及分界线的位置。最大值最小问题，右边为蓝；最小值最大问题，左边为蓝。**左边是蓝色，那l是蓝色边缘条件；右边是蓝色，那r是蓝色边缘条件**
3. **while (l + 1 < r)** 注意这里写法和之前不一样
4. int mid = l + r >> 1
5. if (满足蓝色) 修改为蓝色边界为mid(蓝色可能在左，也可能在右)
6. else 修改红色边界为mid
7. 最后返回值，l是分界线左边，r是分界线右边



下面给一个例子，讲一下如何确定分界线

1. 找到**第一个大于5**的元素下标

   `3 4 4 5 5 5|6 7`
   分界线如图所示

   蓝色区域取小于等于5，最后return r

2. 找到**最后一个小于等于5**的元素

   分界线相同，最后return l

3. 找到**第一个小于等于5**的元素

   `3 4 4|5 5 5 6 7`

   左边为红色，右边为蓝色

   if (arr[mid] >= 5) r = mid

   else l = mid

   最后 if (arr[r] == 5) return r



#### 代码模板

两个版本，分别对应左边为蓝色、右边是蓝色

分界线处自行判断，因此共四个版本

对于一道题目，如果要写多个二分查找函数的话，红蓝分界的划法一般是唯一的，需要改动的一般只是isBlue函数和return的边界

举个例子，如果查找某元素的最小和最大下标，都可以选择左边是蓝色的函数

最小下标的isBlue：if (num < x) return true; 最后return r （注意在这个思想下，我们的目标其实在红色区域，分界线的右边——l恰好是满足蓝色的边界。好好体会这个分界线的找法）

最大下标的isBlue：if (num <= x) return true; 最后return l （l是满足蓝色的边界）

唯一区别就是判断蓝色时，l和r的顺序

isBlue函数写法很灵活，是根据自己划红蓝分界线的条件来写的，没有固定模板

```c++
int binary_search_for_left_is_blue(int *arr, int len, int x) {
    int l = -1, r = len;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (isBlue(arr[mid], x))
            l = mid; // 左边是蓝，所以isBlue为真，l变化
        else
            r = mid;
    }
    // 这里分界线自己判断，本模板默认取l
    // 注意 还需要判断索引是否越界
    if (l >= 0 && l < len && arr[l] == x)
        return l;
    return -1;
}

int binary_search_for_right_is_blue(int *arr, int len, int x) {
    int l = -1, r = len;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (isBlue(arr[mid], x))
            r = mid; // 右边是蓝，所以isBlue为真，r变化
        else
            l = mid;
	}
    if (l >= 0 && l < len && arr[l] == x)
        return l;
    return -1;
}
```

