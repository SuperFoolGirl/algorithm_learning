#include <stdio.h>
#include <stdlib.h>
#define maxn 100010

int find_min(int *A, int b, int n)
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (A[mid] >= b)
            r = mid;
        else
            l = mid + 1;
    }
    return l - 1; // 如果A[mid]==b,下标为l,要找前一个;如果没有相等,l最后指向比b大的第一个数,减1得到比b小的最后一个数
}

int find_max(int *C, int b, int n)
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (C[mid] <= b)
            l = mid + 1;
        else
            r = mid;
    }
    return l; // 同理
}

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    int n;
    long long ans = 0;
    int A[maxn] = {0}, B[maxn] = {0}, C[maxn] = {0};
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &C[i]);
    qsort(A, n, sizeof(int), cmp);
    qsort(B, n, sizeof(int), cmp);
    qsort(C, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++)
    {
        int a = find_min(A, B[i], n);
        int c = find_max(C, B[i], n);
        if (a < 0 || a > n - 1 || c < 0 || c > n - 1)
            continue;
        ans += (long long)(a + 1) * (n - c);
    }
    printf("%lld", ans);
    return 0;
}