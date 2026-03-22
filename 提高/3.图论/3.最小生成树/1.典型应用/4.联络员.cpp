// 本题含重边
// 特殊要求：存在必选边

// 做法：
// 1.先把必选的边全都选上，可能会形成若干连通块(也可能有环)
// 2.把形成的联通块当成一个点，剩下的边连接这些点，求最mst
// 这种思想很有趣！将联通块视为点，之前已经出现过了

// 代码：
// 1.将必选边加入并查集
// 2.将非必选边排序，枚举a-b
// 3.若ab已连通，pass；若ab不连通，加入答案，并把a和b所在的联通块合并
// 可以看到，形式上，就是在kruskal之前进行简单的预处理

// 并查集这个特殊的数据结构，帮我们简化了“将连通块视为点”的代码操作
// 这里具体讲一下
// 首先，并查集在kruskal算法中的作用是什么？
// 对于一个集合(连通块)，我们需要找到它的代表元，也就是根结点(祖宗)
// 对于find(a)，返回的就是a所在的连通块的代表元
// 由此可以看出，一个并查集数组是可以维护多个连通块的，因此kruskal求最小森林就是合法的(第二题)
// 在本题中也一样：对于已经拥有的连通块，将其视为点
// 遍历到边a-b，若a存在于已有连通块，那find(a)返回该连通块的代表元x——这个x就是我们将块视为的“点”
// 好好体会“代表元”的作用

// 下面，讲一下kruskal的另一个特性：
// 视根据题目要求，求出完整的最小生成树(森林)为目标，用进度条来刻画目标完成进度
// 那么，kruskal只做进度条前部分和只做后部分，依然是正确的
// 只做前部分：
// 将原图视为视连通图，那么只做前部分的话，结果是求出了一个“只包含选中点的最小生成森林”——这说明了kruskal求最小生成森林的正确性
// 只做后部分
// 相当于在原来的基础上求最小生成树，即本题的情况，可以用上面并查集的讨论来理解

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, M = 10010;

int n, m;
struct Edge {
    int a, b, w;
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} e[M];
int p[N];
int res, cnt;

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int kruskal() {
    sort(e, e + cnt);

    for (int i = 0; i < cnt; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    while (m--) {
        int t, a, b, w;
        cin >> t >> a >> b >> w;
        if (t == 1) {
            // 必选边，直接加入答案，并把a和b所在的连通块合并
            res += w;
            p[find(a)] = find(b);
        } else {
            // 非必选边，加入边数组，等待kruskal
            e[cnt++] = {a, b, w};
        }
    }

    cout << kruskal() << endl;

    return 0;
}
