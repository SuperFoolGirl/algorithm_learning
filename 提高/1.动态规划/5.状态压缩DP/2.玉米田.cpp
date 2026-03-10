// 棋盘类状压DP代码模板
// 行内合法预处理(state)+行间合法预处理(head[i])+DP

// 本题需要抽象出模型：十字区域内不可重复(以中心往四个方向扩展1格，共5格)
// 第一题是九宫格不可重复
// 因此与第一题思路一样，先确保本行i合法，然后确保i与i-1不冲突即可

// 相比第一题，少了k棋子限制，多了部分格子不可选限制

// 状态表示 f(i,s)
// 集合：所有摆放完前i行，且第i行状态为s的方案数
// 属性：cnt
// 状态计算
// 两个合法：1.行内合法；2.行间合法
// 设第i行状态为a，i-1行状态为b；ab各自行内合法，且b->a行间合法
// f(i,s) = sum{ f(i-1,b) }

// 合法条件
// 行内合法：check数组
// 行间合法：b & a == 0，只需要满足同列不重复即可

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 14, M = 1 << 12, MOD = 1e8;

int n, m;
int g[N];    // 存图，采用状态压缩的方式存储每行的状态
vector<int> state;
vector<int> head[M];
int f[N][M];

bool check(int state) {
    for (int i = 0; i < m; i++) {
        if ((state >> i & 1) && (state >> i + 1 & 1)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int t;
            cin >> t;
            // t=1为可选格，0为不可选格
            // 但是状态压缩DP中，1表示选了这个格子，0表示没选这个格子，因此需要取反
            g[i] += !t << j;
        }
    }

    // 预处理合法状态
    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) {
            state.push_back(i);
        }
    }

    // 处理合法状态之间的转移关系
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            int a = state[i], b = state[j];
            if ((a & b) == 0) {
                head[i].push_back(j);
            }
        }
    }

    f[0][0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int a = 0; a < state.size(); a++) {
            for (int b : head[a]) {
                // 只有当a状态与g[i]状态不冲突时，才可以从b转移到a
                // 即g为1的地方(不可选)，a不得是1；
                // g为0的地方(可选)，a随意
                // 因此，用按位与即可
                if ((g[i] & state[a]) == 0) {
                    f[i][a] = (f[i][a] + f[i - 1][b]) % MOD;
                }
            }
        }
    }

    cout << f[n + 1][0] << endl;

    return 0;
}
