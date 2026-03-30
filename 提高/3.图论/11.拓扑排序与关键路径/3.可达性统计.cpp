// DAG，方案数，一眼DP。但本题不是简单的方案数，需要去重
// 但是本题需要拓扑排序逆序，下面细说

// f(i)表示所有从i出发能到达的点的集合
// 设f(i)的所有出边为i->j1,i->j2,...,i->jk
// 则f(i) = i U f(j1) U f(j2) U ... U f(jk)
// 注意不能取加号，因为集合之间可能有交集；如果取加号，就会把交集部分重复计算了
// 那么，如何状态表示呢？很自然地能想到用二进制串了，并运算用或运算
// 可以自己用二进制实现，不过情景完美契合STL-bitset
// bool原为1byte，压缩后为1bit，空间压缩至1/8
// 对于原8个bool元素的数组，需要比较8次；而位运算只需要1次，效率也大大提升

// 此时发现，这个顺序和DP的递推方向不同
// DP是“儿子从父亲处获取信息”，本题需要“父亲从儿子处获取信息”
// 因此，我们采用逆拓扑排序
// 这种思路也可用于普通DP，这种顺序与定义的差异，在记忆化搜索中也有体现

// 如今了解了DAG与DP的关系，可以更灵活地审视DP了
// 只要保证递推关系符合拓扑序就可以；如果自己的定义与拓扑序相反，那就逆序
// DP所谓的后无效性，其实就是DAG无环的特性，不会产生循环依赖
// 而最优子结构，其实依赖的就是松弛操作条件，也就是状态转移方程而已

#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>

using namespace std;

const int N = 30010, M = 30010;

int n, m;
int h[N], e[M], ne[M], idx;
int q[N], d[N];
// <N>表示一个bitset元素的大小。这是c++特性，写类型和长度均可
// 一般只有bitset需要自定义，因为每个bitset有几位是根据图中点的上限来定的
// 因为一个bitset元素可以表示一系列元素；而每个vector中的int只表示它自己
bitset<N> f[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void toposort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++) {
        if (!d[i]) {
            q[++tt] = i;
        }
    }
    
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q[++tt] = j;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }

    toposort();

    // 逆序遍历拓扑序
    for (int u = n - 1; u >= 0; u--) {
        int t = q[u];
        f[t][t] = 1;  // f(t)至少包含t自己，即f(t)的第t位为1
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            f[t] |= f[j];
        }
    }

    for (int i = 1; i <= n; i++) {
        // count()函数返回bitset中值为1的位的个数，即集合中元素的个数
        cout << f[i].count() << endl;
    }

    return 0;
}
