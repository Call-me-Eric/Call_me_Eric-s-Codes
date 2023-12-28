#include <bits/stdc++.h>
using namespace std; 
const int N = 300; 

int n, m; 
struct Matrix {
    bitset<N> a[N]; 
    
    inline Matrix operator* (const Matrix &y) const {
        Matrix z; 
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k) 
                if (a[i][k]) z.a[i] ^= y.a[k]; 
        return z; 
    }
} a, b; 

inline void poww(Matrix a, int k) {
    Matrix ans = a; --k; 
    for (; k; k >>= 1, a = a * a) if (k & 1) ans = ans * a; 
    ans = ans * b; 
    for (int i = 0; i < n; ++i) cout << ans.a[i][0]; 
    cout << '\n'; 
}

int main(void) {
    freopen("matrix.in", "r", stdin); 
    freopen("matrix.out", "w", stdout); 
    
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n; string x; // n = 300; 
    for (int i = 0; i < n; ++i) {
        cin >> x; // cout << x[0] << "\n"; 
        for (int j = 0; j < n; ++j) a.a[i][j] = x[j] - '0'; 
    }
    // for (int i = n; i < 1000; ++i) cin >> x; 
    cin >> x; 
    for (int i = 0; i < n; ++i) b.a[i][0] = x[i] - '0'; 
    cin >> m; 
    // double st = clock(); 
    while (m--) {
        int k; cin >> k; 
        if (k == 0) {
            for (int i = 0; i < n; ++i) cout << b.a[i][0]; 
            cout << '\n'; 
            continue; 
        }
        poww(a, k); 
        
        /*
        Matrix t = poww(a, k); 
        for (int i = 0; i < n; ++i, cout << "\n") 
            for (int j = 0; j < n; ++j)
                cout << t.a[i][j]; 
        */
    }
    // double ed = clock(); 
    // cerr << 1000 * (ed - st) / CLOCKS_PER_SEC << "ms\n"; 
    return 0; 
}