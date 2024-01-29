#include <bits/stdc++.h>
using namespace std;

int n, k, a[2005][2005]; 
char s[2005]; 

void solve(void) {
    scanf("%d%d", &n, &k); int cnt = n * n; 
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1); 
        for (int j = 1; j <= n; ++j) a[i][j] = s[j] - '0', cnt -= a[i][j]; 
    }   
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    int lmin = 0, rmin = 0, lmax = 1e9, rmax = 1e9, flag = 0;
    for (int i = k; i <= n; i++)
        for (int j = k; j <= n; j++)
            if (a[i][j] + a[i - k][j - k] - a[i - k][j] - a[i][j - k] == 0) {
                flag = 1;
                lmax = min(lmax, i);
                rmax = min(rmax, j);
                lmin = max(lmin, i - k + 1);
                rmin = max(rmin, j - k + 1);
            }
    if (!flag) puts("Alice"); 
    else if (lmin <= lmax && rmin <= rmax) puts("Pluto"); 
    else puts(cnt % 2 == 0 ? "Alice" : "Pluto"); 
}

int main(void) {
    freopen("alien.in", "r", stdin); 
    freopen("alien.out", "w", stdout); 
    
    double st = clock(); 
    int T; scanf("%d", &T); 
    while (T--) solve(); 
    double ed = clock(); 
    cerr << 1000 * (ed - st) / CLOCKS_PER_SEC << "ms\n"; 
    return 0;
}