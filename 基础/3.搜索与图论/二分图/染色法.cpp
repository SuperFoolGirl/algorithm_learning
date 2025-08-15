// 对于一个连通块，如果可以用两种颜色染色，使得相邻的点颜色不同，则这个连通块是二分图
// 第一个点确定了颜色，整个连通块的点就都确定了
// 如果在染色过程中发现有相邻的点颜色相同，则说明不是二分图

// 这里要用到染色/连通块相关算法了
// main函数中遍历所有的点，如果没有被染色，就调用dfs
// 在dfs中，连通块内所有点都会被染色

// 适用于无向图

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int color[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 模拟一下递归的函数堆栈
// 结合递归树，还是一个类似前序遍历的过程：把dfs里的for循环看作是二叉树的两个儿子，只不过这里有多个儿子
// 所以就是先访问根节点，然后从左到右地访问儿子
// 一直从第一个儿子找，直到遇到叶子节点，标好颜色后直接返回true
bool dfs(int u, int c) {
    // 记录当前父节点颜色
    color[u] = c;

    // 遍历u的所有儿子，他们颜色与u必然相反
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];

        // 不能把图完全按二叉树来考虑，对于普通的图，一个节点可能有两个父节点，两个父节点可能共用一个儿子
        if (color[j] == 0) { // 如果未染色
            if (!dfs(j, 3 - c)) { // 颜色只有1，2。注意3-c这个写法，很巧妙
                return false;
            }
        } else { // 如果已染色，判断矛盾
            if (color[j] == c) { // 如果儿子和老爸相同，矛盾
                return false;
            }
        }
    }

    return true;
}

int main() {
    cin >> n >> m;

    memset(h, -1, sizeof h);

    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);    // 无向图加两次
    }

    // 遍历所有点
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) { // 如果dfs返回false，说明有矛盾发生
                flag = false;
                break;
            }
        }
    }

    if (flag) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
