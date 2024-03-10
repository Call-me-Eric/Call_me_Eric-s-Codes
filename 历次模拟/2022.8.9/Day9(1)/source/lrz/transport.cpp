#include <cstdio>

const int MAXN = 1e4;

int n;
int a[2 * MAXN + 10];

int head[2 * MAXN + 10], numEdge;
struct Edge {
	int nxt, to, val;
}edge[2 * MAXN + 10];

void addEdge(int x, int y, int val) {

	++numEdge;
	edge[numEdge].nxt = head[x];
	edge[numEdge].to = y;
	edge[numEdge].val = val;
	head[x] = numEdge;

	return;
}

int ans, cnt;

void dfs(int u, int father) {
	
	++ans;
	cnt += a[u];
	for(int i = head[u]; i; i = edge[i].nxt) {
		int k = edge[i].to;
		if(k != father && edge[i].val <= cnt) {
			cnt -= edge[i].val;
			dfs(k, u);
			cnt += edge[i].val;
		}
	}
	cnt -= a[u];

	return;
}

int main() {

	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i < n; ++i) {
		int x, y, val;
		scanf("%d %d %d", &x, &y, &val);
		addEdge(x, y, val);
		addEdge(y, x, val);
	}
	
	int sum = 0;
	for(int i = 1; i <= n; ++i) {
		ans = 0; cnt = 0;
		dfs(i, -1);
		sum += ans - 1;
	}
	
	printf("%d\n", sum);

	return 0;
}
