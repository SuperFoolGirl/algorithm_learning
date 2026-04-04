// 本题是带权并查集
// 维护d[x]记录x到其所在集合的根结点的距离
// find函数会更新d[x]，使得d[x]始终保持正确
// 若a和b在同一集合中，则a与b之间的距离为|d[a]-d[b]|

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 30010;

int m;
int p[N], d[N], sz[N];

// 注意，在带权并查集中，find要微调
// x加入集合后，下一次调用find再经过它时，它才会进行路径压缩
// 这样思考：x一开始加入的集合是S，但后来S被合并到T中了
// 在压缩之前，p[x]是S的根结点，并不是T中的根结点
// 因此，d[x]记录的是x到S根的距离，而不是x到T根的距离
// 而d[p[x]]由于合并到T中，记录的是S根到T根的距离(在合并集合时手动更新的)
// 那么x到T根的距离应该是：x->S根+S根->T根
// 所以，d[x]+=d[p[x]]，更新d[x]为x到T中根结点的距离
// 当然，上述过程严格来说应该递归考虑，这条路径上的每个未更新的点都会被更新
int find(int x) {
    if (p[x] != x) {
        int root = find(p[x]);  // 先找到根结点
        d[x] += d[p[x]];
        p[x] = root;        // 路径压缩
    }
    return p[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m;
    for (int i = 1; i <= N; i++) {
        // 每个元素都作为集合的根结点，因此d不用动，默认为0
        p[i] = i;
        sz[i] = 1;
    }

    while (m--) {
        char op[2];
        int a, b;
        cin >> op >> a >> b;
        int pa = find(a), pb = find(b);
        if (op[0] == 'M') {
            d[pa] = sz[pb];    // pa所在集合的根结点是pb，因此pa到pb的距离就是pb所在集合的大小
            sz[pb] += sz[pa];
            p[pa] = pb;        // 合并集合
        } else {
            if (pa != pb) {
                cout << "-1\n";
            } else {
                cout << max(0, abs(d[a] - d[b]) - 1) << "\n";    // a和b在同一集合中，输出它们之间的距离
            }
        }
    }
}
