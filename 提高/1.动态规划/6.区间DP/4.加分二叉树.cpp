// 区间DP记录方案数
// 已知中序遍历是(1,2,3...)，因此可以用区间dp

// 状态表示 f(i,j)
// 集合：所有中序遍历是[l,r]这一段的二叉树
// 属性：max
// 状态计算
// 对于f(l,r)，找到最后一个不同点
// 划分依据：根结点所在位置，可以在l,l+1,...,r-1,r
// 因此根结点可以在k，k∈[l,r]
// 分析对应的二叉树结构：
// 根结点为k时，左子树的部分是[l,k-1]，右子树的部分是[k+1,r]
// 数据结构登场——树是递归定义的
// f(l,r) = max{ f(l,k-1) * f(k+1,r) + w[k] }

// 下面考虑记录方案数问题
// 和背包问题类似，开数组g[l][r]，记录转移过程
// 对于树来说，可以用g[l][r]记录中序遍历为[l,r]的二叉树的根结点位置k
// 然后就能通过g递归地构造出整棵树了

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 30;

int n;
int w[N];
int f[N][N], g[N][N];

void dfs(int l, int r) {
    if (l > r) {
        return;
    }

    int root = g[l][r];

    // 前序遍历代码：输出+递归左+递归右
    cout << root << " ";
    dfs(l, root - 1);
    dfs(root + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (len == 1) {
                f[l][r] = w[l];
                // 叶子结点，根结点为自己
                g[l][r] = l;
            } else {
                // 枚举根结点位置k
                for (int k = l; k <= r; k++) {
                    // 如果k=l即根结点为l，则无左子树，权值为1
                    int left = k == l ? 1 : f[l][k - 1];
                    int right = k == r ? 1 : f[k + 1][r];
                    int score = left * right + w[k];
                    // 输出最小字典序答案
                    if (score > f[l][r]) {
                        f[l][r] = score;
                        g[l][r] = k;
                    }
                }
            }
        }
    }

    // 输出最大值
    cout << f[1][n] << endl;

    // 输出方案(整棵树)
    // 根据题意，输出树的方式是，输出其前序遍历
    // 这样，前序+已知的中序就能构建出唯一树了
    dfs(1, n);

    return 0;
}
