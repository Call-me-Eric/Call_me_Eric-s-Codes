#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int B = 500; 

inline int read(void) {
    int x = 0, c = getchar(); 
    while (!isdigit(c)) c = getchar(); 
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
    return x; 
}

int n, VX[150005], b[150005]; 
struct Node {
    int a, b; 
    bool operator< (const Node &x) const { return a < x.a; }
} a[150005]; 

i64 C[150005]; 
inline void add(int x, int k) { for (; x <= n; x += x & -x) C[x] += k; }
inline i64 sum(int x) { i64 r = 0; for (; x; x -= x & -x) r += C[x]; return r; }

int main(void) {
    freopen("value.in", "r", stdin); 
    freopen("value.out", "w", stdout); 
    
    n = read(); 
    for (int i = 1; i <= n; ++i) a[i].a = read(), b[i] = a[i].b = read(); 
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1); 
    for (int i = 1; i <= n; ++i) VX[i] = a[i].a; 
    int nx = unique(VX + 1, VX + n + 1) - VX - 1; 
    int ny = unique(b + 1, b + n + 1) - b - 1; 
    for (int i = 1; i <= n; ++i) a[i].b = lower_bound(b + 1, b + ny + 1, a[i].b) - b; 
    
    i64 ans = 0, w = 0; 
    for (int ix = 1, p = 0; ix <= nx; ++ix) {
        int x = VX[ix], L, R; 
        while (p + 1 <= n && a[p + 1].a < x) {
            ++p; add(1, 1); add(a[p].b + 1, -1); // 为 [1, a[p].b] 加上等差数

            L = 1, R = min(B, n); 
            for (int i = L; i <= R; ++i) w = max(w, b[i] * sum(i)); 
            L = max(a[p].b / 2 - B, 1), R = min(n, a[p].b / 2 + B); 
            for (int i = L; i <= R; ++i) w = max(w, b[i] * sum(i)); 
            L = max(1, a[p].b - B), R = a[p].b; 
            for (int i = L; i <= R; ++i) w = max(w, b[i] * sum(i)); 
        }

        /*
        i64 w = 0; int cnt = 0; 
        
        for (int i = 1; i <= ny; ++i)
            if (W[i] > W[i - 1] && W[i] > W[i + 1]) ++cnt; 
        if (cnt > 1) cerr << cnt << "\n", assert(0); 
        */
        // for (int i = 1; i <= ny; ++i) cout << W[i] << " \n"[i == n]; 

        ans = max(ans, 1ll * x * (n - p) + w); 
    }
    printf("%lld\n", ans); 
    return 0; 
}