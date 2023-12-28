#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i+=1)
#define per(i, x, y) for (int i = (x); i >= (y); i-=1)
#define epr(i, x) for (int i = head[x]; i; i = nxt[i])
#define fi first
#define se second
#define ep emplace
#define eb emplace_back

using namespace std;

typedef long long LL;
typedef pair <int, int> PII;

template <typename T>
inline T gi()
{
    T x = 0; bool f = 0; char c = getchar();
    while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return f ? -x : x;
}

const int N = 200003, M = N << 1;

int n, m;
int tot, head[N], ver[M], nxt[M];
int cnt, deg[N];
bool vis[N];
int fa[N], sz[N], sn[N];

inline void add(int u, int v) {ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;}

int getf(int u) {return fa[u] == u ? u : fa[u] = getf(fa[u]);}

inline void Union(int u, int v)
{
	u = getf(u), v = getf(v);
	if (u ^ v) fa[u] = v, sz[v] += sz[u];
	++sz[v];
}

void dfs(int u, int f)
{
	vis[u] = 1, ++cnt;
	epr(i, u) if (ver[i] ^ f) dfs(ver[i], u);
}

int main()
{
	freopen("li.in", "r", stdin); freopen("li.out", "w", stdout);
	n = gi <int> (), m = gi <int> ();
	iota(fa + 1, fa + 1 + n, 1);
	rep(i, 1, m)
	{
		int u = gi <int> (), v = gi <int> ();
		add(u, v), add(v, u), ++deg[u], ++deg[v], Union(u, v);
	}
	rep(i, 1, n) if (deg[i] > 3) return puts("-1"), !!0;
	int sum = 0; LL res = 0;
	rep(i, 1, n) if (deg[i] == 3)
	{
		epr(j, i) if (deg[ver[j]] > 1) return puts("-1"), !!0; else vis[ver[j]] = 1;
		sum += 3;
	}
	rep(i, 1, n) ++sn[getf(i)];
	rep(i, 1, n) if (getf(i) == i && sz[i] == sn[i]) sum += sz[i];
	rep(i, 1, n) if (deg[i] <= 1 && !vis[i]) dfs(i, 0), res += 1ll * cnt * (cnt + 1) / 2, cnt = 0;
	if (sum) printf("1 %d\n", sum);
	else printf("0 %lld\n", res);
    return !!0;
}
