#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int P = 998244353; 

int n, len[1000005]; 
char tmp[1000005]; 
vector<char> s[1000005]; 
vector<int> w[1000005]; 

int main(void) {
    freopen("unpredictable.in", "r", stdin); 
    freopen("unpredictable.out", "w", stdout); 

    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> n; 
    for (int i = 1; i <= n; ++i) {
        cin >> tmp; int l = strlen(tmp); s[i].resize(l + 1); 
        for (int t = 0; t < l; ++t) s[i][t + 1] = tmp[t]; 
        w[i].resize(l + 1); 
        for (int t = 1; t <= l; ++t) cin >> w[i][t]; 
        len[i] = l; 
    }
    i64 ans = 0; 
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j) {
        int K = 0; 
        for (int k = 1; k <= len[i] && k <= len[j]; ++k) {
            bool f = 1; 
            for (int l = 1; l <= k; ++l)
                if (s[i][l] != s[j][l + len[j] - k]) { f = 0; break; }
            if (f) K = k; 
        }
        ans = (ans + w[i][K] + w[j][K]) % P; 
    }
    for (int i = 2; i < n; ++i) ans = ans * i % P;  
    cout << ans << "\n"; 
    return 0; 
}