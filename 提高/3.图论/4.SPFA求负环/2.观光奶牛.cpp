// 经典问题：01分数规划
// 常与负环、最小生成树、最短路相结合

// 01分数规划问题：求sum1/sum2的最大值
// 通用做法：二分，求最小值最大问题
// 根据sum1和sum2的取值范围，可以求出比值的上下限(二分区间)。
// 枚举mid，check函数为一个关于点权、边权与mid的不等式
// 整理不等式，重新定义图的点权/边权
// 然后转为求负环/求最短路/求mst问题

// 观察check不等式，存在环，使得环上总边权 / 边条数 > mid，即
// sum(w[i])/sum(1)>mid <-> sum(w[i])-mid*sum(1)>0 <-> 图中存在正环
// 二分check等价于判断图中是否存在正环
// 正环怎么处理？1.边变号求负环；2.变求最短路为求最长路

// sum的目标是整个环，不是需要我们自己预处理的数据
// 根据之前对spfa求负环的分析，它会跑满环；在这个过程中，随着松弛，sum就被计算出来了
// 但是，根据之前说的，在检测到负环前，可能已经跑了好几圈负环了，权值更新的值不对了
// 但是，注意，在等价处理后，我们只需要判断新边权的正负性
// 如果判断的是正环，那么如果遇到了正环，它不会断累加正值，即使跑了多轮，最后也不影响符号判断；负环同理

// 点权与边权共存，难以处理
// 之前介绍过一种解决方案：虚拟源点，化点权为边权
// 此外，还可以把点权直接转移到边上，比如统一放到出边上

#include <iostream>
#include <cstring>
#include <algorithm>

    using namespace std;

const int N = 1010, M = 5010;

int n, m;
int wf[N];
int h[N], e[N], wt[M], ne[M], idx;
double dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    wt[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 求负环
bool check(double x) {
    // 距离无需设置
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);
    int hh = 0, tt = 1;

    for (int i = 1; i <= n; i++) {
        q[tt++] = i;
        st[i] = true;
    }

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            // 求最长路，不等号取反
            // wf[t]-mid*wt[i]是原不等式移项后构造的新边权
            if (dist[j] < dist[t] + (wf[t] - x * wt[i])) {
                dist[j] = dist[t] + wf[t] - x * wt[i];
                cnt[j] = cnt[t] + 1;

                if (cnt[j] >= n) {
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

    cin >> n >> m;
    memset(h, -1, sizeof h);

    // 读入点权
    for (int i = 1; i <= n; i++) {
        cin >> wf[i];
    }
    // 读入有向边
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    // 浮点数二分注意写法，l/r无需额外处理
    // 本题为左模板，最小值最大
    double l = 0, r = 1010;  // 保证答案在区间里即可
    // 保留x位小数，则误差设为1e-(x+2)
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.2f\n", r);

    return 0;
}
