#include <bits/stdc++.h>
using namespace std;
constexpr int p = 998244353;
mt19937 rd(random_device{}());
int rand(int l, int r) {
    uniform_int_distribution<> gen(l, r);
    return gen(rd);
}
int main() {
    int n = 700, q = 700;
    cout << n << " " << q << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cout << rd() % p << " ";
        }
        cout << "\n";
    }
    for (int i = 1; i <= q; i++) {
        int z = rand(1, n);
        cout << z << " ";
        for (int j = 1; j <= n + 1; j++) {
            cout << rd() % p << " ";
        }
        cout << "\n";
    }
    return 0;
}