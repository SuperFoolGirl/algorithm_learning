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
