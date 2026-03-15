// 分组，每组内数字两两互质，求最小组数
// 套暴搜思路模板

// 但这个题比较复杂，有必要讲解一下
// 根据思维关惯性，很容易把数视为“点”
// “点”：组，但出口判断是数是否分完
// 扩展：枚举这个组里可以放哪些数
// 如果一个数能加入组，那就没必要开新组，否则一定会偏离最优解(基于贪心的最优性剪枝)
// 如果一个组无法再放数，那就必须新开一组，这是没得商量的
// 所以，代码中用flag约束了开新组的条件

// 本题难点在于把组视为“点”，导致代码逻辑与常规模板有差异
// 但是，决定出口判断的依然是数
// 每个组从头遍历所有的数，能放则放，放不了后，开新组；直到所有数分完，然后递归回去再找更优解
// 这是经典的决策树问题，模板中只是介绍了最直观的一种决策

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int p[N];
int group[N][N];  // group[i]存第i组的数
bool st[N];
int ans = N;

// 判断a和b是否互质
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

bool check(int g[], int gc, int i) {
    // 判断p[i]和g[0, gc)的数是否两两互质
    for (int j = 0; j < gc; j++) {
        if (gcd(p[g[j]], p[i]) > 1) {
            return false;
        }
    }
    return true;
}

// g：枚举到第g组
// gc(group count)：当前第g组已经有gc个数了
// tc(total count)：已经分了多少个数了
// start：当前已经用过的数的个数，后续枚举时只需要枚举[start, u)的数即可(排除等效冗余)
void dfs(int g, int gc, int tc, int start) {
    if (g >= ans) {
        return;
    }
    if (tc == n) {
        ans = g;
        return;
    }

    bool flag = false;  // 标记当前组g是否可以添加元素
    // start之前的都已经被分组了，没有再枚举的意义
    for (int i = start; i < n; i++) {
        if (!st[i] && check(group[g], gc, i)) {
            st[i] = true;
            group[g][gc] = p[i];
            dfs(g, gc + 1, tc + 1, i + 1);
            st[i] = false;

            flag = true;  // 只要有儿子，就会进来
        }
    }

    // 当前组无法再添加元素了，需要新开一组
    // 新开一组的话，需要从头开始枚举
    // 因为0~tc-1的数，有的被分到g组了，有的还没有
    // 需要从0开始，看看这些数能否分到g+1组里去
    if (!flag) {
        dfs(g + 1, 0, tc, 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    // 从第1组开始
    dfs(1, 0, 0, 0);

    cout << ans << endl;

    return 0;
}
