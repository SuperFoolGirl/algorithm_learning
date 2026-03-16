// 非负边权单源最短路，这里用spfa

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2510, M = 12410;

int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

// 注意，spfa中结点可以多次入队，因此需要循环队列
// 循环队列与普通队列代码上略有差异
int spfa() {
    // 循环队列中，tt指向队尾的下一个位置，因此初始化为1
    // 普通队列中，tt指向队尾元素，初始化为0
    int hh = 0, tt = 1;
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    q[0] = S;
    st[S] = true;

    // tt永远指向队尾的下一个位置；因此若hh与tt重合，说明队列为空
    // 相比普通队列写法hh<=tt，循环队列的写法是hh!=tt
    // 普通队列中，tt指向队尾，因此hh与tt可重合
    // 循环队列中，hh和tt大小关系不定，可能到达终点后tt循环了，导致tt<hh合法
    while (hh != tt) {
        int t = q[hh++];
        // 入队后越界判断
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;  // 出队后标记为不在队列中

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    // 因为tt指向队尾的下一个位置
                    // 因此这里需要后置++
                    q[tt++] = j;
                    // 出队后越界判断
                    if (tt == N) {
                        tt = 0;
                    }
                    st[j] = true;  // 入队后标记为在队列中
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    spfa();

    // 保证一定有解，无需判无解
    cout << dist[T] << endl;

    return 0;
}
