#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define maxn 30

int n;
string words[maxn];      // 二维数组
int used[maxn];          // 记录每个单词使用次数
int overlap[maxn][maxn]; // 存第i个单词与第j的单词重叠的长度
int ans = 0;

void dfs(string dragon, int idx)
{
    ans = max(ans, (int)dragon.size());
    used[idx]++;
    for (int i = 0; i < n; i++)
    {
        if (overlap[idx][i] && used[i] < 2)
            // substr单参数形式：从参数1下标起始到结尾
            dfs(dragon + words[i].substr(overlap[idx][i]), i);
    }
    // 体会一下这个回溯位置
    used[idx]--;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> words[i];
    char start;
    cin >> start;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string a = words[i];
            string b = words[j];
            // k用来枚举重合长度。不能从0开始，因为不能包含
            // 从a的第最后一位开始，与b的第一位开始比较，一直比较到a的第二位
            for (int k = 1; k < min(a.size(), b.size()); k++)
            {
                // substr:参数1--起始位置，参数2--取字符数目
                if (a.substr(a.size() - k, k) == b.substr(0, k))
                {
                    overlap[i][j] = k;
                    break; // 重合长度越短越好，这样才能使最后的龙更长，所以尽可能提前退出
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (words[i][0] == start) // 找起点
        {
            dfs(words[i], i); // 参数1--目前的龙 参数2--当前访问到哪个单词，以下标形式储存
        }
    }
    cout << ans;
    return 0;
}