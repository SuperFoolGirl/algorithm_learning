#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

void buildPost(string in, string pre) {
    if (in.size() <= 0) {
        return;
    }
    // 纠错：每轮递归，in和pre长度相等
    if (in.size() != pre.size()) {
        return;
    }

    char root = pre[0];
    int mid = in.find(root);

    // 左
    buildPost(in.substr(0, mid), pre.substr(1, mid));
    // 右
    buildPost(in.substr(mid + 1), pre.substr(mid + 1));
    // 根
    cout << root;
}

int main() {
    string in, pre;
    cin >> in >> pre;
    buildPost(in, pre);

    return 0;
}
