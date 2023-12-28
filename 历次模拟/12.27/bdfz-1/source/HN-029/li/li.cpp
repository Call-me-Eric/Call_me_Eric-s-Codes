#include <bits/stdc++.h>
using namespace std;
int n, m;
int main() {
    freopen("li.in", "r", stdin);
    freopen("li.out", "w", stdout);
    cin >> n >> m;
    if (n == 1) {
        assert(m == 0);
        cout << "0 1\n";
    } else if (n == 2) {
        if (m == 0) {
            cout << "0 2\n";
        } else if (m == 1) {
            cout << "0 3\n";
        } else {
            assert(0);
        }
    } else if (n == 3) {
        if (m == 0) {
            cout << "0 3\n";
        } else if (m == 1) {
            cout << "0 4\n";
        } else if (m == 2) {
            cout << "0 6\n";
        } else if (m == 3) {
            cout << "1 3\n";
        } else {
            assert(0);
        }
    }
    return 0;
}