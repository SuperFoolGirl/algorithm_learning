// 题目分析
// 1. 每个城市只能建立一座桥，且只有友好城市间可建桥
// 2. 桥间不可相交
// 3. 求最多能建立多少座桥

// 如何将合法建桥方式转为最长上升子序列(LIS)问题呢？
// 将建桥看作是函数，南边是自变量，即起点；北边是因变量，即终点
// 合法建桥：从左到右，后一个桥的终点一定在前一个桥的终点的右边
// 转为数学模型：
// 设桥的对应关系为f。如果有i<j且f(i)<f(j)，说明以i.j为起点的桥是合法的
// 这里就可以发现端倪了：合法的桥一定要满足f单调递增
// 从而转为LIS问题：南岸的起点顺序编号，北岸按照与南岸的关系编号，然后在北岸的编号上求LIS

// 核心在于在南北岸上建立函数关系，通过函数的单调性来转化为LIS问题。此过程中将双变量问题转为单变量问题

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e5 + 10;

int n;
PII a[N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    // 南岸按编号排序
    sort(a, a + n);

    // 在北岸的编号上求LIS
    int res = 0;
    for (int i = 0; i < n; i++) {
        f[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j].second < a[i].second) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        res = max(res, f[i]);
    }

    cout << res << endl;

    return 0;
}
