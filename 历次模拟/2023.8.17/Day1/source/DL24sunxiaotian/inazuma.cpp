#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e6 + 0721;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int head[N], nxt[N << 2], to[N << 2], cnt;
ll val[N << 2];
int st[N << 2];
bool vis[N], calc[N];
int n, m, tot, top;
ll ans = inf;

struct node {
	int u, v;
	ll w;
	friend bool operator<(node x, node y) {
		if (x.u != y.u) return x.u < y.u;
		else if (x.v != y.v) return x.v < y.v;
		else return x.w < y.w;
	}
} edge[N << 2];

inline void add_edge(int x, int y, ll z) {
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
	val[cnt] = z;
}

ll cal(int i) {
	ll minn = val[i], minnn = inf, minnnn = inf;
	int prs = top;
	while (prs) {
		if (to[prs] == to[i]) break;
		int v = val[prs];
		if (v < minn) {
			minnnn = minnn;
			minnn = minn;
			minn = v;
		} else if (v < minnn) {
			minnnn = minnn;
			minnn = v;
		} else if (v < minnnn)
			minnnn = v;
		calc[prs] = 1;
		--prs;
	}
	return min(minn + minnn, minnnn);
}

void dfs(int x, int fa) {
	vis[x] = 1;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (y == fa) continue;
		if (vis[y]) {
			ans = min(ans, cal(i));
			continue;
		}
		
		st[++top] = i;
		dfs(y, x);
		if (!calc[top]) ans = min(ans, val[st[top]]);
		--top;
	}
}

int main() {
	freopen("inazuma.in", "r", stdin);
	freopen("inazuma.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		ll z;
		scanf("%d%d%lld", &x, &y, &z);
		edge[++tot] = (node){ x, y, z };
		edge[++tot] = (node){ y, x, z };
	}	
	
	sort(edge + 1, edge + 1 + tot);
	
	for (int i = 1; i <= tot; ) {
		int prs = i + 1;
		while (edge[prs].u == edge[i].u && edge[prs].v == edge[i].v) {
			edge[i].w += edge[prs].w;
			++prs;
//			cout << prs << "\n";
		}
		add_edge(edge[i].u, edge[i].v, edge[i].w);
		i = prs;
	}
	
	dfs(1, 0);
	printf("%lld", ans);
	
	return 0;
}
/*
5 6
1 2 3
1 2 2
2 3 3
2 4 5
2 5 5
3 4 2
*/
