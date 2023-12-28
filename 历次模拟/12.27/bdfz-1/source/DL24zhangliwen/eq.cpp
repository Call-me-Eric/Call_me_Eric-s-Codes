#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 

int n, q, A[705][705]; 
int a[705][705], x[705]; 

inline int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
    return r; 
}
inline int inv(int x) { return poww(x, P - 2); }

int solve(int n, int m) {
    int c = 0, r = 0; 
    for (; r < n && c < m; ++r, ++c) {
        int maxr = r;
        for (int i = r + 1; i < n; ++i) 
            if (a[i][c] > a[maxr][c]) maxr = i; 
        if (maxr != r) swap(a[r], a[maxr]); 
        if (a[r][c] == 0) { --r; continue; }
        for (int i = r + 1; i < n; ++i) if (a[i][c] != 0) {
            int k = 1ll * a[i][c] * inv(a[r][c]) % P; 
            for (int j = c; j < m + 1; j++) 
                a[i][j] = (a[i][j] - 1ll * a[r][j] * k % P + P) % P;
            a[i][c] = 0;
        }
    }
    for (int i = r; i < m; ++i) 
        if (a[i][c] != 0) return -1; 
    if (r < m) return m - r; 
    for (int i = m - 1; i >= 0; --i) {
        for (int j = i + 1; j < m; j++)
            a[i][m] = (a[i][m] - 1ll * a[i][j] * x[j] % P + P) % P;
        x[i] = 1ll * a[i][m] * inv(a[i][i]) % P;
    }
    return 0; // 有唯一解
}

int main(void) {
    freopen("eq.in", "r", stdin); 
    freopen("eq.out", "w", stdout); 
    ios::sync_with_stdio(0); 
    cin >> n >> q; 
    for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) cin >> A[i][j]; 
    for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) a[i][j] = A[i][j]; 
    int pan = solve(n, n);
    if (pan == -1) cout << "No\n"; 
    else if (pan > 0) cout << "Many\n"; 
    else {
        for (int i = 0; i < n; i++) cout << x[i] << " "; 
        cout << "\n"; 
    }
    while (q--) {
        int t; cin >> t; --t; 
        for (int i = 0; i <= n; ++i) cin >> A[t][i]; 
        for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) a[i][j] = A[i][j]; 
        int pan = solve(n, n);
        if (pan == -1) cout << "No\n"; 
        else if (pan > 0) cout << "Many\n"; 
        else {
            for (int i = 0; i < n; i++) cout << x[i] << " "; 
            cout << "\n"; 
        }
    }
    return 0; 
}