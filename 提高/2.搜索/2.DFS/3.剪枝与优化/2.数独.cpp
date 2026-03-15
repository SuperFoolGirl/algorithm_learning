// 从空格子出发搜索
// 可行性剪枝：填可用数字(不与行列宫冲突)，并更新对全局的影响
// 继续搜索下一个空格子
// 终止条件：所有空格子都被填满

// 剪枝：
// 优化搜索顺序：先搜可填数字较少的空格子(每个空格子可填数字的数量)
// 但由于每填一个数字，都会对整体产生影响，因此无法预处理
// 可行性剪枝：已介绍

// 特点：位运算优化
// 对于行来说，是一个9位01串；为1表示数字可用，为0表示数字不可用
// 如010011100，数字2、5、6、7可用
// 这样，每一行的状态表示可以优化为一个int值
// 列、宫同理
// 对于某个空格子而言，通过行、列、宫的状态进行与运算，即可得到该空格子可填数字的状态
// 与完后得到一个9位01串，固然可以用循环来扩展，但更优雅的方案是lowbit
// 回忆：在O(1)时间内返回二进制数中最低位的1所对应的权值
// 这样，每次循环的次数，就是当前空格子可填数字的数量，而不用再枚举9个数

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 9, M = 1 << N;

// 以row为例，共n行，每行用一个int来表示整行的情况
int row[N], col[N], cell[3][3];
char str[100];
int ones[M], map[M];

void init() {
    // 一开始什么都能填，每行/列赋值为全1
    for (int i = 0; i < N; i++) {
        col[i] = row[i] = M - 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cell[i][j] = M - 1;
        }
    }
}

// 辅助函数
// 若标记为真，在(x,y)处填t
// 若标记为假，把(x,y)处的t消掉
void draw(int x, int y, int t, bool is_set) {
    if (is_set) {
        str[x * N + y] = t + '1';
    } else {
        str[x * N + y] = '.';
    }

    int v = 1 << t;  // t对应在行列宫的权值
    if (!is_set) {
        v = -v; // 
    }
    row[x] -= v;
    col[y] -= v;
    cell[x / 3][y / 3] -= v;
}

int lowbit(int x) {
    return x & -x;
}

// 求(x,y)处可填数字
int get(int x, int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}

bool dfs(int cnt) {
    // 出口判断
    if (!cnt) {
        return true;
    }

    // 先找出可填数字最少的空格子
    int minv = 10;
    int x, y;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (str[i * N + j] == '.') {
                // 求出(x,y)处可填数字的状态
                int state = get(i, j);
                // 更新可填数字最小值
                if (ones[state] < minv) {
                    minv = ones[state];
                    x = i, y = j;
                }
            }
        }
    }

    // 扩展，枚举state中的所有1
    int state = get(x, y);
    for (int i = state; i; i -= lowbit(i)) {
        // 求出最低位的1所对应的数字
        int t = map[lowbit(i)];
        // 在(x,y)处填t
        draw(x, y, t, true);
        // 继续搜索下一个空格子
        if (dfs(cnt - 1)) {
            return true;
        }
        // 回退
        draw(x, y, t, false);
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 求出2^i与i的映射关系，节省pow的开销
    for (int i = 0; i < N; i++) {
        map[1 << i] = i;
    }
    // 预处理所有9位数中1的个数
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            ones[i] += i >> j & 1;
        }
    }

    while (cin >> str, str[0] != 'e') {
        // 多组输入，预处理清空数据
        init();

        int cnt = 0;  // 统计空位
        for (int i = 0, k = 0; i < N; i++) {
            for (int j = 0; j < N; j++, k++) {
                if (str[k] != '.') {
                    int t = str[k] - '1';
                    draw(i, j, t, true);
                } else {
                    cnt++;
                }
            }
        }

        dfs(cnt);

        cout << str << endl;
    }

    return 0;
}
