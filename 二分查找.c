// 可以找四个位置
// 给定一个数
// 1 它自己的最小编号
// 2 它自己的最大编号
// 3 小于它的最大数(基于1)
// 4 大于它的最小数(基于2)

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// 最小编号
int min_find(int x, int *arr)
{
    int l = 0, r = 11; // 右下标指向最后一个下标的下一个
    while (l < r)
    {
        int mid = l + r >> 1;
        if (arr[mid] >= x)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    if (arr[l] == x)
    {
        return l;
    }
    // 注意 如果没找到的话
    // 1 如果x没有超过数组最大元素(包括x小于数组最小元素的情况)
    // 此时l是 下标最小的 比x大的数
    // 那么l-1如果没越界的话，就是下标最大的 比x小的数

    // x小于数组最小元素的情况下
    // l的值是0

    // 2 如果x超过数组最大元素
    // 此时l是 数组最大元素的下一位(越界了)
    // 那么l-1恰好是数组最大元素的下标，即n-1
    else
    {
        return -1;
    }
}

// 最大编号
int max_find(int x, int *arr)
{
    int l = 0, r = 11; // 右下标指向最后一个下标的下一个
    while (l < r)
    {
        int mid = l + r >> 1;
        if (arr[mid] <= x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    if (arr[l - 1] == x)
    {
        return l - 1;
    }
    // 注意 如果没找到的话
    // 1 如果x没有小于数组最小元素(包括大于最大元素的情况)
    // 此时l-1是 下标最大的 比x小的数
    // 那么l如果没越界的话，就是下标最小的 比x大的数

    // 如果x大于最大元素
    // l-1的结果为最大元素的下标，即n-1

    // 2 如果x小于数组最小元素
    // l-1的值为-1，越界了
    // 那么l恰好为0，即数组第一项的下标
    else
    {
        return -1;
    }
}

int main()
{
    int arr[11] = {15, 15, 13, 11, 9, 7, 5, 3, 3, 3, 1};
    qsort(arr, 11, sizeof(int), cmp);
    printf("%d %d",min_find(15, arr), max_find(15, arr));
    return 0;
}



// 普通版
// int find(int x)
// {
//     int l = 0, r = n - 1; // 注意右下标
//     while (l <= r)
//     {
//         int mid = l + r >> 1;
//         if (arr[mid] == x)
//         {
//             return mid;
//         }
//         else if (arr[mid] > x)
//         {
//             r = mid - 1;
//         }
//         else
//         {
//             l = mid + 1;
//         }
//     }
// }



// 最小编号
// int find(int x)
// {
//     int l = 0, r = n;
//     while (l < r)
//     {
//         int mid = l + r >> 1;
//         if (arr[mid] >= x)
//         {
//             r = mid;
//         }
//         else
//         {
//             l = mid + 1;
//         }
//     }
//     if (arr[l] == x)
//     {
//         return l;
//     }
//     else
//     {
//         return -1;
//     }
// }



// 最大编号
// int find(int x)
// {
//     int l = 0, r = n;
//     while (l < r)
//     {
//         int mid = l + r >> 1;
//         if (arr[mid] <= x)
//         {
//             l = mid + 1;
//         }
//         else
//         {
//             r = mid;
//         }
//         if (arr[l - 1] == x)
//         {
//             return l - 1;
//         }
//         else
//         {
//             return -1;
//         }
//     }
// }