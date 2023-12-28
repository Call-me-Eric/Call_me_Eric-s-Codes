#include <bits/stdc++.h>
using namespace std; 
typedef unsigned int uint; 
int B = 1103515245, A = 1013904223; 

int M, T; 
int a[105]; 

struct Matrix {
    int a[2][2]; 
    Matrix() { memset(a, 0, sizeof a); }
    void reset(void) { for (int i = 0; i < 2; ++i) a[i][i] = 1; }
    Matrix friend operator* (const Matrix &a, const Matrix &b) {
        Matrix c; 
        for (int i = 0; i < 2; ++i) for (int k = 0; k < 2; ++k) for (int j = 0; j < 2; ++j)
            c.a[i][j] = (c.a[i][j] + 1ll * a.a[i][k] * b.a[k][j]) % M; 
        return c; 
    }
}; 

Matrix poww(Matrix a, int b) {
    Matrix res; res.reset(); 
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int calc(int n) {
    if (n == 1) return 134775813 % M; 
    Matrix t, base; 
    t.a[0][0] = 134775813 % M, t.a[0][1] = 1; 
    base.a[0][0] = B, base.a[0][1] = 0, base.a[1][0] = A, base.a[1][1] = 1; 
    return (t * poww(base, n - 1)).a[0][0]; 
}

int main(void) {
    freopen("dark.in", "r", stdin); 
    freopen("dark.out", "w", stdout); 
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> M >> T; B %= M, A %= M; 
    
    while (T--) {
        int l, r; cin >> l >> r; int n = r - l + 1; 
        a[1] = calc(l); 
        for (int i = 2; i <= n; ++i) a[i] = (1ll * a[i - 1] * B + A) % M; 
        uint ans = 0; 
        for (int i = 1; i <= n; ++i) {
            int res = 0; 
            for (int j = i; j <= n; ++j) {
                if (a[j] & 1) res += 4; 
                else if (a[j] & 3) res += 3; 
                else ++res; 
                if (res > 3 * (j - i + 1)) ++ans; 
            }
        }
        cout << ans << "\n"; 
    }
    return 0; 
}