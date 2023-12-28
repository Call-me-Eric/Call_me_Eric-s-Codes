#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int P = 998244353; 
const int N = 100000; 
const int D[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 

inline void add(int &x, int k) { x += k; x -= x >= P ? P : 0; }

int n, m, tp; 
int a[1505][1505], T[1505][1505]; 
pair<int, int> idx[400005]; 

void init(void) {
    int x = 750, y = 750, v = 1, T = 0, L = 1; 
    a[x][y] = v; idx[v] = make_pair(x, y); 
    while (v <= N) {
        for (int i = 1; i <= L; ++i) x += D[T][0], y += D[T][1], a[x][y] = ++v, idx[v] = make_pair(x, y); 
        T = T + 1 & 3; 
        for (int i = 1; i <= L; ++i) x += D[T][0], y += D[T][1], a[x][y] = ++v, idx[v] = make_pair(x, y); 
        T = T + 1 & 3; 
        ++L; 
    }
}

namespace Sub5 {
    const int N = 200005; 
    const i64 L = 10000000000ll; 
    int ls[N * 80], rs[N * 80], tag[N * 80], T[N * 80], tot, rt; 
    inline void maketag(int &o, i64 l, i64 r, int k) {
        if (!o) o = ++tot; 
        T[o] = (T[o] + 1ll * k * (r - l + 1) % P) % P; 
        tag[o] = (tag[o] + k) % P; 
    }
    inline void pushdown(int o, i64 l, i64 r) {
        if (!tag[o]) return; i64 mid = l + r >> 1; 
        maketag(ls[o], l, mid, tag[o]); 
        maketag(rs[o], mid + 1, r, tag[o]); 
        tag[o] = 0; 
    }
    void update(int &o, i64 l, i64 r, i64 x, i64 y, i64 k) {
        if (!o) o = ++tot; 
        if (x <= l && r <= y) return maketag(o, l, r, k); 
        pushdown(o, l, r); i64 mid = l + r >> 1; 
        if (x <= mid) update(ls[o], l, mid, x, y, k); 
        if (mid < y) update(rs[o], mid + 1, r, x, y, k); 
        T[o] = (T[ls[o]] + T[rs[o]]) % P; 
    }
    int query(int &o, i64 l, i64 r, i64 x, i64 y) {
        if (!o) o = ++tot; 
        if (x <= l && r <= y) return T[o]; 
        pushdown(o, l, r); i64 mid = l + r >> 1, ans = 0; 
        if (x <= mid) ans = query(ls[o], l, mid, x, y); 
        if (mid < y) ans = (ans + query(rs[o], mid + 1, r, x, y)) % P; 
        return ans; 
    }
    void MAIN(void) {
        for (int lst = 0; m--; ) {
            int op; i64 l, r, v; cin >> op >> l >> r; l ^= lst; r ^= lst; 
            if (op == 1) cin >> v, v ^= lst, update(rt, 1, L, l, r, v); 
            else {
                int ans = query(rt, 1, L, l, r); 
                cout << ans << "\n"; 
                if (tp) lst = ans; 
            }
        }
    }
}

int main(void) {
    freopen("maze.in", "r", stdin); 
    freopen("maze.out", "w", stdout); 

    ios::sync_with_stdio(0); cin.tie(0); 
    init(); 
    cin >> m >> tp; int lst = 0; 
    if (m > 2000) return Sub5::MAIN(), 0; 
    for (int lst = 0; m--; ) {
        int op, l, r, v; cin >> op >> l >> r; l ^= lst; r ^= lst; 
        if (op == 1) {
            cin >> v; v ^= lst; 
            for (int i = l; i <= r; ++i) add(T[idx[i].first][idx[i].second], v); 
        } else if (op == 2) {
            int x = idx[l].first, y = idx[l].second; 
            int u = 750, v = 750; 
            if (x > u) swap(x, u); if (y > v) swap(y, v); 
            for (int i = x; i <= u; ++i) for (int j = y; j <= v; ++j)
                add(T[i][j], r); 
        } else {
            int ans = 0; 
            for (int i = l; i <= r; ++i) add(ans, T[idx[i].first][idx[i].second]); 
            cout << ans << "\n"; 
            if (tp) lst = ans; 
        }
    }
    return 0; 
}