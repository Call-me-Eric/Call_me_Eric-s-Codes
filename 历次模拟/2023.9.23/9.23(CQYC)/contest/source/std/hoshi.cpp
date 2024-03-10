#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 0; char ch = getchar();
	while(ch < '0' or ch > '9') f |= (ch == '-'), ch = getchar();
	while(ch >= '0' and ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
int __stk[128], __top;
inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
	do { __stk[++__top] = x % 10, x /= 10; } while(x);
	while (__top) putchar(__stk[__top--] + '0');
}
bool stmer;
const int N = 1e3 + 10, K = 1e4 + 10, M = 3e5 + 10;
struct node {
    int u, v, w, id;
    bool operator < (const node &p) const {
        return w == p.w ? id < p.id : w > p.w;
    }
} e[M];
int n, m, k;
int fa[K][N], ans[M];
int find(int x, int id) { return fa[id][x] == x ? x : fa[id][x] = find(fa[id][x], id); }
bool edmer;
signed main() {
	freopen("hoshi.in", "r", stdin);
	freopen("hoshi.out", "w", stdout);
	cerr << "[Memory] " << (&stmer - &edmer) / 1024 / 1024 << " MB\n";
	n = read(), m = read(), k = read();
    for(int i = 1; i <= m; i++) e[i] = {read(), read(), read(), i};
    sort(e + 1, e + m + 1);

    for(int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        int l = 1, r = k, id = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(!fa[mid][u]) fa[mid][u] = u;
            if(!fa[mid][v]) fa[mid][v] = v;
            int x = find(u, mid), y = find(v, mid);
            x == y ? l = mid + 1 : (id = mid, r = mid - 1);
        }
        if(id) fa[id][find(u, id)] = find(v, id);
        
        ans[e[i].id] = id;
    }
    for(int i = 1; i <= m; i++) write(ans[i]), putchar('\n');
    cerr << "[Runtime] " << (double) clock() / CLOCKS_PER_SEC << " seconds";
	return 0;
} 