#include"bits/stdc++.h"
using namespace std;
#define int long long
int read() {
	int x = 0, fff = 1;
	char c;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			fff = -1;
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * fff;
}
const double eps = 1e-5;
const int N = 2e3 + 6;
const int M = 5e6 + 6;
const int V = 1e7;
const int mod = 998244353;
const int bse = 998244353;
const int inf = 1e15;
const double pi = acos(-1);
int n, m;
struct node {
	int x1, y1, x2, y2, id;
	bool operator<(node t)const {
		return abs(x2 - x1) + abs(y2 - y1) < abs(t.x2 - t.x1) + abs(t.y2 - t.y1);
	}
} p[N];
vector<pair<int, int>>pth[N];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
int vis[N][N];
void dfs(int x, int y, int id) {
	if(id == m + 1) {
		for(int i = 1; i <= m; i++) {
			printf("%u\n", pth[i].size() + 1);
			printf("%lld %lld\n", p[p[i].id].x1, p[p[i].id].y1);
			for(auto v : pth[i]) printf("%lld %lld\n", v.first, v.second);
		}
		exit(0);
	}
	if(x == p[id].x2 && y == p[id].y2) {
		dfs(p[id + 1].x1, p[id + 1].y1, id + 1);
		return ;
	}
	for(int i = 1; i <= 4; i++) {
		int tx = x + dx[i], ty = y + dy[i];
		if(tx < 1 || tx > n || ty < 1 || ty > n || vis[tx][ty]) continue;
		vis[tx][ty] = 1;
		pth[p[id].id].push_back({tx, ty});
		dfs(tx, ty, id);
		pth[p[id].id].pop_back();
		vis[tx][ty] = 0;
	}
}
signed main() {
	freopen("flowfree.in", "r", stdin);
	freopen("flowfree.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= m; i++) p[i] = {read(), read(), read(), read()}, p[i].id = i, vis[p[i].x1][p[i].y1] = 1;
	sort(p + 1, p + 1 + m);
	dfs(0, 0, 0);
	return 0;
}
/*
9 9
6 1 7 3
7 2 6 9
8 2 6 8
6 2 4 8
5 2 5 4
2 2 5 5
2 3 3 4
2 4 3 8
3 5 3 7
*/
