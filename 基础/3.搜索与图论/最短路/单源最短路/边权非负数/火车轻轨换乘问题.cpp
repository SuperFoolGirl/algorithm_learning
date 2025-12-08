/*
寒假到了，小明准备坐火车回老家，现在他从学校出发去火车站，CC市去火车站有两种方式：轻轨和公交车。小明为了省钱，准备主要以乘坐公交为主。CC市还有一项优惠政策，持学生证可以免费乘坐一站轻轨（但只能乘坐一站）。小明想尽快到达火车站，请编写程序为小明找到一条从学校到火车站最快的路线及换乘轻轨的方案。

假设换乘时间忽略不计，公交车与轻轨站点相同，但线路和速度不一定相同，所有线路都是双向的。可以第一站就乘坐轻轨，也可以最后一站乘坐轻轨，也可以在中间某站坐轻轨。如果乘坐轻轨和不乘坐轻轨到达火车站的时间相同，则无需换乘轻轨。最多坐一站轻轨。

输入格式:
输入包含多组数据。每组数据第一行为3个整数n、s和t，分别表示车站数（编号为1至n），小明学校所在的站和火车站所在的站。下一行为一个整数m，表示公交车的线路信息，接下来m行，每行为3个正整数a、b、c，表示公交车从a站到b站需要c分钟。下一行为一个整数k，表示轻轨的线路信息，接下来k行，每行为3个正整数x、y、z，表示轻轨从x站到y站需要z分钟。所有整数均不超过20000。

输出格式:
对每组数据输出2行。第1行为1个整数T，表示从学校到达火车站的最短时间；第2行为一个整数K，表示在站点K换乘轻轨，若有多个可能的换乘点，则输出编号最小者，如果无需换乘轻轨，则第二行输出“no
metro”。
*/

// 轻轨可能独自占有某些线路
// 比如公交站不存在2->4的边，但轻轨有
// 因此，不能只简单地考虑边权问题
// 轻轨也需要一张独立的图，而不是用哈希表简单存边

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

const int N = 2e4 + 10, M = N * 2;
const int INF = 0x3f3f3f3f;

int h1[N], e1[M], ne1[M], w1[M], idx1;
int h2[N], e2[M], ne2[M], w2[M], idx2;
// 多状态的情况下，需要多维函数来存储状态
int d[N][2];        // d[i][0]表示未坐轻轨到达i的最短距离，d[i][1]表示已坐轻轨到达i的最短距离
int tr_nodes[N];    // 记录到达每个节点时的换乘点，-1表示无效
int n, s, t, m, k;
pair<int, int> res;

void add1(int a, int b, int c) {
    e1[idx1] = b;
    ne1[idx1] = h1[a];
    w1[idx1] = c;
    h1[a] = idx1++;
}

void add2(int a, int b, int c) {
    e2[idx2] = b;
    ne2[idx2] = h2[a];
    w2[idx2] = c;
    h2[a] = idx2++;
}

struct Node {
    int node;
    int dist;
    int used;
    int tr_node;    // 记录换乘点

    // 比较逻辑放在结构体里，不用单独写一个比较类了
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

void dijkstra() {
    memset(d, 0x3f, sizeof d);
    memset(tr_nodes, -1, sizeof tr_nodes);

    d[s][0] = 0;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({s, 0, 0, -1});    // 起点，距离0，未坐轻轨，换乘点-1表示无效

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        int node = curr.node;
        int dist = curr.dist;
        int used = curr.used;
        int tr_node = curr.tr_node;

        // 当前状态不是最优，跳过
        if (dist > d[node][used]) {
            continue;
        }
        // 当前已换乘，且换乘点不是最优，跳过
        if (used && tr_nodes[node] != -1 && tr_node > tr_nodes[node]) {
            continue;
        }

        // 不论是否坐过轻轨，都可以选择不坐
        // 没坐过，就在d[j][0]处更新；坐过了，就在d[j][1]处更新
        for (int i = h1[node]; i != -1; i = ne1[i]) {
            int j = e1[i];
            int wt1 = w1[i];

            if (d[j][used] > dist + wt1) {
                d[j][used] = dist + wt1;
                pq.push({j, d[j][used], used, tr_node});

                // 如果已换乘，更新接下来的状态也为相同的换乘点
                // 堆元素可以直接把信息入队，数组需要自己来传递信息进行维护
                if (used) {
                    tr_nodes[j] = tr_node;
                }
            } else if (d[j][used] == dist + wt1 && used) {
                // 如果距离相同，且已换乘，则尝试更新换乘点为字典序更小的
                // 这里要好好思考下遍历图的结构
                // 终点是一样的，都是j
                // 上一次更新d[j][1]时，换乘点是基于那个时候的tr_node，设为v
                // 现在的tr_node可能更小，数值上小于v
                // 但不管怎么说，换乘点都已经是历史了
                // 即使可能中间的路线都不同，但殊途同归地来到此处
                // 从现在开始，走下去的结果都是相同的。因此也不需要额外入队
                // 所以可以直接更新换乘点
                if (tr_nodes[j] > tr_node) {
                    tr_nodes[j] = tr_node;
                    // 没有入队的必要
                    // 换乘已经发生在历史了，往后是一样的
                }
            }
        }

        // 如果没坐过轻轨，可以选择坐轻轨
        // 现在遍历轻轨图，与公交图是互相独立的；即使有起点终点相同的边，也不会冲突
        if (used == 0) {
            for (int u = h2[node]; u != -1; u = ne2[u]) {
                int v = e2[u];
                int wt2 = w2[u];

                // 注意，d[v][1]，只通过轻轨到达v的距离
                // 达到v的轻轨可能不止一条
                if (d[v][1] > dist + wt2) {
                    d[v][1] = dist + wt2;
                    pq.push({v, d[v][1], 1, node});
                    tr_nodes[v] = node;    // 记录换乘点为当前节点
                } else if (d[v][1] == dist + wt2) {
                    // 此前已经有通过换乘点x到达v的轻轨路径了
                    // 那么它一定被记录在tr_nodes[v]里
                    // 现在的换乘点是node，尝试更新为更小的那个
                    // 仍然不需要入队，理由同上
                    if (tr_nodes[v] > node) {
                        tr_nodes[v] = node;
                    }
                }
            }
        }
    }

    int ans_dist = min(d[t][0], d[t][1]);
    int ans_tr = -1;
    if (d[t][1] < d[t][0] && d[t][1] != INF) {    // 仅当轻轨可达且更优时
        ans_dist = d[t][1];
        ans_tr = tr_nodes[t];
    }
    res = {ans_dist, ans_tr};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> s >> t) {
        memset(h1, -1, sizeof h1);
        memset(h2, -1, sizeof h2);
        idx1 = 0;
        idx2 = 0;

        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            add1(a, b, c);
            add1(b, a, c);
        }

        cin >> k;
        for (int i = 0; i < k; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            add2(a, b, c);
            add2(b, a, c);
        }

        dijkstra();

        cout << res.first << endl;
        if (res.second == -1) {
            cout << "no metro" << endl;
        } else {
            cout << res.second << endl;
        }
    }

    return 0;
}
