// 1. 记忆化搜索dps，TLE了一个点
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1005

int n;
vector<vector<int>> nums(MAXN, vector<int>(MAXN, 0)); // 二维数组
vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0));   // 从第x行第y列开始的最大路径和

int dfs(int x, int y)
{
    if (x > n)
        return 0;
    if (dp[x][y])
        return dp[x][y];

    int sum = max(dfs(x + 1, y), dfs(x + 1, y + 1)) + nums[x][y];

    dp[x][y] = sum;
    return sum;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> nums[i][j];

    cout << dfs(1, 1);
    return 0;
}


// 2. 顺序递推，AC
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1005

int n;
vector<vector<int>> nums(MAXN, vector<int>(MAXN, 0)); // 二维数组
vector<vector<int>> f(MAXN, vector<int>(MAXN, 0));    // 从起点到第x行第y列的最大路径和

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> nums[i][j];

    f[1][1] = nums[1][1];
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + nums[i][j];

    // 注意下面这个多个数取最值的写法
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[n][i]);
    cout << ans;
    return 0;
}


// 3. 逆序递推，AC
// 注意起点、递推公式、递推数组
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1005

int n;
vector<vector<int>> nums(MAXN, vector<int>(MAXN, 0)); // 二维数组
vector<vector<int>> f(MAXN, vector<int>(MAXN, 0));    // 从第x行第y列开始的最大路径和

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            cin >> nums[i][j];

    for (int i = 1; i <= n; i++)
        f[n][i] = nums[n][i];

    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            f[i][j] = max(f[i + 1][j], f[i + 1][j + 1]) + nums[i][j];

    cout << f[1][1];
    return 0;
}



// 小小总结一下题感
// 1dfs > 2记忆化搜索 > 3逆序递推 > 4顺序递推 > 5优化空间
// 其中主要做的步骤是12和4
// 12的状态数组命名为dp，4的状态数组命名为f
// dp和f的含义可以互补的。一般来说，dp表示i到终点的最优解，f表示起点到i的最优解。但这一点不是绝对的，可以根据题目的特点来调整
// 所谓顺序递推，就是说出发方向和12是相同的。通过递推数组和递推公式的微调，来克服递推与递归的相反性
// dp和f数组的维度取决于映射条件的数目，数组维度决定了递推遍历的循环数目

// 而逆序递推中，起点与12是相反的，但递推数组和递推公式完全相同



/*
再加深下对递归、顺序递推、逆序递推的理解
下面阐述的是一般模型：
1. dp数组
递归、逆序递推：i - n
顺序递推：1 - i

2. 状态转移公式
递归与逆序递推相同
顺序递推与它们有变动

3. 起点与出口
递归：起点和出口都是1
顺序递推：起点是1，出口是n
逆序递推：起点是n，出口是1

4. 感性认识
递归中，归回来的过程，就是逆序递推的过程
因此 逆序递推的基准情况是dp[n]/dp[n+1](起点是n-1/n)
dp的含义是i-n。因此dp[n]是很容易得出来的基准情况，层层递推到dp[1]，即出口
逆序递推的递推公式中，由于是倒序，因此靠前的元素是靠后的元素的递推结果

而顺序递推中，基准情况是dp[1]/dp[0](起点是2/1)
dp的含义是1-i。因此dp[1]是很容易得出来的基准情况，层层递推到dp[n]，即出口
靠后的元素是靠前的元素的递推结果
*/