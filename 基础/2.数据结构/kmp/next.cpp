#include <iostream>
#include <vector>

using namespace std;

void getNext(const string& p, vector<int>& ne) {
    int n = p.size();

    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && p[i] != p[j]) {
            j = ne[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        ne[i] = j;
    }
}

int main() {
    string p;
    cin >> p;
    vector<int> next(p.size(), 0);
    getNext(p, next);

    for (int elem : next) {
        cout << elem << " ";
    }

    return 0;
}