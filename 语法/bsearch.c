#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int main()
{
    int arr[10] = {4, 6, 0, 3, 1, 2, 9, 5, 7, 8};
    // 必须自己排序
    qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), cmp);
    // 函数返回类型为void* 要强转
    // 虽然已经排序了 但还是要穿比较函数
    // 参数1是要找的元素地址 其他与qsort相同
    int *ret = (int *)bsearch(arr + 6, arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), cmp);
    printf("%d", *ret);
    puts("");
    // ans记录ret下标偏移量 即最后找到ret的下标
    // int ans = 0;
    // while (ret != arr)
    // {
    //     ret--;
    //     ans++;
    // }
    // 关于指针加减法
    // 指针相减的前提是 指针都指向数组的元素 相减直接得到偏移量
    // 也可以加减常数 如上面所示
    printf("%d", ret - arr); // 指针直接相减得到偏移量

    //printf("%d", ans);
    return 0;
}