// 如果一个节点只有一个子节点，在前序和后序中，无法确定这个子节点是左子树还是右子树
// 找到树中所有度为1的点，每有一个度为1的点，根据乘法原理，可能的答案翻一倍

// 如果 b 是 a 唯一的孩子，那么：
// 在前序里，b 一定紧跟在 a 后面（pre[i] 是 a，pre[i + 1] 是 b）。 
// 在后序里，a 一定紧跟在 b 后面（post[j - 1] 是 b，post[j] 是 a）。

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int ans;
string pre, post;

int main() {
    cin >> pre >> post;

    int n = pre.size(), m = post.size();
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (pre[i] == post[j] && pre[i + 1] == post[j - 1]) {
                ans++;
            }
        }
    }

    cout << (1 << ans);

    return 0;
}
