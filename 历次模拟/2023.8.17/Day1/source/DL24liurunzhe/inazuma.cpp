# include <cstdio>
# include <algorithm>

using std::min;

const int MAXN = 2e6 + 5;

int n, m;

int head[MAXN << 1], numE = 1;

int numD;

std::vector<int> vec[MAXN << 1];

struct Edge {
	int nxt, to, val;
	
	Edge(int N = 0, int T = 0, int V = 0) {
		nxt = N, to = T, val = V;
	}
} edge[MAXN << 1];

void addE2(int x, int y, int val) {
	edge[++numE] = Edge(head[x], y, val), head[x] = numE;
	edge[++numE] = Edge(head[y], x, val), head[y] = numE;
}

int dfn[MAXN << 1], low[MAXN << 1], tot;

int stk[MAXN << 1], *tp = stk;

bool vis[MAXN << 1];

void tarjan(int u, int lst) {
	dfn[u] = low[u] = ++tot, *tp ++ = u;
	int cnt = 0;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if ((k ^ 1) == lst) continue;
		if (!dfn[k]) 
			tarjan(k, i), low[u] = min(low[u], low[k]);
		else {
			low[u] = min(low[u], dfn[k]);
			if (low[k] >= dfn[u]) {
				++numD;
				while (*(tp - 1) != u) {
					vec[numD].push_back(*--tp);
				}
				vec[numD].push_back(u);
			}
		}
	}
}

void dfs(int u, int t, int lst, int& mn1, int& mn2, int& mn3) {
	if (u == t && lst) return;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if ((i ^ 1) == lst) continue;
		if (!vis[k]) continue;
		if (mn1 >= edge[i].val) mn3 = mn2, mn2 = mn1, mn1 = edge[i].val;
		else if (mn2 >= edge[i].val) mn3 = mn2, mn2 = edge[i].val;
		else if (mn3 >= edge[i].val) mn3 = edge[i].val;
		dfs(k, t, i, mn1, mn2, mn3);
	}
}

int main() {
	
//	freopen("inazuma.in", "r", stdin);
//	freopen("inazuma.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y, val;
		scanf("%d %d %d", &x, &y, &val);
		addE2(x, y, val);
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) tarjan(i, -1);
	}
	int ans = 1e9;
	for (int i = 1; i <= numD; ++i) {
		if (vec[i].size() == 2) {
			printf("%d %d\n", vec[i][0], vec[i][1]);
			int x = vec[i][0];
			for (int j = head[x]; j; j = edge[j].nxt) {
				int k = edge[j].to;
				if (k == vec[i][1]) ans = min(ans, edge[j].val);
			}
		} else {
			printf("%d\n", vec[i].size());
			for (int k : vec[i]) vis[k] = true;
			int mn1 = 1e9, mn2 = 1e9, mn3 = 1e9;
			dfs(vec[i][0], vec[i][0], 0, mn1, mn2, mn3);
			ans = min(mn1 + mn2, mn3);
			for (int k : vec[i]) vis[k] = false;
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
