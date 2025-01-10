// 总结一下 qsort参数3以及对应的cmp写法大概有三种
// 1 对一维数组元素进行排序 参数3为sizeof(type)，cmp为 *(type*)a，结构体为(*(struct type*)a).val
// 2 对二维数组进行字典序排序 参数3为sizeof(arr[0])，cmp为 (type*)a，唯一直接写的一个，因为本身就是列指针
// 3 对指针数组进行字典序排序 参数3为sizeof(type*)，cmp为 *(type**)a
// 参数3可以无脑写sizeof(arr[0])的 参数2如果数组不是开了很大的话 可以无脑写sizeof(arr)/sizeof(arr[0])


// 指针数组
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b); // 参数是列指针
}

int main()
{
    char arr[5][5] = {"ddd", "aaa", "eee", "bb", "c"};
    char *p[5] = {NULL};
    for (int i = 0; i < 5; i++)
    {
        p[i] = arr[i];
    }
    qsort(p, 5, sizeof(char *), cmp);
    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%s\n", p[i]); // 这里要是用p+i的话会多打印一些乱码
    //     // p[i]是每一行首元素地址 p+i是每一行的地址
    //     // 但其实应该用首元素地址的 还是参考arr
    // }
    printf("%c", *(p[1] + 1)); // p是二维指针
    return 0;
}



// 二维数组
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b); // strcmp的参数是列指针 所以强转一下即可
}

int cmp1(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    char *arr[15] = {NULL};
    char p[15][60] = {0};
    int arrIdx = 0;
    for (int i = 0; i < n; i++)
    {
        int idx = 0;
        char ch = getchar();
        while (ch != EOF && ch != '\n') // 注意是&& 不如直接gets，直接把EOF和换行转换为\0
        {
            p[i][idx++] = ch;
            ch = getchar();
        }
        arr[arrIdx++] = p[i];
    }
    qsort(p, n, sizeof(p[0]), cmp); // 参数3传的是列指针（字典序要传列指针，如果要排每一行的话，用for循环 不过3位置就不是指针了）
    qsort(arr, n, sizeof(char *), cmp1); // 指针数组版
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", p[i]);   // 二维指针-列指针
        printf("%s\n", arr[i]); // 二维指针-列指针
    }
    return 0;
}



// 结构体
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct A
{
    char s[100];
    int space;
};

int cmp(const void *a, const void *b)
{
    return strcmp((*(struct A *)a).s, (*(struct A *)b).s); // s是列指针
}

int main()
{
    struct A a[5] = {0}; // C语言的数组都要初始化的
    for (int i = 0; i < 5; i++)
    {
        int idx = 0;
        char ch = getchar();
        while (ch != EOF && ch != '\n')
        {
            a[i].s[idx++] = ch;
            ch = getchar();
        }
    }
    qsort(a, 5, sizeof(struct A), cmp);
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", a[i].s);
    }
    return 0;
}