// 数据量太大，需要离散化
// 离散化分为两种：
// 1.保序：排序+去重+二分
// 2.不要求保序：哈希表(写法更简单)
// 本题不要求保序

// 对于相等条件和不等条件，先判后判顺序不影响答案
// 这里选择先判相等，再判不等

// 本题是相当契合并查集的，相等的都在同一集合中
// 如果遍历到一个不等关系，说集合里有两个元素不等，那就矛盾了，整个集合就废了
// 这也是为什么要先判相等再判不等，否则得不到正确结果

#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 2000010;

struct Query {
    int x, y, e;
} query[N];

int n, m;
int p[N];
unordered_map<int, int> S;

// 求x的离散化值
int get(int x) {
    if (!S.count(x)) {
        S[x] = ++n;
    }
    return S[x];
}

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        n = 0;  // 离散化元素个数，用来给离散化元素编号
        cin >> m;
        for (int i = 0; i < m; i++) {
            int x, y, e;
            cin >> x >> y >> e;
            query[i] = {get(x), get(y), e};
        }

        for (int i = 1; i <= n; i++) {
            p[i] = i;
        }

        // 合并所有相等约束条件
        for (int i = 0; i < m; i++) {
            if (query[i].e == 1) {
                int pa = find(query[i].x), pb = find(query[i].y);
                if (pa != pb) {
                    p[pa] = pb;
                }
            }
        }

        // 检查所有不等约束条件是否矛盾
        bool has_conflict = false;
        for (int i = 0; i < m; i++) {
            if (query[i].e == 0) {
                int pa = find(query[i].x), pb = find(query[i].y);
                if (pa == pb) {
                    has_conflict = true;
                    break;
                }
            }
        }

        if (has_conflict) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
