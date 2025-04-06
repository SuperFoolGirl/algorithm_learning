// 本题有双指针解法

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int find_min(vector<long long> &arr, long long x, int n)
{
    int l = -1, r = n;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (arr[mid] < x)
            l = mid;
        else
            r = mid;
    }
    if (arr[r] == x)
        return r;
    return -1;
}

int find_max(vector<long long> &arr, long long x, int n)
{
    int l = -1, r = n;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (arr[mid] <= x)
            l = mid;
        else
            r = mid;
    }
    if (arr[l] == x)
        return l;
    return -1;
}

int main()
{
    long long c;
    int n;
    long long ans = 0;
    scanf("%d %lld", &n, &c);
    vector<long long> arr(n);

    for (int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);
    sort(arr.begin(), arr.end());

    long long cnt = 0;
    for (int i = 0; i < n; i++)
    {
        // 我一开始的想法是遍历二维for循环，这也太蠢了
        // 完全可以优化成一重for循环
        long long x = arr[i] + c;
        long long ret1 = find_min(arr, x, n);
        long long ret2 = find_max(arr, x, n);
        if (ret1 != -1 && ret2 != -1)
            ans += ret2 - ret1 + 1;
    }
    printf("%lld", ans);
    return 0;
}