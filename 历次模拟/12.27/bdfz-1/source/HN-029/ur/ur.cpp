#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("ur.in", "r", stdin);
    freopen("ur.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    if (k == n) {
        for (int i = 1; i <= n; i++) {
            cout << "1";
        }
        cout << "\n";
    } else if (k <= 1) {
        for (int i = 1; i <= n; i++) {
            cout << "0";
        }
        cout << "\n";
    }
    return 0;
}