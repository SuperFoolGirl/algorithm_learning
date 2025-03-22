#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int x, vector<int> &trees, int n, int k)
{
    int sum = 0;
    for (auto i : trees)
    {
        sum += i / x;
        if (sum >= k)
            return true;
    }
    return sum >= k;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> trees(n);
    int max_tree = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &trees[i]);
        max_tree = max(max_tree, trees[i]);
    }

    // 二分查找对象：分割后每段木头的长度
    // 长度越短，分割的的段数越多
    // 因此蓝色区域在左边
    int l = 0, r = max_tree + 1;
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if (check(mid, trees, n, k))
            l = mid;
        else
            r = mid;
    }

    if (check(r, trees, n, k))
        printf("%d\n", r);
    else
        printf("%d\n", l);
    return 0;
}