// 树的直径的应用

// 如果x和y之间可以互相转换，那么就在二者之间加一条无向边(可互相转换)
// 对于x而言，x指出去的边只有这一条(虽然是无向边，入边和出边相同，但为了方便暂时这样说)
// 但x的入边可能有多条：x本身可能作为多个数字的约数之和，被其他数字指向
// 考虑树的结构，父亲只有一个，但儿子可以有多个
// 因此，虽然是x与y的转换是以x为主导的，但结构上应当视y为x的父亲

// 对1~n的数字都施以这样的法则，结果会得多棵树，即森林
// 下面模拟一下，以x-y为x-x约束之和的形式(1-0不存在，因此x从2开始)：
// 2-1, 3-1, 4-3, 5-1, 7-1, 8-7, 9-4, 10-8
// 6-6不存在，因为6不大于6；这种情况下，6就会作为一棵树的根结点

// 我们的任务，就是在这多棵树中，找到一条最长的路径
// 树的要求：不可出现相同的数字，即在同一棵树中，每个结点只能出现一次
// 因此，需要先建树，然后求树的直径
// 本题边权为1，可以用直径模板，无需第一题的down思路；不过这里还是用一下down思路，来练习一下树形DP

// 问题来了，如何快速建树，即求约数之和呢？
// 试除法本题可接受，对于x，枚举1~sqrt(x)的数，时间复杂度为O(n*sqrt(n))
// 提供一个更快的做法：借助筛法的思想
// 不是求每个数的约数，而是求每个数i的倍数，若j是i的倍数，则i是j的约数
// for (int i = 1; i <= n; i++) for (int j = 2; j * i <= n; j++)
// 典型调和级数(内层循环与外层i有关)，时间复杂度为O(nlogn)，更优一些

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010;

int n;
int h[N], e[N], ne[N], idx;
int sum[N];
// 存一下哪些树是树根，便于dfs；毕竟dfs总是从树根出发
// 为了迎合默认初始化为false，取false为树根，true为非树根
bool st[N];
int ans;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dfs(int u) {
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        int d = dfs(j) + 1;
        if (d >= d1) {
            d2 = d1;
            d1 = d;
        } else if (d > d2) {
            d2 = d;
        }
    }
    ans = max(ans, d1 + d2);
    return d1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    // 预处理约数之和
    for (int i = 1; i <= n; i++) {
        // j从2开始，因为题目要求i不是i的约数之和的组成部分；同时乘改除防止越界
        for (int j = 2; j <= n / i; j++) {
            sum[j * i] += i;
        }
    }

    memset(h, -1, sizeof h);
    for (int i = 2; i <= n; i++) {
        if (i > sum[i]) {
            add(sum[i], i);
            // i有父亲，因此i不是树根
            st[i] = true;
        }
    }

    // 枚举所有树根
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            dfs(i);
        }
    }

    cout << ans << endl;

    return 0;
}
