// 本题有二分解法

// 这道题不是双指针了，而是快慢三指针
// 一个快指针，两个慢指针，快指针遍历数组，两个慢指针锁定范围

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;

typedef long long ll;

int n, c;
ll arr[N];

int main()
{
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);

    sort(arr, arr + n);
    // a为快指针，注意快慢指针锁范围时，控制快指针的范围即可
    // b1,b2为慢指针，锁定范围
    ll res = 0;
    for (int a = 0, b1 = 0, b2 = 0; a < n; a++)
    {
        // 卡>和>=的区别在二分查找时见过
        // >=会使b1落在目标的右边，即大于x的第一个数
        // >会使b2落在第一个x上
        // 二者作差，就是x的个数
        while (b1 <= a && arr[a] - arr[b1] >= c) // >=
            b1++;
        while (b2 <= a && arr[a] - arr[b2] > c) // >
            b2++;
        res += b1 - b2;
    }
    printf("%lld", res);
    return 0;
}