// 把字符串的每个状态看成图中的一个节点，边权为1；求从起点到终点的最短路

#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

const int N = 6;

int n;
string a[N], b[N];

int extend(queue<string>& q, unordered_map<string, int>& d1, unordered_map<string, int>& d2) {
    // 按照bfs模板来写，从取出队头开始
    string t = q.front();
    q.pop();

    // 扩展
    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < n; j++) {
            // 从i开始，取出a[j]的长度的子串，替换成b[j]，得到新状态
            if (t.substr(i, a[j].size()) == a[j]) {
                // 替换后，t的0~i-1部分不变，i~i+a[j].size()-1部分替换成b[j]，i+a[j].size()~末尾部分不变
                string state = t.substr(0, i) + b[j] + t.substr(i + a[j].size());

                // 入队判重
                if (d1.count(state)) {
                    continue;
                }

                // 入队前终点判断
                if (d2.count(state)) {
                    // A->t->state->B，其中t->state为1
                    return d1[t] + d2[state] + 1;
                }

                // 入队
                d1[state] = d1[t] + 1;
                q.push(state);
            }
        }
    }

    // 没有重合，返回非法值
    return 11;
}

int bfs(string A, string B) {
    // 起点队列，终点队列
    queue<string> qa, qb;
    // 从起点开始的距离与从终点开始的距离
    unordered_map<string, int> da, db;
    qa.push(A), qb.push(B);
    da[A] = 0, db[B] = 0;

    // 一旦某一端队列为空，还没找到答案，说明两个区域不连通
    while (qa.size() && qb.size()) {
        // 扩展队列容量较小的一端
        // 出队->扩展，因此要从出队代码中限制
        int t;  // 存储出队元素的步数
        if (qa.size() <= qb.size()) {
            t = extend(qa, da, db);
        } else {
            t = extend(qb, db, da);
        }

        // extend完成扩展、入队
        // 终点判断的延续，从位置上看，是写在入队处
        if (t <= 10) {
            return t;
        }
    }

    return 11;  // 非法答案
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string A, B;
    cin >> A >> B;
    // 不知有几个规则，但最多为6
    while (cin >> a[n] >> b[n]) {
        n++;
    }

    int step = bfs(A, B);

    if (step > 10) {
        cout << "NO ANSWER!" << endl;
    } else {
        cout << step << endl;
    }

    return 0;
}
