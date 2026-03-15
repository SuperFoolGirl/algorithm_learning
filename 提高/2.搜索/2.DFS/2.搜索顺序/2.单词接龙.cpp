// 重要题设：可任意选择重合部分的长度
// 但是，若a整体是b的前缀，则不能相连
// 看似复杂，但其实应该要想到贪心：
// 重合长度越短，越靠近最优结果
// 因此，重合长度从1开始枚举，只要有答案，立刻停止

// 本题应该想到要抽象成图，若a与b可相连，则建立边
// 另外，做过DP后，应该意识到要预处理所有单词之间的重合关系
// 若b能接在a后面，则b是a的可扩展点

// 还有，每个单词最多用两次，这是给建边的规模设限了

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 21;

int n;
string word[N];
int g[N][N];
int used[N];
int ans;

// 对于本题来说，随着接龙体不断扩展
// 递归参数：dragon、last在改变
// 数据结构：单词使用情况在改变
// 因此，used参与恢复现场
void dfs(string dragon, int last) {
    // 没有出口，依赖dfs自然结束
    // 因此需要时刻更新答案
    ans = max(ans, (int)dragon.size());

    // 出栈时，更新使用情况
    used[last]++;

    // 枚举扩展单词
    for (int i = 0; i < n; i++) {
        if (g[last][i] && used[i] < 2) {
            dfs(dragon + word[i].substr(g[last][i]), i);
        }
    }

    // 恢复现场
    used[last]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> word[i];
    }

    char start;
    cin >> start;

    // 预处理单词之间的重合关系
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string a = word[i], b = word[j];
            // 求a的后缀和b的前缀的最长重合长度，k枚举长度
            for (int k = 1; k < min(a.size(), b.size()); k++) {
                if (a.substr(a.size() - k) == b.substr(0, k)) {
                    g[i][j] = k;
                    break;  // 从1开始枚举，找到第一个重合长度就停止了
                }
            } 
        }
    }

    // 从首字母为start的单词开始搜
    for (int i = 0; i < n; i++) {
        if (word[i][0] == start) {
            // 参数：接龙体，末尾单词的编号
            dfs(word[i], i);
        }
    }

    cout << ans << endl;

    return 0;
}
