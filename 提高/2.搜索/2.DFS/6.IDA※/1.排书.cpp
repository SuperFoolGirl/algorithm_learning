// 搜索过程很像区间DP
// 书总长为n，1~n
// 枚举移动书目的长度i，长度为i的段共n-i+1个
// 拿出去这i本书后，剩余n-i本书，产生n-i+1个空位；除去原先的位置，剩余n-i个空位
// 但上述有2倍重复，实际上只需要枚举"在自己之后的书"所产生的空位即可
// 枚举这些空位

// 迭代加深+IDA*做法：
// 找启发函数：走到终点的最小步数
// 对于一个有序序列，正确前驱-后继关系应当为n-1个：1-2,2-3,...,n-1-n
// 对于每次移动书目操作，一共会改变3个后继关系
// 我们可以认为这3次改变一定都是正确的(满足了“小于等于性”)
// tot统计所有不正确的后继，每次移动会修复三个；因此启发函数为tot/3上取整
// 考虑到cpp的除法下取整，改写为(tot+2)/3

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 15;

int n;
int q[N];
int w[5][N];  // 记录depth层的状态，回退时直接覆盖即可

int f() {
    int tot = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (q[i] + 1 != q[i + 1]) {
            tot++;
        }
    }
    return (tot + 2) / 3;
}

bool dfs(int u, int depth) {
    // 迭代加深+IDA*
    if (u + f() > depth) {
        return false;
    }
    // 出口判断——全部有序
    // 这里居然是用启发函数来判断的，很有意思
    if (f() == 0) {
        return true;
    }

    // 枚举长度
    for (int len = 1; len <= n; len++) {
        // 枚举起点
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            // 枚举空位，只往后放+放到k的后面去
            for (int k = r + 1; k < n; k++) {
                memcpy(w[depth], q, sizeof q);

                // 将区间[l,r]的书目移动到k的后面去：
                // 1.将原先[r+1,k]前移，起点为l
                // 2.将原先[l,r]的部分顺着上面继续往后放
                int y = l;  // x从w中获取原数据，y更新写入q
                for (int x = r + 1; x <= k; x++, y++) {
                    q[y] = w[depth][x];
                }
                for (int x = l; x <= r; x++, y++) {
                    q[y] = w[depth][x];
                }

                if (dfs(u + 1, depth)) {
                    return true;
                }

                memcpy(q, w[depth], sizeof q);
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> q[i];
        }

        int depth = 1;
        while (depth < 5 && !dfs(0, depth)) {
            depth++;
        }

        if (depth >= 5) {
            cout << "5 or more" << endl;
        } else {
            cout << depth << endl;
        }
    }

    return 0;
}
