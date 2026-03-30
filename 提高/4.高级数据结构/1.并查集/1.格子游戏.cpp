// 如果遍历到的两个点已经属于同一个集合了，就说明形成环了

// 代码细节
// 并查集由于是一维索引，因此把二维坐标转为一维坐标，更便于实现
// 最简单的方式：对于(x,y)从(0,0)开始，一维坐标为x*n+y
// 如果从(1,1)开始，则f({x,y})=x*n+y这个映射不能一一对应
// 但这只是映射问题，可视为简单hash，保证映射唯一即可

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 40010;

int n, m;
int p[N];

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int get(int x, int y) {
    return x * n + y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n * n; i++) {
        p[i] = i;
    }

    int res = 0;
    for (int i = 1; i <= m; i++) {
        int x, y;
        char d;
        cin >> x >> y >> d;

        // 获取二维坐标对应的一维坐标
        // 其实可以看作是映射，只要映射关系唯一即可
        // 对于部分边界问题，只要保证映射合法，就可以忽略，毕竟只是空间开销而已
        // 但对于当前问题，如果不处理边界，会导致映射不唯一
        x--, y--;
        int a = get(x, y);
        int b;
        if (d == 'D') {
            b = get(x + 1, y);
        } else {
            b = get(x, y + 1);
        }

        int pa = find(a), pb = find(b);
        if (pa == pb) {
            res = i;
            break;
        }
        p[pa] = pb;
    }

    if (!res) {
        cout << "draw" << endl;
    } else {
        cout << res << endl;
    }

    return 0;
}
