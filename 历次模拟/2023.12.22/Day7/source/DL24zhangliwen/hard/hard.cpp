#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int P = 998244353; 

inline int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
    return r; 
}

int n, s; 
int a[2005], f[100005]; 

int main(void) {
    freopen("hard.in", "r", stdin); 
    freopen("hard.out", "w", stdout); 

    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n; int mx = 0; 
    for (int i = 1; i <= n; ++i) cin >> a[i], s += a[i], mx = max(mx, a[i]); 
    f[1] = s - 1;  
    f[2] = 2ll * f[1] - 1; 
    for (int i = 3; i <= mx; ++i) f[i] = (2ll * f[i - 1] - f[i - 2] + 1ll * (s - 1) * poww(s - i + 1, P - 2) % P) % P; 
    int ans = 0; 
    for (int i = 1; i <= n; ++i) ans = (ans + f[a[i]]) % P; 
    cout << (ans + P) % P << "\n"; 
    return 0; 
}