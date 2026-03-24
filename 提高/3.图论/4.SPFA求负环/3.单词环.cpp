// 本题要点：
// 1.建图
// 2.01分数规划
// 3.优化

// 1.建图
// 很自然的考虑方式是，把每个字符串视为一个点
// 如果能首尾相连，则两个字符串之间连一条有向边
// 根据题目数据，最多有1e5个点
// 要知道，可能有很多单词的结尾是一样的，也就是出现了很多“相同的点”
// 会导致空间大量浪费
// 因此换一种建图思路：把字符串看成边
// 分别取字符串的前2个字符和后2个字符，看作是两个点，用字符串这条边沟通起来
// 所有二位字符的组合是26*26=676个
// 因此最多有676个点，边数为1e5，完全可以接受

// 2.01分数规划
// 观察check不等式，存在环，使得环上总边权/边条数>mid，即
// sum(w[i])/sum(1)>mid <-> sum(w[i])-mid*sum(1)>0 <-> 图中存在正环
// 可以发现，若想让不等式成立，则mid尽可能小即可；而由题目条件，mid最小为0
// 如果mid=0都不成立，那就没法成立了——因此，这一点可以作为剪枝
// 然后，正常二分最小值最大即可

// 3.优化
// 当spfa很慢的时候，应该是测试数据故意卡了
// 这个时候，就得写上限了——超过上限就直接返回true，避免超时
// 经验上，如果点总共被松弛超过2n次，就可以认为存在负环了；当然，在时间允许的情况下，可以再大一些

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 700, M = 100010;

int n;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool check(int mid) {
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 1;

    // 本题未统计点数，直接跑到上限
    for (int i = 0; i < N; i++) {
        q[tt++] = i;
        st[i] = true;
    }

    int count = 0;  // 统计松弛次数

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i] - mid) {
                dist[j] = dist[t] + w[i] - mid;
                cnt[j] = cnt[t] + 1;

                // 优化：当松弛次数超过2n次，说明存在负(正)环了
                if (++count > 2 * N) {
                    return true;
                }

                if (cnt[j] >= N) {  // 注意，本题n是边，点数未知，但N是点数上限
                    return true;
                }

                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) {
                        tt = 0;
                    }
                    st[j] = true;
                }
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    while (cin >> n) {
        memset(h, -1, sizeof h);
        idx = 0;

        for (int i = 0; i < n; i++) {
            cin >> str;
            if (str.size() > 2) {
                // 求开头两个字符
                // 注意，考虑更简单的状态表示：将两个字符视为26进制数(不会重复，表示唯一)
                int left = (str[0] - 'a') * 26 + (str[1] - 'a');
                // 求结尾两个字符
                int right = (str[str.size() - 2] - 'a') * 26 + (str[str.size() - 1] - 'a');

                // 有向边 left->right，边权为字符串长度
                add(left, right, str.size());
            }
        }

        if (!check(0)) {
            cout << "No solution" << endl;
        } else {
            double l = 0, r = 1000;
            while (r - l > 1e-4) {
                double mid = (l + r) / 2;
                if (check(mid)) {
                    l = mid;
                } else {
                    r = mid;
                }
            }

            printf("%.2f\n", l);
        }
    }

    return 0;
}
