// 这个题目主要练习一下基于DAG出边的DP，即PULL-DP；此前大多使用的是PUSH-DP
// 枚举所有可能的状态，用每个状态来更新其能够转移到的状态
// 对于本题来说，存在非法状态，需要判断。放到DAG中可以这样理解：非法点不应当存在于图中，理论上，它们可能会错误地更新其他状态
// 但实际上，这些非法点会被状态转移方程给拦住，因此这里continue起到一个剪枝作用：删掉的话不会导致错误，但效率大大降低

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 110, M = 21, INF = 0x3f3f3f3f;

int n, m, k;
int f[1 << M];
int candy[N];    // 预处理每包糖果的状态

int main() {
    cin >> n >> m >> k;

    int c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> c;
            candy[i] |= 1 << (c - 1);
        }
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int i = 0; i < 1 << m; i++) {
        // 如果自身是非法结点，则无法用它来更新下一轮结点
        if (f[i] == INF) {
            continue;
        }
        for (int j = 0; j < n; j++) {
            int st = i | candy[j];
            f[st] = min(f[st], f[i] + 1);
        }
    }

    int res = f[(1 << m) - 1];
    if (res == INF) {
        res = -1;
    }
    cout << res << endl;

    return 0;
}
