// 还没尝试搭配qsort
#include <stdio.h>

int main()
{
    int arr[3][3] = {4, 5, 8, 3, 6, 1, 2, 9, 7};
    int *p = arr[0];                      // 列指针
    int(*s)[3] = arr;                     // 行指针 取第一行地址
    int *t[3] = {arr[0], arr[1], arr[2]}; // 列指针 取每行首元素地址

    for (int i = 0; i < 9; i++)
    {
        printf("%d ", arr[0][i]); // 这诡异的操作，二维指针当一维指针用
    }
    puts("");

    printf("%p %p", &arr[0][4], &arr[1][1]); // 地址真的相同
    puts("");

    for (int i = 0; i < 9; i++)
    {
        // printf("%d ", p[0][i]); // 报错 因为是列指针
        printf("%d ", *(p + i)); // 成功
        printf("%d ", p[i]);     // 与上一句等价 可以
    }
    puts("");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // printf("%d ", p[i][j]); // 报错 因为是列指针
            // printf("%d ", *(*(p + i) + j)); // 报错 因为是列指针
            printf("%d ", *(p + i * 3 + j)); // 成功
        }
    }
    puts("");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", s[i][j]);         // 成功 因为是行指针
            printf("%d ", *(*(s + i) + j)); // 成功 因为是行指针

            printf("%d ", t[i][j]);         // 成功 因为是行指针
            printf("%d ", *(*(t + i) + j)); // 成功 因为是行指针
        }
    }
    puts("");

    for (int i = 0; i < 9 - 1; i++)
    {
        printf("%d ", s[0][i]); // 也行 二维指针都是相通的
        printf("%d ", t[0][i]); // 也行 二维指针都是相通的
    }
    return 0;
}

// malloc开辟的一维数组 对应的指针名是一维指针
// 下面尝试用malloc开辟二维数组

// 三种方法
// 1 二级指针
// 2 数组指针
// 3 一维数组模拟二维数组
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 1 二级指针 3*2
    // 感觉最好用 两个malloc之后直接当二维指针用
    int **a = (int **)malloc(sizeof(int *) * 3); // malloc前后两个括号，左边是右边的高级指针;左括号与左值类型相同
    for (int i = 0; i < 3; i++)
        a[i] = (int *)malloc(sizeof(int) * 2); // a[i]本身是列指针，指向每行首元素 回忆一下普通开辟一个一维数组，左值也是一个一级p
                                               // int *p = (int)malloc(sizeof(int) * m);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            a[i][j] = 1;
            printf("%d ", a[i][j]);
        }
        puts("");
    }
    return 0;
}

// 2 数组指针
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int(*p)[2] = (int(*)[2])malloc(sizeof(int) * 3 * 2); // 好好观察
    // 左值与malloc左括号都是行指针；malloc右括号是行指针解引用 即一行的元素，然后再乘行数(类比一维数组malloc开辟)
    printf("%p %p\n", p[1] + 1, *(p + 1) + 1/*, p + 1 * 2 + 1*/); // 注意第三种写法 二维指针不能这样写
    printf("%p\n", &p[0][1 * 2 + 1]); // 与上面一样 别忘了这个骚操作
    // 虽然这个看上去与上面第三个等价 但事实就是不同 上面那个就是列指针独有的写法
    int *s = p[0]; // 列指针 第一行首元素地址
    printf("%p", s + 1 * 2 + 1); // 而一维指针就可以这样写(这其实就是第三种办法的模式 一维数组模拟二维数组)
    return 0;
}

// 3 模拟
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = (int *)malloc(sizeof(int) * 3 * 2);                  // 3行2列
    printf("%p %p %p\n", p + 1 * 2 + 1, &p[1 * 2 + 1], p[1] + 1); // 第三种写法不对 这是二维指针的写法
    // int **s = &p;                                                 // 用二维指针接手咯,但这样不行
    // printf("%p %p %p\n", &s[1][1], s[1] + 1, *(s + 1) + 1);       // 地址与上面不同
    return 0;
}
