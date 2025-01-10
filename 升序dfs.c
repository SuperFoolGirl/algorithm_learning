// 洛谷p1157
// 保证输出单一 实现了去重
// 答案自动形成升序字典序 无需qsort排
// 另外 对于有些for循环dfs的题目 无需去重 形成的答案也是自动字典序升序的 如洛谷p2089

#include <stdio.h>

void dfs(int x, int n, int *tmp, int r, int *first, int begin)
{
    if (x > r)
    {
        if (*first) // 指针指向的值不会因调用堆栈的变化产生变化 永久性改变
            puts("");
        (*first)++;
        for (int i = 1; i <= r; i++)
            printf("%3d", tmp[i]);
        return;
    }
    for (int i = begin; i <= n; i++) // 就是这个begin
    {
        tmp[x] = i;
        dfs(x + 1, n, tmp, r, first, i + 1);
        tmp[x] = 0;
    }
}

int main()
{
    int n, r;
    scanf("%d %d", &n, &r);
    int tmp[22] = {0};
    int first = 0;
    int *p = &first;
    dfs(1, n, tmp, r, p, 1);
    return 0;
}