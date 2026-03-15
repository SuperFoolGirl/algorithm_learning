// 和上一题类似
// 暴搜思路参考“搜索顺序”
// 枚举每只小猫(通过dfs参数来推进枚举)
// 枚举当前小猫放到哪个车上(dfs内扩展)
// 要么把猫放到已有的车上，要么新开一辆车

// 下面考虑如何剪枝
// 1. 优化搜索顺序
// 轻的猫和重的猫，显然把重的猫放前面好，这样会增强“车的不可选性”，从而减少分支
// 因此，先对猫排序，优先枚举重猫
// 2. 排除等效冗余
// 本就没有重复情况，略
// 3. 可行性剪枝
// 如果一只猫放上来时已经超重，直接砍掉
// 4. 最优性剪枝
// 如果当前方案的车已经大于ans了，直接砍掉
// 5. 记忆化搜索
// 无

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n, m;
int w[N];
int sum[N];
int ans = N;  // min初始化

void dfs(int u, int k) {
    // 最优性剪枝
    if (k >= ans) {
        return;
    }

    // 出口
    if (u == n) {
        // 经过上方的最优性剪枝，k一定是更优解了
        ans = k;
        return;
    }

    // 枚举当前猫放到哪个车上，当前共k辆
    for (int i = 0; i < k; i++) {
        // 可行性剪枝
        if (sum[i] + w[u] <= m) {
            sum[i] += w[u];
            dfs(u + 1, k);
            // 恢复现场
            sum[i] -= w[u];
        }
    }
    // 新车
    sum[k] += w[u];
    dfs(u + 1, k + 1);
    sum[k] -= w[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    sort(w, w + n, greater<int>());

    dfs(0, 0);

    cout << ans << endl;

    return 0;
}
