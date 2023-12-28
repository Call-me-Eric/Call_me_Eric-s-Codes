#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e7 + 5;
int n;
vector<int> P;
bool vis[N];
bool check(int x) {
    vector<int> a;
    while (x) {
        a.push_back(x % 10);
        x /= 10;
    }
    int k = a.size();
    if (a[0] == 9) {
        int c4 = 0, c9 = 0;
        for (int w : a) {
            if (w == 1 || w == 8 || w == 2 || w == 3 || w == 5 || w == 7) {
                return 0;
            }
            if (w == 4) {
                c4++;
                // if (c4 == 2) {
                //     return 0;
                // }
            }
            if (w == 9) {
                c9++;
            }
        }
        if (c9 != 3) {
            return 0;
        }
        return 1;
    }
    return 0;
}
int main() {
    cin >> n;
    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            P.push_back(i);
        }
        for (int p : P) {
            int j = i * p;
            if (j > n) break;
            vis[j] = 1;
            if (i % p == 0) break;
        }
    }
    for (int p : P) {
        if (check(p)) {
            cout << p << " ";
        }
    }
    cout << "\n";
    return 0;
}