// 分层/拆点

// 一类钥匙可以开一类门，多把钥匙可以在同一格
// 只要拿到钥匙，就可以从任意方向开门通过，不止局限在一边
// 扩展时(必须合法——无墙、遇门时有钥匙)边权都为1
// 捡钥匙、开锁没有消耗，不计入额外边权
// 显然，同一格可以重复走；只有最简单的最短路模型不能重复(因为重复走必然得不到最好答案)
// 本题中，“绕远路”所带来的收益能够抵消“绕远路”所带来的额外边权，因此可以重复走

// 解决问题的方法：增加状态数组dist的状态，类比DP
// 在DP中，状态数组是f；在图论中，状态数组是dist
// 图论中还涉及队列，队列中点的属性一般为“点序号/坐标+所有属性”
// 我们回到属性这个属于DP的词——f数组的属性是max/min/cnt，dist的属性是距离；属性是唯一的
// 除了属性，还剩状态表示；这时会发现关键了：
// dist一般只有一个状态：dist(i)表示起点到i的最短距离(或者对于方格图，需要用坐标(x,y)代替i)
// 如果没有门的话，那就是纯BFS问题，不用管钥匙；但如果考虑门和钥匙的话，就需要增加一些状态了
// 如dist({x,y},state)表示起点到坐标(x,y)的最短距离，state表示当前拥有的钥匙状态，为s位二进制数，s是钥匙的种类数
// (当然，这个问题很久之前有讨论过——将状态数组视为函数，需要增加必要的函数参数，同时扩大数组的维数)

// 注意，判重数组st需要共享dist的状态表示，因为st标记的是“每个状态是否访问过/在队内”，而不是“每个点”

// 下面用DP分析方法来拆解这道题目
// 状态表示 d(x,y,state)
// 集合：所有从起点走到坐标(x,y)，且当前拥有的钥匙状态为state的路径集合
// 属性：min
// 状态转移(松弛操作)
// 这里插一句。之前分析过状态转移和松弛操作本质上是一样的
// 状态转移：根据方程约束，看自己能从哪个子集状态转移而来
// 松弛操作：根据松弛条件，看当前状态能用来更新哪个状态
// 显然，对于图论来说，后者更自然；因此状态转移方程和松弛方程写法上不太一样
// 松弛方程：考虑d(x,y,state)可以用来更新哪些状态，列写出来
// 1.如果(x,y)有钥匙，那么一定会拿起来：d(x,y,state|key) = min(d(x,y,state|key), d(x,y,state))
// 2.常规转移：向上下左右四个方向走，移动后坐标为(a,b)
//   没有门和墙，或门前有钥匙：d(a,b，state) = min(d(a,b,state), d(x,y,state)+1)
//   补充：此处的+1视为边权，和+w[i]是一样的
// 3.其他情况：不合法，continue

// 代码结构
// 首先，不能用DP来写，因为不是拓扑图
// 因此，用图论算法来写即可
// 本题由于只有01边权，可以用双端队列BFS
// 答案：max(d[n][m][s1], d[n][m][s2], ...)，s1、s2、...是所有包含了目标钥匙的状态

// 简化代码:
// 1.二维坐标映射到一维，编号从左到右从上到下
// 2.虽然题目是方格图，但需要用邻接表来存边；否则难以识别墙、门等。每个格子为点，若四个方向可扩展，即有对应出边；
// 3.题目只给出了墙和门，边需要自己创建；借助set+方向数组遍历来创建出可通过的边

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <unordered_set>

#define x first
#define y second

using namespace std;

// 二维坐标压缩成一维后，状态表示为二维，使用pair即可
typedef pair<int, int> PII;

const int N = 11, M = N * N, E = 400, P = 1 << 10;

int n, m, p, k;
int h[M], e[E], ne[E], w[E], idx;
int g[N][N], key[M];
int d[M][P];
bool st[M][P];  // 01BFS类似dijkstra，因此st作用为判出队
unordered_set<PII> edges;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

void build() {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    // 枚举所有边——枚举点+方向数组即可
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int u = 0; u < 4; u++) {
                int x = i + dx[u], y = j + dy[u];
                if (x < 1 || x > n || y < 1 || y > m) {
                    continue; 
                }
                // 拿出这条边对应的两点
                int a = g[i][j], b = g[x][y];
                // 如果不是墙/门，就是普通边
                if (!edges.count({a, b})) {
                    add(a, b, 0);
                    // 这里不用加另一条边，遍历到对面那个点时，它会自己加的，没必要重复加
                }
            }
        }
    }
}

int bfs() {
    memset(d, 0x3f, sizeof d);
    d[1][0] = 0;  // 起点坐标为(1,1)，编号为1，初始状态没有钥匙

    deque<PII> q;
    q.push_back({1, 0});

    while (q.size()) {
        PII t = q.front();
        q.pop_front();

        int ver = t.x, state = t.y;
        if (st[ver][state]) {
            continue;
        }
        st[ver][state] = true;

        // 终点判断
        if (ver == g[n][m]) {
            return d[ver][state];
        }

        // 根据松弛操作的分析，在扩展前，原地先考虑是否有钥匙可以拿
        if (key[ver]) {
            if (d[ver][state | key[ver]] > d[ver][state]) {
                d[ver][state | key[ver]] = d[ver][state];
                q.push_front({ver, state | key[ver]});  // 拿钥匙不增加边权，放在队头
            }
        }

        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            // 如果是门，且没有钥匙，则无法通过
            // w[i]需要-1，钥匙的id偏移了一位
            if (w[i] && !(state >> (w[i] - 1) & 1)) {
                continue;
            }
            if (d[j][state] > d[ver][state] + 1) {
                d[j][state] = d[ver][state] + 1;
                q.push_back({j, state});  // 走边增加边权，放在队尾
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> p >> k;
    memset(h, -1, sizeof h);
    // 二维坐标映射到一维
    for (int i = 1, t = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            g[i][j] = t++;
        }
    }

    // 门和墙
    while (k--) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        // 找到点对应的编号
        int a = g[x1][y1], b = g[x2][y2];
        // 将墙/门加入set，注意双向
        edges.insert({a, b}), edges.insert({b, a});
        // 如果是门，说明两点间右边；墙就不用了，无论如何也走不了
        if (c) {
            // c如果不是0，则代表门的类型，存在w数组中；w=0代表普通边，不需要钥匙
            // 本题是01边权，不需要存储边权；边权体现在deque的push方式上
            add(a, b, c), add(b, a, c);
        }
    }

    // 处理其他边
    build();

    // 读钥匙
    int s;
    cin >> s;
    while (s--) {
        int x, y, id;
        cin >> x >> y >> id;
        // |=：与等，因为每个格子可能有多把钥匙
        // 题目id从1开始，为了节省一位，可以令id从0开始，这样2^0即第一位就可以参与状态表示了
        key[g[x][y]] |= 1 << (id - 1);
    }

    cout << bfs() << endl;

    return 0;
}
