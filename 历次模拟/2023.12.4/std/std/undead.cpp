#include <bits/stdc++.h>
using namespace std; 
const int P = 998244353; 
const int I = (P + 1) / 2; 

inline int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P)
        if (b & 1) r = 1ll * r * a % P; 
    return r; 
}

inline void rev(int &x) { x = P - x; }
inline void add(int &x, int y) { x += y; if (x > P) x -= P; } 
inline void del(int &x, int y) { x -= y; if (x < 0) x += P; }
inline void mul(int &x) { x = x + x; if (x > P) x -= P; }
inline void div(int &x) { x = 1ll * x * I % P; }

int n = 100002, q, B, pos[100005]; 
int fac[100005], ifac[100005], ans[100005];
struct Query {
    int l, r, id; 
    bool operator< (const Query &a) const {
        if (pos[l] != pos[a.l]) return l < a.l; 
        if (pos[l] & 1) return r < a.r; 
        return r > a.r; 
    }
} Q[100005];
inline int C(int n, int m) {
    if (n < m || m < 0) return 0; 
    return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P; 
}

int main(void) {
    // freopen("undead.in", "r", stdin); 
    // freopen("undead.out", "w", stdout); 
	
    ios::sync_with_stdio(0); cin.tie(0); 
    cin >> q; 
    for (int i = 1; i <= q; ++i) cin >> Q[i].l >> Q[i].r, Q[i].id = i; 
    B = n / sqrt(q); fac[0] = ifac[0] = ifac[1] = 1;
    for (int i = 1; i <= n; ++i) pos[i] = (i - 1) / B + 1; 
    for (int i = fac[0] = 1; i <= n; ++i) fac[i] = 1LL * fac[i - 1] * i % P; 
    ifac[n] = poww(fac[n], P - 2); 
    for (int i = n - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 

    sort(Q + 1, Q + q + 1);
    for (int i = 1, L = 0, R = 0, F = 1, G = 1, H = 1; i <= q; ++i) {
        auto addn = [&] (int n, int m) {
            add(F, G); 
            if ((n + m) & 1) del(F, C(n - 1, m)); 
            mul(G); del(G, C(n - 1, m)); 
            if (n % 2 == 0) add(H, C(n, m)); 
        };
        auto deln = [&] (int n, int m) {
            if (n % 2 == 0) del(H, C(n, m)); 
            add(G, C(n - 1, m)); div(G); 
            del(F, G); 
            if ((n + m) & 1) add(F, C(n - 1, m)); 
        };
        auto addm = [&] (int n, int m) {
            add(G, C(n, m)); 
            rev(H); add(H, C(((n + 2) / 2) * 2, m + 1)); div(H); 
            if (m & 1) add(F, C(n + 1, m + 1)), del(F, H); 
            else add(F, H); 
        };
        auto delm = [&] (int n, int m) {
            if (m & 1) del(F, C(n + 1, m + 1)), add(F, H); 
            else del(F, H); 
            mul(H); del(H, C(((n + 2) / 2) * 2, m + 1)); rev(H); 
            del(G, C(n, m)); 
        };
        while (L < Q[i].l) addn(++L, R);
        while (R < Q[i].r) addm(L, ++R);
        while (L > Q[i].l) deln(L--, R);
        while (R > Q[i].r) delm(L, R--);
        // printf("%d %d F = %d, G = %d, H = %d\n",L,R,F,G,H);
        ans[Q[i].id] = F;
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << "\n"; 
    return 0;
}