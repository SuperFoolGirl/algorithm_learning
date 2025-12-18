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
    // 左：in是左根右，post是左右根，左子树长度为mid，二者都是从0开始取mid个字符作为左子树
    buildPre(in.substr(0, mid), post.substr(0, mid));
    // 右：对于in，右子树是从mid+1开始到结尾；对于post，左子树结尾下标是mid-1，右子树是从mid开始到倒数第2个字符
    buildPre(in.substr(mid + 1), post.substr(mid, in.size() - mid - 1));
}

int main() {
    string in, post;
    cin >> in >> post;
    buildPre(in, post);

    return 0;
}
