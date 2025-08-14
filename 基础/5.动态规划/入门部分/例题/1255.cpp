// 本题展示了记忆化搜索
// 不过需要用到高精度才能拿满分 这里先略过了

#include <iostream>

int n;
int ans = 0;
int mem[6000] = {0};

int dfs(int x)
{
    if (mem[x]) // 记忆化搜索
        return mem[x];

    int sum = 0;
    if (x == 1)
        sum = 1; // 这里不要直接return 后面要执行记忆化，存储完后返回
    else if (x == 2)
        sum = 2;
    else
        sum = dfs(x - 1) + dfs(x - 2);

    mem[x] = sum; // 记忆化
    return sum;   // 回忆非void函数的递归返回值
}

int main()
{
    std::cin >> n;
    std::cout << dfs(n);
    return 0;
}



// 高精度写法
// 参考lanqiao的10425题处的高精度写法
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int N = 5010;

int n;
map<int, string> dp;

string add(string &a, string &b)
{
    vector<int> x;
    vector<int> y;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (auto c : a)
        x.push_back(c - '0');
    for (auto c : b)
        y.push_back(c - '0');

    // 反转要还原，以后还要用
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    // 高精度加高精度，要保证两个数的长度一致
    // 扩容为0，避免越界访问
    int longer = max(x.size(), y.size());
    x.resize(longer, 0);
    y.resize(longer, 0);

    int carry = 0;
    // 这里不需要另外开一个res数组，直接在x或y的基础上加就行
    for (int i = 0; i < longer; i++)
    {
        carry += x[i] + y[i];
        x[i] = carry % 10;
        carry /= 10;
    }
    if (carry)
        x.push_back(carry);

    string res;
    for (auto i : x)
        res.push_back(i + '0');
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    cin >> n;
    dp[1] = "1";
    dp[2] = "2";
    for (int i = 3; i <= n; i++)
        dp[i] = add(dp[i - 1], dp[i - 2]);
    cout << dp[n];
    return 0;
}