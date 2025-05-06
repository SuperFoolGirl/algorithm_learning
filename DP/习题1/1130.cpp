// 初学感叹：写dp犹如魔法一般，莫名其妙就写出来了。。
// 1. 递归写法
#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

#define maxn 2010

vector<vector<int>> dp(maxn,
                       vector<int>(maxn, 0));   // dp[i][j]代表 处于第i组第j步时
                                                // 完成后续步骤所需要的最少天数(i-n，这个题的dp是符合我的刻板印象的)
vector<vector<int>> Date(maxn, vector<int>(maxn, 0));
int n, m;

int dfs(int group, int step) {
    if (step > n) {
        return 0;
    }
    if (dp[group][step]) {
        return dp[group][step];
    }

    return dp[group][step] =
               min(dfs(group, step + 1) + Date[group][step], dfs(group % m + 1, step + 1) + Date[group % m + 1][step]);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> Date[i][j];
        }
    }

    // 不需要dp.clear()
    int ans = 0x7fffffff;
    for (int i = 1; i <= m; i++) {
        ans = min(ans, dfs(i, 1));
    }
    cout << ans;

    return 0;
}

// 2. 顺序递推
#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

#define maxn 2010

vector<vector<int>> dp(maxn, vector<int>(maxn, 0));   // dp[i][j]代表 处于第i组第j步时 所需要的最少天数(0-i)
vector<vector<int>> Date(maxn, vector<int>(maxn, 0));
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> Date[i][j];
        }
    }

    // 初始化边界条件
    // 这个条件不太好想。总之 千万别自以为边界条件就是0
    // 对于每一组的第一步，所需的最少天数就是该组第一步的天数
    for (int i = 1; i <= m; i++) {
        dp[i][1] = Date[i][1];
    }

    // 搞清楚 在这个题里 步数才是最外层循环，即决定顺序逆序的根本
    // 步数从2开始，因为递推边界条件是1
    // 已经被计算出来的值只会用于后续递推，不会再被更改
    for (int j = 2; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            dp[i][j] = min(dp[(i - 2 + m) % m + 1][j - 1], dp[i][j - 1]) + Date[i][j];   // 最难的点在于这个模运算
        }
    }

    // dfs写法中 dfs跑了个for循环
    // 对应的方法是，dp也跑了个for循环找答案
    int ans = 0x7fffffff;
    for (int i = 1; i <= m; i++) {
        ans = min(ans, dp[i][n]);
    }

    cout << ans;
    return 0;
}

/*
模运算的思路：
1. 初始思路
如果不考虑组号从 1 开始以及循环的情况，单纯计算上一组号，很自然地会想到用上当前组号 i 减去 1，即 i -
1。但在本题中，组号是从 1 开始的，并且要处理循环的情况，直接使用 i - 1 会出现问题。
2. 转换为从 0 开始编号
为了方便使用取模运算处理循环情况，我们先把组号从 1 到 m 的编号转换为从 0 到 m - 1 的编号。这只需要将当前组号 i 减去 1
即可，转换后的组号为 i - 1。
3. 计算上一组的编号（从 0 开始）
在转换后的编号系统中，计算上一组的编号就可以用 (i - 1) - 1，也就是 i - 2。不过，当 i = 1 时，i - 2 的结果是
-1，这不符合我们从 0 到 m - 1 的编号范围。为了保证结果在合法范围内，我们可以加上 m 再对 m 取模，即 (i - 2 + m) %
m。这样做的原理是：加上 m
不会改变结果的本质，因为在取模运算中，一个数加上或减去模数的整数倍，结果不变；而取模运算会把结果限制在 0 到 m - 1
的范围内。
4. 转换回从 1 开始编号
最后，我们要把从 0 到 m - 1 的编号再转换回从 1 到 m 的编号，只需要在结果上加上 1 就行，所以最终得到的表达式就是 (i - 2 +
m) % m + 1。
*/

// 3. 逆序递推
#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

#define maxn 2010

vector<vector<int>> dp(maxn, vector<int>(maxn, 0));   // dp[i][j]代表 处于第i组第j步 后续步骤所需要的最少天数(i-n)
vector<vector<int>> Date(maxn, vector<int>(maxn, 0));
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> Date[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        dp[i][n] = Date[i][n];           // 走到这里就只有一步了,后续天数是确定的
    }

    for (int j = n - 1; j >= 1; j--) {   // 逆序
        for (int i = 1; i <= m; i++) {
            dp[i][j] = min(dp[i][j + 1], dp[(i % m) + 1][j + 1]) + Date[i][j];
        }
    }

    int ans = 0x7fffffff;
    for (int i = 1; i <= m; i++) {
        ans = min(ans, dp[i][1]);
    }

    cout << ans;
    return 0;
}
