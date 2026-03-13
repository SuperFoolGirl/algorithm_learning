// 华容道

// 启发函数：
// 当前状态中每个数与它目标位置的曼哈顿距离之和
// 每个点都走到目标位置，才算结束
// 曼哈顿距离：|x1-x2| + |y1-y2|，多源BFS-矩阵距离

// 无解情况：
// 若序列逆序对个数为奇数，则无解
// 逆序对：对于一个数列，如果存在i < j且a[i] > a[j]，则称(a[i], a[j])是数列的一个逆序对
// 证明略

// 堆维护的状态：{启发函数值, string状态}

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>

#define x first
#define y second

using namespace std;

typedef pair<int, string> PIS;

// 启发函数
// i时state中的某个数字，i-1为其一维坐标
// 则二维坐标应该是 (i-1)/3,(i-1)%3
int f(string state) {
    int res = 0;
    for (int i = 0; i < 9; i++) {
        // x不是一个具体的数字，是一个空位
        // 其他数字放好了，x就自然空出来那个位置了
        if (state[i] != 'x') {
            int t = state[i] - '1';  // 当前数字的目标一维坐标
            // 计算曼哈顿距离
            // i是其实际一维坐标，t是其目标一维坐标
            res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    }
    return res;
}

string bfs(string start) {
    unordered_map<string, int> dist;
    unordered_map<string, pair<char, string>> pre;    // 记录前驱，状态+选择
    priority_queue<PIS, vector<PIS>, greater<PIS>> pq;
    string end = "12345678x";
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    char op[4] = {'u', 'r', 'd', 'l'};  // 选择的方向

    dist[start] = 0;
    // dist[start]为0，可以省略；这里为了符合逻辑就保留了
    pq.push({dist[start] + f(start), start});

    while (pq.size()) {
        auto t = pq.top();
        pq.pop();

        string state = t.y;

        // 终点判断(A*不需要重复出队判断)
        if (state == end) {
            break;
        }

        // 这里用二维坐标来存一维坐标
        // 编程坐标：下为x正方向，右为y正方向
        int x, y;    // 找到x的位置并记录3*3坐标
        for (int i = 0; i < 9; i++) {
            if (state[i] == 'x') {
                x = i / 3;
                y = i % 3;
                break;
            }
        }

        // 扩展；根据题意，可移动方向基于四联通
        string source = state;    // 备份原状态，为了下一次交换需要恢复
        for (int i = 0; i < 4; i++) {
            // 注意，这里扩展的是空位x的位置
            // 看看谁能移动到x的位置上来
            int a = x + dx[i], b = y + dy[i];

            if (a < 0 || a >= 3 || b < 0 || b >= 3) {
                continue;
            }

            // 交换前恢复
            state = source;
            // 交换状态
            swap(state[x * 3 + y], state[a * 3 + b]);

            // 松弛操作
            // 哈希表默认状态没有初始化为无穷大，因此这里要特判
            // 如果第一次松弛这个状态，则无条件松弛
            if (!dist.count(state) || dist[state] > dist[source] + 1) {
                dist[state] = dist[source] + 1;
                pre[state] = {op[i], source};
                pq.push({dist[state] + f(state), state});
            }
        }
    }

    string res;
    // 反向推导路径
    while (end != start) {
        res += pre[end].x;
        end = pre[end].y;
    }
    reverse(res.begin(), res.end());

    return res;  // 已经保证有解了，一定可以总从while中break出来
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 初始状态：start含有x，seq不含x
    // seq用于统计逆序对
    string start, seq;
    char c;

    while (cin >> c) {
        start += c;
        if (c != 'x') {
            seq += c;
        }
    }

    // 统计逆序对
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (seq[i] > seq[j]) {
                cnt++;
            }
        }
    }

    // 无解情况：逆序对个数为奇数
    // A*算法在无解时效率不及BFS，因此预处理无解情况
    if (cnt & 1) {
        cout << "unsolvable" << endl;
    } else {
        cout << bfs(start) << endl;
    }

    return 0;
}
