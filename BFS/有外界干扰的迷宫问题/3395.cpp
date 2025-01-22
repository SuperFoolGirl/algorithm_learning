#include <iostream>
#include <queue>
#include <cstring>
#define maxn 1010
using namespace std;

int t, n;
queue<pair<int, int>> q;
int dist[maxn][maxn];
pair<int, int> obstacle[2 * maxn];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool bfs(int x, int y)
{
    while (!q.empty())
        q.pop();

    q.push({x, y});
    dist[x][y] = 0;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i];
            int b = t.second + dy[i];

            if (a < 1 || a > n || b < 1 || b > n)
                continue;
            if (dist[a][b] != -1)
                continue;

            int now = dist[t.first][t.second];
            dist[a][b] = now + 1;
            q.push({a, b});

            if (now < 2 * n - 2)
                dist[obstacle[now].first][obstacle[now].second] = now;

            if (a == n && b == n)
                return true;
        }
    }
    return false;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        if (n == 1) // 特判
        {
            cout << "Yes" << endl;
            continue;
        }
        memset(dist, -1, sizeof dist);
        memset(obstacle, 0x3f, sizeof obstacle);
        // 这个数组创建得挺巧妙 pair的用法就是在刷题过程中练出来的
        for (int i = 0; i < 2 * n - 2; i++)
            cin >> obstacle[i].first >> obstacle[i].second;
        bfs(1, 1) ? cout << "Yes" : cout << "No";
        cout << endl;
    }
    return 0;
}