// 较复杂的分组背包问题
// 这里提供分组背包的另一个审视维度：树
// 每种选法对应一个决策，每个决策是从根结点到叶子结点的一条路径

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define v first
#define w second

using namespace std;

typedef pair<int, int> PII;

const int N = 70, M = 32010;

// n为物品个数，m为钱数
int n, m;
PII master[N];  // 记录所有主件
vector<PII> servant[N];  // 记录主件对应的附件，由于一个主件有若干附件，因此用vector来存储
int f[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 处理输入
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int v, p, q;
        cin >> v >> p >> q;  // q若不为0，则为附件的主件编号，即对应的i
        if (!q) {
            // 主件
            master[i] = {v, v * p};
        } else {
            // 附件
            servant[q].push_back({v, v * p});
        }
    }

    // 枚举物品
    for (int i = 1; i <= n; i++) {
        // 题目交代v是非负整数，有是0的可能
        if (master[i].v) {
            // 倒序枚举价格
            for (int j = m; j >= 0; j--) {
                // 枚举附件的所有组合情况，附件的组合数是2^k，其中k是附件的数量
                // 这里补充一点位运算知识：2^k作为最大枚举量，写作二进制，一共有k位
                // 这重循环一共要遍历2^k次；对于每个循环变量k，将其视为一个k位二进制数，供下面的u使用
                // 下面的u循环遍历这k位，每一位的0/1状态分别表示对应附件的选/不选情况
                // 举个例子，s[i].size()=3时，k需要从0遍历到7
                // 换成二进制，也就是000-111，每个数长度为3
                // 然后每个循环变量k要供给下面的逐位遍历的u使用
                // u遍历位数为3，因为k长度为3
                for (int k = 0; k < 1 << servant[i].size(); k++) {
                    // 总钱数和总重要度，先加上主件的
                    int v = master[i].v, w = master[i].w;
                    // 枚举每个组合中，各附件的情况
                    for (int u = 0; u < servant[i].size(); u++) {
                        // 如果组合k中包含附件u
                        if (k >> u & 1) {
                            v += servant[i][u].v;
                            w += servant[i][u].w;
                        }
                    }
                    // 此时，已经把k代表的附件组合的v和w计算完成，可以进行状态转移了
                    // 更新f[j]，即在价格不超过j的前提下，选主件i和附件组合k的情况
                    if (j >= v) {
                        f[j] = max(f[j], f[j - v] + w);
                    }
                }
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
