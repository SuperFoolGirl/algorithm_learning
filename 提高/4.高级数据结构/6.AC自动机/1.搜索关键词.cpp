#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 最多N个单词，每个单词长度最大为S，因此字典树结点数最多为N*S
const int N = 10010, S = 55, M = 1000010;

int n, m;
int tr[N * S][26], cnt[N * S], idx;
char str[M];
int q[N * S];
int ne[N * S];

void insert(char s[]) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int t = s[i] - 'a';
        if (!tr[p][t]) {
            tr[p][t] = ++idx;
        }
        p = tr[p][t];
    }
    cnt[p]++;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++) {
        if (tr[0][i]) {
            q[++tt] = tr[0][i];
        }
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int p = tr[t][i];
            if (!p) {
                tr[t][i] = tr[ne[t]][i];
            } else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }
}

int query() {
    int res = 0;
    for (int i = 0, j = 0; str[i]; i++) {
        int t = str[i] - 'a';
        j = tr[j][t];

        int p = j;
        while (p) {
            res += cnt[p];
            cnt[p] = 0;
            p = ne[p];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
        memset(ne, 0, sizeof ne);
        idx = 0;

        cin >> n;
        while (n--) {
            cin >> str;
            insert(str);
        }

        build();

        cin >> str;
        cout << query() << '\n';
    }

    return 0;
}
