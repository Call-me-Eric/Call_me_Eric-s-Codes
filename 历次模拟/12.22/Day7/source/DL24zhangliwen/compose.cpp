// 答案只有 k 种

#include <bits/stdc++.h>
using namespace std; 

int n, m, q; 

namespace Sub1 {

vector<vector<int>> a;  
void MAIN(void) {
    for (int i = 1; i <= m; ++i) {
        vector<int> t(n); 
        for (int &x : t) cin >> x; 
        a.push_back(t); 
    }
    while (q--) {
        int op, x, y; cin >> op >> x >> y; --x; --y; 
        if (op == 1) {
            vector<int> t(n); 
            for (int i = 0; i < n; ++i) t[i] = max(a[x][i], a[y][i]); 
            a.push_back(t); 
        } else if (op == 2) {
            vector<int> t(n); 
            for (int i = 0; i < n; ++i) t[i] = min(a[x][i], a[y][i]); 
            a.push_back(t); 
        } else cout << a[x][y] << "\n"; 
    }
}

}

namespace Sub2 {

int op[100005], x[100005], y[100005], ans[100005]; 
int a[13][100005]; 
bitset<7000> t[100025]; 
void MAIN(void) {
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= n; ++j) cin >> a[i][j]; 
    for (int i = 1; i <= q; ++i) cin >> op[i] >> x[i] >> y[i]; 
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(r + 6999, n); // 处理 l 到 r 的特征
        int k = m; 
        for (int i = 1; i <= m; ++i) for (int j = l; j <= r; ++j)
            t[i][j - l] = a[i][j] - 1; 
        for (int i = 1; i <= q; ++i) {
            if (op[i] == 1) t[++k] = t[x[i]] | t[y[i]]; 
            else if (op[i] == 2) t[++k] = t[x[i]] & t[y[i]]; 
            else if (l <= y[i] && y[i] <= r) ans[i] = t[x[i]][y[i] - l]; 
        }
    }
    for (int i = 1; i <= q; ++i) if (op[i] == 3) cout << ans[i] + 1 << "\n"; 
}

}

int main(void) {
    freopen("compose.in", "r", stdin); 
    freopen("compose.out", "w", stdout); 
    
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n >> m >> q; 
    if (n <= 100) return Sub1::MAIN(), 0; 
    Sub2::MAIN(); 
    return 0; 
}