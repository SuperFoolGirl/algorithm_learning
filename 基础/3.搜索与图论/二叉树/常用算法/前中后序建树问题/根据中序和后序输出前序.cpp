#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

void buildPre(string in, string post) {
    if (in.size() <= 0) {
        return;
    }
    // 纠错：每轮递归，in和post长度相等
    if (in.size() != post.size()) {
        return;
    }

    char root = post.back();
    int mid = in.find(root);

    // 根
    cout << root;
    // 左
    buildPre(in.substr(0, mid), post.substr(0, mid));
    // 右
    buildPre(in.substr(mid + 1), post.substr(mid, in.size() - mid - 1));
}

int main() {
    string in, post;
    cin >> in >> post;
    buildPre(in, post);

    return 0;
}
