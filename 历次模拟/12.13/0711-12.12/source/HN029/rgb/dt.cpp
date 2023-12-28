#include <bits/stdc++.h>
using namespace std;
mt19937 rd(random_device{}());
int rand(int l, int r) {
    uniform_int_distribution<> gen(l, r);
    return gen(rd);
}
int main() {
    int r, g, b, m;
    cin >> r >> g >> b >> m;
    int n = r + g + b + 1;
    assert(n - 1 <= m && m <= 1ll * n * (n - 1) / 2);
    cout << r << " " << g << " " << b << " " << m << "\n";
    map<int, map<int, bool>> vis;
    for (int i = 2; i <= n; i++) {
        int p = rand(1, i - 1);
        vis[p][i] = vis[i][p] = 1;
        int col = rand(1, 3);
        char c;
        if (col == 1) {
            c = 'r';
        } else if (col == 2) {
            c = 'g';
        } else {
            c = 'b';
        }
        cout << p << " " << i << " " << c << "\n";
    }
    for (int i = n; i <= m; i++) {
        int u, v;
        do {
            u = rand(1, n);
            v = rand(1, n);
        } while (u == v || vis[u][v]);
        vis[u][v] = vis[v][u] = 1;
        int col = rand(1, 3);
        char c;
        if (col == 1) {
            c = 'r';
        } else if (col == 2) {
            c = 'g';
        } else {
            c = 'b';
        }
        cout << u << " " << v << " " << c << "\n";
    }
    return 0;
}