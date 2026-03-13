// 最小步数模型的特点是数据量大，状态转移复杂

// 类似八数码问题
// 将本题状态转移的过程可以视为一个图，从初状态开始扩散，边权都为1，直到找到目标状态为止
// 说是“状态转移”，不过本题是以出边为转移路径去思考的，而非动态规划的入边递推
// 一看，同边权求最短路，第一反应就是bfs了
// 状态表示方面，可以用哈希

#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

char g[2][4];
unordered_map<string, int> dist;
// 本题需要输出转移路径，需要记录前驱状态
// char记录转移方式，string记录具体转移状态
unordered_map<string, pair<char, string>> pre;
queue<string> q;

// 把2*4魔版变成顺时针的字符串
string get() {
    string res;
    for (int i = 0; i < 4; i++) {
        res += g[0][i];
    }
    for (int i = 3; i >= 0; i--) {
        res += g[1][i];
    }
    return res;
}

// 把字符串按顺时针顺序转回2*4魔版
void set(string s) {
    for (int i = 0; i < 4; i++) {
        g[0][i] = s[i];
    }
    // 这里用双循环变量处理，更直观
    for (int i = 3, j = 4; i >= 0; i--, j++) {
        g[1][i] = s[j];
    }
}

string move0(string s) {
    set(s);

    for (int i = 0; i < 4; i++) {
        swap(g[0][i], g[1][i]);
    }

    return get();
}

string move1(string s) {
    set(s);

    // 缓存，挨个蠕动，最后填坑
    char v0 = g[0][3], v1 = g[1][3];
    for (int i = 3; i > 0; i--) {
        g[0][i] = g[0][i - 1];
        g[1][i] = g[1][i - 1];
    }
    g[0][0] = v0, g[1][0] = v1;

    return get();
}

string move2(string s) {
    set(s);

    // 方法同move1
    char v = g[0][1];
    g[0][1] = g[1][1];
    g[1][1] = g[1][2];
    g[1][2] = g[0][2];
    g[0][2] = v;

    return get();
}

void bfs(string start, string end) {
    // 特判
    if (start == end) {
        return;
    }

    q.push(start);
    dist[start] = 0;

    // 哈希表dist不用memset来起到防止重复访问，直接count()

    while (!q.empty()) {
        string t = q.front();
        q.pop();

        // 进行三次扩展
        string m[3];
        m[0] = move0(t);
        m[1] = move1(t);
        m[2] = move2(t);

        // 入队判断，为了避免重复代码，写成循环
        for (int i = 0; i < 3; i++) {
            // 重复访问判断
            if (dist.count(m[i])) {
                continue;
            }

            dist[m[i]] = dist[t] + 1;
            pre[m[i]] = {i + 'A', t};

            // 终点判断
            // 数据更新要写在终点判断前，因为终点也需要这些数据
            // 若不是终点，再push
            if (m[i] == end) {
                return;
            }
            q.push(m[i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int x;
    string start, end;
    for (int i = 1; i <= 8; i++) {
        cin >> x;
        start += i + '0';
        end += x + '0';
    }

    bfs(start, end);

    cout << dist[end] << endl;

    // 反向构建路径
    string res;
    while (end != start) {
        res += pre[end].first;
        end = pre[end].second;
    }
    reverse(res.begin(), res.end());
    if (res.size() > 0) {
        cout << res << endl;
    }

    return 0;
}
