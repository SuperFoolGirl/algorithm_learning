#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int ne[N];
vector<int> ans;

bool kmp(string &p, string &s) {
    int n = p.size();    // 模式串p的长度
    int m = s.size();    // 主串s的长度

    // 计算next数组
    for (int i = 1, j = 0; i < n; i++) {    // 注意i从1开始
        while (j > 0 && p[i] != p[j]) {
            j = ne[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        ne[i] = j;
    }

    // kmp匹配
    for (int i = 0, j = 0; i < m; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = ne[j - 1];
        }
        if (s[i] == p[j]) {
            j++;
        }
        if (j == n) {
            ans.push_back(i - n + 1); // 记录匹配位置
            j = ne[j - 1];
        }
    }
    return !ans.empty();
}

int main() {
    string s, p;
    cin >> s >> p;

    if (kmp(p, s)) {
        for (int t : ans) {
            cout << t << ' ';
        }
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}
