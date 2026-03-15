// 加成序列x共m个数，下标从1开始，其中x[1]=1, x[m]=n
// x序列严格单调递增
// 对于除了x[1]外的所有x[k]，都有x[i]+x[j]=x[k], 其中i,j<k，但i,j可相同
// 因此可以立刻推得x[2]=2, x[3]=3/4

// 首先，画一下本题的搜索树. n上限为100
// 在最好的情况下，1,2,4,8,...，64,n
// 在最坏的情况下，会构造出1,2,3,...98,99,n
// 100层，那很恐怖了；但能感性地感觉到，答案应该在较浅的位置

// 剪枝
// 1.优化搜索顺序
// 首先，明确本题的搜索顺序是什么——枚举x每个位置的数字
// x[1]和x[2]已经固定了，接下来枚举x[3]，然后是x[4]，直到x[m-1]，最后是x[m]
// 画搜索树，怎样可以使得扩展的结点更少？
// 往更大的数靠拢，更快地“逼近n”，即上面说的1,2,4,8...
// 枚举到8时，再扩展，儿子只有C42+4个；如果走的是1,2,3,4...，枚举到8时，儿子就有C82+8个了(不考虑可行性)
// 2.排除等效冗余
// 以上面说的儿子组合为例，这些儿子的任意两个组合计算得到的和可能相同。只保留一种情况即可
// 做法：对于所有可能的答案，建立bool数组；被找到一次后就标记，不再搜索第二次
// 3.可行性剪枝
// 1.Cx2+x个儿子中，x部分存在不可行解(不满足严格单调递增)
// 2.儿子之和大于n

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n;
int path[N];

bool dfs(int u, int depth) {
    // 迭代加深限制
    if (u > depth) {
        return false;
    }
    // 出口判断
    if (path[u - 1] == n) {
        return true;
    }

    // 每个栈帧都需要一个独立的st数组，来标记当前层的儿子组合是否被搜索过了
    bool st[N] = {0};
    // 别忘从大到小枚举
    for (int i = u - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            int s = path[i] + path[j];
            if (s > n || s <= path[u - 1]) {
                continue;
            }
            if (st[s]) {
                continue;
            }

            st[s] = true;
            path[u] = s;
            // 别忘了，有返回值的dfs，需要维护传递链
            if (dfs(u + 1, depth)) {
                return true;
            }
            // path不必回退，等待覆盖即可
            // st不是全局属性，不需要恢复；用过的不会再用了
        }
    }
    
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    path[0] = 1;
    while (cin >> n, n) {
        // 开始迭代加深，枚举深度
        int depth = 1;
        while (!dfs(1, depth)) {
            depth++;
        }

        // 输出答案
        // 此时depth依然有用——表示搜索层数，也就是路径长度
        for (int i = 0; i < depth; i++) {
            cout << path[i] << ' ';
        }
    }

    return 0;
}
