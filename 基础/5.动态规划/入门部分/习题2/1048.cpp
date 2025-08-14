#include <iostream>
#include <vector>
#include <algorithm>
#define maxn 110
using namespace std;

int T, M;
vector<int> drag(maxn, 0);
vector<int> value(maxn, 0);
vector<int> dp(1010, 0);

int main()
{
    cin >> T >> M;
    for (int i = 1; i <= M; i++)
        cin >> drag[i] >> value[i];

    // 隐含dp[0] = 0：背包容量为0的情况下，价值只能为0
    for (int i = 1; i <= M; i++)
        for (int j = T; j >= drag[i]; j--)
            dp[j] = max(dp[j], dp[j - drag[i]] + value[i]);

    cout << dp[T] << endl;
    return 0;
}