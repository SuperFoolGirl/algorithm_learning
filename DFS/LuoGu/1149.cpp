// 第一次抄的题解答案
// 一共三个位置，每个位置枚举不同的数字
#include <iostream>
using namespace std;

int num[1111] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, opt[3] = {0};
int n, ans = 0;

void dfs(int x)
{
    for (int i = 0; i <= 1111; i++)
    {
        if (n - num[i] >= 0)
        {
            opt[x] = i;
            n -= num[i];
            if (x == 2)
            {
                if (opt[0] + opt[1] == opt[2] && n == 0)
                {
                    ans++;
                    // return; 这里不要习惯性return 还要执行下面的返还 把dfs给else掉很巧妙
                    // 因为这次的dfs依然是选择了一个数 而不是另起了一个新dfs 所以需要本次就复原
                }
            }
            else
                dfs(x + 1);
            n += num[i];
        }
    }
}
int main()
{
    cin >> n;
    n -= 4;
    // 这里求出所有的火柴数 很巧妙
    for (int i = 10; i <= 1111; i++)
        num[i] = num[i / 10] + num[i % 10];
    dfs(0);
    cout << ans;
    return 0;
}