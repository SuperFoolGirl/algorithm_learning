// 木棒指切断前的情况
// 木棍指切断后的情况
// 最外层，从小到大枚举木棒长度
// “点”：木棒——从前往后依次拼每一根木棒

// 可以发现，这样不会漏情况
// 复杂搜索问题很忌讳漏情况

// 剪枝
// 1.木棒长度|木棍长度之和sum，因此最外层只枚举sum的约数
// 2.先枚举长木棍，优化搜索顺序
// 3.1 排除等效冗余：木棍只要填满木棒即可，顺序无所谓，避免重复搜索；要按组合的方式来搜索
// 3.2 如果当前木棒无法再添加木棍了，那么和它属性相同的木棒也必然无法添加木棍了，直接回溯
// 3.3 如果木棒的第一根木棍失败，则当前长度方案一定失败，直接回溯
// 3.4 如果木棒的最后一根木棍失败，则当前长度方案一定失败，直接回溯

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 70;

int n;
int w[N], sum, length;
bool st[N];

// u: 当前枚举到第几根木棍
// s: 当前木棒已经拼了多长了
// start: 排除等效冗余
bool dfs(int u, int s, int start) {
    if (u * length == sum) {
        return true;
    }
    // 如果当前木棒已经拼满了，继续枚举下一根木棒
    if (s == length) {
        // start取0，和“分成互质组”原理一样
        // 这里需要加return，否则传递链就断掉了，当前层会错误地继续执行
        // 当前层无法再操作了，把球踢给下一层，同时做好接受它归回结果的准备
        return dfs(u + 1, 0, 0);
    }

    // 枚举木棍
    for (int i = start; i < n; i++) {
        // 可行性剪枝
        if (st[i]) {
            continue;
        }
        if (s + w[i] > length) {
            continue;
        }

        st[i] = true;
        if (dfs(u, s + w[i], i + 1)) {
            return true;
        }
        st[i] = false;

        // 到达此处，说明w[i]无法添加到当前木棒了
        
        // 剪枝3.3
        if (s == 0) {
            return false;
        }

        // 剪枝3.4
        if (s + w[i] == length) {
            return false;
        }

        // 剪枝3.2
        // 由于已排序，长度相同的木棍会在一起
        int j = 0;
        while (j < n && w[j] == w[i]) {
            j++;
        }
        i = j - 1;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while (cin >> n, n) {
        memset(st, 0, sizeof st);
        sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> w[i];
            sum += w[i];
        }

        // 优化搜索顺序，先枚举长木棍
        sort(w, w + n, greater<int>());

        // 从小到大枚举木棒长度
        // 最短的才是最优解，找到了直接break
        // 最差情况为所有木棍组成一根木棒，枚举到sum时就一定能找到解了
        length = 1;
        while (true) {
            if (sum % length == 0 && dfs(0, 0, 0)) {
                cout << length << endl;
                break;
            }
            length++;
        }
    }

    return 0;
}
