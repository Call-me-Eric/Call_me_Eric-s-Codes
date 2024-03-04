#include <bits/stdc++.h>
using namespace std; 

inline int read(void) {
	int x = 0, c = getchar(); 
	while (!isdigit(c)) c = getchar(); 
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); 
	return x; 
}

int n, m; 
struct edge {
	int u, v, w;
	edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
	bool operator< (const edge &a) const {
		return w < a.w; 
	}
} e[2000005];
int fa[1000005], siz[1000005]; 
inline int find(int x) {
	while (x != fa[x]) x = fa[x]; 
	return x; 
}
struct Node {
	int x, y, s; 
} tmp; 
struct staff {
	int u, v, w; Node t; 
	staff(int u, int v, int w, Node t) : u(u), v(v), w(w), t(t) {}
	bool operator< (const staff &a) const { return w < a.w; }
};
multiset<staff> S;
inline void merge(int x, int y) {
	int u = find(x), v = find(y); 
	if (u == v) return; 
	if (siz[u] > siz[v]) swap(u, v); 
	fa[u] = v; siz[v] += siz[u]; 
	tmp = {u, v, siz[u]}; 
}

int nxt[2000005], pre[2000005]; 
int main(void) {
	freopen("inazuma.in", "r", stdin); 
	freopen("inazuma.out", "w", stdout); 
	n = read(), m = read(); 
	for (int i = 1; i <= m; ++i) e[i].u = read(), e[i].v = read(), e[i].w = read(); 
	for (int i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1; 
	sort(e + 1, e + m + 1); 
	for (int i = m + 1; i >= 0; --i) nxt[i] = i - 1, pre[i] = i + 1; 
	
	int ans = 0, res = 0;
//	int rnd = 1;  
	while (1) {
//		printf("Round %d:\n", rnd++); 
//		for (auto it : S) printf("%d %d %d\n", it.u, it.v, it.w); 
		while (S.size()) {
			auto it = S.begin(); 
//			printf("pending %d %d %d %d\n", it->u, it->v, it->w, ans); 
			if (it->w <= ans) {
				Node u = it->t; 
				fa[u.x] = u.x; siz[u.y] -= u.s; 
//				printf("del %d %d %d\n", it->u, it->v, it->w); 
				S.erase(it); 
				--res; 
			} else break; 
		}
		for (int i = nxt[m + 1]; i >= 1; i = nxt[i])	
			if (find(e[i].u) != find(e[i].v) && e[i].w) {
				merge(e[i].u, e[i].v); ++res; 
				if (res == n - 1) break; 
//				printf("add %d %d %d\n", e[i].u, e[i].v, e[i].w); 
				S.emplace(e[i].u, e[i].v, e[i].w + ans, tmp); 
				e[i].w = 0;  
				nxt[pre[i]] = nxt[i]; pre[nxt[i]] = pre[i]; 
			}
		if (res != n - 1) break; 
		ans = S.begin()->w; 
//		printf("ans = %d\n", ans); 
	}
	printf("%d\n", ans); 
	return 0; 
}
