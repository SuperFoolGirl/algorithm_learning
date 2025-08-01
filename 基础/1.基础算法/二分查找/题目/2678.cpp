// 思路非常牛逼。二分上难度，主要在于check函数的实现
// 二分查找对象为最小跳跃距离
// 左边是蓝色区域
// 正常来说，m越大，搬走的石头越多，得到的答案越好
// 但必须保证操作次数不超过m

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

bool check(int x, vector<int> &rocks, int n, int m) {
    int cnt = 0;                             // 操作次数
    int i = 0;                               // 下一个石头的位置
    int now = 0;                             // 当前石头的位置
    while (i < n + 1)                        // 注意这里不能取等，因为里面要i++
    {
        i++;                                 // 相对于now，偏移一个位置
        while (rocks[i] - rocks[now] < x)    // x是二分查找枚举的最短距离，如果小于这个距离，那就要搬掉这个石头
        {
            cnt++;                           // 操作次数+1
            if (i < n + 1) {                 // 如果i不是最后一个石头，那就继续往后找。注意嵌套while循环很容易越界，越界条件要重复写
                i++;
            } else {
                // 这里已经来到了最后一个石头
                if (cnt <= m) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        now = i;        // 更新当前石头的位置
    }
    return cnt <= m;    // 操作次数不超过m
}

int main() {
    int l, n, m;
    scanf("%d %d %d", &l, &n, &m);

    // 注意这里的rocks数组，是n+2大小的，因为要包括起点和终点
    vector<int> rocks(n + 2);
    rocks[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        scanf("%d", &rocks[i]);
    }
    rocks[n + 1] = l;

    int left = 0, right = l + 1;
    while (left + 1 < right) {
        int mid = left + right >> 1;
        if (check(mid, rocks, n, m)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (check(right, rocks, n, m)) {
        printf("%d\n", right);
    } else {
        printf("%d\n", left);
    }
}
