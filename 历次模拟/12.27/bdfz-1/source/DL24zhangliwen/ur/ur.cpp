#include <bits/stdc++.h>
using namespace std;

int n, k; 
int ans[1000005]; 

bool isprime(int n) {
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return 0; 
    return 1; 
}

int main(void) {
    // freopen("ur.in", "r", stdin); 
    // freopen("ur.out", "w", stdout); 
    ios::sync_with_stdio(0); 
    cin >> n >> k; 
    if (n == 1) {
        cout << k << "\n"; 
        return 0; 
    }
    if (k == n) {
        for (int i = 1; i <= n; ++i) cout << '1'; cout << '\n'; 
        return 0; 
    }
    if (k <= 1 || isprime(n)) {
        for (int i = 1; i <= n; ++i) cout << '0'; cout << '\n'; 
        return 0; 
    }
    int t = 2, i = 1; 
    while (n % t != 0) ++t; 
    while (k >= t) {
        k -= t; 
        for (int p = i; p <= n; p += n / t) ans[p] = 1; 
        ++i; 
    }
    for (int i = 1; i <= n; ++i) cout << ans[i]; 
    return 0;
}