#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

namespace Sub1 {
    const int P = 1000000007; 
    int poww(int a, int b) {
        int r = 1; 
        for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
        return r; 
    }
    void MAIN(void) {
        int n; cin >> n; 
        cout << (poww(3, n) + 3 * poww(-1, n) + P) % P << "\n"; 
    }
}
namespace Sub3 {
    int n, m; 
    i64 a[100005]; 
    void MAIN(void) {
        cin >> n >> m; 
        for (int i = 1; i <= n; ++i) cin >> a[i], a[i] += a[i - 1]; 
        while (m--) {
            int l, r; cin >> l >> r; 
            cout << a[r] - a[l - 1] << "\n"; 
        }
    }
}

int main(void) {
    freopen("crack.in", "r", stdin); 
    freopen("crack.out", "w", stdout); 
    
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    if (T <= 2) return Sub1::MAIN(), 0; 
    if (T <= 3) return Sub3::MAIN(), 0; 
    return 0; 
}