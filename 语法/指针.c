// 行指针针对二维数组以上 一维数组只有列指针
// 列指针三种：a[i] *(p+i) &a[i][0]
// 行指针两种：&a[i] p+i
// 可以看到前两种上下是一一对应的
// 数组指针用来作形参比较多 实参的话得自己写一个 但作形参需要写行元素个数 意义不大，还是传列指针好用

// 一维指针：一维数组名、一级指针
// 二维指针：二维数组名、指针数组、数组指针、二级指针（使用有限制 详见再论指针）



// 列指针传参(以三维矩阵为例)
#include <stdio.h>

void print1(int *p, int row, int col, int high)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int k = 0; k < high; k++)
            {
                printf("%d ", *(p + i * col * high + j * high + k));
            }
        }
    }
}

int main()
{
    int arr[3][3][2] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    print1(&arr[0][0][0], 3, 3, 2); // 三维数组其他列指针的形式不会写 但这个是铁定对的
    return 0;
}

// 行指针传参(数组指针)
#include <stdio.h>

void print2(int (*p)[5], int size) // 数组指针作形参，需要传行元素个数
{
    for (int i = 0; i < 5; i++)
    {
        // printf("%d ", p[0][i]);
        printf("%d ", *(*p + i)); // 一维数组用数组指针的脑残用法
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    print2(&arr, 5);
    return 0;
}

// 再来一个行指针
#include <stdio.h>

void print3(int (*p)[3], int row) // 数组指针作二维数组形参
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", (*(p + i))[j]); // 注意这里的写法
        }
    }
}
int main()
{
    int arr[3][3] = {1, 4, 6, 3, 5, 9, 3, 5, 1};
    print3(arr, 3);
    return 0;
}
