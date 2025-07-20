// 有双指针解法

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100010;

int n;
int A[N], B[N], C[N];

// 左边是蓝色
int searchA(int x)
{
    int l = 0, r = n + 1;
    while (l + 1 < r)
    {
        int mid = (l + r) >> 1;
        if (A[mid] < x)
            l = mid;
        else
            r = mid;
    }
    if (A[l] < x)
        return l;
    return -1;
}

// 右边是蓝色
int searchC(int x)
{
    int l = 0, r = n + 1; // 回顾左右边界的写法
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (C[mid] > x)
            r = mid;
        else
            l = mid;
    }
    // 此时r是满足蓝色的边缘条件：左边是蓝色，那l是蓝色边缘条件；右边是蓝色，那r是蓝色边缘条件
    if (C[r] > x)
        return r;
    return -1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &B[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &C[i]);

    // 二分查找必须排序
    sort(A + 1, A + n + 1);
    sort(C + 1, C + n + 1);

    // 遍历数组B，在A中找小于B中元素的最大序号，在C中找大于B中元素的最小序号
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int a = searchA(B[i]);
        int c = searchC(B[i]);
        if (a == -1 || c == -1)
            continue;
        ans += ll(a) * (n - c + 1);
    }
    printf("%lld\n", ans);
    return 0;
}