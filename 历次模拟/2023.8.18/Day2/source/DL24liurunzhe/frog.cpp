# include <cstdio>
# include <algorithm>

using std::max;

const int MAXN = 5e4 + 5;

int n;

int val[MAXN << 1];

struct Node {
	int a, b, c, d, e, f;
} node[MAXN << 1];

int head[MAXN << 1], numE;

struct Edge {
	int nxt, to, val;
	
	Edge(int N = 0, int T = 0, int V = 0) {
		nxt = N, to = T, val = V;
	}
} edge[5010 * 5010];

void addE(int x, int y, int val) {
	edge[++numE] = Edge(head[x], y, val), head[x] = numE;
}

int dis[MAXN << 1];

int ind[MAXN << 1];

int que[MAXN << 1], *tl = que, *hd = que;

void toposort() {
	*tl ++ = 0;
	while (hd != tl) {
		int u = *hd ++;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int k = edge[i].to;
			if (--ind[k] == 0) *tl ++ = k;
			dis[k] = max(dis[k], dis[u] + edge[i].val);
		}
	}
}

int main() {
	
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d %d %d %d %d", &node[i].a, &node[i].b, &node[i].c, &node[i].d, &node[i].e, &val[i]), node[i].f = i;
	}
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 0; j <= n; ++j) if (j != i) {
			if (node[j].a <= node[i].a && node[j].b <= node[i].b && node[j].c <= node[i].c && node[j].d <= node[i].d && node[j].e <= node[i].e && node[j].f <= node[i].f)
				addE(j, i, val[i]), ++ind[i];
		}
	}
	toposort();
	for (int i = 1; i <= n; ++i) printf("%d\n", dis[i]);
	
	return 0;
}
