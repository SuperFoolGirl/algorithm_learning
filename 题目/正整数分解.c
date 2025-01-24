// 这是第一个版本 但很狼狈 用到了很多memcpy和qsort
// 通过leetcode的三数之和题目 应该能意识到，排序对题目产生的影响
// 以及洛谷p1036，通过升序枚举来保证不重复
// 本题也应该能通过改变dfs里的枚举顺序来避免多余的操作，而不是无脑for循环
// 对于这种限定条件的 其实不能无脑搜索，否则自己得为无脑买单

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, ans[200][20] = {0}, idxAns = 0, tmp[20] = {0}, idxTmp = 0, help[20] = {0};

int cmp2(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

void dfs(int x)
{
    if (x == n)
    {
        memcpy(help, tmp, sizeof(tmp));             // 把tmp拷贝一份，因为要排序，排序会打乱dfs
        qsort(help + 1, idxTmp, sizeof(int), cmp2); // 倒序排序
        for (int i = 1; i <= idxAns; i++)
        {
            if (memcmp(ans[i], help, sizeof(tmp)) == 0) // 注意memcmp有参数3 且在cmp函数外都要写==0来判断数组相等 这里目的是去重
                return;
        }
        memcpy(ans[++idxAns], help, sizeof(tmp)); // string.h头文件下的函数 void*参数基本都是用列指针
        return;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        if (x + i <= n)
        {
            tmp[++idxTmp] = i;
            dfs(x + i);
            tmp[idxTmp--] = 0; // 后置--很巧妙
        }
    }
}

int cmp(const void *a, const void *b)
{
    return memcmp((int *)b, (int *)a, sizeof(int) * 16);
}

int main()
{
    scanf("%d", &n);
    dfs(0);
    qsort(ans + 1, idxAns, sizeof(ans[1]), cmp); // 排字典序 注意参数3是列指针
    for (int i = 1; i <= idxAns; i++)
    {
        printf("%d=", n);
        int cnt = 0;
        for (int j = 1; ans[i][j] != 0; j++)
        {
            if (cnt)
            {
                printf("+");
            }
            cnt++;
            printf("%d", ans[i][j]);
        }
        puts("");
    }
    return 0;
}

// 改进版 剪枝枚举 升序去重
// 洛谷p2404
// 凡是碰到dfs 都考虑下能否这样简单剪枝
// 注意 可升序去重后 答案自动形成升序字典序

#include <stdio.h>
#include <string.h>

int n, ansArr[200][10] = {0}, ans1[10] = {0}, idx1 = 0, idx2 = 0;

void dfs1(int x, int start)
{
    if (x == n)
        memcpy(ansArr[++idx2], ans1, sizeof(ans1)); // 杜绝了重复的情况 直接加入答案 而且答案自动形成升序字典序
    for (int i = start; i < n; i++) // 每次枚举的元素都大于等于start，形成升序
    {
        if (x + i <= n)
        {
            ans1[++idx1] = i;
            dfs1(x + i, i); // 根据题目需要 start有时传i（大于等于）  有时传i+1（大于）
            ans1[idx1--] = 0;
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs1(0, 1);
    for (int i = 1; i <= idx2; i++)
    {
        int cnt = 0;
        for (int j = 1; ansArr[i][j] != 0; j++)
        {
            if (cnt)
                printf("+");
            cnt++;
            printf("%d", ansArr[i][j]);
        }
        puts("");
    }
    return 0;
}