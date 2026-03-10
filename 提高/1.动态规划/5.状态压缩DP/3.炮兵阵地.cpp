// 棋盘型
// 相比第二题，十字往外扩散了一圈
// 山地H不可部署炮兵，只能在平原P上部署

// 分析
// 本题开始涉及上两行的状态，但很简单：连续两列且连续三列不得同时部署
// 但其实满足连续两列不重复，就满足了连续三列不重复
// 因此，状态表示上也要再加一重状态维度
// 分析状态计算原则：找最后一个不一样的点
// f(i,j,k)中，第i行和第i-1行的状态已经锁死了，因此最后一个不同的点出现在i-2行
// 设i-2行状态为c，i-1行状态为a，i行状态为b
// 考虑需要满足的条件：
// 1. 连续两列不得重复：((a&b)|(a&c)|(b&c)==0)
// 2. 山地不可部署：((g[i-1]&a)|(g[i]&b)==0)

// 状态表示 f(i,j,k)
// 集合：所有已经摆完前i行，且第i-1行状态是j，第i行状态是k的方案的最大值
// 属性：max
// 状态计算
// f(i,a,b) = max{ f(i-1,c,a) }

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 11, M = 1 << 10;

int n, m;
int g[110];
int cnt[110];  // 预处理每行状态中1的个数，方便后续计算最大值
vector<int> state;
int f[2][M][M];  // 为了节省空间，i维度只保留两行，滚动数组

// 行内两个部署点，间隔至少为2
// 如果第i列为1，则i+1和i+2列必须为0
bool check(int state) {
    for (int i = 0; i < 1 << m; i++) {
        if ((state >> i & 1) && ((state >> i + 1 & 1) || (state >> i + 2 & 1))) {
            return false;
        }
    }
    return true;
}

int count(int state) {
    int res = 0;
    for (int i = 0; i < m; i++) {
        res += state >> i & 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            // H山地不可部署
            if (c == 'H') {
                g[i] += 1 << j;
            }
        }
    }

    // 预处理行内合法
    for (int i = 0; i < 1 << m; i++) {
        if (check(i)) {
            state.push_back(i);
            cnt[i] = count(i);
        }
    }

    // 使用滚动数组，无法预处理合法行间状态，直接DP；行间处理交给continue过滤
    // i-2行状态c，i-1行状态a，i行状态b
    // i枚举正在处理的行数，jku枚举三行合法状态
    for (int i = 1; i <= n + 2; i++) {
        // 枚举i-1行状态a
        for (int j = 0; j < state.size(); j++) {
            // 枚举i行状态b
            for (int k = 0; k < state.size(); k++) {
                // 枚举i-2行状态c
                for (int u = 0; u < state.size(); u++) {
                    int a = state[j], b = state[k], c = state[u];
                    // 连续两列不得重复
                    if ((a & b) || (a & c) || (b & c)) {
                        continue;
                    }
                    // 山地不可部署
                    if ((g[i - 1] & a) || (g[i] & b)) {
                        continue;
                    }
                    // 滚动数组，每一项与1
                    // 与1结果为1说明是奇数，与1结果为0说明是偶数
                    f[i & 1][j][k] = max(f[i & 1][j][k], f[i - 1 & 1][u][j] + cnt[b]);
                }
            }
        }
    }

    // i+2行状态为0，且i行状态也为0
    cout << f[n + 2 & 1][0][0] << endl;

    return 0;
}
