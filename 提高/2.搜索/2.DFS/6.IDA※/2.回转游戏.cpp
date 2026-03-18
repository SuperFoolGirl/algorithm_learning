// 操作为A~H 8种
// 搜索：按照字典序去搜索每一步的操作

// 启发函数：
// 这个思路与上个题很像，注意学习这种思路
// 对于中间8个格子
// 每次操作只会改变其中一个格子
// 因此，可以统计8个格子中，出现最多的数字的个数x
// 则最少还需要8-x次才能到达目标状态

// 本题属于代码比较复杂的类型，需要做好各种预处理

// 另外，还有一个很明显的优化
// 本题中，8种4对操作，两两抵消
// 若进行了A操作，则下一步一定不能枚举F操作

// 位置编号：
// 从上到下，从左到右，从0开始编号，编号0-23

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 24;

int n;
int path[100];
int q[N];

// 8种操作，每种操作下有7个元素，记录其编号
int op[8][7] = {
    {0,  2,  6,  11, 15, 20, 22},
    {1,  3,  8,  12, 17, 21, 23},
    {10, 9,  8,  7,  6,  5,  4 },
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8,  3,  1 },
    {22, 20, 15, 11, 6,  2,  0 },
    {13, 14, 15, 16, 17, 18, 19},
    {4,  5,  6,  7,  8,  9,  10}
};

// 逆操作
// A-H操作，令为0-7
int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2};

// 中间8个数的位置
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

void operate(int x) {
    // 操作共性：把0~5移动到1~6，把6移动到0
    // 存储当前操作x的0位置元素
    int t = q[op[x][0]];
    for (int i = 0; i < 6; i++) {
        q[op[x][i]] = q[op[x][i + 1]];
    }
    q[op[x][6]] = t;
}

int f() {
    int sum[4] = {0};
    for (int i = 0; i < 8; i++) {
        sum[q[center[i]]]++;
    }

    int s = 0;
    for (int i = 1; i <= 3; i++) {
        s = max(s, sum[i]);
    }

    return 8 - s;
}

// “点”：具体方案选择，体现在last中
// 用path来维护整个路径的答案，因此path参与恢复现场
bool dfs(int u, int depth, int last) {
    if (u + f() > depth) {
        return false;
    }

    // 出口判断复习：借助启发函数
    if (f() == 0) {
        return true;
    }

    // 扩展：枚举各个操作
    for (int i = 0; i < 8; i++) {
        // 跳过逆操作
        if (opposite[i] != last) {
            operate(i);
            path[depth] = i;
            if (dfs(u + 1, depth, i)) {
                return true;
            }
            // path无需恢复，整个状态需要恢复
            operate(opposite[i]);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while (cin >> q[0], q[0]) {
        for (int i = 1; i < N; i++) {
            cin >> q[i];
        }

        int depth = 0;
        while (!dfs(0, depth, -1)) {
            depth++;
        }

        // 输出操作方案
        if (!depth) {  // 一步都没有扩展，即起点和终点重合
            cout << "No moves needed" << endl;
        } else {
            for (int i = 0; i < depth; i++) {
                cout << path[i] + 'A';
            }
        }
        // 输出中间数字
        cout << endl << q[6] << endl;
    }

    return 0;
}
