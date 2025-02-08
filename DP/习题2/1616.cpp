#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t, m;
    vector<int> drag(10010, 0);
    vector<int> value(10010, 0);
    vector<long long> dp(10000010, 0); // 这都能爆

    cin >> t >> m;
    for (int i = 1; i <= m; i++)
        cin >> drag[i] >> value[i];

    for (int i = 1; i <= m; i++)
        for (int j = drag[i]; j <= t; j++)
            dp[j] = max(dp[j], dp[j - drag[i]] + value[i]);

    cout << dp[t] << endl;
    return 0;
}