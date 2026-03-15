// 01背包问题
// 将达达视为背包，容量为W；共n个物品，每个物品重量为G[i]
// 求最大重量，因此本题重量就是价值

// 但不能用DP做，因为数据范围很大，空间复杂度和时间复杂度都无法承受

// 但n很小，因此暴搜
// 依次枚举每个物品选或不选——这太朴素了
// 双向DFS思路如下：
// 已知最大重量为W，物品数量为n
// 先dfs前k件物品，打表所凑出的重量
// 再dfs后n-k件物品，对于搜索到的每一种方案的重量S，在表中二分不超过W-S的最大重量
// k可以在n/2的基础上适当偏移，因为后一半还有二分的开销；因此令k>n/2
// 综上，这个算法展现的思想是：空间换时间

// 剪枝：先搜大物品，更快地接近W——排序

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 46;

int n, m, k;
int w[N];
// weight用于前k件物品打表，k共25个，用二进制表示选或不选的状态
// 因此，weight应该开2^25大小，后续还要排序以二分
int weights[1 << 25], cnt = 1; // cnt记录打表的方案数
int ans;

// u: 当前枚举过了的物品数量
// s: 当前枚举过的物品的重量和
void dfs1(int u, int s) {
    if (u == k) {
        // weights[0]也应当是一种方案，全0二进制串表示不选任何物品，重量为0
        weights[cnt++] = s;
        return;
    }

    // 不选当前物品
    dfs1(u + 1, s);
    // 选当前物品
    if ((LL)s + w[u] <= m) {
        dfs1(u + 1, s + w[u]);
    }
}

int bsearch(int x) {
    int l = 0, r = cnt - 1;
    int mid = l + r + 1 >> 1;
    if (weights[mid] <= x) {
        l = mid;
    } else {
        r = mid - 1;
    }
    return weights[l];
}

void dfs2(int u, int s) {
    if (u == n) {
        // <=m-s，答案在左边
        int maxv = bsearch(m - s);
        ans = max(ans, maxv + s);
        return;
    }

    dfs2(u + 1, s);
    if ((LL)s + w[u] <= m) {
        dfs2(u + 1, s + w[u]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    sort(w, w + n, greater<int>());

    // 前k件物品打表
    k = n / 2 + 2;
    dfs1(0, 0);

    sort(weights, weights + cnt);
    // unique: 删除数组内重复元素，返回一个指向新数组末尾的迭代器
    // 如果在后面再减去数组首地址，就得到了新数组的长度，即不重复元素的个数
    cnt = unique(weights, weights + cnt) - weights;

    dfs2(k, 0);

    cout << ans << endl;

    return 0;
}
