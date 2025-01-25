// 视频题解
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

int num[2][4];
unordered_map<string, int> dist;               // 记录到达每个状态的步数
unordered_map<string, pair<char, string>> pre; // 存从哪个状态来的，以及操作串
queue<string> q;

void set1(string s) // 把字符串写成二维数组
{
    for (int i = 0; i < 4; i++)
        num[0][i] = s[i] - '0';
    for (int i = 3, j = 4; i >= 0; i--, j++)
        num[1][i] = s[j] - '0';
}

string get1() // 把二维数组写成字符串
{
    string res;
    for (int i = 0; i < 4; i++)
        res += to_string(num[0][i]);
    for (int i = 3; i >= 0; i--)
        res += to_string(num[1][i]);
    return res;
}

string move0(string s) // A操作
{
    set1(s);
    for (int i = 0; i < 4; i++)
        swap(num[0][i], num[1][i]);
    return get1();
}

string move1(string s)
{
    set1(s);
    // 把最后一列存起来，然后其他位置都往后一位
    char v0 = num[0][3];
    char v1 = num[1][3];

    for (int i = 3; i > 0; i--)
        for (int j = 0; j < 2; j++)
            num[j][i] = num[j][i - 1];
    num[0][0] = v0;
    num[1][0] = v1;
    return get1();
}

string move2(string s)
{
    set1(s);
    char v = num[0][1];
    num[0][1] = num[1][1];
    num[1][1] = num[1][2];
    num[1][2] = num[0][2];
    num[0][2] = v;
    return get1();
}

int bfs(string start, string end)
{
    q.push(start);
    dist[start] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        if (t == end)
            return dist[t];

        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);

        for (int i = 0; i < 3; i++)
        {
            string s = m[i];
            if (!dist.count(s))
            {
                dist[s] = dist[t] + 1;
                pre[s] = {i + 'A', t};
                q.push(s);
            }
        }
    }
    return -1;
}

int main()
{
    int x;
    string start, End;
    start = "12345678";
    for (int i = 1; i <= 8; i++)
    {
        cin >> x;
        End += to_string(x);
    }
    cout << bfs(start, End) << endl;

    string res;
    // End通过second一直回溯到start，这样一来操作串就是逆序的
    while (End != start)
    {
        res += pre[End].first;
        End = pre[End].second;
    }
    reverse(res.begin(), res.end());
    cout << res << endl;
    return 0;
}

// 自己实现
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

struct node
{
    string status;
    string ans;
};

node Start = {"12345678", ""}; // 初始状态按顺时针遍历排列
string End;
queue<node> q1;
unordered_map<string, int> vis; // 记录已访问状态
// 原本我存了个哈希表用来记录每个状态的操作串，但其实没必要
// 哈希表的作用是索引，我们并不总是需要索引这个属性
// 当需要取操作串的时候，也只是对队首进行操作，直接访问结构体就可以了

void bfs()
{
    q1.push(Start);
    vis[Start.status] = 1;

    while (!q1.empty())
    {
        auto t = q1.front();
        q1.pop();

        if (t.status == End)
        {
            cout << t.ans.size() << endl;
            cout << t.ans << endl;
            return;
        }

        // 学习这种遍历写法
        for (char op : {'A', 'B', 'C'})
        {
            string new_status;
            if (op == 'A')
            {
                new_status = t.status;
                reverse(new_status.begin(), new_status.end());
            }
            else if (op == 'B')
                new_status = t.status[3] + t.status.substr(0, 3) + t.status.substr(5, 3) + t.status[4];
            else
                new_status = string(1, t.status[0]) + t.status[6] + t.status[1] + t.status[3] + t.status[4] + t.status[2] + t.status[5] + t.status[7];

            if (!vis.count(new_status))
            {
                vis[new_status] = 1;
                q1.push({new_status, t.ans + op});
            }
        }
    }
}

int main()
{
    int num;
    for (int i = 0; i < 8; i++)
    {
        cin >> num;
        End += char(num + '0');
    }
    bfs();
    return 0;
}