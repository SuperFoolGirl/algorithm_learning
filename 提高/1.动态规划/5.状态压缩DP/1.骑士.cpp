// 状态压缩一般分为两类：
// 1. 棋盘式(基于连通性)
// 2. 集合式(表示每个元素是否在集合中，常借助二进制)

// 状态表示 f(i,j,s) s为n位二进制数
// 集合：所有只摆在前i行，一共放了j枚国王，且第i行摆放状态为s的方案
// 属性：cnt

// 状态计算
// 根据题意，第i行的摆法只与i-1行有关，与其他更上方的行无关
// 只看i-1行，但一共有2^n种状态，因此分成2^n个子状态，即决策循环2^n次
// 第i行需要保证本行本身不冲突、与i-1行不冲突
// 用b表示i-1行的状态，a表示i行的状态
// 根据DP常用的“找最后一个不一样的点”——考虑i-1行：
// 已经摆放了i-1行，已经放了j-count(a)枚国王，count(a)为i-1行1的数量
// 则i-1行状态表示为 f(i-1,j-count(a),b)

// 12满足i与i-1不冲突，3满足i行本身不冲突
// 再复习下运算：
// &按位与，把两个二进制数的每一位进行比较，只有当两位都是1时结果才是1，否则为0
// &&逻辑与，比较两个表达式的值，只有当两个表达式都为真时结果才为真，否则为假
// 1. a & b == 0 (同一列不得摆放)
// 2. a | b 不能有两个重复的1，否则会违背3*3
// 3. b & (b << 1) == 0 (同一行不得摆放)

// 因此，状态转移方程为：


#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 12, M = 1 << 10, K = 110;

int n, m;
vector<int> state; // 存储合法状态
vector<int> head[M];  // 每个状态能转移到的其他状态
int cnt[M]; // 每个状态1的数量
LL f[N][K][M];

// 满足单行不冲突的状态
bool check(int state) {
    // 遍历本行的每一位，如果有两位连续的1，则不合法
    // 这里的位运算处理，与上方分析不同，为了方便使用了逻辑与
    for (int i = 0; i < n; i++) {
        if ((state >> i) & 1 && (state >> i + 1) & 1) {
            return false;
        }
    }
    return true;
}

int count(int state) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += state >> i & 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 预处理所有合法状态，类似思路可参考基础课
    // 这里的合法状态是考虑单行的合法状态，即满足同一行不冲突的状态
    // 如果不预处理的话，在主流程中，每次判断本行是否有相邻的1就会很麻烦
    for (int i = 0; i < 1 << n; i++) {
        if (check(i)) {
            // i是合法状态的值，是离散的
            // state的下标本身是连续的
            state.push_back(i);
            // 统计i状态中1的数量
            cnt[i] = count(i);
        }
    }

    // 建立不同合法状态之间的转移关系(合法状态指满足3)
    // 也就是i-1行和i行之间的关系
    // i-1行与i行之间可能是任意满足3的状态的组合
    // 体会状态压缩DP常用的“预处理”
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            int a = state[i], b = state[j];
            // 寻找满足12的3
            if ((a & b) == 0 && check(a | b)) {
                // a可以转移到b
                // 注意ij是下标，ab是状态值
                // head数组是依赖state数组的下标的
                head[i].push_back(j);
            }
        }
    }

    // DP初始化：cnt属性一般为1
    f[0][0][0] = 1;

    // 这里使用一个小技巧：i枚举到n+1
    // 原则上，枚举到n，然后需要遍历f[n][m][a]来找出最大值
    // 但如果枚举到n+1，最后输出f[n+1][m][0]，第n+1行什么也不放，即为目标结果
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= m; j++) {
            // 每行应当有2^n种状态，但由于不合法状态被过滤掉了，因此只有state.size()种状态
            for (int a = 0; a < state.size(); a++) {
                // 枚举所有a能到达的状态b
                for (int b : head[a]) {
                    // 回忆cnt数组，只存储合法状态的1的数量
                    int c = cnt[state[a]];
                    if (j >= c) {
                        f[i][j][a] += f[i - 1][j - c][b];
                    }
                }
            }
        }
    }

    // 输出f[n+1][m][0]，第n+1行什么也不放，即为目标结果
    cout << f[n + 1][m][0] << endl;

    return 0;
}
