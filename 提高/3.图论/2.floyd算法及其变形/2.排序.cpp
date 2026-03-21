// 求传递闭包
// 传递闭包 ：若a->b, b->c, 则a->c
// 即把所有间接相连的点也全部相连

// 若A<B，则有d[A][B]=1
// 若AB无关，则有d[A][B]=0/INF
// 下面描述三种关系关乎答案，是全局的，需要跑check来判断
// 1.矛盾：d[A][A]=1
// 2.关系唯一确定：d[i][j]与d[j][i]有且仅有一个1
// 3.不确定：1、2都不满足
// 注意排序输出，标记+每次输出最小数即可

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 26;

int n, m;
int g[N][N], d[N][N];
bool st[N];

void floyd() {
    // 不能污染g
    memcpy(d, g, sizeof g);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 传递闭包
                // 不要忘了|，因为d[i][j]可能已经是1了
                d[i][j] |= d[i][k] && d[k][j];
            }
        }
    }
}

int check() {
    // 判断矛盾
    for (int i = 0; i < n; i++) {
        if (d[i][i]) {
            return 2;
        }
    }

    // 判断是否唯一确定
    // j只需要枚举到i，否则会重复枚举
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (!d[i][j] && !d[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

char get_min() {
    for (int i = 0; i < n; i++) {
        if (!st[i]) {
            // 判断i是否是最小的
            bool flag = true;
            for (int j = 0; j < n; j++) {
                if (!st[j] && d[j][i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                st[i] = true;
                return i + 'A';
            }
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while (cin >> n >> m, n || m) {
        memset(g, 0, sizeof g);
        // type=0不确定，1表示唯一确定，2表示矛盾
        int type = 0, t;

        // 每次新加一条边，都需要跑一次floyd，来判断当前的关系是唯一确定、矛盾、还是不确定
        for (int i = 1; i <= m; i++) {
            char str[5];
            cin >> str;
            // 取出两个字母
            int a = str[0] - 'A', b = str[2] - 'A';

            // 如果还不确定，那就继续加边，继续验证
            if (!type) {
                g[a][b] = 1;
                floyd();
                type = check();
                // 本次加边后得出答案，记录轮次
                if (type) {
                    t = i;
                }
            }
        }

        // 输出结果
        if (!type) {
            cout << "Sorted sequence cannot be determined." << endl;
        } else if (type == 1) {
            memset(st, 0, sizeof st);
            cout << "Sorted sequence determined after " << t << " relations: ";
            // 从小到达输出关系序列
            // n是变量数，一定能全部输出
            for (int i = 0; i < n; i++) {
                cout << get_min();
            }
            cout << "." << endl;
        } else {
            cout << "Inconsistency found after " << t << " relations." << endl;
        }
    }

    return 0;
}
