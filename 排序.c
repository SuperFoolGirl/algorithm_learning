#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n = 10;
    int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    // 选择（主元）
    // 未优化
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    // 优化
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[k] > arr[j])
                k = j;
        }
        int tmp = arr[i];
        arr[i] = arr[k];
        arr[k] = tmp;
    }



    // 冒泡排序
    // 未优化
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    // 优化
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                flag = true;
            }
        }
    }



    // 插入排序
    // 推荐写法
    for (int i = 1; i < n; i++)
    {
        int now = arr[i], j;
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] > now)
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = now;
    }

    // 课本写法
    for (int i = 1; i < n; i++)
    {
        int j = i - 1;
        while (j >= 0 && arr[j] > arr[i])
            j--;
        int tmp = arr[i];
        for (int k = i - 1; k > j; k--)
            arr[k + 1] = arr[k];
        arr[j + 1] = tmp;
    }



    // 计数排序
    int vis[10000] = {0};
    for (int i = 0; i < n; i++)
        vis[arr[i]]++;
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < vis[i]; j++)
            printf("%d ", i);
    }

    return 0;
}


// 冒泡排序递归实现
#include <stdio.h>

void bubbleSort(int *arr, int len)
{
    if (len == 0)
        return;
    int flag = 0;
    for (int i = 0; i < len - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            flag = 1;
            int tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
        }
    }
    if (!flag)
        return;
    bubbleSort(arr, len - 1);
}

int main()
{
    int arr[10] = {5, 6, 3, 4, 2, 1, 8, 7, 10, 9};
    bubbleSort(arr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    return 0;
}



// 选择排序递归实现
#include <stdio.h>

void selectSort(int *arr, int n)
{
    if (n < 2)
        return;
    int first = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[first])
            first = i;
    }
    if (first != 0)
    {
        int tmp = arr[0];
        arr[0] = arr[first];
        arr[first] = tmp;
    }
    selectSort(arr + 1, n - 1); // 已经排好的舍弃掉 从左边逼近右边
}

int main()
{
    int arr[6] = {2, 5, 7, 3, 1, 4};
    selectSort(arr, 6);
    for (int i = 0; i < 6; i++)
        printf("%d ", arr[i]);
    return 0;
}


// 插入排序递归实现
#include <stdio.h>

void insertSort(int *arr, int n)
{
    // 注意这个递归实现 完全后序
    if (n < 2)
        return;

    insertSort(arr, n - 1);

    // 倒过来其实完全就是内层循环 递归充当了外层循环
    // tmp相当于now,i相当于j
    int tmp = arr[n - 1], i;
    for (i = n - 2; i >= 0; i--)
    {
        if (arr[i] > tmp)
            arr[i + 1] = arr[i];
        else
            break;
    }
    arr[i + 1] = tmp;
}

int main()
{
    int arr[6] = {2, 5, 7, 3, 1, 4};
    insertSort(arr, 6);
    for (int i = 0; i < 6; i++)
        printf("%d ", arr[i]);
    return 0;
}