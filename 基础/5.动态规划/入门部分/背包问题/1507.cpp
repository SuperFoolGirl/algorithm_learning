// 二维费用背包问题
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> h(410, 0);
vector<int> t(410, 0);
vector<int> k(510, 0);
int H, T, n;
vector<vector<int>> dp(410, vector<int>(410, 0));

int main()
{
    cin >> H >> T;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i] >> t[i] >> k[i];

    for (int i = 1; i <= n; i++)
        for (int j = H; j >= h[i]; j--)
            for (int l = T; l >= t[i]; l--)
                dp[j][l] = max(dp[j][l], dp[j - h[i]][l - t[i]] + k[i]);

    cout << dp[H][T];
    return 0;
}