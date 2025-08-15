// 二分图是一种特殊的图，它的顶点可以被分为两个不相交的集合，且所有边都连接这两个集合中的顶点。
// 但二分图所抽象出来的两个集合，并不一定满足单射的关系（也不满足满射，但不予讨论）
// 匹配是二分图中的一个边集，其中任意两条边都没有共同的顶点。这个匹配中的每一条边都代表了左右两个集合之间的一个一对一（单射）配对。
// 匈牙利算法就是为了找到一个最大匹配，即边数最多的那个匹配。
// 这个算法最终找到了一个最大数量的单射配对集合，而这个集合的边数就是二分图的最大匹配数。

// 下方示例代码的前提：左集合来匹配右集合

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 510, M = 100010;
int h[N], e[M], ne[M], idx;
int match[N];     // match[x]，x为右集合的点，则match[x]为左集合中与x匹配的点
bool st[M];
int n1, n2, m;    // 左集合n1个点，右集合n2个点，共m条边

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool find(int x) {
    // 遍历所有儿子，放在二分图中，就是遍历左集合中点x映射到右集合中的所有边
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            st[j] = true;
            // 如果未匹配，或者已匹配的左集合的点，可以找到“下家”，也就是说可以有别的选择，那就把他给绿了
            // 模拟算法流程，被绿的mathch[j]现任j被抢了，再次进入find，在for循环里遍历到另一个下家即可。j被if判断给ban了
            if (!match[j] || find(match[j])) {    // find函数接收左集合点参数，match数组记录左集合点参数
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
    memset(h, -1, sizeof h);

    cin >> n1 >> n2 >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;    // 保证输入为，a是左集合的点，b是右集合的点
        add(a, b);        // 虽然是无向图，但添加一次就够了。匈牙利算法关注的是两个集合间的映射/匹配
    }

    // 匈牙利算法核心部分
    int res = 0;                       // 最大匹配数
    for (int i = 1; i <= n1; i++) {    // 遍历左集合的点
        // 点i要开始匹配右集合的点了，先全部初始化为false，表示都还未考虑；
        // 即使是已经心有所属的右集合点，也不用管，match数组已经记录了；而且，匈牙利算法中，就算对方已经心有所属了，也能抢过来
        memset(st, false, sizeof st);
        if (find(i)) {
            res++;
        }
    }
    cout << res << endl;

    return 0;
}
