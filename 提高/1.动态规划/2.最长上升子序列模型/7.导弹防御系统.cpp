// 题目分析
// 和上一题一样，求LIS的最小个数
// 区别在于，本题既可以选择上升子序列，也可以选择下降子序列；单套系统必须保持一个方向的单调性

// 思路
// 由于多了一种选择，因此需要引入DFS来进行指数枚举
// 上一题中，g用来维护下降子序列的结尾，每个元素有两种情况
// 本题中，每个元素的两个情况前，又加了一重选择：上升还是下降
// 上一题中，对于两种情况，我们通过贪心对搜索进行了优化；本题中新加入的一重选择，找不到更好的方式，那就暴力搜索，即DFS
// 选择只有两个，DFS的开销为2^n，贪心算法开销为nlogn，整体开销为nlogn*2^n，考虑到n<=50，还是可以接受的

// 补充1
// DP是图论的子集，是对搜索的一种优化
// 如果DP无法解决问题，那就要靠暴搜了

// 补充2：DFS求最小步数问题
// 在搜索中，DFS用得更多；BFS缺点如下：
// 1. 空间占用大，存储的数据是指数级别的
// 2. 不容易剪枝，DFS一剪就是一棵子树
// BFS相比DFS，本身就有“最小”的天然性质，因此DFS求最小值时需要借助一些间接的方式
// 1. 全局变量记录最小值，在DFS过程中不断更新
// 2. 迭代加深

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 50;

int n;
int a[N];
int up[N], down[N];
int ans;

void dfs(int u, int su, int sd) {
    // 剪枝坏答案
    if (su + sd >= ans) {
        return;
    }

    // 递归出口
    if (u == n) {
        // 走到这里来说明坏答案已经剪枝掉了
        // 因此剪枝写法是：先写答案剪枝，再写出口剪枝
        ans = su + sd;
        return;
    }

    // 情况1：上升子序列
    int k = 0;
    while (k < su && a[u] <= up[k]) {
        k++;
    }

    // 深搜备份，用于恢复现场。恢复现场的目的是不破坏up数组，只在某条路中对up数组修改，回溯回来后要保证up数组不变，以免影响其他路的搜索
    int t = up[k];

    up[k] = a[u];
    if (k < su) {
        // a[u]可以插入到已有的上升子序列中
        dfs(u + 1, su, sd);
    } else {
        // a[u]独立成一个新的上升子序列
        dfs(u + 1, su + 1, sd);
    }

    // 恢复现场
    // 通过递归树来理解恢复现场的效果：
    // 层层回溯时，需要将这一层函数体执行完才会回去，因此一定会走到本行；逐层修改的up需要逐层恢复
    // 只要涉及回溯来更换路径，就需要恢复现场
    up[k] = t;

    // 情况2：下降子序列
    k = 0;
    while (k < sd && a[u] >= down[k]) {
        k++;
    }
    t = down[k];
    down[k] = a[u];
    if (k < sd) {
        dfs(u + 1, su, sd);
    } else {
        dfs(u + 1, su, sd + 1);
    }
    // 恢复现场
    down[k] = t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n, n) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // 最坏情况下，每个数单独作为一个序列
        ans = n;

        // 参数：当前枚举到的数；当前上升子序列个数；当前下降子序列个数
        dfs(0, 0, 0);

        cout << ans << endl;
    }

    return 0;
}
