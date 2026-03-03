// 一个精灵只能被捉一次，因此对应01背包问题
// 01背包母题包括体积、价值
// 其中，体积称之为花费，价值即为价值
// 01背包问题是一维花费问题，本题涉及多个花费指标
// 寻找花费和价值，直接看题目。题目问什么，什么就是价值，也就是属性值
// 花费1：精灵球数量
// 花费2：皮卡丘体力值
// 价值：捕捉到的小精灵数量
// 本题的价值有两个字段，且第二字段与花费挂钩，这个单独处理即可，无需多虑

// 状态表示 f(i,j,k)
// 集合：表示从前i个物品中选，花费1不超过j，且花费2不超过k的选法集合
// 属性：最值
// 状态计算：枚举第i个物品选或不选两种情况
// f(i,j,k) = max{f(i-1,j,k), f(i-1,j-v1[i], k-v2[i]) + w[i]}
// 最终取f(k,n,m)为答案；然后考察f(k,n,0~m-1)是否有与f(k,n,m)相同的值，如果有，则说明存在花费2更小的选法，更新答案(但f(k,n,m)一定是最大结果)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, M = 510;

int n, V1, V2;
int f[N][M];  // 依旧是将i这一维降掉了，只保留花费维度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> V1 >> V2 >> n;
    // 最外层降维掉了，i从1开始还是0开始无妨，无需考虑i-1影响
    for (int i = 0; i < n; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        for (int j = V1; j >= v1; j--) {
            for (int k = V2; k >= v2; k--) {
                f[j][k] = max(f[j][k], f[j - v1][k - v2] + 1);
            }
        }
    }

    cout << f[V1][V2] << endl;

    // 寻找花费2更小的选法
    int k = V2;
    while (k > 0 && f[V1][k] == f[V1][V2]) {
        k--;
    }
    cout << V2 - k << endl;

    return 0;
}
