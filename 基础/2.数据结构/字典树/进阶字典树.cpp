// 相对于字典树模板，本内容改进如下：
// 1.封装字典树，可读性更强
// 2.拓宽了字符范围，支持小写字母和数字
// 3.给每个节点维护了一个权值，进而优化掉了cnt数组(权值为0视为非单词节点)
// 4.每个节点维护一个res数组，存储以当前节点为前缀的单词列表，按照频率从大到小排序，频率相同按字典序排序(这部分内容可以去掉，与dfs函数有关)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, string> PIS;

// 所有可能的字符串数量。如"string"共含有6个字符串，"string"、"strin"、"stri"、"str"、"st"、"s"，因此N要足够大
const int N = 200010;

// 字典树节点，tr[i]表示单词i，每个单词用idx索引
struct Node {
    int son[36];
    int val;
    // res存储以当前节点为前缀的单词列表，按照频率从大到小排序，频率相同按字典序排序
    vector<PIS> res;
} tr[N];

int n, m, k, idx;

bool cmp(const PIS& a, const PIS& b) {
    if (a.first != b.first) {
        return a.first > b.first;    // 频率从大到小排序
    }
    return a.second < b.second;      // 频率相同按字典序排序
}

// 字符统一用数字编址，方便数组索引
int get_id(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return 26 + c - '0';
}

void insert(string& s, int val) {
    int p = 0;    // 从根结点开始
    for (char c : s) {
        int u = get_id(c);
        if (!tr[p].son[u]) {
            tr[p].son[u] = ++idx;
        }
        p = tr[p].son[u];
    }
    // 更新当前节点的频率值，取最大值
    tr[p].val = max(tr[p].val, val);
}

// 若v是u的子结点，那么以v为前缀的单词也是以u为前缀的单词，因此可以把v的结果合并到u中
// u为当前节点编号，path为当前路径上的字符串
void dfs(int u, string& path) {
    // 先收集u的所有子树的结果
    for (int i = 0; i < 36; i++) {
        int cur = tr[u].son[i];
        if (cur) {
            char c = i < 26 ? 'a' + i : '0' + (i - 26);
            path.push_back(c);

            dfs(cur, path);

            // 此时以cur为根的子树已经处理完毕，把cur的结果合并到u中
            for (auto& t : tr[cur].res) {
                tr[u].res.push_back(t);
            }

            // cur的res是没有保存cur本身的，如果cur也是单词，那么需要把cur也加入u的res中
            // 判断cur是否是单词：看是否有val值
            if (tr[cur].val > 0) {
                tr[u].res.push_back({tr[cur].val, path});
            }

            path.pop_back();    // 回溯以处理u的下一个子结点
        }
    }

    // u的res已经包含了所有以u为前缀的单词，按照要求排序
    sort(tr[u].res.begin(), tr[u].res.end(), cmp);

    // 去重防止res包含重复值，影响正确性
    tr[u].res.erase(unique(tr[u].res.begin(), tr[u].res.end()), tr[u].res.end());

    // 保留前k个
    if (tr[u].res.size() > k) {
        tr[u].res.resize(k);
    }
}

void query(string& s) {
    int p = 0;
    for (char c : s) {
        int u = get_id(c);
        if (!tr[p].son[u]) {
            cout << "no suggestion\n";
            return;
        }
        p = tr[p].son[u];
    }

    // 输出前k个严格以s为前缀的单词
    if (tr[p].res.empty()) {
        cout << "no suggestion\n";
        return;
    }
    for (auto& t : tr[p].res) {
        cout << t.second << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;

    while (n--) {
        int val;
        string s;
        cin >> val >> s;
        insert(s, val);
    }

    // 预处理字典树，计算每个节点的前k个单词，避免每次搜索
    string path;
    dfs(0, path);

    while (m--) {
        string s;
        cin >> s;
        query(s);
        if (m) {
            cout << "\n";
        }
    }

    return 0;
}
